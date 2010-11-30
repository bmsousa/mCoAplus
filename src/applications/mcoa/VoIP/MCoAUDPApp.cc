//
// Copyright (C) 2010 Bruno Sousa
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//


#include <omnetpp.h>
#include "MCoAUDPApp.h"
#include "MCOAVoIPMsg_m.h"
#include "UDPControlInfo_m.h"
#include "IPAddressResolver.h"


Define_Module(MCoAUDPApp);

void MCoAUDPApp::initialize(int stage)
{
    // because of IPAddressResolver, we need to wait until interfaces are registered,
    // address auto-assignment takes place etc.
    //if (stage==2){
	MCoAUDPBase::startMCoAUDPBase();

	seqTx=seqRx=0;

	pktSent.setName("MCOA VOIP packet sent");
	pktRcv.setName("MCOA VOIP packet rcv");
	pktRcvDelay.setName("MCOA VOIP packet rcv delay");

	isDestiny = par("isDestiny");
	getRequest = par("getRequest");
	nRequests = par("nRequests");

	startApp();
    //}
}

void MCoAUDPApp::finish()
{
}

IPvXAddress MCoAUDPApp::chooseDestAddr()
{
    int k = intrand(destAddresses.size());
    return destAddresses[k];
}

void MCoAUDPApp::startApp(){

	localPort = par("localPort");
	destPort  = par("destPort");

	const char *destAddrs = par("destAddresses");
	cStringTokenizer tokenizer(destAddrs);
	const char *token;
	while ((token = tokenizer.nextToken())!=NULL)
		destAddresses.push_back(IPAddressResolver().resolve(token));

	if (destAddresses.empty())
		return;

	bindToPort(localPort);

	simtime_t startTime = par("startTime");
	stopTime = par("stopTime");

	if (!isDestiny){
		cMessage *timer = new cMessage("sendTimer");
		scheduleAt(startTime + (double)par("messageFreq"), timer);
	}

}

void MCoAUDPApp::handleMessage(cMessage *msg){





	if (msg->isSelfMessage())
	{

		if (msg->getKind() == MK_REMOVE_ADDRESS_PAIR ){
			MCoAUDPBase::treatMessage(msg);

			return; // and that's it!
		}


		// send, then reschedule next sending
		if (!isDestiny){

			if (nRequests> 0){
				if (seqTx < nRequests){
					sendPacket();
					scheduleAt(simTime()+(double)par("messageFreq"), msg);
				}else {
					EV << "VoIP requests have already been sent" << seqTx << endl;
					delete msg;
				}
			}

			if (stopTime>0){
				if (simTime() < stopTime){
					sendPacket();
					scheduleAt(simTime()+(double)par("messageFreq"), msg);
				}else {
					EV << "VoIP app stopping at" << stopTime << endl;
					delete msg;
				}
			}
		}
	}else{
        // process incoming packet
        processPacket(PK(msg));
    }

}

cPacket *MCoAUDPApp::createPacket()
{
    char msgName[32];
    //sprintf(msgName,"MCoAUDPEcho-%d", counter++);
    sprintf(msgName,"MCoAUDPEcho");

    seqTx++;
    pktSent.record(seqTx);
    MCoAVoIPMsg *message = new MCoAVoIPMsg(msgName);
    message->setByteLength(par("messageLength").longValue());
    message->setCurSeq(seqTx);
    message->setCurTime(simTime().dbl());
    message->setIsRequest(getRequest);

    statPacketVOIP aux;
    aux.seq = seqTx;
    aux.delay = 0;
    aux.treated = false;

    StatsPkt.insert(std::make_pair(seqTx,aux ));
    return message;
}


void MCoAUDPApp::sendPacket()
{
    cPacket *payload = createPacket();
    IPvXAddress destAddr = chooseDestAddr();

    sendToUDPMCOA(payload,
    		localPort,
    		destAddr,
    		destPort,
    		true); //append control info


    numSent++;
}


void MCoAUDPApp::processPacket(cPacket *msg)
{
    if (msg->getKind() == UDP_I_ERROR)
    {
        delete msg;
        return;
    }

    MCoAVoIPMsg *packet = check_and_cast<MCoAVoIPMsg *>(msg);

    if (packet->getIsRequest())
    {
        UDPControlInfo *controlInfo = check_and_cast<UDPControlInfo *>(packet->getControlInfo());

        // swap src and dest
        IPvXAddress srcAddr = controlInfo->getSrcAddr();
        int srcPort = controlInfo->getSrcPort();
        controlInfo->setSrcAddr(controlInfo->getDestAddr());
        controlInfo->setSrcPort(controlInfo->getDestPort());
        controlInfo->setDestAddr(srcAddr);
        controlInfo->setDestPort(srcPort);

        packet->setIsRequest(false);
        packet->setCurTime(simTime().dbl() - packet->getCurTime());


        sendToUDPMCOA(packet,
        		controlInfo->getSrcPort(),
        		controlInfo->getDestAddr(),
        		controlInfo->getDestPort(),
        		false); //do not append control info

        //send(packet, "udpOut");
    }
    else
    {
    	seqRx++;
    	long auxseqRx = packet->getCurSeq();

    	SPkt::iterator pos = StatsPkt.find(auxseqRx);
    	if (pos != StatsPkt.end()) {
    		bool pktTreated;
    		pktTreated = (pos->second).treated;

    		if (!pktTreated){
    			(pos->second).treated = true;
    			(pos->second).delay = packet->getCurTime();
    			pktRcv.record(auxseqRx);
    			pktRcvDelay.record(packet->getCurTime());
    		}
    	}

        simtime_t rtt = simTime() - packet->getCreationTime();
        //EV << "RTT: " << rtt << "\n";
        delete msg;
    }
    numReceived++;
}



