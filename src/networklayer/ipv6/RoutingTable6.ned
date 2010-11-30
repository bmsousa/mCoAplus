//
// Copyright (C) 2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program; if not, see <http://www.gnu.org/licenses/>.
//


package inet.networklayer.ipv6;

//
// \IPv6 Routing Table and Neighbour Discovery data structures.
//
// @see IPv6, IPv6NeighbourDiscovery, ICMPv6
//
simple RoutingTable6
{
    parameters:
        xml routingTableFile;
        bool isRouter;
        
        int max_ha_binding_lifetime = default(60*60);
        int max_rr_binding_lifetime = default(60*60);
        
        int ipv6_reachable_time = default(30); 
        int ipv6_retrans_timer = default(1); 
        int ipv6_delay_first_probe = default(5); 
        
        //For routers
        int ipv6_adv_reachable_time = default(3600); //3600s
        int ipv6_adv_retrans_timer  = default(1); // 1s
        
        @display("i=block/table");
}
