/**
 * Copyright (C) 2010
 * Bruno Sousa
 * Laboratory and Communications and Telematics (LCT), University of Coimbra

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "MCoANetConf6.h"
#include "IInterfaceTable.h"
#include "IPAddressResolver.h"
#ifndef WITHOUT_IPv6
#include "IPv6InterfaceData.h"
#include "RoutingTable6.h"
#endif

Define_Module(MCoANetConf6);

void MCoANetConf6::initialize(int stage)
{
#ifndef WITHOUT_IPv6
    // FIXME refactor: make routers[] array? (std::vector<cTopology::Node*>)
    // FIXME: spare common beginning for all stages?

    cTopology topo("topo");

    // extract topology
    topo.extractByProperty("node");
    EV << "cTopology found " << topo.getNumNodes() << " nodes\n";

    // Configuration of prefixes performed in routing6 file.
    if (stage==2)
    {
       //configureAdvPrefixes(topo);
    }
    else if (stage==3)
    {
        addOwnAdvPrefixRoutes(topo);
        addStaticRoutes(topo);
    }
#else
    error("MCoANetConf6 not supported: WITHOUT_IPv6 option was defined during compilation");
#endif
}

void MCoANetConf6::handleMessage(cMessage *)
{
    error("this module doesn't handle messages, it runs only in initialize()");
}

bool MCoANetConf6::isIPNode(cTopology::Node *node)
{
    return IPAddressResolver().findInterfaceTableOf(node->getModule()) != NULL;
}

#ifndef WITHOUT_IPv6
void MCoANetConf6::addStaticRoutes(cTopology& topo)
{
    int numIPNodes = 0;

    EV << "MCoANetConf6 Adding routes for " << topo.getNumNodes() << endl;

    // fill in routing tables
    for (int i = 0; i < topo.getNumNodes(); i++)
    {
        cTopology::Node *destNode = topo.getNode(i);

        // skip bus types
        if (!isIPNode(destNode))
            continue;

        numIPNodes++; // FIXME split into num hosts, num routers
        RoutingTable6 *destRt = IPAddressResolver().routingTable6Of(destNode->getModule());
        IInterfaceTable *destIft = IPAddressResolver().interfaceTableOf(destNode->getModule());

        // don't add routes towards hosts
        if (!destRt->par("isRouter").boolValue())
            continue;

        // get a list of globally routable prefixes from the dest node
        std::vector<const IPv6InterfaceData::AdvPrefix*> destPrefixes;
        for (int x = 0; x < destIft->getNumInterfaces(); x++)
        {
            InterfaceEntry *destIf = destIft->getInterface(x);
            EV << "MCoANetConf6 getting address for interface " << destIf->getInterfaceId() << endl;

            if (destIf->isLoopback())
                continue;

            for (int y = 0; y < destIf->ipv6Data()->getNumAdvPrefixes(); y++)
                if (destIf->ipv6Data()->getAdvPrefix(y).prefix.isGlobal())
                    destPrefixes.push_back(&destIf->ipv6Data()->getAdvPrefix(y));
        }

        std::string destModName = destNode->getModule()->getFullName();

        // calculate shortest paths from everywhere towards destNode
        topo.calculateUnweightedSingleShortestPathsTo(destNode);

        // add route (with dest=destPrefixes) to every router routing table in the network
        for (int j = 0; j < topo.getNumNodes(); j++)
        {
            if (i == j)
                continue;
            if (!isIPNode(topo.getNode(j)))
                continue;

            cTopology::Node *atNode = topo.getNode(j);
            if (atNode->getNumPaths() == 0)
                continue;       // not connected

            RoutingTable6 *rt = IPAddressResolver().routingTable6Of(atNode->getModule());
            IInterfaceTable *ift = IPAddressResolver().interfaceTableOf(atNode->getModule());

            // skip hosts' routing tables
            if (!rt->par("isRouter").boolValue())
                continue;

            // determine the local interface id
            cGate *localGate = atNode->getPath(0)->getLocalGate();
            InterfaceEntry *localIf = ift->getInterfaceByNodeOutputGateId(localGate->getId());

            // determine next hop link address. That's a bit tricky because
            // the directly adjacent cTopo node might be a non-IP getNode(ethernet switch etc)
            // so we have to "seek through" them.
            cTopology::Node *prevNode = atNode;
            // if there's no ethernet switch between atNode and it's next hop
            // neighbour, we don't go into the following while() loop
            while (!isIPNode(prevNode->getPath(0)->getRemoteNode()))
                prevNode = prevNode->getPath(0)->getRemoteNode();

            // ok, the next hop is now just one step away from prevNode
            cGate *remoteGate = prevNode->getPath(0)->getRemoteGate();
            cModule *nextHop = remoteGate->getOwnerModule();
            IInterfaceTable *nextHopIft = IPAddressResolver().interfaceTableOf(nextHop);
            InterfaceEntry *nextHopOnlinkIf = nextHopIft->getInterfaceByNodeInputGateId(remoteGate->getId());

            // find link-local address for next hop
            IPv6Address nextHopLinkLocalAddr = nextHopOnlinkIf->ipv6Data()->getLinkLocalAddress();

            // traverse through address of each node
            // add to route table
            for (unsigned int k = 0; k < destPrefixes.size(); k++)
            {
                rt->addStaticRoute(destPrefixes[k]->prefix, destPrefixes[k]->prefixLength,
                                   localIf->getInterfaceId(), nextHopLinkLocalAddr);
            }
        }
    }

    // update display string
   // setDisplayString(numIPNodes, topo.getNumNodes()-numIPNodes);
}

void MCoANetConf6::addOwnAdvPrefixRoutes(cTopology& topo)
{
    // add globally routable prefixes to routing table
    for (int i = 0; i < topo.getNumNodes(); i++)
    {
        cTopology::Node *node = topo.getNode(i);

        // skip bus types
        if (!isIPNode(node))
            continue;

        RoutingTable6 *rt = IPAddressResolver().routingTable6Of(node->getModule());
        IInterfaceTable *ift = IPAddressResolver().interfaceTableOf(node->getModule());

        // skip hosts
        if (!rt->par("isRouter").boolValue())
            continue;

        // add globally routable prefixes to routing table
        for (int x = 0; x < ift->getNumInterfaces(); x++)
        {
            InterfaceEntry *ie = ift->getInterface(x);

            if (ie->isLoopback())
                continue;

            for (int y = 0; y < ie->ipv6Data()->getNumAdvPrefixes(); y++)
                if (ie->ipv6Data()->getAdvPrefix(y).prefix.isGlobal())
                    rt->addOrUpdateOwnAdvPrefix(ie->ipv6Data()->getAdvPrefix(y).prefix,
                                                ie->ipv6Data()->getAdvPrefix(y).prefixLength,
                                                ie->getInterfaceId(), 0);
        }
    }
}


#endif
