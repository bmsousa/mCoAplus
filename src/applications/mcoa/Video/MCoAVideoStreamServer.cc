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

#include "MCoAVideoStreamServer.h"
#include "UDPControlInfo_m.h"

Define_Module(MCoAVideoStreamServer);

inline std::ostream& operator<<(std::ostream& out, const MCoAVideoStreamServer::VideoStreamData& d) {
    out << "client=" << d.clientAddr << ":" << d.clientPort
        << "  size=" << d.videoSize << "  pksent=" << d.numPkSent << "  bytesleft=" << d.bytesLeft;
    return out;
}
MCoAVideoStreamServer::MCoAVideoStreamServer() {
	// TODO Auto-generated constructor stub

}

MCoAVideoStreamServer::~MCoAVideoStreamServer() {
	// TODO Auto-generated destructor stub
	for (unsigned int i=0; i<streamVector.size(); i++)
	        delete streamVector[i];
}

void MCoAVideoStreamServer::initialize()
{
	MCoAUDPBase::startMCoAUDPBase();

    waitInterval = &par("waitInterval");
    packetLen = &par("packetLen");
    videoSize = &par("videoSize");
    localPort = par("localPort");
    int destPort = par("destPort");


    WATCH_PTRVECTOR(streamVector);

    bindToPort(localPort);

    PktSent.setName("MCOA VIDEO Packet Sent");
}

void MCoAVideoStreamServer::finish()
{
    //recordScalar("streams served", numStreams);
    //recordScalar("packets sent", numPkSent);
}

void MCoAVideoStreamServer::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
    	if (msg->getKind() == MK_REMOVE_ADDRESS_PAIR ){
			MCoAUDPBase::treatMessage(msg);

			return; // and that's it!
		}

        // timer for a particular video stream expired, send packet
        sendStreamData(msg);
    }
    else
    {
        // start streaming
        processStreamRequest(msg);
    }
}

void MCoAVideoStreamServer::processStreamRequest(cMessage *msg)
{
    // register video stream...
    UDPControlInfo *ctrl = check_and_cast<UDPControlInfo *>(msg->getControlInfo());

    VideoStreamData *d = new VideoStreamData;
    d->clientAddr = ctrl->getSrcAddr();
    d->clientPort = ctrl->getSrcPort();
    d->videoSize = (*videoSize);
    d->bytesLeft = d->videoSize;
    d->numPkSent = 0;
    d->seqTx = 0; //First Request
    streamVector.push_back(d);

    cMessage *timer = new cMessage("VideoStreamTmr");
    timer->setContextPointer(d);

    // ... then transmit first packet right away
    sendStreamData(timer);

    //numStreams++;
}


void MCoAVideoStreamServer::sendStreamData(cMessage *timer)
{
    VideoStreamData *d = (VideoStreamData *) timer->getContextPointer();

    // generate and send a packet
    //cPacket *pkt = new cPacket("VideoStrmPk");
    MCoAVideoStreaming *pkt_video = new MCoAVideoStreaming();
    long pktLen = packetLen->longValue();
    if (pktLen > d->bytesLeft)
        pktLen = d->bytesLeft;
    //pkt->setByteLength(pktLen);
    d->seqTx = d->seqTx +1;

	pkt_video->setByteLength(pktLen);
	pkt_video->setCurSeq(d->seqTx);
	pkt_video->setCurTime(simTime().dbl());

    //sendToUDP(pkt, serverPort, d->clientAddr, d->clientPort);
	sendToUDPMCOA(pkt_video, localPort, d->clientAddr, d->clientPort, true);

    d->bytesLeft -= pktLen;
    d->numPkSent++;

    //Statistics
    PktSent.record(pkt_video->getCurSeq());

    // reschedule timer if there's bytes left to send
    if (d->bytesLeft!=0)
    {
        simtime_t interval = (*waitInterval);
        scheduleAt(simTime()+interval, timer);
    }
    else
    {
        delete timer;
        // TBD find VideoStreamData in streamVector and delete it
    }
}

