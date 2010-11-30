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


#ifndef __INET_UDPECHOAPP_H
#define __INET_UDPECHOAPP_H

#include <vector>
#include <omnetpp.h>

#include "MCoAUDPBase.h"


/**
 * UDP application. See NED for more info.
 */
class INET_API MCoAUDPApp : public MCoAUDPBase
{
  protected:
	bool isDestiny;
	bool getRequest;
	long seqTx;
	long seqRx;
	long nRequests;
	simtime_t stopTime;

	int localPort, destPort;
	std::vector<IPvXAddress> destAddresses;

	int numSent;
	int numReceived;

	struct statPacketVOIP{
		long seq;
		bool treated;
		long delay;
	};
	typedef std::map<long , statPacketVOIP> SPkt;
	SPkt StatsPkt;

	//Statistics
	cOutVector pktSent;
	cOutVector pktRcv;
	cOutVector pktRcvDelay;
    virtual cPacket *createPacket();
    virtual void processPacket(cPacket *msg);
    void handleMessage(cMessage *msg);
    void startApp();
    virtual void sendPacket();
    virtual IPvXAddress chooseDestAddr();



  protected:
    virtual void initialize(int stage);
    virtual void finish();
};

#endif


