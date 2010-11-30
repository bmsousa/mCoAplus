/**
 * Copyright (C) 2007
 * Faqir Zarrar Yousaf
 * Communication Networks Institute, University of Dortmund, Germany.
 * Christian Bauer
 * Institute of Communications and Navigation, German Aerospace Center (DLR)

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

#ifndef __XMIPV6_H__
#define __XMIPV6_H__

#include <stdio.h>
#include <string.h>
#include <vector>
#include <set>
#include <omnetpp.h>
#include "IPv6Address.h"
#include "IPv6Datagram.h"
#include "IPv6NDMessage_m.h"
#include "IPv6ControlInfo.h"
#include "IPv6InterfaceData.h"
#include "InterfaceEntry.h"
#include "InterfaceTable.h"
#include "InterfaceTableAccess.h"
#include "RoutingTable6.h"
#include "RoutingTable6Access.h"
#include "IPv6NeighbourCache.h"
#include "ICMPv6.h"
#include "ICMPv6Access.h"
#include "IPv6NeighbourDiscovery.h"
//###### ADDITIONAL HEADERS ADDED BY ZARRAR YOUSAF @ CNI, UNI Dortmund on 23.05.07 ######
#include "MobilityHeader.h"
#include "IPAddressResolver.h"
#include "IPv6NeighbourDiscoveryAccess.h"
#include "BindingUpdateList.h"
#include "BindingUpdateListAccess.h"
#include "BindingCache.h"
#include "BindingCacheAccess.h"
// Added by CB
#include "IPv6TunnelingAccess.h"
// 14.01.08 - CB
#include "NotificationBoard.h"

// Bruno Sousa 2010/4/29
//#include "MobilityHeader_m.h"
//#include "MobilityOptions.h"
#include "MCoA.h"
#include "MCoAAccess.h"
#include "KeyMCoABind.h"
#include "XMIPv6SM.h"
#include <platdep/timeutil.h>

// 13.9.07
// Keys for timer list (=message type)
#define KEY_BU			0 // Binding Update
#define KEY_HI			1 // HoTI
#define KEY_CI			2 // CoTI
#define KEY_BR			3 // Binding Refresh Request
#define KEY_BUL_EXP		4 // BUL entry expiry // 12.06.08 - CB
#define KEY_BC_EXP		5 // BC entry expiry // 17.06.08 - CB
#define KEY_HTOKEN_EXP	6 // home token expiry // 10.07.08 - CB
#define KEY_CTOKEN_EXP	7 // care-of token expiry // 10.07.08 - CB


// 21.9.07
#define TRANSMIT_TYPE_BU	51 // BUTransmitIfEntry
#define TRANSMIT_TYPE_TI	52 // TestInitTransmitIfEntry
// 12.06.08 - CB
#define EXPIRY_TYPE_BUL		61 // BULExpiryIfEntry
#define EXPIRY_TYPE_BC		62 // BCExpiryIfEntry
// 10.07.08 - CB
#define EXPIRY_TYPE_TOKEN	63 // {Home, CareOf}TokenExpiryIfEntry

/**
 * Implements RFC 3775 Mobility Support in IPv6.
 */
class INET_API xMIPv6 : public cSimpleModule, protected INotifiable
{
  public:
	  virtual ~xMIPv6();

  protected:
	IInterfaceTable* ift;
	RoutingTable6* rt6;
	BindingUpdateList* bul; //31.07.07
	BindingCache* bc; //31.07.07
	IPv6Tunneling* tunneling; // 21.08.07 - CB
	class INET_API IPv6NeighbourDiscovery* ipv6nd;

	// statistic collection
	cOutVector statVectorBUtoHA, statVectorBUtoCN, statVectorBUtoMN;
	// 1 means BA from HA, 2 means BA from CN
	cOutVector statVectorBAtoMN;
	// 1 means BA to register BU, 2 means BA to deregister BU message
	// 3 means invalid BA
	cOutVector statVectorBAfromHA, statVectorBAfromCN;

	cOutVector statVectorHoTItoCN, statVectorCoTItoCN;
	cOutVector statVectorHoTtoMN, statVectorCoTtoMN;
	cOutVector statVectorHoTfromCN, statVectorCoTfromCN;


	/** NB is used for MIH signalling */
	NotificationBoard* nb; // 14.01.08 - CB

	/**
	 * MCoA configuration
	 *
	 * */
	 MCoA* mCoA;


	 /*
	  * Class to indicate the states of xMIPv6
	  */
	 XMIPv6SM* mipv6sm;




	/**
	 * The base class for all other timers that are used for retransmissions.
	 */
	class TimerIfEntry
	{
	public:
		cMessage* timer; // pointer to the scheduled timer message
		virtual ~TimerIfEntry() {}; // to make it a polymorphic base class


		IPv6Address dest; // the address (HA or CN(s) for which the message is sent
		simtime_t ackTimeout; // timeout for the Ack
		simtime_t nextScheduledTime; // time when the corrsponding message is supposed to be sent
		InterfaceEntry* ifEntry;  // interface from which the message will be transmitted
	};

	// 13.9.07 - CB
	struct KeyTimer
	{
		int type; // type of the message (BU, HoTI, CoTI) stored in the map, indexed by this key
		int interfaceID; // ID of the interface over which the message is sent
		IPv6Address dest; // the address of either the HA or the CN
		int BID; // The BID of a binding -- Bruno Sousa

		KeyTimer(IPv6Address _dest, int _interfaceID, int _type, int _bid)
		{dest=_dest;interfaceID=_interfaceID;type=_type;BID=_bid; }



        bool operator<(const KeyTimer& b) const
        {
        	if (type < b.type){ return true;
        	}else {
        		if (interfaceID < b.interfaceID){ return true;
        		}else{
        			if(BID < b.BID){return true;}
        			else{
        				if (dest < b.dest) {return true;}
        				else {
        					 return false;
        				}
        			}
         		}
        	}
		}


        bool operator>(const KeyTimer& b) const
		{
			if (type > b.type){ return true;
			}else {
				if (interfaceID > b.interfaceID){ return true;
				}else{
					if(BID > b.BID){return true;}
					else{
						if (dest > b.dest) {return true;}
						else {
							 return false;
						}
					}
				}
			}
		}

        bool operator==(const KeyTimer& b) const
		{
			if (type == b.type && interfaceID == b.interfaceID && BID == b.BID && dest == b.dest  ) {
				return true;
			}else return false;

		}

        bool operator!=(const KeyTimer& b) const
		{
			return !operator==(b);

		}
	};
	typedef std::map<KeyTimer,TimerIfEntry*> TransmitIfList;
	TransmitIfList transmitIfList;

	/** holds the tuples of currently available {InterfaceID, CoA} pairs */
	// Struct with interface ID and BID, to work similar to virtual interfaces eth0:1, eth0:2
	struct ifBID{
		int ifID;
		int iBID;

		bool operator<(const ifBID& sIf) const {
			if (ifID < sIf.ifID ) {
				return true;
			}else {
				if (iBID < sIf.iBID) {
					return true;
				}else return false;
			}
		}

	};

	//typedef std::map<int,IPv6Address> InterfaceCoAList;
	typedef std::map<ifBID,IPv6Address> InterfaceCoAList;
	InterfaceCoAList interfaceCoAList;

	/*
	 * Bruno Sousa 2010/5/6
	 *  holds the tuples of CoA and BID pairs
	 */
	typedef std::map<IPv6Address,int> CoABIDList;
	CoABIDList CoABIDs;

	/*
	 * Bruno Sousa
	 * Hold the information about nodes capabilities related with MCoA
	 */
	struct CapMCoA {
		bool mCoA_support;
		bool m_prohibited;
		bool m_bulk_reg_prohibited;
		bool mc_sim_home_and_foreign_prohibited;
		bool FlagOverwrite;
	};
	typedef std::map<IPv6Address, CapMCoA> NodesMCoACap;
	NodesMCoACap nodesMCoACaps;

	// A vector that will contain and maintain a list of all the CN(s) that the MN is in communication with. Although this is a quick fix, but this list should be populated and depopulated in sync with the destination cache. Final version should rely on the destinaion cache for acquiring the CN(s) address for use in Correspodent Registeration (Zarrar 27.07.07)
public:

	/*
	typedef std::vector<IPv6Address> CNList;
	CNList cnList;
	CNList::iterator itCNList; // declaring an iterator over the cnList vector
	*/
	typedef std::vector<int> cnBIDs;
	/*
	class nBIDs{
	  public:
		std::vector<int> cnBIDs;
	};
	*/
	typedef std::map<IPv6Address, cnBIDs> CNListBIDs;
	CNListBIDs cnListBIDs;

protected:
	/** Subclasses for the different timers */
	class BUTransmitIfEntry : public TimerIfEntry
	{
	public:
		uint buSequenceNumber ; // sequence number of the BU sent
		uint lifeTime; // lifetime of the BU sent, 4.9.07 - CB
		//Time variable related to the time at which BU was sent
		simtime_t presentSentTimeBU;//stores the present time at which BU is/was sent
		bool homeRegistration; // indicates whether this goes to HA or CN; Added by CB

		IPv6Address adrCoA; // Address of MN to be included in th Mobility Options
		int BID; // addedd by Bruno Sousa
	};

	//##############################Added by Christian, 27.08.07#################################
	class TestInitTransmitIfEntry : public TimerIfEntry
	{
	public:
		MobilityHeader* testInitMsg; // either the HoTI or CoTI

		IPv6Address adrCoA; // Address of MN to be included in th Mobility Options
		int BID; // addedd by Bruno Sousa

	};
	//##############################End Christian#################################
	//##############################Added by Christian, 27.08.07#################################
	class BRTransmitIfEntry : public TimerIfEntry
	{
	public:
		uint retries; // number of BRRs already sent

		IPv6Address adrCoA; //Bruno Sousa - Corresponds to the CoA and not to the HoA which is the dest of these messages
		int BID;
		IPv6Address adrCN; //Address of CN to which the BR must be triggered.
	};
	//##############################End Christian#################################

	// Added 11.06.08 - CB
	class BULExpiryIfEntry : public TimerIfEntry
	{
	public:
		IPv6Address CoA, HoA; // the CoA and HoA of the MN that were used for this BUL entry
		int BID; //Bruno Sousa
	};

	class BCExpiryIfEntry : public TimerIfEntry
	{
	public:
		IPv6Address HoA; // HoA of the MN
		int BID; //Bruno Sousa
	};

	class TokenExpiryIfEntry : public TimerIfEntry
	{
	public:
		IPv6Address cnAddr;
	    int tokenType;

	    IPv6Address adrCoA;
	    int BID;


	};


  protected:
	/************************Miscellaneous Stuff***************************/
	virtual int numInitStages() const {return 4;}
	virtual void initialize(int stage);
	virtual void handleMessage(cMessage *msg);

	//================MIPv6 Related Functions=================================================
	/**
	  * This is where all the mobility messages are sifted through and sent to appropriate functions
	  * for processing.
	  */
	void processMobilityMessage(MobilityHeader* mipv6Msg, IPv6ControlInfo *ctrlInfo);

	/**
	 * This method finally creates the timer structure and schedules the message for sending.
	 */
	void createBUTimer( KeyMCoABind &keyMCoA, const IPv6Address& buDest, InterfaceEntry* ie, const uint lifeTime, bool homeRegistration); // 4.9.07 - CB

	/**
	 * Similiar to the previous one, this method creates an BU timer with registration lifetime equal to 0.
	 */
	void createDeregisterBUTimer( KeyMCoABind &keyMCoA, const IPv6Address& buDest, InterfaceEntry* ie); // 4.9.07 - CB

	/*
	 * This method creates and starts a timer for an advertising interface over which BUs will be sent until it gets acknowledged
	 * by an appropriate BA. This routine also "intialises" the necessary variables in a struct BUTransmitIfEntry that is created to
	 * keep these variables for access.
	 */
	void createBUTimer( KeyMCoABind &keyMCoA, const IPv6Address& buDest,InterfaceEntry* ie); //05.06.07, update 28.08.07 - CB, 14.9.07 - CB

	/*
	 * Creates BU Timer according to the CoABIDList.
	 */
	void MCoAcreateBUTimer(KeyMCoABind &keyMCoA, const IPv6Address& buDest,InterfaceEntry* ie, const bool allBIDS);

	/**
	 * This method is called when the timer created in createBUTimer() has fired.
	 * The BU is created and the appropriate method for sending it called. The timer structure is updated and rescheduled.
	 */
	void sendPeriodicBU(cMessage *msg); //06.06.07

	/**
	 * Bruno Sousa modified to include Mobility Options  2010/4/10
	 *
	 * Method for creating and sending a BU by a MN.
	 *
	 */
	void createAndSendBUMessage(const IPv6Address& dest,InterfaceEntry* ie, const uint buSeq, const uint lifeTime, const int bindAuthData ,
								MobOption_Binding_AuthorizationData *aDat,
								MobilityBIDOptions* mOpt , const int nMobOpts);


	/**
	 * Update the an entry of the BUL with the provided parameters.
	 */
	void updateBUL(BindingUpdate* bu, KeyMCoABind &keyMCoA, const IPv6Address& dest, const IPv6Address& CoA, InterfaceEntry* ie, const simtime_t sendTime); //04.06.07

	/**
	 * This method takes an interface and a destination address and returns the appropriate IfEntry for an BU.
	 * Is supposed to be used until the valid BA is received for the respective BU.
	 */
	xMIPv6::BUTransmitIfEntry* fetchBUTransmitIfEntry(InterfaceEntry *ie, const IPv6Address& dest); //08.06.07

	/**
	 * Append an IPv6ControlInfo object to the Mobility Messages (BU, BA etc) and send it out to the IPv6 Module
	 */
	void sendMobilityMessageToIPv6Module(cMessage *msg, const IPv6Address& destAddr, const IPv6Address& srcAddr = IPv6Address::UNSPECIFIED_ADDRESS, int interfaceId = -1, simtime_t sendTime = 0); // overloaded for use at CN - CB
	//void sendMobilityMessageToIPv6Module(cMessage *msg, const IPv6Address& destAddr, simtime_t sendTime = 0); // overloaded for use at CN - CB

	/**
	 * Process a BU - only applicable to HAs and CNs.
	 */
	void processBUMessage(BindingUpdate * bu, IPv6ControlInfo * ctrlInfo);

	/**
	 * Validate a BU - only applicable to HAs and CNs
	 */
	bool validateBUMessage(BindingUpdate *bu, IPv6ControlInfo *ctrlInfo);

	/**
	 * Similiar to validateBUMessage(). However, this one is used only by HA to verify deregistration BU.
	 */
	bool validateBUderegisterMessage(BindingUpdate *bu, IPv6ControlInfo *ctrlInfo); // 4.9.07 - CB


	/**
	 * Bruno Sousa 2010/5/4
	 *
	 * Validate a BID Option
	 */
	bool validateBIDOption(MobOption_Binding_Identifier_Mobility& mobOpt, BindingUpdate *bu, IPv6ControlInfo *ctrlInfo);

	/**
	 * Constructs and send a BA to the IPv6 module. Only applicable to HAs and CNs.
	 */
	void createAndSendBAMessage(const IPv6Address& src, const IPv6Address& dest, IPv6ControlInfo* ctrlInfo, const BAStatus& baStatus, const uint baSeq,
			const int bindingAuthorizationData, const uint lifeTime, simtime_t sendTime = 0,
			MobilityBIDOptions *MobOpts=NULL); // 14.9.07 - CB  // Bruno Sousa 2010/5/4

	/**
	 * Processes the received BA and creates tunnels or mobility header paths if appropriate.
	 */
	void processBAMessage(BindingAcknowledgement * ba, IPv6ControlInfo * ctrlInfo);
	void MCOAprocessBAMessage_DeregALL(BindingAcknowledgement * ba, IPv6ControlInfo * ctrlInfo, InterfaceEntry *ie, IPv6Address &baSource);
	void MCOAprocessBAMessage_Normal(BindingAcknowledgement * ba, IPv6ControlInfo * ctrlInfo, InterfaceEntry *ie, IPv6Address &baSource, KeyMCoABind &keyMCoA, int ci);

	/**
	 * Validates a Binding Acknowledgement for a mobile node.
	 */
	bool validateBAck(const BindingAcknowledgement& ba, const IPv6ControlInfo* ctrlInfo); // update 12.9.07

	/**
	 * Creates and sends Binding Error message.
	 */
	void createAndSendBEMessage(const IPv6Address& dest, const BEStatus& beStatus); // update 12.9.07 - CB


  public:
	/**
	 * Initiates the Mobile IP protocol.
	 * Method to be used when we have moved to a new access network and the new CoA is available for that interface.
	 */
	void initiateMIPv6Protocol(InterfaceEntry *ie, IPv6Address& CoA); //27.07.07


	/**
	 * This method destroys all tunnels associated to the previous CoA
	 * and sends appropriate BU(s) to HA and CN(s).
	 */
	void returningHome(const IPv6Address& CoA, InterfaceEntry *ie); // 4.9.07 - CB

	/*
	 *
	 */
	void returningHomeMCoA( InterfaceEntry *ie); // 16/6/2010 Method to return home  to all the Multiple CoAs.


//
// Route Optimization related functions
//
	 /** Alain Tigyo, 21.03.2008
	  *  The following method is used for triggering RO to a CN.
	  */
	virtual void triggerRouteOptimization(const IPv6Address& destAddress, const IPv6Address& mCoA, const  int iBID, const IPv6Address& HoA, InterfaceEntry* ie);

  protected:
	/**
	 * Creates HoTI and CoTI messages and sends them to the CN if timers are not already existing.
	 * If home and care-of tokens are already available a BU is directly sent to the CN.
	 */
	virtual void initReturnRoutability( const IPv6Address& cnDest, InterfaceEntry* ie,  KeyMCoABind &keyMCoA); // 27.08.07 - CB

	/**
	 * Creates and schedules a timer for either a HoTI or a CoTI transmission.
	 */
	void createTestInitTimer(MobilityHeader* testInit, const IPv6Address& dest, InterfaceEntry* ie, KeyMCoABind &keyMCoA, simtime_t sendTime = 0 ); // 27.08.07 - CB

	/**
	 * If a TestInit timer was fired, this method gets called. The message is sent and the Binding Update List accordingly updated.
	 * Afterwards the transmission timer is rescheduled.
	 */
	void sendTestInit(cMessage *msg); // 27.08.07 - CB

	/**
	 * Cancels the current existing timer and reschedules it with initial values.
	 */
	/*void resetTestInitIfEntry(const IPv6Address& dest, int interfaceID, int msgType);*/

	/**
	 * Similiar to the other resetTestInitIfEntry() method, but this one searches for the appropriate
	 * transmission structure first as the interfaceID is not known but needed as lookup key.
	 */
	/*void resetTestInitIfEntry(const IPv6Address& dest, int msgType); // 14.01.08 - CB*/

	/**
	 * Reset the transmission structure for a BU and reschedule it for the provided time.
	 */
	void resetBUIfEntry(const IPv6Address& dest, int interfaceID, simtime_t retransmissionTime);

	/**
	 * Creates and sends a HoTI message to the specified destination.
	 */
	void createAndSendHoTIMessage(const IPv6Address& cnDest, InterfaceEntry* ie, KeyMCoABind &keyMCoA , const IPv6Address &CoA=IPv6Address::UNSPECIFIED_ADDRESS);

	/**
	 * Creates and sends a CoTI message to the specified destination.
	 */
	void createAndSendCoTIMessage(const IPv6Address& cnDest, InterfaceEntry* ie , KeyMCoABind &keyMCoA,  const IPv6Address &CoA=IPv6Address::UNSPECIFIED_ADDRESS);

	/**
	 * Create and send a HoT message.
	 */
	void processHoTIMessage(HomeTestInit* HoTI, IPv6ControlInfo* ctrlInfo); // 27.08.07 - CB

	/**
	 * Create and send a CoT message.
	 */
	void processCoTIMessage(CareOfTestInit* CoTI, IPv6ControlInfo* ctrlInfo); // 27.08.07 - CB

	/**
	 * First verifies a received HoT message and sends a BU to the CN if the care-of keygen token
	 * is available as well. Retransmission of HoTI message is rescheduled.
	 */
	void processHoTMessage(HomeTest* HoT, IPv6ControlInfo* ctrlInfo); // 28.07.07 - CB

	/**
	 * Verifies a HoT according to the RFC, Section 11.6.2
	 */
	bool validateHoTMessage(const HomeTest& HoT, const IPv6ControlInfo* ctrlInfo, InterfaceEntry* ie); // 27.08.07 - CB

	/**
	 * Like processHoTMessage(), but related to CoT.
	 */
	void processCoTMessage(CareOfTest* CoT, IPv6ControlInfo* ctrlInfo); // 28.07.07 - CB

	/**
	 * Like validateHoTMessage(), but related to CoT.
	 */
	bool validateCoTMessage(const CareOfTest& CoT, const IPv6ControlInfo* ctrlInfo, InterfaceEntry* ie); // 27.08.07 - CB

	/**
	 * Send a BU depending on current status of:
	 * * Registration or Deregistration phase
	 * * Availability of tokens
	 *
	 * Return true or false depending on whether a BU has been sent or not.
	 */
	bool checkForBUtoCN(KeyMCoABind &keyMCoA, BindingUpdateList::BindingUpdateListEntry& bulEntry, InterfaceEntry *ie);

	/**
	 * Creates a timer for sending a BU.
	 */
	void sendBUtoCN(KeyMCoABind &keyMCoA, BindingUpdateList::BindingUpdateListEntry& bulEntry, InterfaceEntry *ie); // 28.07.07 - CB

	/**
	 * Process the Type 2 Routing Header which belongs to the provided datagram.
	 *
	 * Swaps the addresses between the original destination address of the datagram and
	 * the field in the routing header.
	 */
	void processType2RH(IPv6Datagram* datagram, IPv6RoutingHeader* rh);

	/**
	 * Perform validity checks according to RFC 3775 - Section 6.4
	 */
	bool validateType2RH(const IPv6Datagram& datagram, const IPv6RoutingHeader& rh);

	/**
	 * Process the Home Address Option which belongs to the provided datagram.
	 *
	 * Swaps the addresses between the original source address of the datagram and
	 * the field in the option.
	 */
	void processHoAOpt(IPv6Datagram* datagram, HomeAddressOption* hoaOpt);


//
// Binding Refresh Request related functions
//

	/**
	 * Creates a timer for a Binding Refresh Request message that is going to be fired in scheduledTime seconds.
	 */
	void createBRRTimer(const IPv6Address& brDest, InterfaceEntry* ie, const uint scheduledTime, KeyMCoABind& keyMCoA); // 18.9.07 - CB

	/**
	 * Handles a fired BRR message transmission structure.
	 * Creates and sends and appropriate Binding Refresh Request.
	 * Transmission structure is rescheduled afterwards.
	 */
	void sendPeriodicBRR(cMessage *msg); // 18.09.07 - CB

	/**
	 * Creates a Binding Refresh Request and sends it to the IPv6 module.
	 */
	void createAndSendBRRMessage(const IPv6Address& dest, InterfaceEntry* ie,  KeyMCoABind& keyMCoA); // 18.09.07 - CB

	/**
	 * Processes the Binding Refresh Message.
	 */
	void processBRRMessage(BindingRefreshRequest* brr, IPv6ControlInfo* ctrlInfo); // 18.9.07 - CB


protected:
//
// Helper functions
//

	/**
	 * Deletes the appropriate entry from the transmitIfList and cancels
	 * the corresponding retransmission timer.
	 *
	 * Bruno Sousa add BID
	 */
	bool cancelTimerIfEntry(const IPv6Address& dest, int interfaceID, int msgType, int bid);
	bool cancelTimerIfEntry2(TransmitIfList::iterator & pos);



	/**
	 * Checks whether there exists an TransmitIfEntry for the specified values.
	 * In case a new XXXTimerIfEntry is added, this method has to be appropriately extended in order
	 * to cover the new data structure.
	 * Returns true on success and false otherwise.
	 */
	//Bruno Sousa
	//bool pendingTimerIfEntry(IPv6Address& dest, int interfaceID, int msgType);

	/**
	 * Returns a pointer to an TimerIfEntry object identified by the provided key,
	 * which can be one of the possible polymorphic types. In case there does not yet
	 * exist such an entry, a new one is created.
	 * The type of the TimerIfEntry is specified with the provided timerType.
	 */
	TimerIfEntry* getTimerIfEntry(KeyTimer& key, int timerType);

	/**
	 * Searches for a transmitEntry with the given destination address which is of type
	 * timerType.
	 * Returns NULL if no such entry exists.
	 */
	TimerIfEntry* searchTimerIfEntry(IPv6Address& dest, int timerType);

	/**
	 * Removes timers of all types for the specified destination address and interfaceId.
	 * Whenever a new mobility related timer is added, is MUST be added within this method
	 * to ensure proper removal.
	 */
	void removeTimerEntries(const IPv6Address& dest, int interfaceId);

	void removeTimerEntries2(const IPv6Address& dest, int interfaceId); //Bruno Sousa
	/*
	 * Cancels all the Timer Entries
	 */
	void removeAllTimerEntries(int interfaceId);

	/**
	 * Cancel all timers (TransmitIf entities for HA and CNs) related to the provided interfaceId and CoA.
	 * In addition the tunnels to the Home Agent and the CNs are destroyed as well.
0	 */
	void cancelEntries(int interfaceId, IPv6Address& CoA, int iBID);

	/**
	 * Remove all entries from the interfaceCoAList.
	 */
	void removeCoAEntries();

//
// Helper functions for BUL/BC expiry management
//
	/**
	 * Creates or overwrites a timer for BUL expiry that fires at provided scheduledTime.
	 */
	void createBULEntryExpiryTimer(KeyMCoABind &keyMCoA, BindingUpdateList::BindingUpdateListEntry* entry, InterfaceEntry* ie, simtime_t scheduledTime);

	/**
	 * Handles the situation of a BUL expiry. Either a BU is sent in advance for renewal or the BUL entry is removed.
	 */
	void handleBULExpiry(cMessage* msg);

	/**
	 * Creates or overwrites a timer for BC expiry that fires at provided scheduledTime.
	 */
	void createBCEntryExpiryTimer(KeyMCoABind &keyMCoA, IPv6Address HoA, InterfaceEntry* ie, simtime_t scheduledTime);

	/**
	 * Handles the expiry of a BC entry.
	 * Entry is removed from BC and tunnels/routing paths are destroyed.
	 */
	void handleBCExpiry(cMessage* msg);

//
// Helper functions for token expiry
//
	/**
	 * Creates or overwrites a timer for home keygen token expiry that fires at provided scheduledTime.
	 */
	void createHomeTokenEntryExpiryTimer(IPv6Address& cnAddr, InterfaceEntry* ie, simtime_t scheduledTime, KeyMCoABind& keyMCoA) { createTokenEntryExpiryTimer(cnAddr, ie, scheduledTime, KEY_HTOKEN_EXP, keyMCoA); };

	/**
	 * Creates or overwrites a timer for care-of keygen token expiry that fires at provided scheduledTime.
	 */
	void createCareOfTokenEntryExpiryTimer(IPv6Address& cnAddr, InterfaceEntry* ie, simtime_t scheduledTime, KeyMCoABind& keyMCoA) { createTokenEntryExpiryTimer(cnAddr, ie, scheduledTime, KEY_CTOKEN_EXP, keyMCoA); };

private:
	/**
	 * Creates or overwrites a timer for {home, care-of} keygen token expiry that fires at provided scheduledTime.
	 * Parameter tokenType is provided as KEY_XTOKEN_EXP
	 */
	void createTokenEntryExpiryTimer(IPv6Address& cnAddr, InterfaceEntry* ie, simtime_t scheduledTime, int tokenType, KeyMCoABind& keyMCoA);

	/**
	 * Handles the event that indicates that a {care-of,home} keygen token has expired.
	 */
	void handleTokenExpiry(cMessage* msg);

public:
	//int get_and_calcBID(const IPv6Address indar);
	int get_and_calcBID(const IPv6Address indar, InterfaceEntry *ie);
	IPv6Address get_adr_from_bid(const int bid);

	//IPv6Address getAddr_by_BID(int iBID);

	bool eraseBID(const IPv6Address &inadr);

	void prtTimers(void);

	void addCapabilitiesNode(IPv6Address, CapMCoA);
	bool delCapabilitiesNode(IPv6Address);


	bool updateCnList(const IPv6Address &adr, int iBID);
	bool deleteCnList( const IPv6Address &adr, int iBID);
	bool delBIDCnList( const IPv6Address &adr, int iBID);

	/*
	 * Method to clear BUL EXPIRY and remove Bindings.
	 */
	bool clear_and_remove_Binding(KeyMCoABind &key, InterfaceEntry* ie );

	/*
	 * Method to determine an address randomly
	 */
	IPv6Address get_addr_randomly_from_BIDS(InterfaceEntry* ie );


	/*
	 * Method to determine to retrieve an address to be used as CoA (in messages)
	 * according the configurations used.
	 */
	IPv6Address getMIPv6CoA(InterfaceEntry* ie, IPv6Address dest );


	MCoA *getMCoA() const
	{
		return mCoA;
	}

	XMIPv6SM *getMipv6sm() const
	{
		return mipv6sm;
	}

	void setMCoA(MCoA *mCoA)
	{
		this->mCoA = mCoA;
	}

	void setMipv6sm(XMIPv6SM *mipv6sm)
	{
		this->mipv6sm = mipv6sm;
	}



protected:
	int set_mobilityoptions_for_cn(KeyMCoABind &key, InterfaceEntry* ie, IPv6Address &buDest, uint lifetime, IPv6Address &CoA, MobilityBIDOptions *&mOpt, MobOption_Binding_AuthorizationData *&aDat);

	int set_mobilityoptions_for_ha(KeyMCoABind &key, InterfaceEntry* ie, IPv6Address &buDest, uint lifetime, IPv6Address &CoA, MobilityBIDOptions *&mOpt, MobOption_Binding_AuthorizationData *&aDat);

	void perform_clean_coa(KeyMCoABind &key, bool isHA);

	/**
	 * Called by the NotificationBoard whenever a change of a category
	 * occurs to which this client has subscribed.
	 */
	virtual void receiveChangeNotification(int category, const cPolymorphic *details);

	void perform_clean_at_home(cMessage *msg);

	std::map<KeyTimer,TimerIfEntry*>::iterator ftimer(KeyTimer key);

	bool sync_preferred_address(IPv6Address CoA_del, InterfaceEntry * ie);

};

#endif //__XMIPV6_H__
