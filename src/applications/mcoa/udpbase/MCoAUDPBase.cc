/**
 * Copyright (C) 2010
 * Bruno Sousa
 * Laboratory and Communications and Telematics (LCT), University of Coimbra, Portugal

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


#include <omnetpp.h>
#include "MCoAUDPBase.h"
#include "UDPSocket.h"
#include "UDPControlInfo_m.h"


Define_Module(MCoAUDPBase);

MCoAUDPBase::MCoAUDPBase(){

}

MCoAUDPBase::~MCoAUDPBase(){
	adrsAvailable.clear();
}

/**
 * Initialize tunnel manager.
 */
void MCoAUDPBase::startMCoAUDPBase()
{
	localPort = par("localPort");
	destPort  = par("destPort");

	useMCoA = par("useMCoA");
	isDestiny= par("isDestiny");

	nb = NotificationBoardAccess().get();
	//if (useMCoA){
	nb->subscribe(this, NF_IPv6_TUNNEL_ADDED);
	nb->subscribe(this, NF_IPv6_TUNNEL_DELETED);
	//}
	lenAdrs=0;



	setUseMode(par("useMode"));

	EV << "MCoAUDP Application initialized using MCoA capabilities ? " << useMCoA << endl;
}




void MCoAUDPBase::bindToPort(int port)
{
    EV << "Binding to UDP port " << port << endl;

    // TODO UDPAppBase should be ported to use UDPSocket sometime, but for now
    // we just manage the UDP socket by hand...
    cMessage *msg = new cMessage("UDP_C_BIND", UDP_C_BIND);
    UDPControlInfo *ctrl = new UDPControlInfo();
    ctrl->setSrcPort(port);
    ctrl->setSockId(UDPSocket::generateSocketId());
    msg->setControlInfo(ctrl);
    send(msg, "udpOut");
}


int MCoAUDPBase::bindToPort(int port, IPvXAddress &srcAddr)
{
    EV << "Binding UDP at  " << srcAddr << ":" << port << endl;

    // TODO UDPAppBase should be ported to use UDPSocket sometime, but for now
    // we just manage the UDP socket by hand...
    cMessage *msg = new cMessage("UDP_C_BIND", UDP_C_BIND);
    UDPControlInfo *ctrl = new UDPControlInfo();
    ctrl->setSrcPort(port);
    ctrl->setSrcAddr(srcAddr);
    ctrl->setSockId(UDPSocket::generateSocketId());
    msg->setControlInfo(ctrl);
    send(msg, "udpOut");

    return (ctrl->getSockId());
}

void MCoAUDPBase::unBindPort(int port, IPvXAddress &srcAddr, int sockId){
	 EV << "Unbinding UDP at  " << srcAddr << ":" << port << endl;

	// TODO UDPAppBase should be ported to use UDPSocket sometime, but for now
	// we just manage the UDP socket by hand...
	cMessage *msg = new cMessage("UDP_C_UNBIND", UDP_C_UNBIND);
	UDPControlInfo *ctrl = new UDPControlInfo();
	ctrl->setSrcPort(port);
	ctrl->setSrcAddr(srcAddr);
	ctrl->setSockId(sockId);
	msg->setControlInfo(ctrl);
	send(msg, "udpOut");


}

void MCoAUDPBase::sendToUDP(cPacket *msg, const IPvXAddress& srcAddr, int srcPort, const IPvXAddress& destAddr, int destPort, bool appendCtrlInfo)
{
    // send message to UDP, with the appropriate control info attached
    msg->setKind(UDP_C_DATA);
    if (appendCtrlInfo){
		UDPControlInfo *ctrl = new UDPControlInfo();
		ctrl->setSrcAddr(srcAddr);
		ctrl->setSrcPort(srcPort);
		ctrl->setDestAddr(destAddr);
		ctrl->setDestPort(destPort);
		msg->setControlInfo(ctrl);

		EV << "Sending packet: ";
		printPacket(msg);
    }

    send(msg, "udpOut");
}


void MCoAUDPBase::printPacket(cPacket *msg)
{
    UDPControlInfo *ctrl = check_and_cast<UDPControlInfo *>(msg->getControlInfo());

    IPvXAddress srcAddr = ctrl->getSrcAddr();
    IPvXAddress destAddr = ctrl->getDestAddr();
    int srcPort = ctrl->getSrcPort();
    int destPort = ctrl->getDestPort();

    ev  << msg << "  (" << msg->getByteLength() << " bytes)" << endl;
    ev  << srcAddr << " :" << srcPort << " --> " << destAddr << ":" << destPort << endl;
}



void MCoAUDPBase::sendToUDPMCOA(cPacket *msg, int srcPort, const IPvXAddress& destAddr, int destPort,  bool appendCtrlInfo)
{
	bool sentMsg=false;

    // send message to UDP, with the appropriate control info attached
    msg->setKind(UDP_C_DATA);

    EV << "MCoAUDPBase sending UDPMCOA method useMCoA?" <<useMCoA << "  with len=" << lenAdrs << " for dest " << destAddr <<endl;

    AdrInfo auxadr;

    if (!useMCoA || lenAdrs == 0) {
    	/*if (appendCtrlInfo){
			UDPControlInfo *ctrl = new UDPControlInfo();
			ctrl->setSrcPort(srcPort);
			ctrl->setDestAddr(destAddr);
			ctrl->setDestPort(destPort);
			msg->setControlInfo(ctrl);
    	}
		EV << "Sending packet: ";
		printPacket(msg);

		send(msg, "udpOut");
		*/
    	TrysendToUDPMCOA(msg,  srcPort, destAddr, destPort , appendCtrlInfo);
    }else{
    	if (useMode == MCOA_TUN_ALL_ADR_ALL){
    		std::vector<AdrInfo>::iterator it;

			for (it=adrsAvailable.begin(); it < adrsAvailable.end(); it++){
				if (it->deleted) {
					EV << "MCoAUDPBase Socket id  " << it->sockID << " with pairs (" << it->mSrc  << "," << it->mDest << ") is marked has deleted, deleting message." << endl;
					//cancelAndDelete(msg);
					//delete(msg);
					continue;
				}else {
					if (it->mDest == destAddr){
						cPacket *msg1 = msg->dup();
						EV << "MCoAUDPBase duplicating message for adr " << it->mSrc << endl;
						//Please note dup objects need to add controlinfo.
						sendToUDP(msg1, it->mSrc, srcPort, destAddr, destPort , true);
						sentMsg= true;
					}else {
						EV << "MCoAUDPBase destination address differs " << it->mDest << " from conf. destAddress  " << destAddr << endl;

						if (!isDestiny){ // Sender can be single-homed
							cPacket *msg1 = msg->dup();
							EV << "MCoAUDPBase in Sending node duplicating message for adr " << it->mSrc << endl;
							//Please note dup objects need to add controlinfo.
							sendToUDP(msg1, it->mSrc, srcPort, destAddr, destPort , true);
							sentMsg= true;
						}
					}
				}

			}
			if (!sentMsg){
				EV << "All the addresses were marked as deleted ! trying a standard send" << endl;
				TrysendToUDPMCOA(msg,  srcPort, destAddr, destPort , appendCtrlInfo);
			}
    	}else {
    		/*
    		 * For each packet to send choose a random path
    		 */
    		if (useMode == MCOA_TUN_ALL_ADR_SINGLE_RR){
    			//if (prefAddress.isUnspecified()){
				int idx =  (int)intrand(lenAdrs); // start from zero
				EV << "MCoAUDPBAse chosen index" << idx << " from " << lenAdrs << endl;

				IPvXAddress adrtoSend = adrsAvailable[idx].mSrc;
				sendToUDP(msg, adrtoSend, srcPort, destAddr, destPort, appendCtrlInfo );

					/*
					 * Demonstration code how to activate prefered address
					 *
					if (prefAddress.isIPv6()){
						IPv6PrefAdr *ippref =  new IPv6PrefAdr(prefAddress.get6(), 0);
						nb->fireChangeNotification(NF_MCOA_APP_PREFERED_ADDRESS, ippref);
					}
					*/
    			//}
    		}else {
    			/*
    			 * Use always the first address present in the vector
    			 */
    			if (useMode == MCOA_TUN_ALL_ADR_SINGLE_FIRST){
    				IPvXAddress adrtoSend = adrsAvailable[0].mSrc;

    				sendToUDP(msg, adrtoSend, srcPort, destAddr, destPort, appendCtrlInfo );
    			}
    		}
    	}
    }
}


void MCoAUDPBase::TrysendToUDPMCOA(cPacket *msg, int srcPort, const IPvXAddress& destAddr, int destPort,  bool appendCtrlInfo)
{
    // send message to UDP, with the appropriate control info attached
    msg->setKind(UDP_C_DATA);

	if (appendCtrlInfo){
		UDPControlInfo *ctrl = new UDPControlInfo();
		ctrl->setSrcPort(srcPort);
		ctrl->setDestAddr(destAddr);
		ctrl->setDestPort(destPort);
		msg->setControlInfo(ctrl);
	}
	EV << "Sending packet: ";
	printPacket(msg);

	send(msg, "udpOut");

}



IPvXAddress MCoAUDPBase::getPrefAddress() const
{
	return prefAddress;
}

std::string MCoAUDPBase::getUseMode() const
{
	return useMode;
}



void MCoAUDPBase::setPrefAddress(IPvXAddress prefAddress)
{
	this->prefAddress = prefAddress;
}

void MCoAUDPBase::setUseMode(std::string iuseMode)
{
	this->useMode = iuseMode;
	EV << "MCoAUDPBase Setting use mode to " << this->useMode << endl;
}

void MCoAUDPBase::receiveChangeNotification(int category, const cPolymorphic *details){


	 if (simulation.getContextType()==CTX_INITIALIZE)
	        return;  // ignore notifications during initialize

	Enter_Method_Silent();
	printNotificationBanner(category, details);
	EV << "MCoAUDPBase receiving notifications for category " << category << endl;

	IPv6TunAdr *adrInfo =check_and_cast<IPv6TunAdr*>(details);
	AdrInfo adraux;

	if (isDestiny){
		//According to HA_OPT sets (see xMIPv6 in processBAmessage methods).
		//adraux.mSrc = adrInfo->getEntry();
		//adraux.mDest = adrInfo->getDestTrigger();
		adraux = initRecAdr(adrInfo->getEntry(), adrInfo->getDestTrigger() );
	}else {
		//According to RH2 sets (see xMIPv6 in processBUmessage methods).
		//adraux.mSrc = adrInfo->getEntry();
		//adraux.mDest = adrInfo->getExit();
		adraux = initRecAdr(adrInfo->getEntry(), adrInfo->getExit() );
	}


	if (!useMCoA){
		EV << "MCoAUDPBAse Configured to ignore notifications" << endl;
		return;
	}

	if (category==NF_IPv6_TUNNEL_ADDED)
	{
		EV << "NEW address obtained " << adrInfo << endl;
		if (!isAdrInVec(adraux)){
			adrsAvailable.push_back(adraux);
			lenAdrs++;
			if (!adraux.mSrc.isUnspecified()){
				adraux.sockID= MCoAUDPBase::bindToPort(localPort, adraux.mSrc);
			}
			EV << "MCoAUDPBase address " <<  adraux.mSrc << " added sucessfully len=" << lenAdrs << endl;
		}else{
			EV << "Address is already in vector not adding" << endl;
		}


	}else if (category==NF_IPv6_TUNNEL_DELETED){
		EV << "Address to be removed obtained" << endl;
		if (markAsdelAdrInVec(adraux)){
			lenAdrs--;
			lenAdrs <0 ? lenAdrs=0 : lenAdrs ;
			EV << "Entry removed successfully now with " << lenAdrs << " addresses!" << endl;
			if (!adraux.mSrc.isUnspecified()){

				cMessage *DelAdrPair = new cMessage("MCoAUDPBase_delAdr", MK_REMOVE_ADDRESS_PAIR);
				DelAdrPair->setContextPointer(&adraux);
				scheduleAt(simTime() + MCOAUDPBASE_DELAY_MSG_REMOVE, DelAdrPair);

				//unBindPort(localPort, adraux.mSrc, adraux.sockID );
				/*
				 * Unbinding at run time seems to present some problems in sync the messages
				 * within the UDP transport layer.
				 *
				 *
				 */
			}
		}
	}
}

bool MCoAUDPBase::isAdrInVec( AdrInfo ipadr){

	std::vector<AdrInfo>::iterator it;

	for (it=adrsAvailable.begin(); it < adrsAvailable.end(); it++){
		if ((it->mSrc  == ipadr.mSrc) && (it->mDest == ipadr.mDest)){
			if (it->deleted){
				adrsAvailable.erase(it); // entry was deleted clear it now!
				lenAdrs = adrsAvailable.size(); //refresh len
				return false;
			}else {
				return true;
			}
		}
	}
	return false;
}


bool MCoAUDPBase::markAsdelAdrInVec( AdrInfo  ipadr){

	std::vector<AdrInfo>::iterator it;
	bool res=false;
	for (it=adrsAvailable.begin(); it < adrsAvailable.end(); it++){
		if (it->mSrc  == ipadr.mSrc && it->mDest == ipadr.mDest)
		{
			//adrsAvailable.erase(it);
			it->deleted = true;
			res = true;
			break;
		}

	}
	return res;
}

bool MCoAUDPBase::delAdrInVec( AdrInfo  &ipadr){

	std::vector<AdrInfo>::iterator it;
	bool res=false;
	for (it=adrsAvailable.begin(); it < adrsAvailable.end(); it++){
		if (it->mSrc  == ipadr.mSrc && it->mDest == ipadr.mDest)
		{
			adrsAvailable.erase(it);
			res = true;
			break;
		}
	}

	lenAdrs = adrsAvailable.size(); //refresh len
	return res;
}

MCoAUDPBase::AdrInfo MCoAUDPBase::initRecAdr(IPvXAddress Src, IPvXAddress Dest ){

	AdrInfo  aRet ;
	aRet.mSrc = Src;
	aRet.mDest = Dest;
	aRet.deleted = false;

	return aRet;
}

void MCoAUDPBase::treatMessage(cMessage *msg)
{
	if (msg->getKind() == MK_REMOVE_ADDRESS_PAIR ){
		EV << "MCoAUDPApp application receiving delete pair message"<< endl;
		MCoAUDPBase::AdrInfo * adraux = (MCoAUDPBase::AdrInfo *)msg->getContextPointer();
		//MCoAUDPBase::unBindPort(localPort, adraux->mSrc, adraux->sockID ); // See MCoAUDPBase comment
		EV << "MCoAUDPApp application performing unbind of socket " << adraux->sockID << " at simTime " << simTime() << endl;
		MCoAUDPBase::delAdrInVec(*adraux);

		delete msg;
	}
}
