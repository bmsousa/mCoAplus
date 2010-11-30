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


#ifndef __INET_UDPAPPBASE_H
#define __INET_UDPAPPBASE_H

#include <omnetpp.h>
#include "IPvXAddress.h"
#include "MCoADefs.h" //MCoA
#include "NotificationBoard.h"
#include "IPv6TunAdr.h" //MCoA
#include "IPv6PrefAdr.h"

#define MK_REMOVE_ADDRESS_PAIR 1
#define MCOAUDPBASE_DELAY_MSG_REMOVE 0.5
#define STR_MK_REMOVE_ADDRES_PAIR "MCoAUDPBase_delAdr"

/**
 * Contains a few utility functions as protected methods, for sending
 * and receiving UDP packets.
 */
class INET_API MCoAUDPBase : public cSimpleModule, protected INotifiable
{
protected:

	struct stAdrInfo {
		IPvXAddress mSrc;
		IPvXAddress mDest;
		int sockID;
		bool deleted;
	};
	typedef stAdrInfo AdrInfo;

	std::string useMode;
	std::vector<AdrInfo > adrsAvailable;

	IPvXAddress prefAddress;
	NotificationBoard *nb;
	int lenAdrs;

	int localPort, destPort;
	bool useMCoA;
	bool isDestiny;

  public:
	MCoAUDPBase();
	~MCoAUDPBase();

	IPvXAddress getPrefAddress() const;
	std::string getUseMode() const;

	void setPrefAddress(IPvXAddress prefAddress);
	void setUseMode(std::string useMode);

	bool isAdrInVec( AdrInfo ipadr);
	bool markAsdelAdrInVec(AdrInfo ipadr);
	bool delAdrInVec(AdrInfo &ipadr);


	MCoAUDPBase::AdrInfo initRecAdr(IPvXAddress Src, IPvXAddress Dest );

    /**
     * Tells UDP we want to get all packets arriving on the given port
     */
     virtual void bindToPort(int port);
     virtual int bindToPort(int port, IPvXAddress &srcAddr); // to return sock id
     virtual void unBindPort(int port, IPvXAddress &srcAddr, int sockId);

    /**
     * Sends a packet over UDP
     */
     //virtual void sendToUDP(cPacket *msg, int srcPort, const IPvXAddress& destAddr, int destPort);
     virtual void sendToUDP(cPacket *msg, const IPvXAddress& srcAddr, int srcPort, const IPvXAddress& destAddr, int destPort, bool appendCtrlInfo);
     /**
     	 * Sends a packet over UDP
     	 */
	virtual void sendToUDPMCOA(cPacket *msg, int srcPort, const IPvXAddress& destAddr, int destPort, bool appendCtrlInfo=true);
	virtual void TrysendToUDPMCOA(cPacket *msg, int srcPort, const IPvXAddress& destAddr, int destPort, bool appendCtrlInfo=true);


    /**
     * Prints a brief about packets having an attached UDPControlInfo
     * (i.e. those which just arrived from UDP, or about to be send to UDP).
     */
    virtual void printPacket(cPacket *msg);

    /*
     *
     */
    virtual void startMCoAUDPBase();

  protected:
  	/**
  	 * Called by the NotificationBoard whenever a change of a category
  	 * occurs to which this client has subscribed.
  	 */
  	virtual void receiveChangeNotification(int category, const cPolymorphic *details);

  	//virtual void handleMessage(cMessage *msg);
  	virtual void treatMessage(cMessage *msg);
};


#endif


