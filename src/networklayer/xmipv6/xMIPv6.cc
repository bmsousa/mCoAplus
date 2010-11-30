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

#include "xMIPv6.h"
#include <algorithm>
#include <limits.h>
#include <stdlib.h>
#include <iostream>
#include "NotifierConsts.h"

#define MK_SEND_PERIODIC_BU			1
// 18.09.07 - CB
#define MK_SEND_PERIODIC_BR			2
#define MK_SEND_TEST_INIT			11
#define MK_BUL_EXPIRY				21		// 12.06.08 - CB
#define MK_BC_EXPIRY				22		// 17.06.08 - CB
#define MK_TOKEN_EXPIRY				23		// 10.07.08 - CB

#define MK_MCOA_CLEAN_AT_HOME       99		// Bruno Sousa for MCoA implementation

#define BRR_TIMEOUT_THRESHOLD		5		// time in seconds before the expiry of a BU when a Binding Refresh Msg. will be sent
#define BRR_RETRIES					4		// number of BRRs to be sent to MN
#define MAX_TOKEN_LIFETIME			500		//210  // maximum valid lifetime for the tokens used in RR
#define MAX_RR_BINDING_LIFETIME		4000	//420  // maximum valid lifetime of a binding for CNs
#define TEST_INIT_RETRANS_FACTOR	8	 	// HoTI and CoTI will be retransmitted every MAX_RR_BINDING_LIFETIME * TEST_INIT_RETRANS_FACTOR seconds


// sizes of mobility messages and headers in bytes
#define SIZE_MOBILITY_HEADER	6	// 6.1.1 mobility header = 48 bit
#define SIZE_BU					6	// 6.1.7 BU message = 48 bit
#define SIZE_HOA_OPTION			20	// HoA option = 128+16 bit + 16 (dest. opts. header)
#define SIZE_BIND_AUTH_DATA		14	// 6.2.7 Binding Auth. Data = 112 bit
#define SIZE_BACK				6	// 6.1.8 BAck message = 48 bit
#define	SIZE_NONCE_INDICES		6	// 6.2.6 Nonce Indices = 48 bit (PadN = 16 bit) -> no padding required for nonce indices
#define SIZE_HOTI				10  // 6.1.3 HoTI = 80 bit
#define SIZE_COTI				10  // 6.1.4 CoTI = 80 bit
#define	SIZE_HOT				18  // 6.1.5 HoT = 144 bit
#define	SIZE_COT				18	// 6.1.6 CoT = 144 bit
#define	SIZE_BE					18	// 6.1.9 BE message = 144 bit
#define	SIZE_BRR				2	// 6.1.2 BRR reserved = 16 bit


Define_Module(xMIPv6);




/**
 * Destructur
 *
 * Ensures that the memory from the list with all TimerIfEntry's gets
 * properly released.
 */
xMIPv6::~xMIPv6()
{
	TransmitIfList::iterator it = transmitIfList.begin();

	while ( it != transmitIfList.end() )
	{
		KeyTimer key = it->first;

		// advance pointer to make sure it does not become invalid
		// after the cancel() call
		++it;

		cancelTimerIfEntry(key.dest, key.interfaceID, key.type, key.BID);
	}

	cnListBIDs.clear();
	nodesMCoACaps.clear();
	CoABIDs.clear();

	delete mipv6sm;
//	delete mCoA;
}


void xMIPv6::initialize(int stage)
{
	if (stage == 0)
	{
    	EV << "Initializing xMIPv6 module" << endl;

		nb = NotificationBoardAccess().get();

		//Bruno Sousa
		nb->subscribe(this, NF_MIPv6_MN_RETURNED_HOME);



	}
	else if (stage == 1)
		tunneling = IPv6TunnelingAccess().get(); // access to tunneling module, 21.08.07 - CB
	// update 13.9.07 - CB
	// moved rt6 initialization to here, as we should
	// set the MIPv6 flag as soon as possible for use
	// with other modules.
	else if (stage==2)
	{
        rt6 = RoutingTable6Access().get();
		ASSERT(rt6 != NULL);
        rt6->setMIPv6Support(true); // 4.9.07 - CB

		// moved init stuff from rt6 to here as this is actually
		// the right place for these parameters
		// 26.10.07 - CB
		rt6->setIsHomeAgent( par("isHomeAgent") );
		rt6->setIsMobileNode( par("isMobileNode") );

		/* Bruno Sousa 2010/4/29
		 * Set the sets of MCoA configuration
		 *
		 * */
		mCoA = MCoAAccess().get();
		mCoA->setProhibited( mCoA->par("m_prohibited"));
		mCoA->setBulk_reg_prohibited( mCoA->par("m_bulk_reg_prohibited"));
		mCoA->setMc_sim_home_and_foreign_prohibited( mCoA->par("mc_sim_home_and_foreign_prohibited"));

		mCoA->setTypeUseMCoA( mCoA->par("TypeUseMCoA")  ) ;
		mCoA->setDeregisterALL(mCoA->par("deregisterALL"));

		EV << "[MCOA] >>>>>>> MCoA for this topology is " << mCoA->getProhibited() << endl;
		EV << "[MCOA] >>>>>>> MCoA Bulk Reg for this topology is " << mCoA->getBulk_reg_prohibited() << endl;
		EV << "[MCOA] >>>>>>> MCoA sim Home and Foreign for this topology is " << mCoA->getMc_sim_home_and_foreign_prohibited() << endl;
		EV << "[MCOA] >>>>>>> MCoA Type Use of MCoA  " << mCoA->getTypeUseMCoA() << endl;

		mipv6sm = new XMIPv6SM();
	}

    // We have to wait until the 4th stage (stage=3) with scheduling messages,
    // because interface registration and IPv6 configuration takes places
    // in the first two stages.
	else if (stage==3)
    {
        ift = InterfaceTableAccess().get();
        ipv6nd = IPv6NeighbourDiscoveryAccess().get(); //Zarrar Yousaf 17.07.07

        if ( rt6->isMobileNode() )
        {
			bul = BindingUpdateListAccess().get();  // Zarrar Yousaf 31.07.07
			bc = NULL;

        }
		else
		{
			bc = BindingCacheAccess().get(); // Zarrar Yousaf 31.07.07
			bul = NULL;
		}

        //WATCH_VECTOR(cnList);

        //WATCH_MAP(interfaceCoAList);
        //WATCH_MAP(cnListBIDs);
        WATCH_MAP(CoABIDs);
        //WATCH_MAP(cnListBIDs);


        //statistics
        statVectorBUtoHA.setName("BU to HA");
		statVectorBUtoCN.setName("BU to CN");
		statVectorBUtoMN.setName("BU to MN");
		statVectorBAtoMN.setName("BA to MN");
		statVectorBAfromHA.setName("BA from HA");
		statVectorBAfromCN.setName("BA from CN");
		statVectorHoTItoCN.setName("HoTI to CN");
		statVectorCoTItoCN.setName("CoTI to CN");
		statVectorHoTtoMN.setName("HoT to MN");
		statVectorCoTtoMN.setName("CoT to MN");
		statVectorHoTfromCN.setName("HoT from CN");
		statVectorCoTfromCN.setName("CoT from CN");



     }
}


void xMIPv6::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() )
    {
        EV << "Self message received!\n";


        if (msg->getKind()==MK_SEND_PERIODIC_BU)
        {
            EV << "Periodic BU Timeout Message Received\n";
            sendPeriodicBU(msg);
        }
        else if (msg->getKind()==MK_SEND_PERIODIC_BR)
        {
            EV << "Periodic BRR Timeout Message Received\n";
            sendPeriodicBRR(msg);
        }
        else if (msg->getKind()==MK_SEND_TEST_INIT) // 28.08.07 - CB
        {
        	EV << "HoTI/CoTI Timeout Message Received\n";
        	sendTestInit(msg);
        }
        else if (msg->getKind()==MK_BUL_EXPIRY) // 12.06.08 - CB
        {
        	EV << "BUL Expiry Timeout Message Received\n";
        	handleBULExpiry(msg);
        }
        else if (msg->getKind()==MK_BC_EXPIRY) // 12.06.08 - CB
        {
        	EV << "BC Expiry Timeout Message Received\n";
        	handleBCExpiry(msg);
        }
        else if ( msg->getKind() == MK_TOKEN_EXPIRY ) // 11.07.08 - CB
        {
        	EV << "RR token expired" << endl;
        	handleTokenExpiry(msg);
        }
        else if ( msg->getKind() == MK_MCOA_CLEAN_AT_HOME ) // Bruno Sousa
		{
			EV << "to perform Clean" << endl;
			perform_clean_at_home(msg);
		}
        else
            error("Unrecognized Timer");//stops sim w/ error msg.
    }
    // Zarrar Yousaf @ CNI Dortmund Uni on 29.05.07
    // if its a MIPv6 related mobility message
    else if ( dynamic_cast<MobilityHeader*>(msg) )
    {
    	EV <<" Received MIPv6 related message" << endl;
        IPv6ControlInfo *ctrlInfo = check_and_cast<IPv6ControlInfo*>(msg->removeControlInfo());
        MobilityHeader *mipv6Msg = (MobilityHeader*)(msg);
        processMobilityMessage(mipv6Msg, ctrlInfo);
	}
    // CB on 29.08.07
    // normal datagram with an extension header
    else if ( dynamic_cast<IPv6Datagram*>(msg) )
    {
    	IPv6ExtensionHeader* eh = (IPv6ExtensionHeader*) msg->getContextPointer();

    	if ( dynamic_cast<IPv6RoutingHeader*>(eh) )
    		processType2RH( (IPv6Datagram*) msg, (IPv6RoutingHeader*) eh);
    	else if ( dynamic_cast<HomeAddressOption*>(eh) )
    		processHoAOpt( (IPv6Datagram*) msg, (HomeAddressOption*) eh);
    	else
    		opp_error("Unknown Extension Header.");
    }
    else
        opp_error("Unknown message type received.");
}


void xMIPv6::processMobilityMessage(MobilityHeader* mipv6Msg, IPv6ControlInfo* ctrlInfo)
{
	EV <<"Processing of MIPv6 related mobility message" << endl;

	if ( dynamic_cast<BindingUpdate*>(mipv6Msg) )
	{
		EV <<"Message recognised as BINDING UPDATE (BU) From: " << ctrlInfo->getSrcAddr() << "  to: " << ctrlInfo->getDestAddr()  << endl;
		//EV << "\n<<<<<<<<Giving Control to processBUMessage()>>>>>>>\n";
		BindingUpdate *bu = (BindingUpdate*) mipv6Msg;
		processBUMessage(bu, ctrlInfo);
	}
	else if ( dynamic_cast<BindingAcknowledgement*>(mipv6Msg) )
	{
		EV <<"Message recognised as BINDING ACKNOWLEDGEMENT (BA)" << endl;
		//EV << "\n<<<<<<<<Giving Control to processBAMessage()>>>>>>>\n";
		BindingAcknowledgement *ba = (BindingAcknowledgement*) mipv6Msg;
		processBAMessage(ba, ctrlInfo);
	}
	// 28.08.07 - CB
	else if ( dynamic_cast<HomeTestInit*>(mipv6Msg) )
	{
		EV <<"Message recognised as HOME TEST INIT (HoTI)" << endl;
		processHoTIMessage( (HomeTestInit*) mipv6Msg, ctrlInfo);
	}
	else if ( dynamic_cast<CareOfTestInit*>(mipv6Msg) )
	{
		EV <<"Message recognised as CARE-OF TEST INIT (CoTI)" << endl;
		processCoTIMessage( (CareOfTestInit*) mipv6Msg, ctrlInfo);
	}
	else if ( dynamic_cast<HomeTest*>(mipv6Msg) )
	{
		EV <<"Message recognised as HOME TEST (HoT)" << endl;
		processHoTMessage( (HomeTest*) mipv6Msg, ctrlInfo );
	}
	else if ( dynamic_cast<CareOfTest*>(mipv6Msg) )
	{
		EV <<"Message recognised as CARE-OF TEST (CoT)" << endl;
		processCoTMessage( (CareOfTest*) mipv6Msg, ctrlInfo );
	}
	else if ( dynamic_cast<BindingRefreshRequest*>(mipv6Msg) )
	{
		EV <<"Message recognised as Binding Refresh Request" << endl;
		processBRRMessage( (BindingRefreshRequest*) mipv6Msg, ctrlInfo );
	}
	else
	{
		EV <<"Unrecognised mobility message... Dropping" << endl;
		delete ctrlInfo;
		delete mipv6Msg;
	}
}


void xMIPv6::initiateMIPv6Protocol(InterfaceEntry *ie, IPv6Address& CoA)
{
	Enter_Method_Silent(); // can be called by NeighborDiscovery module

	//trigger MIPv6 once.
	//if (!mipv6sm->getMIPv6triggered() || (!mCoA->getProhibited() && mCoA->getTypeUseMCoA() != MCOA_TUN_ALL_ADR_ALL)){
	if (!mipv6sm->getMIPv6triggered() ){
		if( !( ie->isLoopback() ) && rt6->isMobileNode() )
		{
			EV << "Initiating Mobile IPv6 protocol..  for " << CoA << endl;


			// The MN is supposed to send a BU to the HA after forming a CoA
			IPv6Address haDest = ie->ipv6Data()->getHomeAgentAddress(); // HA address for use in the BU for Home Registration

			if (!mCoA->getProhibited()){
				KeyMCoABind keyAux =  KeyMCoABind(CoA,get_and_calcBID(CoA, ie), haDest );

				if (mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_ALL || mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_SINGLE_RR || mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_SINGLE_FIRST){
					//MCoAcreateBUTimer(keyAux, haDest, ie, false); //register all the CoA
					MCoAcreateBUTimer(keyAux, haDest, ie, true); //register all the CoA
					//MIPv6triggered = true;
				}  else{
					MCoAcreateBUTimer(keyAux, haDest, ie, false); //register all the CoA
				}


			}else {
				/*
				 * Regular MIPv6
				 */

				KeyMCoABind keyMCoA = KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, haDest);

				createBUTimer(keyMCoA, haDest, ie);
			}

			// RO with CNs is triggered after receiving a valid BA from the HA
		}

		// a movement occured -> BUL entries for CNs not valid anymore
		IPv6Address HoA = ie->ipv6Data()->getMNHomeAddress();
		//for(itCNList = cnList.begin(); itCNList != cnList.end(); itCNList++) // run an iterator through the CN map
		for (CNListBIDs::iterator it = cnListBIDs.begin();
				 it != cnListBIDs.end();
				 it++)
		{

			//IPv6Address cn = *(itCNList);
			IPv6Address cn = (*it).first;
			std::vector<int> aBIDs = (*it).second;
			std::vector<int>::iterator bit;

			for (CoABIDList::iterator itCoA = CoABIDs.begin();
					itCoA != CoABIDs.end() ;
					itCoA++){

				int auxBID = itCoA->second;
				updateCnList(cn, auxBID); // to assure that CN has also all the CoAs in the list to regestir.

				/*
				 * for standard MIPv6 the vector should only have one BID.
				 */
				IPv6Address auxCoA = get_adr_from_bid(auxBID);

				KeyMCoABind keyM;
				if (!mCoA->getProhibited()){
					keyM = KeyMCoABind(auxCoA , auxBID, cn );
				}else {
					keyM =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID , cn );
				}


				if (bul->isInBindingUpdateList(keyM)){
					//bul->resetBindingCacheEntry(*bulEntry);
					tunneling->destroyTunnelForExitAndTrigger(HoA, cn);

					clear_and_remove_Binding(keyM, ie);
				}
			}
		}

		/*
		 * Bruno Sousa
		 *
		 * When this method is invoked, for sure, that MN is leaving Home network, at least on
		 * a single interface instance.
		 */
		mipv6sm->TRG_MIPv6init();
		//ie->ipv6Data()->setReturningHome(false);

	}else {
		EV << "MIPv6 has already been triggered, sorry... ignoring new CoA event " << CoA  << endl;

		// Register only in the HA???
		if (!mCoA->getProhibited() && mCoA->getTypeUseMCoA() != MCOA_TUN_SINGLE_ADR_SINGLE){



			EV << "Initiating Mobile IPv6 protocol on a second(or more) try  for " << CoA << endl;

			// The MN is supposed to send a BU to the HA after forming a CoA
			IPv6Address haDest = ie->ipv6Data()->getHomeAgentAddress(); // HA address for use in the BU for Home Registration

			KeyMCoABind keyAux =  KeyMCoABind(CoA,get_and_calcBID(CoA, ie), haDest );

			// Create timer only for the current CoA
			MCoAcreateBUTimer(keyAux, haDest, ie, false); //register all the CoA

			int numAdr = ie->ipv6Data()->getAddresses().size();
			for (int j=0; j< numAdr;j++){
				IPv6Address auxAdr  = ie->ipv6Data()->getAddress(j);

				if (auxAdr.isGlobal()){
					if (fetchBUTransmitIfEntry(ie, auxAdr) ==NULL){
						//send
						KeyMCoABind keyAux1 =  KeyMCoABind(auxAdr,get_and_calcBID(auxAdr, ie), haDest );
						MCoAcreateBUTimer(keyAux1, haDest, ie, false); //register all the CoA
						EV << "MIPv6 Procedure starting for address " << auxAdr << endl;
					}else {
						EV << "MIPv6 Procedure already started for address " << auxAdr << endl;
						// assume it was already sent.
					}
				}
			}
		}
	}
}


/**
 * This method destroys the HA tunnel associated to the previous CoA
 * and sends an appropriate BU to the HA.
 */
void xMIPv6::returningHome(const IPv6Address& CoA, InterfaceEntry* ie)
{
	//Enter_Method_Silent(); // can be called by NeighborDiscovery module

	/*11.5.4
	  A mobile node detects that it has returned to its home link through
	  the movement detection algorithm in use (Section 11.5.1), when the
	  mobile node detects that its home subnet prefix is again on-link.*/

	EV << "MIPv6 Returning home procedure... with CoA=" << CoA << endl;


	// cancel timers, 14.9.07 - CB

	// eventually we could have some unacknowledged BUs
	// we have to cancel these: first the one for the Home Agent...
	const IPv6Address& HA = ie->ipv6Data()->getHomeAgentAddress();


	KeyMCoABind   keyMCoA;
	if (!mCoA->getProhibited()){
		keyMCoA =  KeyMCoABind(CoA, get_and_calcBID(CoA, ie), HA); // Based on the Home Agent Address.
	}else {
		keyMCoA = KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, HA); // Based on the Home Agent Address.
	}

	if (bul->getMobilityState(keyMCoA) != BindingUpdateList::DEREGISTER && bul->getMobilityState(keyMCoA) != BindingUpdateList::NONE){

		if (!mipv6sm->getReturnedHome())
		  removeTimerEntries2( HA, ie->getInterfaceId());

		EV << "[MCOA] Destroying tunnel between " << CoA << " and "  << HA << endl;
		tunneling->destroyTunnel(CoA, HA);

		bul->setMobilityState(keyMCoA,  BindingUpdateList::DEREGISTER);
		// unregister binding from HA..
		createDeregisterBUTimer(keyMCoA, HA , ie);

	}else{
		EV << "[MCOA] Already Started the Deregistration for this address in HA " << keyMCoA << endl;
	}
	EV << "Deresgitered with HA... with CoA=" << CoA << endl;


	for (CNListBIDs::iterator it = cnListBIDs.begin();
				 it != cnListBIDs.end();
				 it++)
	{

		IPv6Address cn = (*it).first;
		std::vector<int> aBIDs = (*it).second;
		std::vector<int>::iterator bit;

		// we first cancel potential timers for the respective CN
		if (!mipv6sm->getReturnedHome())
		  removeTimerEntries2(cn, ie->getInterfaceId());

		keyMCoA.setDestBID(cn);

		if (!mCoA->getProhibited()){

			EV << "[MCOA] ReturnHome signalling CN " << cn << ", " << keyMCoA.getBID() << " size " << aBIDs.size() << endl;

			mipv6sm->TRG_returnHome(ie->ipv6Data()->getMNHomeAddress());

			EV << "[MCOA] Destroying tunnel between MN and CN " << keyMCoA.getAddr() << " and "  << cn << endl;

			tunneling->destroyTunnel(cn,keyMCoA.getAddr(), ie->ipv6Data()->getMNHomeAddress() ); // for T2RH only in CN
			tunneling->destroyTunnel(keyMCoA.getAddr(), ie->ipv6Data()->getMNHomeAddress(), cn ); // for HA_OpT

			//mipv6sm->setReturnedHome(true);

			if (bul->isInBindingUpdateList(keyMCoA)){
				BindingUpdateList::BindingUpdateListEntry* bulEntry = bul->lookup2(keyMCoA);
				ASSERT(bulEntry!=NULL);
				bulEntry->state = BindingUpdateList::DEREGISTER;

				//create Deregister timer for CN.
				createDeregisterBUTimer(keyMCoA, cn , ie);
				//checkForBUtoCN(keyMCoA, *bulEntry, ie);
			}else {
				EV << "TRYING to delete non existent binding " << keyMCoA << endl;
			}
		}else{
			/*
			 * StandardMIPv6
			 */
			if (!mipv6sm->getReturnedHome()){

				keyMCoA.setAddr(IPv6Address::UNSPECIFIED_ADDRESS);
				keyMCoA.setBID(MCOA_UNSIGNED_BID);

				if ( bul->isInBindingUpdateList( keyMCoA ) ) // 20.9.07 - CB
				{

					mipv6sm->setReturnedHome(true);
					mipv6sm->setMIPv6preferredAddr(ie->ipv6Data()->getMNHomeAddress());

					BindingUpdateList::BindingUpdateListEntry* bulEntry = bul->lookup(keyMCoA);
					ASSERT(bulEntry!=NULL);
					bulEntry->state = BindingUpdateList::DEREGISTER;

					checkForBUtoCN(keyMCoA, *bulEntry, ie);

					EV << "[MCOA] Destroying tunnel between MN and CN " << CoA << " and "  << cn << endl;
					tunneling->destroyTunnel(mipv6sm->getMIPv6preferredAddr(), ie->ipv6Data()->getMNHomeAddress(), cn ); // for HA_OpT

				}
			}else{
				EV << "[MCOA] Already Started the Deregistration for this address in CN (mipv6) " << keyMCoA << endl;
			}
		}
	}

	// It is returning home no functionalities of MIPv6 are required anymore.
	//MIPv6triggered = false;
	mipv6sm->setMIPv6triggered(false);

	EV << "Deresgitered with CNs... with CoA=" << CoA << endl;
}


void xMIPv6::returningHomeMCoA( InterfaceEntry* ie)
{
	Enter_Method_Silent(); // can be called by NeighborDiscovery module

	if (!mipv6sm->getReturnedHome()){
	IPv6Address CoA;



	EV << " BUL size" << bul->bindingUpdateList.size() << endl;

	if (!mCoA->getProhibited()){

			if (mCoA->getTypeUseMCoA() != MCOA_TUN_SINGLE_ADR_SINGLE){
				if (mCoA->getDeregisterALL() == MCoA::DEREGISTER_ALL_SIMULTANEOUSLY ||
						mCoA->getDeregisterALL() == MCoA::DEREGISTER_ONE_BY_ONE)
				{
					for (CoABIDList::iterator it = CoABIDs.begin(); it != CoABIDs.end(); it++){
						CoA = it->first;

						if ( ie->ipv6Data()->removeAddressInVec(CoA)){
							sync_preferred_address(CoA, ie);
							EV << "Returning Home removed Address CoA = " << CoA << " Successfully " << endl;
						}
					}


					for (CoABIDList::iterator it = CoABIDs.begin(); it != CoABIDs.end(); it++){
						CoA = it->first;
						returningHome(CoA, ie);
						EV << "Node returned home - removing CoA... " << CoA << endl;

						//CoABIDs.erase(CoA); // erase only on BA reception ???
						EV << "Now with " << CoABIDs.size() << " addresses" << endl;
					}

				//The node has returned home
				nb->fireChangeNotification(NF_MIPv6_MN_RETURNED_HOME, NULL);

				return;
				}
			}


		CoABIDList::iterator it = CoABIDs.begin();

		CoA = it->first;

		if ( ie->ipv6Data()->removeAddressInVec(CoA)){
			sync_preferred_address(CoA, ie);
			EV << "Returning Home removed Address CoA = " << CoA << " Successfully " << endl;
		}

		returningHome(CoA, ie);
		EV << "Node returned home - removing CoA... " << CoA << endl;

		//The node has returned home
		nb->fireChangeNotification(NF_MIPv6_MN_RETURNED_HOME, NULL);


	}else { // Regular MIPv6
		CoA = ie->ipv6Data()->removeAddress(IPv6InterfaceData::CoA);
		//CoA = ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::CoA);

		returningHome(CoA, ie);
		EV << "Node returned home - removing CoA... " << CoA << endl;

		//The node has returned home
		nb->fireChangeNotification(NF_MIPv6_MN_RETURNED_HOME, NULL);
	}

	}else{
		EV << "[MCOA] node has already started the return home operation on this interface " << endl;
	}
}




void xMIPv6::MCoAcreateBUTimer(KeyMCoABind &keyMCoA, const IPv6Address& buDest,InterfaceEntry* ie, const bool allBIDS)
{
	KeyMCoABind aux;


	if (allBIDS){

		for (CoABIDList::iterator it = CoABIDs.begin() ;
					it != CoABIDs.end();
					it++ )
		{
			aux.setAddr(it->first);
			aux.setBID(it->second);
			aux.setDestBID(buDest);

			EV << "[MCoA]-MCoAcreateBUTimer creating BU Timer for all CoAs --> " << aux << " just created! " << endl;
			createBUTimer(aux, buDest, ie);
		}

	}else {
		EV << "[MCoA]-MCoAcreateBUTimer creating BU Timer for only one CoA --> " << keyMCoA << " just created! " << endl;
		createBUTimer(keyMCoA, buDest, ie);

	}

}


void xMIPv6::createBUTimer( KeyMCoABind &keyMCoA, const IPv6Address& buDest, InterfaceEntry* ie)
{
	EV << "[MCOA] BUTimer Bu Timer for " << keyMCoA.getDestBID() << ", " << keyMCoA.getBID() << " with CoA =" << keyMCoA.getAddr() << "?=" << buDest << endl;

	if (keyMCoA.getAddr() == ie->ipv6Data()->getMNHomeAddress()){

		EV << "Trying to set HOa as a CoA  " << keyMCoA.getAddr() << endl;
		eraseBID(keyMCoA.getAddr());
		return ;
	}
	// update 12.06.08 - CB
	// if we send a new BU we can delete any potential existing BUL expiry timer for this destination
	cancelTimerIfEntry(keyMCoA.getDestBID(), ie->getInterfaceId(), KEY_BUL_EXP, keyMCoA.getBID());

	BindingUpdateList::BindingUpdateListEntry* bulEntry = bul->fetch(keyMCoA,buDest); // CB, 10.10.08


	ASSERT(bulEntry!=NULL); // CB, 10.10.08
	if (bulEntry->state != BindingUpdateList::DEREGISTER)
		bulEntry->state = BindingUpdateList::REGISTER;

	// update lifetime, 14.9.07
	//if ( homeRegistration )
	uint lifetimebind;
	bool hflag;
	if ( buDest == ie->ipv6Data()->getHomeAgentAddress() ){ // update 12.06.08 - CB
		lifetimebind = ie->ipv6Data()->_maxHABindingLifeTime();
		hflag = true;
	}else {
		lifetimebind = ie->ipv6Data()->_maxHABindingLifeTime();
		hflag = false;
	}

	if ( bulEntry != NULL && bulEntry->state == BindingUpdateList::DEREGISTER ) {// Bruno Sousa
		createDeregisterBUTimer(keyMCoA, buDest, ie);
		EV << "[MCOA] sending Deregistration  " << keyMCoA << endl;
	}else{
		EV << "Creating BU " << keyMCoA << endl;
		createBUTimer(keyMCoA, buDest, ie, lifetimebind, hflag);
	}

}


void xMIPv6::createDeregisterBUTimer( KeyMCoABind &keyMCoA, const IPv6Address& buDest, InterfaceEntry* ie)
{
	/*11.5.4
	  The mobile node SHOULD then send a Binding Update to its home agent,
      to instruct its home agent to no longer intercept or tunnel packets
      for it. In this home registration, the mobile node MUST set the
      Acknowledge (A) and Home Registration (H) bits, set the Lifetime
      field to zero, and set the care-of address for the binding to the
      mobile node's own home address.  The mobile node MUST use its home
      address as the source address in the Binding Update.*/

	/*11.7.2
	   If the Binding Update is sent to the correspondent node, requesting
	   the deletion of any existing Binding Cache entry it has for the
	   mobile node, the care-of address is set to the mobile node's home
	   address and the Lifetime field set to zero.*/

	//createBUTimer(buDest, ie, 0, homeRegistration);
	// update 12.06.08 - CB
	createBUTimer(keyMCoA, buDest, ie, 0, buDest == ie->ipv6Data()->getHomeAgentAddress());
}


void xMIPv6::createBUTimer( KeyMCoABind &keyMCoA, const IPv6Address& buDest, InterfaceEntry* ie, const uint lifeTime, bool homeRegistration)
{
	Enter_Method("createBUTimer()");

	cMessage *buTriggerMsg = new cMessage("sendPeriodicBU", MK_SEND_PERIODIC_BU);

	// update 13.9.07 - CB
	// check if there already exists a BUTimer entry for this key
	KeyTimer key( keyMCoA.getDestBID(), ie->getInterfaceId(), KEY_BU, keyMCoA.getBID() );

	// fetch a valid TimerIfEntry obect
	BUTransmitIfEntry* buIfEntry = (BUTransmitIfEntry*) getTimerIfEntry(key, TRANSMIT_TYPE_BU);
	// TODO: Investigate problem witht he following line. : runtime error because of attempted message rescheduling
	//if (buIfEntry->timer != NULL){ //Bruno Sousa not cancelling first timer.
	 cancelAndDelete(buIfEntry->timer);
	//}

	buIfEntry->dest = keyMCoA.getDestBID();
	buIfEntry->ifEntry = ie;
	buIfEntry->timer = buTriggerMsg;

	// update 10.09.07 - CB
	// retrieve sequence number from BUL
	// if no entry exists, the method will return 0
	buIfEntry->buSequenceNumber = bul->getSequenceNumber(keyMCoA); //the sequence number gets initialized and stored here

	buIfEntry->lifeTime = lifeTime;

	/*11.8
	  If the mobile node is sending a Binding Update and does not have
	  an existing binding at the home agent, it SHOULD use
	  InitialBindackTimeoutFirstReg (see Section 13) as a value for the
	  initial retransmission timer.*/
	//if ( !bul->isInBindingUpdateList(buDest) )
	if ( !bul->isInBindingUpdateList(keyMCoA) )
		buIfEntry->ackTimeout = ie->ipv6Data()->_initialBindAckTimeoutFirst();//the backoff constant gets initialised here
	/*Otherwise, the mobile node should use the specified value of
	  INITIAL_BINDACK_TIMEOUT for the initial retransmission timer.*/
	else
		buIfEntry->ackTimeout = ie->ipv6Data()->_initialBindAckTimeout();  // if there's an entry in the BUL, use different value

	buIfEntry->homeRegistration = homeRegistration; // added by CB, 28.08.07

	buIfEntry->adrCoA = keyMCoA.getAddr();
	buIfEntry->BID    = keyMCoA.getBID();

	buTriggerMsg->setContextPointer(buIfEntry); // attaching the buIfEntry info corresponding to a particular address ith message

	// send BU now, 14.9.07 - CB
	//scheduleAt(buIfEntry->initScheduledBUTime, buTriggerMsg); //Scheduling a message which will trigger a BU towards buIfEntry->dest
	scheduleAt(simTime(), buTriggerMsg); //Scheduling a message which will trigger a BU towards buIfEntry->dest

	EV << "DBGTimer BU Timer created for " << keyMCoA.getDestBID() << " , " << buIfEntry->BID << " dest " << buIfEntry->dest << "  with CoA " << keyMCoA.getAddr()
	   << " at simtime " << simTime() << " with lifetime " << lifeTime  << " and in BuIfEntry " << buIfEntry->lifeTime
	   << " with sequenceNumber " << buIfEntry->buSequenceNumber << endl;

}


void xMIPv6::sendPeriodicBU(cMessage *msg)
{
	EV <<"Sending periodic BU message at time: " << simTime() << " seconds." << endl;
	BUTransmitIfEntry *buIfEntry = (BUTransmitIfEntry*) msg->getContextPointer(); //detaching the corresponding buIfEntry pointer
	EV << "### lifetime of buIfEntry=" << buIfEntry->lifeTime << " and seq#= " << buIfEntry->buSequenceNumber << endl;

	InterfaceEntry* ie = buIfEntry->ifEntry; //copy the ie info
	IPv6Address& buDest = buIfEntry->dest;
	IPv6Address buAdrCoA  = buIfEntry->adrCoA;
	int aBID = buIfEntry->BID;
	KeyMCoABind keyMCoA;

	if (!mCoA->getProhibited()){
		keyMCoA  = KeyMCoABind(buAdrCoA, aBID, buDest);
	}else {
		keyMCoA = KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, buDest); // Based on the Home Agent Address.
	}

	buIfEntry->presentSentTimeBU = simTime(); //records the present time at which BU is sent

	buIfEntry->nextScheduledTime = buIfEntry->presentSentTimeBU + buIfEntry->ackTimeout;
	/*11.8
	  The retransmissions by the mobile node MUST use an exponential back-
	  off process in which the timeout period is doubled upon each
	  retransmission*/
	buIfEntry->ackTimeout = (buIfEntry->ackTimeout)* 2;

	// update 12.9.07 - CB
	// moved to here, 24.9.07 - CB
	/*Each Binding Update MUST have a Sequence Number greater than the
	  Sequence Number value sent in the previous Binding Update to the same
	  destination address (if any). The sequence numbers are compared
	  modulo 2**16, as described in Section 9.5.1.*/
	buIfEntry->buSequenceNumber = (buIfEntry->buSequenceNumber+1) % 65536;


	// Added by CB, 28.08.07
	if ( !buIfEntry->homeRegistration ) // this BU goes to a CN
	{
		EV << "SEARCHING FOR COA in KEY " << keyMCoA << endl;
		//IPv6Address CoA = ie->ipv6()->globalAddress();
		//prtTimers();
		IPv6Address CoA = bul->getCoA(keyMCoA); // 24.9.07 - CB


		//TODO think of a good mechanism to obtain the appropriate/correct CoA
		// Problem 1: ie->ipv6()->globalAddress() retrieves the HoA
		// Problem 2: bul->getCoA(buDest) becomes a problem in case of Multihoming
		// Solution: globalAddress(TYPE_COA) ?

		int bindingAuthorizationData = bul->generateBAuthData(keyMCoA, CoA);
		EV << "SEARCHED FOR BA AUTH " << bindingAuthorizationData << " for key " << keyMCoA << " for dest" << buDest << endl;
		/* Bruno Sousa 2010/4/29
		 * [MCOA]
		 */

		int nOpts=0, nOptsBID=0;

		MobilityBIDOptions* mOpt = new MobilityBIDOptions();

		// By default add Binding Authorization data.
		MobOption_Binding_AuthorizationData* aDat = new MobOption_Binding_AuthorizationData();
		aDat->setAuthenticator(bindingAuthorizationData);
		aDat->setMobOptionType(OPTION_BINDING_AUTHORIZATION_DATA);
		aDat->setMobOptionLength(LEN_BINDING_AUTHORIZATION_DATA - LEN_MOBOPTS_HEADER_FIELDS);
		aDat->setPayloadLength(LEN_BINDING_AUTHORIZATION_DATA);

		nOpts++;

		if (!mCoA->getProhibited()){
			nOptsBID=set_mobilityoptions_for_cn(keyMCoA, ie, buDest, buIfEntry->lifeTime, CoA,  mOpt, aDat);
			//Bruno Sousa  -- decommet for no Bulk registration


		} //MCOA

		//EV << "[MCOA] >>>>>> send preparing to send in Home Registration " << nOpts << " MobilityOptions" <<endl ;
		if (bul->MCoABULentrytoUpdate(keyMCoA, buIfEntry->buSequenceNumber, buIfEntry->lifeTime)){
			createAndSendBUMessage(buDest, ie, buIfEntry->buSequenceNumber, buIfEntry->lifeTime, bindingAuthorizationData, aDat, mOpt, nOptsBID);
		}else{
			EV << "Entry in BUL not updated due to policies for CN!" << keyMCoA << " buLife=" << buIfEntry->lifeTime << " BUseq=" << buIfEntry->buSequenceNumber  << " performing clean!"<< endl;

			delete aDat;
			delete mOpt;
		}

		// statistic collection
		statVectorBUtoCN.record(1);
	}
	else
	{
		// TO the Home Agent


		IPv6Address CoA = buAdrCoA;
		int nOpts=0, nOptsBID=0;
		MobilityBIDOptions* mOpt = new MobilityBIDOptions();

		// By default add Binding Authorization data.
		MobOption_Binding_AuthorizationData* aDat = new MobOption_Binding_AuthorizationData();
		aDat->setAuthenticator(UNDEFINED_BIND_AUTH_DATA);
		aDat->setMobOptionType(OPTION_BINDING_AUTHORIZATION_DATA);
		aDat->setMobOptionLength(LEN_BINDING_AUTHORIZATION_DATA - LEN_MOBOPTS_HEADER_FIELDS);
		aDat->setPayloadLength(LEN_BINDING_AUTHORIZATION_DATA);

		nOpts++;

		//EV << "[MCOA] >>>>>> send MCoA starting in BU cn to set mobOpts of binding Autho " << endl;
		if (!mCoA->getProhibited()){
			nOptsBID=set_mobilityoptions_for_ha(keyMCoA, ie, buDest, buIfEntry->lifeTime, CoA,  mOpt, aDat);
		}

		if (bul->MCoABULentrytoUpdate(keyMCoA, buIfEntry->buSequenceNumber, buIfEntry->lifeTime)){
			createAndSendBUMessage(buDest, ie, buIfEntry->buSequenceNumber, buIfEntry->lifeTime, 0, aDat, mOpt, nOptsBID);
		}else{
			EV << "Entry in BUL not updated due to policies for HA!" << keyMCoA << " buLife=" << buIfEntry->lifeTime << " BUseq=" << buIfEntry->buSequenceNumber  << " performing clean!"<< endl;

			delete aDat;
			delete mOpt;
		}




		// statistic collection
		statVectorBUtoHA.record(1);
	}

	/*if ( buIfEntry->ackTimeout < ie->ipv6()->_maxBindAckTimeout() ) // update comparison operator, 12.9.07 - CB
	{
		//buIfEntry->presentBindAckTimeout = buIfEntry->nextBindAckTimeout; //reassign the timeout value
		//scheduleAt(buIfEntry->nextScheduledTime, msg);
	}
	else*/
	if ( ! (buIfEntry->ackTimeout < ie->ipv6Data()->_maxBindAckTimeout()) )
	{
		ev<<"Crossed maximum BINDACK timeout...resetting to predefined maximum." << endl;//buIfEntry->nextBindAckTimeout<<" ++++++\n";
		//ev<<"\n++++Present Sent Time: "<<buIfEntry->presentSentTimeBU<<" Present TimeOut: "<<buIfEntry->ackTimeout<<endl;
		//buIfEntry->nextScheduledTime = buIfEntry->presentSentTimeBU + buIfEntry->maxBindAckTimeout;
		buIfEntry->ackTimeout = ie->ipv6Data()->_maxBindAckTimeout();
		//buIfEntry->nextScheduledTime = ie->ipv6()->_maxBindAckTimeout();
		//ev<<"\n++++Next Sent Time: "<<buIfEntry->nextScheduledTime<<endl;//" Next TimeOut: "<<buIfEntry->nextBindAckTimeout<<endl;
		//scheduleAt(buIfEntry->nextScheduledTime, msg);
	}
	//EV << "DBGTimer Present Sent Time: " << buIfEntry->presentSentTimeBU <<", Present TimeOut: " << buIfEntry->ackTimeout <<  "  lifetime: "<< buIfEntry->lifeTime << endl;
	EV << "Next Sent Time: " << buIfEntry->nextScheduledTime << endl;//<<" Next TimeOut: "<<buIfEntry->nextBindAckTimeout<<endl;
	scheduleAt(buIfEntry->nextScheduledTime, msg);
}


int xMIPv6::set_mobilityoptions_for_cn(KeyMCoABind &keyMCoa, InterfaceEntry *ie, IPv6Address &buDest, uint lifetime, IPv6Address &CoA,
									MobilityBIDOptions *&mOpt, MobOption_Binding_AuthorizationData *&aDat)
{
	CapMCoA capnodes;
	int nOpts=0, nOptsBID=0;
	IPv6Address buAdrCoA = keyMCoa.getAddr();
	bool hflag = false; //home binding

	capnodes.m_prohibited = false;
	capnodes.mCoA_support = true;


	MobOption_Binding_Identifier_Mobility* aux = new MobOption_Binding_Identifier_Mobility();
	aux->setPayloadLength(LEN_BID_WITH_COA);
	aux->setMobOptionType(OPTION_BINDING_IDENTIFIER_MOBILITY);
	aux->setMobOptionLength(LEN_BID_WITH_COA - LEN_MOBOPTS_HEADER_FIELDS);
	aux->setHFlag(hflag); // BU is sent to CN

	if (!mCoA->getBulk_reg_prohibited()){ //CN may not support this.
		capnodes.m_bulk_reg_prohibited = false;
		capnodes.FlagOverwrite =false;

		int auxS = CoABIDs.size();
		mOpt->setMobOptsArraySize(auxS);

		KeyMCoABind  kkMCoA ;
		capnodes.m_bulk_reg_prohibited = true;
		capnodes.FlagOverwrite = false;


		//if (mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_ALL){ // TO Register all the addresses

		 if (mCoA->getTypeUseMCoA() != MCOA_TUN_SINGLE_ADR_SINGLE){ // TO Register all the addresses

			if (mCoA->getDeregisterALL()==MCoA::DEREGISTER_ONE_BY_ONE && lifetime==0){
				//This option is not working
				//Bruno Sousa 2010/07/09
				mOpt->setMobOptsArraySize(1);
				kkMCoA = KeyMCoABind(CoA, get_and_calcBID(CoA, ie), buDest);
				aux->setKMCoA(kkMCoA);

				mOpt->setMobOpts(nOptsBID, *aux);
				nOptsBID++;
				nOpts++;

			}else {

				for (CoABIDList::iterator it = CoABIDs.begin(); it != CoABIDs.end(); it++){

						IPv6Address ipaux = it->first;
						KeyMCoABind  kkMCoA ;

						EV << "[MCoA] DBG including in BU to CN " << ipaux << endl;

						//if (ipaux.isGlobal() && ie->ipv6Data()->getAddressType(ipaux) ==  IPv6InterfaceData::CoA)
						if (ipaux.isGlobal() )
						{
							kkMCoA = KeyMCoABind(ipaux, get_and_calcBID(ipaux, ie), buDest);
							aux->setKMCoA(kkMCoA);

							mOpt->setMobOpts(nOptsBID, *aux);
							nOptsBID++;
							nOpts++;
							//EV << "[MCOA] >>>>>> send BU message with BID " << aux->getBindingID() << " and CoA addr " << ipaux  <<endl ;
						}else {
							EV << "[MCOA] >>>>>> ignoring address " << ipaux << endl;
						}
				}
			}

		}else {
			//TODO:


		}

		if (mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_SINGLE_FIRST){ // TO Register First Address

			//Set the preferred Address
			if (!mipv6sm->getSetPreferedAddr()){
				ie->ipv6Data()->setPreferredAddress(buAdrCoA);
				mipv6sm->setSetPreferedAddr(true);
				mipv6sm->setMIPv6preferredAddr(ie->ipv6Data()->getPreferredAddress());
			}else{
				ie->ipv6Data()->setPreferredAddress(mipv6sm->getMIPv6preferredAddr());
			}
		}

		if(mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_SINGLE_RR){ // TO Register in Round Robin

			buAdrCoA = get_addr_randomly_from_BIDS(ie);
			if (buAdrCoA != IPv6Address::UNSPECIFIED_ADDRESS){
				//Set the preferred Address
				if (!mipv6sm->getSetPreferedAddr()){
					ie->ipv6Data()->setPreferredAddress(buAdrCoA);
					mipv6sm->setSetPreferedAddr(true);
					mipv6sm->setMIPv6preferredAddr(ie->ipv6Data()->getPreferredAddress());
				}else {
					ie->ipv6Data()->setPreferredAddress(mipv6sm->getMIPv6preferredAddr());
				}

			}else {
				EV << "The random Address was wrongly generated!" << endl;
			}

		}




		}//Bulk

		else {

			KeyMCoABind  kkMCoA ;
			capnodes.m_bulk_reg_prohibited = true;
			capnodes.FlagOverwrite = false;

			mOpt->setMobOptsArraySize(1);
			//aux->setCoA(buAdrCoA);
			aux->setHFlag(false); // BU is sent to HA
			//aux->setBindingID(get_and_calcBID(buAdrCoA));
			kkMCoA = KeyMCoABind(buAdrCoA, get_and_calcBID(buAdrCoA, ie), buDest);
			aux->setKMCoA(kkMCoA);

			mOpt->setMobOpts(nOptsBID, *aux);
			nOptsBID++;
			nOpts++;

			//Set the preferred Address
			//TODO: If no bulk support exist it is better to have the same system as with single registration (mipv6sm->setAddress
			ie->ipv6Data()->setPreferredAddress(buAdrCoA);
		}

		addCapabilitiesNode(buDest, capnodes);
		return (nOptsBID);
}







int xMIPv6::set_mobilityoptions_for_ha(KeyMCoABind &key, InterfaceEntry* ie, IPv6Address &buDest, uint lifetime, IPv6Address &CoA,
								MobilityBIDOptions *&mOpt, MobOption_Binding_AuthorizationData *&aDat)
{
	CapMCoA capnodes;
	int nOpts=0, nOptsBID=0;
	IPv6Address buAdrCoA = CoA;
	bool hflag= false;

	capnodes.m_prohibited = false;
	capnodes.mCoA_support = true;

	MobOption_Binding_Identifier_Mobility* aux = new MobOption_Binding_Identifier_Mobility();
	aux->setHFlag(hflag); // BU is sent to HA
	aux->setPayloadLength(LEN_BID_WITH_COA);
	aux->setMobOptionType(OPTION_BINDING_IDENTIFIER_MOBILITY);
	aux->setMobOptionLength(LEN_BID_WITH_COA - LEN_MOBOPTS_HEADER_FIELDS);

	if (!mCoA->getBulk_reg_prohibited()){ //Bulk Registration
		capnodes.m_bulk_reg_prohibited = false;
		capnodes.FlagOverwrite = false;

		int auxS = CoABIDs.size();
		mOpt->setMobOptsArraySize(auxS);
		KeyMCoABind  kkMCoA ;

		if (mCoA->getDeregisterALL()==MCoA::DEREGISTER_ONE_BY_ONE && lifetime==0){
			mOpt->setMobOptsArraySize(1);

			kkMCoA =  KeyMCoABind(CoA, get_and_calcBID(CoA, ie), buDest);
			aux->setKMCoA(kkMCoA);

			mOpt->setMobOpts(nOptsBID, *aux);
			nOptsBID++;
			nOpts++;

		}else {

			for (CoABIDList::iterator it = CoABIDs.begin(); it != CoABIDs.end(); it++){

					IPv6Address ipaux = it->first;
					EV << "[MCoA] DBG including in BU to HA " << ipaux << endl;

					if (ipaux.isGlobal() )
					{
						kkMCoA = KeyMCoABind(ipaux, get_and_calcBID(ipaux, ie), buDest);
						aux->setKMCoA(kkMCoA);

						mOpt->setMobOpts(nOptsBID, *aux);
						nOptsBID++;
						nOpts++;

					}else {
						EV << "[MCOA] >>>>>> ignoring address " << ipaux << endl;
					}
			}


			if (!mipv6sm->getSetPreferedAddr()){
				IPv6Address auxIP;
				if (mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_SINGLE_FIRST){
					CoABIDList::iterator it = CoABIDs.begin();
					auxIP = it->first;
				}

				if (mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_SINGLE_RR){
					auxIP = get_addr_randomly_from_BIDS(ie);
				}

				mipv6sm->setSetPreferedAddr(true);
				mipv6sm->setMIPv6preferredAddr(auxIP);
			}

		}

	}//Bulk Registration at the HOME Agent
	else {

		KeyMCoABind  kkMCoA ;
		capnodes.m_bulk_reg_prohibited = true;
		capnodes.FlagOverwrite = false;

		mOpt->setMobOptsArraySize(1);
		kkMCoA = KeyMCoABind(buAdrCoA, get_and_calcBID(buAdrCoA, ie), buDest);
		aux->setKMCoA(kkMCoA);

		mOpt->setMobOpts(nOptsBID, *aux);
		nOptsBID++;
		nOpts++;

		//Set the preferred Address
		//TODO: Bruno Check when Home Agent does not support Bulk registration.
		ie->ipv6Data()->setPreferredAddress(buAdrCoA);
	}

	addCapabilitiesNode(buDest, capnodes);
	return (nOptsBID);
}


void xMIPv6::createAndSendBUMessage(const IPv6Address& dest, InterfaceEntry* ie, const uint buSeq, const uint lifeTime, const int bindAuthData,
		MobOption_Binding_AuthorizationData *abAutho,
		MobilityBIDOptions *aBIDmob, const int nMobOpts)
{


	EV << "" << endl;
	EV <<"Creating and sending Binding Update " ;

	IPv6Address CoA = getMIPv6CoA(ie, dest);

	EV << " with CoA " << CoA << endl;

	if ( CoA.isUnspecified() ){
		CoA = ie->ipv6Data()->getPreferredAddress(); // in case a CoA is not availabile (e.g. returning home)
		EV << " SEnding message to preferred Addr " << CoA << endl;
	}

	BindingUpdate *bu = new BindingUpdate("Binding Update");

	/*11.7.1
	  To register a care-of address or to extend the lifetime of an
	  existing registration, the mobile node sends a packet to its home
	  agent containing a Binding Update, with the packet constructed as
	  follows:*/
	/*11.7.2
	 A Binding Update is created as follows:*/
	bu -> setMobilityHeaderType(BINDING_UPDATE);

	/*11.7.1
	  o  The value specified in the Lifetime field MUST be non-zero and
	     SHOULD be less than or equal to the remaining valid lifetime of
	     the home address and the care-of address specified for the
	     binding.*/
	/*6.1.7
	  Lifetime
      16-bit unsigned integer.  The number of time units remaining
      before the binding MUST be considered expired.  A value of zero
      indicates that the Binding Cache entry for the mobile node MUST be
      deleted.  (In this case the specified care-of address MUST also be
      set equal to the home address.)  One time unit is 4 seconds.
	 */
	bu -> setLifetime(lifeTime / 4);

	bu -> setSequence(buSeq);

	/*11.7.1
	  o  The Acknowledge (A) bit MUST be set in the Binding Update.*/
	bu -> setAckFlag(true);

	/*o  The Home Registration (H) bit MUST be set in the Binding Update.*/
	// set flag depending on whether the BU goes to HA or not - CB
	bu->setHomeRegistrationFlag( dest == ie->ipv6Data()->getHomeAgentAddress() ); // update CB 07.08.08

	/*11.7.1
	  o  If the mobile node's link-local address has the same interface
		 identifier as the home address for which it is supplying a new
	     care-of address, then the mobile node SHOULD set the Link-Local
	     Address Compatibility (L) bit.
	  o  If the home address was generated using RFC 3041 [18], then the
	     link local address is unlikely to have a compatible interface
	     identifier.  In this case, the mobile node MUST clear the Link-
	     Local Address Compatibility (L) bit.*/
	// The link identifiers are always the same in our simulations. As
	// long as this is not changing, we can stick to the value "true"
	bu -> setLinkLocalAddressCompatibilityFlag(true); // fine for now

	bu -> setKeyManagementFlag(false); // no IKE/IPsec available anyway

	/*11.7.1
	  o  The packet MUST contain a Home Address destination option, giving
	     the mobile node's home address for the binding.*/
	/*11.7.2
	  o  The home address of the mobile node MUST be added to the packet in
	     a Home Address destinationEV << "[MCOA] >>>> Setting key KeyMCOA" << HomeAddr << ", "<< BID << endl;
	//std::cout.flush(); option, unless the Source Address is
	     the home address.*/
	IPv6Address HoA = ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::HoA);
	ASSERT( !HoA.isUnspecified() );

	// As every IPv6 Datagram sending the BU has to have the Home Address Option, I have
	// made this field a part of BU message to ease my task of simulation...
	// this can be accessed from the InterfaceTable of the MN.
	bu->setHomeAddressMN(HoA) ;//HoA of MN


	/*11.7.2EV << "[MCOA] >>>> Setting key KeyMCOA" << HomeAddr << ", "<< BID << endl;
	//std::cout.flush();
	  o  The Mobility Header is constructed according to rules in Section
		 6.1.7 and Section 5.2.6, including the Binding Authorization Data
		 (calculated as defined in Section 6.2.7) and possibly the Nonce
		 Indices mobility options.*/
	bu->setBindingAuthorizationData(bindAuthData); // added for BU to CN, 28.08.07 - CB

	// Bruno Sousa 2010/4/29
	// Mobility Options are included...
	int sizeOpts=0, ci_mob=0;
	unsigned int ci;


	if (nMobOpts > 0 ){
		//TODO: Bruno-check Add nonce indices option
		bu->setMobBindingAuthorization(*abAutho);
		sizeOpts+= abAutho->getPayloadLength();
		bu->setMobBIDmobilityArraySize(aBIDmob->getMobOptsArraySize());

		for (ci=0; ci< aBIDmob->getMobOptsArraySize(); ci++){
			KeyMCoABind& keyMCoA = aBIDmob->getMobOpts(ci).getKMCoA();

			IPv6Address adrCoA = keyMCoA.getAddr();

			if (!adrCoA.isUnspecified() && adrCoA.isGlobal()){
				bu->setMobBIDmobility(ci_mob, aBIDmob->getMobOpts(ci));

				KeyMCoABind& keyMCoA = aBIDmob->getMobOpts(ci).getKMCoA();

				sizeOpts+= aBIDmob->getMobOpts(ci).getPayloadLength();


				EV<<"\n\n[MCOA] >>>>> send [in BU message] BU with dest " << keyMCoA.getDestBID() << "  and  BID " << keyMCoA.getBID()
						<< " for CoA "<< keyMCoA.getAddr() << " and sequenceNumber " << bu->getSequence()   <<  endl;

				/*11.7.1
				  When sending a Binding Update to its home agent, the mobile node MUST
				  also create or update the corresponding Binding Update List entry, as
				  specified in Section 11.7.2.*/
				updateBUL( bu, keyMCoA, dest, adrCoA, ie, simTime() );

				ci_mob++;
			}else {
				EV<<"[MCOA] >>>>>ignore Option with addr " << adrCoA  <<endl;
			}
		}

		bu->setMobBIDmobilityArraySize(ci_mob);

		EV<<"[MCOA-BU]>>>>> send nOptions included in BU "<<nMobOpts <<" with size"<< sizeOpts << " lifetime " << bu->getLifetime()  <<endl;

		//For this destination it is necessary to force Registrations overwriting
		NodesMCoACap::iterator it = nodesMCoACaps.find(dest);
		if (it != nodesMCoACaps.end()){
			if (it->second.FlagOverwrite){
				bu->setOverwriteFlag(true);
				EV << "[MCOA] Registrations for  " << dest << " are to be overwritten " << endl;
			}
		}

	}else{
		/*
		 * Regular MIPv6
		 */
		KeyMCoABind keyMCoA =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, dest);

		// update 13.09.07 - CB
		//int nonceIndicesSize = 0;
		if ( ! bu->getHomeRegistrationFlag() )
			sizeOpts += SIZE_NONCE_INDICES;

		//TODO: Check if this should not be removed.... Bruno

		// setting message size, 10.09.07 - CB
		//int bindAuthSize = 0;
		if (bindAuthData != UNDEFINED_BIND_AUTH_DATA)
			sizeOpts += SIZE_BIND_AUTH_DATA;  // (6.2.3 PadN = 16 bit) -> no padding required if nonces provided // TODO check whether nonces valid

		/*11.7.1
		  When sending a Binding Update to its home agent, the mobile node MUST
		  also create or update the corresponding Binding Update List entry, as
		  specified in Section 11.7.2.*/
		updateBUL( bu, keyMCoA, dest, CoA, ie, simTime() );
	}


	bu->setByteLength( SIZE_MOBILITY_HEADER + SIZE_BU + SIZE_HOA_OPTION + sizeOpts );

	/*11.7.1
	  When sending a Binding Update to its home agent, the mobile node MUST
	  also create or update the corresponding Binding Update List entry, as
	  specified in Section 11.7.2.*/
	/*updateBUL( bu, keyMCoA, dest, CoA, ie, simTime() ); */


	/*11.7.1
	  o  The care-of address for the binding MUST be used as the Source
	     Address in the packet's IPv6 header, unless an Alternate Care-of
	     Address mobility option is included in the Binding Update.  This
	     option MUST be included in all home registrations, as the ESP
	     protocol will not be able to protect care-of addresses in the IPv6
	     header.  (Mobile IPv6 implementations that know they are using
	     IPsec AH to protect a particular message might avoid this option.
	     For brevity the usage of AH is not discussed in this document.)*/
	/*11.7.2
	  o  The current care-of address of the mobile node MUST be sent either
		 in the Source Address of the IPv6 header, or in the Alternate
		 Care-of Address mobility option.
	  o  The Destination Address of the IPv6 header MUST contain the
	     address of the correspondent node.*/


	sendMobilityMessageToIPv6Module(bu, dest, CoA, ie->getInterfaceId());




	delete aBIDmob; //Clean up
	delete abAutho;
}


void xMIPv6::updateBUL(BindingUpdate* bu, KeyMCoABind &keyMCoA,  const IPv6Address& dest, const IPv6Address& CoA, InterfaceEntry* ie, const simtime_t sendTime)
{

	uint buLife = 4 * bu->getLifetime(); /* 6.1.7 One time unit is 4 seconds. */ // update 11.06.08 - CB
	uint buSeq = bu->getSequence();

	EV << "TO UPDATE BUL  with seq " << buSeq << endl;


	IPv6Address HoA = bu->getHomeAddressMN();

	// to point to the struct where i am globally recording the startisitcs for sent time and next sent time for the BU:
	//BUTransmitIfEntry *buIfEntry = fetchBUTransmitIfEntry(ie, dest);

	KeyTimer key( keyMCoA.getDestBID(), ie->getInterfaceId(), KEY_BU, keyMCoA.getBID() );
	EV << " TO SEARCH " <<   keyMCoA.getDestBID() << " with int " << ie->getInterfaceId() << endl;

	//prtTimers();

	TransmitIfList::iterator pos = ftimer(key );
	BUTransmitIfEntry *buIfEntry = (BUTransmitIfEntry*) (pos->second);

	if (buIfEntry == NULL) {
		EV << "No scheduled BU entry available! for KEY_BU " << dest << " , ->" << keyMCoA.getAddr() << ", " << keyMCoA.getBID() << endl ;

		prtTimers();
		return;
	}

	//ASSERT(bul);

	//if (bul->MCoABULentrytoUpdate(keyMCoA, buSeq)){
		bul->addOrUpdateBUL(keyMCoA, dest, HoA, CoA, buLife, buSeq, sendTime, ie->getInterfaceId());//, nextSentTime); //updates the binding Update List
		EV << "#### Updated BUL with lifetime=" << buLife << " and sequenceNumber=" << buSeq << endl;
	//}else{

	//}
}


xMIPv6::BUTransmitIfEntry* xMIPv6::fetchBUTransmitIfEntry(InterfaceEntry *ie, const IPv6Address& dest)
{
	// TODO use STL search algorithm

	// update 13.9.07 - CB
	for (TransmitIfList::iterator it=transmitIfList.begin(); it!=transmitIfList.end(); it++)
	{
		if ( dynamic_cast<BUTransmitIfEntry*>(it->second) )
		{
			BUTransmitIfEntry *buIfEntry = (BUTransmitIfEntry*) (it->second);
			if ( buIfEntry->ifEntry->getInterfaceId() == ie->getInterfaceId() && buIfEntry->dest == dest ) // update 5.9.07 - CB
				return buIfEntry;
		}
	}
	return NULL;
}


void xMIPv6::sendMobilityMessageToIPv6Module(cMessage *msg, const IPv6Address& destAddr,
    const IPv6Address& srcAddr, int interfaceId, simtime_t sendTime) // overloaded for use at CN - CB
{

	EV <<"Appending ControlInfo to mobility message\n";
    IPv6ControlInfo *controlInfo = new IPv6ControlInfo();
    controlInfo->setProtocol(IP_PROT_IPv6EXT_MOB); // specifies the next header value for the Mobility Header (=135)
    controlInfo->setDestAddr(destAddr);
    controlInfo->setSrcAddr(srcAddr);
    controlInfo->setHopLimit(255);
    controlInfo->setInterfaceId(interfaceId);
    msg->setControlInfo(controlInfo);

    EV <<"ControlInfo appended successfully. Sending mobility message to IPv6 module\n";

    EV << "controlInfo: DestAddr=" << controlInfo->getDestAddr()
       << " SrcAddr=" << controlInfo->getSrcAddr()
       << " InterfaceId=" << controlInfo->getInterfaceId() << endl;

	// TODO solve the HA DAD problem in a different way
	// (delay currently specified via the sendTime parameter)
	if ( sendTime > 0 )
		sendDelayed(msg, sendTime, "toIPv6");
	else
		send(msg,"toIPv6");
}





void xMIPv6::processBUMessage(BindingUpdate* bu, IPv6ControlInfo* ctrlInfo)
{


	EV << "Entered BU processing method" << endl;

	/*if ( ( !rt6->isMobileNode() && !rt6->isRouter() && !rt6->isHomeAgent() ) ||
		 ( rt6->isRouter() && rt6->isHomeAgent() && !rt6->isMobileNode() )
	   ) // if node is either HA or CN, only then a BA is sent otherwise not.
	*/
	// BA is not sent when node is a mobile node and not a HA at the same time
	if ( rt6->isMobileNode() && ! rt6->isHomeAgent() ) 	// rewrote condition to make it more clear - CB
	{
		EV << "Wrong Node: not HA or CN" << endl;
		if ( ev.isGUI() )
			bubble("Wrong Node: not HA or CN");
		delete bu;
		delete ctrlInfo;
		return;
	}

	BAStatus status;
	bool validBUMessage;
	int interfaceID = ctrlInfo->getInterfaceId();
	InterfaceEntry *ie = ift->getInterfaceById(interfaceID);

	validBUMessage = validateBUMessage(bu, ctrlInfo);

	if (validBUMessage)
	{
		EV << "[MCOA] >>> BU message is valid " << endl;

		IPv6Address& HoA = bu -> getHomeAddressMN();

		bool mcoaRegistered_with_success = false;
		bool mcoaDeregistered = false;

		IPv6Address& CoA = ctrlInfo->getSrcAddr();
		IPv6Address& destAddress = ctrlInfo->getDestAddr();
		uint buLifetime = bu->getLifetime() * 4; /* 6.1.7 One time unit is 4 seconds. */
		uint buSequence = bu->getSequence();
		bool homeRegistration = bu->getHomeRegistrationFlag();

		IPv6Address& MNHoA = bu->getHomeAddressMN();

		/*
		 * Multiple registrations are enabled. RFC5648 is to be run
		 */
		if (!mCoA->getProhibited()){ //
			EV << "[MCOA] >>> is Active for this node Home Agent? (" << rt6->isHomeAgent() <<")   Mobile Node ("<< rt6->isMobileNode() << ")  Router ("<< rt6->isRouter() <<")"  << endl;

			unsigned int ci=0;
			int  nMobOpts=0;
			int buBID;
			//bool use_bu_mcoa = false;
			//bool use_bu_mcoa_toCN = false;


			MobilityBIDOptions* mOpts = new MobilityBIDOptions();
			MobOption_Binding_Identifier_Mobility* auxOpt;


			/*
			 * TODO:
			 * This Option has some troubles when removing the entries from the bul
			 * as bul entry expires might exist.
			 */
			if (buLifetime==0 && mCoA->getDeregisterALL()==MCoA::DEREGISTER_ALL_SIMULTANEOUSLY) {

				if ( rt6->isHomeAgent()) {
					EV << "[MCOA] HA Receiving BU with lifetime = 0 ... processing " << endl;
				}else {
					EV << "[MCOA] CN Receiving BU with lifetime = 0 ... processing " << endl;
				}

				if (bc->deleteALLEntries() ) {mcoaDeregistered= true; }
				tunneling->destroyTunnels(destAddress);
				mcoaRegistered_with_success = true;


				//cancel timers
				removeTimerEntries2(destAddress,interfaceID);

			}else {

				mOpts->setMobOptsArraySize(bu->getMobBIDmobilityArraySize());
				EV << "[MCOA] Receiving BU with nOptions= " << bu->getMobBIDmobilityArraySize() << endl;
				for (ci=0;ci < bu->getMobBIDmobilityArraySize();ci++){

					auxOpt = &bu->getMobBIDmobility(ci);

					//EV << " MYOPTION IN " << auxOpt->getKMCoA();
					//KeyMCoABind keyBID = auxOpt->getKMCoA();
					KeyMCoABind keyBID = KeyMCoABind(auxOpt->getKMCoA().getAddr(),
													 auxOpt->getKMCoA().getBID(),
													 auxOpt->getKMCoA().getDestBID() );

					buBID = keyBID.getBID();
					IPv6Address  adrCoA = keyBID.getAddr();

					keyBID.setAddr(MNHoA); // In the Binding Cache the key is the HoA and BID tuple.
					keyBID.setDestBID(destAddress);


					/*
					 * Section 6.2
					 * If the Lifetime field in the Binding Update is set to zero, the
					  receiving node deletes the binding entry that corresponds to the
					  BID in the Binding Identifier mobility option.  If the receiving
					  node does not have an appropriate binding for the BID, it MUST
					  reject the Binding Update and send a Binding Acknowledgement with
					  status set to 133 [not home agent for this mobile node].
					 *
					 */
					if (buLifetime == 0){
						if( rt6->isHomeAgent()){
							EV << "[MCOA] HA Receiving BU with lifetime = 0 ... processing " << keyBID.getAddr() << endl;

							cancelTimerIfEntry(keyBID.getAddr(), interfaceID, KEY_BC_EXP, keyBID.getBID());

							// de-register binding
							if (!bc->deleteEntry(keyBID) && ! auxOpt->getHFlag()){ // Not HOME agent for BID and BID without H flag
								status = NOT_HA_FOR_THIS_MN; //enum defined in MobilityHeader.msg file
								uint baSeqNumber = bu->getSequence(); //the sequence number from Rxed BU is copied into BA.
								createAndSendBAMessage(destAddress, CoA, ctrlInfo, status,
										bu->getBindingAuthorizationData(), baSeqNumber, buLifetime,
										0, mOpts); // swapped src and dest, 4.9.07 - CB, update lifeTime 14.9.07 - CB
								EV << "Error: Not HA for this MN. Responding with appropriate BA..."<<endl;
								delete bu;
								delete ctrlInfo;
								return;
							}

							/*
							 * Section 6.2
							 *
							 * If the 'O' flag is set in the de-registering Binding Update, it is
								  ignored.  If the 'H' flag is set, the home agent stores a home
								  address in the Care-of Address field of the binding cache entry.
								  The home agent MUST follow the descriptions described in Section
								  5.6.
							 */
							//TODO: Check
							if (auxOpt->getHFlag()){
								bool existingBinding = bc->isInBindingCache(keyBID);
								EV << "[MCOA] >>>>> H-flag BID exist? ( " << existingBinding << ") with BID=" << keyBID.getBID() << endl;

								bc->addOrUpdateBC(keyBID, keyBID.getAddr(), buLifetime, buSequence, homeRegistration); // moved to there, 11.9.07 - CB

								// for both HA and CN we create a BCE expiry timer
								createBCEntryExpiryTimer(keyBID, keyBID.getAddr(), ift->getInterfaceById( ctrlInfo->getInterfaceId() ), simTime()+buLifetime);

								//TODO: Check section 5.6 for full behaviour of HA
							}

							// The registration with the lifetime = 0 is sucessful
							mcoaRegistered_with_success = true;
							mcoaDeregistered = true;
						}else { // for CN
							EV << "[MCOA] CN Receiving BU with lifetime = 0 ... processing "<< adrCoA << " and BID=" << keyBID.BID << endl;

							if (bc->deleteEntry(keyBID)){

								cancelTimerIfEntry(keyBID.getAddr(), interfaceID, KEY_BC_EXP, keyBID.getBID()); //Cancel the respective timer

								EV << "[MCOA] CN deleted in BC "<< adrCoA << " and BID=" << keyBID.BID << endl;
								mcoaRegistered_with_success = true;
								mcoaDeregistered = true;
								//bc->prtBindings();
							}
						}

						//destroy tunnels
						tunneling->destroyTunnel(destAddress, adrCoA, MNHoA);
					}

					if (buLifetime > 0){
						//EV << "[MCOA] >>>>> perform registration " << endl;

						/* Section 6.2
						 * If the 'O' flag is set in the Binding Update, the receiving
						   node removes all the existing bindings and registers the
						   received binding(s).
						 */
						if (bu->getOverwriteFlag()){
							//delete first, then add
							bc->deleteEntry(keyBID);
							//No matter the result, just create new ones.
							bc->addOrUpdateBC(keyBID, adrCoA, buLifetime, buSequence, homeRegistration); // moved to there, 11.9.07 - CB
							// for both HA and CN we create a BCE expiry timer
							createBCEntryExpiryTimer(keyBID, keyBID.getAddr(), ift->getInterfaceById( ctrlInfo->getInterfaceId() ), simTime()+buLifetime);
						}else {

							/*
							 * Section 6.2 -- Bruno Sousa
							 *  If the 'O' flag is unset in the Binding Update and the receiver
								 has a regular binding that does not have a BID for the mobile
								 node, it must not process the Binding Update.  The receiver
								 should send a Binding Acknowledgement with status set to [MCOA
								 NON-MCOA BINDING EXISTS].
							 */

							//TODO: Check this will always be true (as implemented) when MN is MCOA compliant
							//      and HA is not.
							KeyMCoABind auxKey =  KeyMCoABind(keyBID);
							auxKey.setBID(MCOA_UNSIGNED_BID);


							if (bc->isInBindingCache(auxKey, adrCoA)){ // The BID exist with the UNSIGNED VALUE
								status = MCOA_NON_MCOA_BINDING_EXISTS; //enum defined in MobilityHeader.msg file
								uint baSeqNumber = bu->getSequence(); //the sequence number from Rxed BU is copied into BA.
								createAndSendBAMessage(destAddress, CoA, ctrlInfo, status,
										bu->getBindingAuthorizationData(), baSeqNumber, buLifetime,
										0, mOpts); // swapped src and dest, 4.9.07 - CB, update lifeTime 14.9.07 - CB
								EV << "[MCOA] Error: NON MCOA BINDING EXISTS..." << endl;
								delete bu;
								delete ctrlInfo;
								return; // not process binding
							}


							/*
							 *	If the receiver already has a binding with the same BID but
							 *        different care-of address, it MUST update the binding and
							 *        respond with a Binding Acknowledgement with status set to 0
							 *        [Binding Update accepted].
							 *
							 *  If the receiver does not have a binding entry for the BID, it
								 registers a new binding for the BID and responds with a Binding
								 Acknowledgement with status set to 0 [Binding Update accepted].
							 *
							 *
							 */
							if (bc->isInBindingCacheOnlyBID(keyBID.getBID()) || !bc->isInBindingCache(keyBID)  ){

								EV << "[MCOA] >>>>> performed Successful registration of " << keyBID.getAddr()  << endl;


								bc->addOrUpdateBC(keyBID, adrCoA, buLifetime, buSequence, homeRegistration); // moved to there, 11.9.07 - CB
								// for both HA and CN we create a BCE expiry timer
								createBCEntryExpiryTimer(keyBID, keyBID.getAddr(), ift->getInterfaceById( ctrlInfo->getInterfaceId() ), simTime()+buLifetime);

								// Sucess
								mcoaRegistered_with_success= true;

								/*constructed as follows:
								  o  The Status field MUST be set to a value 0, indicating success.*/
								status = BINDING_UPDATE_ACCEPTED; //enum defined in MobilityHeader.msg file
								auxOpt->setStatus(BINDING_UPDATE_ACCEPTED);
							}
						}



						if ( rt6->isHomeAgent() ) // establish tunnel to MN - CB
						{
							IPv6Address& HA = destAddress;

							// All the addresses
							if (mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_ALL ||
								mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_SINGLE_FIRST ||
								mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_SINGLE_RR
							   ) {
								if (tunneling->findTunnel(HA, adrCoA, MNHoA) != 0){
									EV << "Tunnel exists already doing nothing " << endl;
								}else {
									// Do not delete the tunnel that might exist
									tunneling->destroyTunnel(HA, adrCoA);

									tunneling->createTunnel(IPv6Tunneling::NORMAL, HA, adrCoA, MNHoA);
									EV << "DBG created tunnel in HA to  " << adrCoA << " and " << MNHoA << endl;
								}
							}
						}
						else // CN, update 18.9.07 - CB
						{
							// we first destroy the already existing RH2 path if
							// there exists one
							IPv6Address& CNAddress = destAddress;

							/*
							 * AS all the addresses are registered leave open the possibility to use them
							 * as applications (or MIPv6) wants...
							 * Therefore, no distinction in the tunnels...
							 */

								// All the addresses
								if (mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_ALL ||
									mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_SINGLE_FIRST ||
									mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_SINGLE_RR
									)
								{

									if (tunneling->findTunnel(CNAddress, adrCoA, MNHoA) != 0){
										EV << "Tunnel exists for CN already doing nothing " << endl;
									}else {
										tunneling->destroyTunnel(CNAddress, adrCoA ,MNHoA);

										// establish RH2 pseudo-tunnel at correspondent node - CB
										tunneling->createTunnel(IPv6Tunneling::T2RH, CNAddress, adrCoA, MNHoA); // update 10.06.08 - CB

										EV << "DBG created tunnel in CN " << CNAddress << " to  " << adrCoA << " and " << MNHoA << endl;
									}

									// cancel existing Binding Refresh Request timer
									// (if there exists one)
									//cancelTimerIfEntry(MNHoA, interfaceID, KEY_BR, MCOA_UNSIGNED_BID);
									cancelTimerIfEntry(keyBID.getAddr(), interfaceID, KEY_BR, keyBID.getBID());
									KeyMCoABind keybrr = KeyMCoABind(adrCoA, keyBID.getBID(), CNAddress);
									createBRRTimer(keyBID.getAddr(), ie, buLifetime - BRR_TIMEOUT_THRESHOLD, keybrr); // 18.9.07 - CB

								}else{
									EV << "CN is ignoring address " << adrCoA << endl;
								}

						}
					}//lifetime > 0
					//EV << " MYOPTION OUT " << auxOpt->getKMCoA();
					mOpts->setMobOpts(nMobOpts, (*auxOpt) ); // Set on the end... of current iteration
					nMobOpts++;
				} //for
			}//lifetime=0 and with no options



			// Run through all the Mobility Options and registered with success
			if ((mcoaRegistered_with_success && bu->getAckFlag()) ||  (mcoaRegistered_with_success && mcoaDeregistered ) ){

				/*
				 * a Binding Acknowledgement is sent, all the
				 * Binding Identifier mobility options stored in the Binding Update MUST
				 * be copied to the Binding Acknowledgement except the Status field.
				 */
				status = BINDING_UPDATE_ACCEPTED; //enum defined in MobilityHeader.msg file
				uint baSeqNumber = bu->getSequence();
				//uint lifeTime = 0; // Bruno Sousa
				uint lifeTime = buLifetime;
				EV << "[MCOA-BA] Sending BA msg to " <<  destAddress << " CoA " << CoA  << " and lifetime " << buLifetime << endl;

				createAndSendBAMessage(destAddress, CoA, ctrlInfo, status, baSeqNumber,
						bu->getBindingAuthorizationData(), lifeTime,
						0, mOpts);
			}

			//bc->prtBindings();
		}else {

		/*
		 *  Standard MIPv6
		 *
		 */
		//Bruno Sousa 2010/5/4 MCOA
		KeyMCoABind  keyBID = KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, destAddress);



		// UPDATE, 4.9.07
		// handling for binding de-registration

		/*9.5.1
		  If the Lifetime specified in the Binding Update is zero or the
		  specified care-of address matches the home address for the
		  binding, then this is a request to delete the cached binding for
		  the home address. [...] If the Home Registration (H) bit is set
		  in the Binding Update, the Binding Update is processed according
		  to the procedure specified in Section 10.3.2; otherwise, it is
		  processed according to the procedure specified in Section 9.5.3.*/
		if ( (buLifetime == 0) || (CoA == HoA) )
		{
			// Check home registration flag -> not much difference in Section 10.3.2 and 9.5.3 for our purpose

			// de-register binding
			if ( rt6->isHomeAgent() && ! validateBUderegisterMessage(bu, ctrlInfo) && bc->getBCSize() > 0 ) // HAs have to validate the BU
			{
				/* If the receiving node has no entry marked as a home registration
				   in its Binding Cache for this mobile node, then this node MUST
				   reject the Binding Update and SHOULD return a Binding
				   Acknowledgement to the mobile node, in which the Status field is
				   set to 133 (not home agent for this mobile node).*/
				status = NOT_HA_FOR_THIS_MN; //enum defined in MobilityHeader.msg file
				uint baSeqNumber = bu->getSequence(); //the sequence number from Rxed BU is copied into BA.
				createAndSendBAMessage(destAddress, CoA, ctrlInfo, status,
						bu->getBindingAuthorizationData(), baSeqNumber, buLifetime); // swapped src and dest, 4.9.07 - CB, update lifeTime 14.9.07 - CB

				EV << "Error: Not HA for this MN. Responding with appropirate BA...\n";
				delete bu;
				delete ctrlInfo;
				return;
			}
			/*9.5.3
			  Any existing binding for the given home address MUST be deleted.  A
   			  Binding Cache entry for the home address MUST NOT be created in
   			  response to receiving the Binding Update.*/
			/*10.3.2
			  If the home agent does not reject the Binding Update as described
   			  above, then it MUST delete any existing entry in its Binding Cache
   			  for this mobile node.*/
			bc->deleteEntry(keyBID);

			/*In addition, the home agent MUST stop intercepting packets on the
			  mobile node's home link that are addressed to the mobile node*/
			// of course this is also true for CNs
			tunneling->destroyTunnelFromTrigger(HoA);

			// kill BC expiry timer
			//cancelTimerIfEntry(HoA, ctrlInfo->getInterfaceId(), KEY_BC_EXP, MCOA_UNSIGNED_BID); // No BID option
			//cancelTimerIfEntry(keyBID.getDestBID(), ctrlInfo->getInterfaceId(), KEY_BC_EXP, keyBID.getBID()); // No BID option

			cancelTimerIfEntry(keyBID.getDestBID(), ctrlInfo->getInterfaceId(), KEY_BC_EXP, keyBID.getBID()); // No BID option

			/*10.3.2
			  Then, the home agent MUST return a Binding Acknowledgement to the mobile node */
			/*9.5.4
			  o  If the Acknowledge (A) bit set is set in the Binding Update, a
      		  Binding Acknowledgement MUST be sent.*/
			if ( rt6->isHomeAgent() || bu->getAckFlag()  )
			{
				/*constructed as follows:
				  o  The Status field MUST be set to a value 0, indicating success.*/
				status = BINDING_UPDATE_ACCEPTED; //enum defined in MobilityHeader.msg file
				/*o  The Sequence Number field MUST be copied from the Sequence Number
		  		  given in the Binding Update.*/
				uint baSeqNumber = bu->getSequence();
				/*o  The Lifetime field MUST be set to zero.*/
				uint lifeTime = 0;

				/*//The following was omitted://
				  o  The Key Management Mobility Capability (K) bit is set or cleared
		  		  and actions based on its value are performed as described in the
		  		  previous section.  The mobile node's home address is used as its
		  		  new care-of address for the purposes of moving the key management
		  		  connection to a new endpoint.
				  o  The Binding Refresh Advice mobility option MUST be omitted.*/
				createAndSendBAMessage(destAddress, CoA, ctrlInfo, status, baSeqNumber,
						bu->getBindingAuthorizationData(), lifeTime); // swapped src and dest, 4.9.07 - CB

			}

			if ( ! rt6->isHomeAgent() ) // this is a CN, 18.9.07 - CB
			{
				// cancel existing Binding Refresh Request timer
				// (if there exists one)
				int interfaceID = ctrlInfo->getInterfaceId();
				//cancelTimerIfEntry(HoA, interfaceID, KEY_BR, MCOA_UNSIGNED_BID);
				cancelTimerIfEntry(keyBID.getDestBID(), interfaceID, KEY_BR, keyBID.getBID());


				delBIDCnList(keyBID.getDestBID(), keyBID.getBID());

				EV << "CN replying to BU with lifetime=0"  << endl;

				/*constructed as follows:
				  o  The Status field MUST be set to a value 0, indicating success.*/
				status = BINDING_UPDATE_ACCEPTED; //enum defined in MobilityHeader.msg file
				/*o  The Sequence Number field MUST be copied from the Sequence Number
				  given in the Binding Update.*/
				uint baSeqNumber = bu->getSequence();
				/*o  The Lifetime field MUST be set to zero.*/
				uint lifeTime = 0;
				createAndSendBAMessage(destAddress, CoA, ctrlInfo, status, baSeqNumber,
										bu->getBindingAuthorizationData(), lifeTime); // swapped src and dest, 4.9.07 - CB
			}

			EV << "Deregistered binding\n";
			bubble("Deregistered binding!");
		}
		else
		{
			// update 10.9.07 - CB

			// binding lifetime is nonzero
			/*9.5.1
			  If the Lifetime specified in the Binding Update is nonzero and the
			  specified care-of address is not equal to the home address for the
			  binding, then this is a request to cache a binding for the home
			  address. If the Home Registration (H) bit is set in the Binding
			  Update, the Binding Update is processed according to the procedure
			  specified in Section 10.3.1; otherwise, it is processed according
			  to the procedure specified in Section 9.5.2.*/
			if (homeRegistration)
			{
				/* 10.3.1
				   o  If the node implements only correspondent node functionality, or
				      has not been configured to act as a home agent, then the node MUST
				      reject the Binding Update.  The node MUST also return a Binding
				      Acknowledgement to the mobile node, in which the Status field is
				      set to 131 (home registration not supported).*/
				if ( ! rt6->isHomeAgent() )
				{
					status = HOME_REGISTRATION_NOT_SUPPORTED; //enum defined in MobilityHeader.msg file
					uint baSeqNumber = bu->getSequence();
					uint lifeTime = 0;
					createAndSendBAMessage(destAddress, CoA, ctrlInfo, status, baSeqNumber,
							bu->getBindingAuthorizationData(), lifeTime);


					delete bu;
					delete ctrlInfo;
					return;
				}
				else if ( ! rt6->isOnLinkAddress(HoA) ) // update 11.9.07 - CB
				{
					/*Else, if the home address for the binding (the Home Address field
					  in the packet's Home Address option) is not an on-link IPv6
					  address with respect to the home agent's current Prefix List, then
					  the home agent MUST reject the Binding Update and SHOULD return a
					  Binding Acknowledgement to the mobile node, in which the Status
					  field is set to 132 (not home subnet).*/
					status = NOT_HOME_SUBNET; //enum defined in MobilityHeader.msg file
					uint baSeqNumber = bu->getSequence();
					uint lifeTime = 0;
					createAndSendBAMessage(destAddress, CoA, ctrlInfo, status, baSeqNumber,
							bu->getBindingAuthorizationData(), lifeTime);


					delete bu;
					delete ctrlInfo;
					return;
				}
			}

			bool existingBinding = bc->isInBindingCache(keyBID);
			bc->addOrUpdateBC(keyBID, CoA, buLifetime, buSequence, homeRegistration); // moved to there, 11.9.07 - CB
			// for both HA and CN we create a BCE expiry timer
			createBCEntryExpiryTimer(keyBID, HoA, ift->getInterfaceById( ctrlInfo->getInterfaceId() ), simTime()+buLifetime);

			/*10.3.1
			  Regardless of the setting of the Acknowledge (A) bit in the Binding
			  Update, the home agent MUST return a Binding Acknowledgement to the
			  mobile node*/
			/*9.5.4
			  If the Acknowledge (A) bit set is set in the Binding Update, a
  			  Binding Acknowledgement MUST be sent.  Otherwise, the treatment
  			  depends on the below rule.*/
			if ( bu->getAckFlag() || rt6->isHomeAgent() )
			{
				/*10.3.1
				  The Status field MUST be set to a value indicating success.  The
      			  value 1 (accepted but prefix discovery necessary) MUST be used if
      			  the subnet prefix of the specified home address is deprecated, or
      			  becomes deprecated during the lifetime of the binding, or becomes
      			  invalid at the end of the lifetime.  The value 0 MUST be used
      			  otherwise.  For the purposes of comparing the binding and prefix
      			  lifetimes, the prefix lifetimes are first converted into units of
      			  four seconds by ignoring the two least significant bits.*/
				status = BINDING_UPDATE_ACCEPTED; //enum defined in MobilityHeader.msg file
				/*The Sequence Number field MUST be copied from the Sequence Number
      			  given in the Binding Update.*/
				uint baSeqNumber = bu->getSequence();
				/*The Lifetime field MUST be set to the remaining lifetime for the
				  binding as set by the home agent in its home registration Binding
				  Cache entry for the mobile node, as described above.*/
				//keyBID->setAddr(HoA);
				//keyBID->setBID(MCOA_UNSIGNED_BID);
				uint lifeTime = bc->getLifetime(keyBID);

				/* 10.3.1
				   Unless this home agent already has a binding for the given home
				   address, the home agent MUST perform Duplicate Address Detection [13]
				   on the mobile node's home link before returning the Binding
				   Acknowledgement.*/
				simtime_t sendTime;
				if ( rt6->isHomeAgent() )
					// HA has to do DAD in case this is a new binding for this HoA
					sendTime = existingBinding ? 0 : 1;
				else
					sendTime = 0;

				createAndSendBAMessage(destAddress, CoA, ctrlInfo, status, baSeqNumber,
						//bu->getBindingAuthorizationData(), 15, sendTime); // swapped src and dest, 4.9.07 - CB
						bu->getBindingAuthorizationData(), lifeTime, sendTime,
						NULL); // swapped src and dest, 4.9.07 - CB // corrected lifetime value 18.06.08 - CB

				/*If this Duplicate Address Detection fails for the given
				  home address or an associated link local address, then the home agent
				  MUST reject the complete Binding Update and MUST return a Binding
				  Acknowledgement to the mobile node, in which the Status field is set
				  to 134 (Duplicate Address Detection failed).*/
				// TODO
			}
			else // condition: ! bu->getAckFlag()
			{
				EV<<"BU Validated as OK: ACK FLAG NOT SET"<< endl;
				bubble ("!!!BU VALID --- ACK FLAG = False !!!");
			}

			if ( rt6->isHomeAgent() ) // establish tunnel to MN - CB
			{
				IPv6Address& HA = destAddress;

				// we first destroy the already existing tunnel if
				// there exists one
				tunneling->destroyTunnelForEntryAndTrigger(HA, HoA);

				tunneling->createTunnel(IPv6Tunneling::NORMAL, HA, CoA, HoA);
				//bubble("Established tunnel to mobile node.");
			}
			else // CN, update 18.9.07 - CB
			{
				// we first destroy the already existing RH2 path if
				// there exists one
				IPv6Address& CNAddress = destAddress;
				tunneling->destroyTunnelForEntryAndTrigger(CNAddress, HoA);

				// establish RH2 pseudo-tunnel at correspondent node - CB
				tunneling->createTunnel(IPv6Tunneling::T2RH, CNAddress, CoA, HoA); // update 10.06.08 - CB

				// cancel existing Binding Refresh Request timer
				// (if there exists one)
				int interfaceID = ctrlInfo->getInterfaceId();


				//cancelTimerIfEntry(HoA, interfaceID, KEY_BR, keyBID.getBID());
				cancelTimerIfEntry(keyBID.getDestBID(), interfaceID, KEY_BR, keyBID.getBID());

				// and then we initialize a (new) BRR timer that gets
				// fired as soon as the BU lifetime is closing to 0.
				// Then we send Binding Refresh Requests once again
				// until we receive a valid BU.
				// FOX uncommented BRR below

				/* */
				// Bruno Sousa 2010/6/12 Decommented code bellow
				//InterfaceEntry *ie = ift->getInterfaceById(interfaceID);
				//createBRRTimer(HoA, ie, buLifetime - BRR_TIMEOUT_THRESHOLD, keyBID); // 18.9.07 - CB
				KeyMCoABind keybrr = KeyMCoABind(CoA, keyBID.getBID(), CNAddress);
				createBRRTimer(keyBID.getAddr(), ie, buLifetime - BRR_TIMEOUT_THRESHOLD, keyBID); // 18.9.07 - CB
			}
		}

	  }//MCOA
	}
	else
	{
		EV << "BU Validation Failed: Dropping message"<<endl;
		bubble("BU Validation Failed: Dropping Packet");
	}



	delete bu;
	delete ctrlInfo;
}


bool xMIPv6::validateBUMessage(BindingUpdate *bu, IPv6ControlInfo *ctrlInfo)
{
	// Performs BU Validation according to RFC3775 Sec 9.5.1

	EV <<"\n<<<<<<<<<ROUTINE WHERE BU GETS VALIDATED>>>>>>>>>>>>>>><<\n";

	// ################################
	// modifed structure, 28.08.07 - CB
	// ################################
	//bool result = true;

	IPv6Address& src = ctrlInfo->getSrcAddr();
	IPv6Address& destAddress = ctrlInfo->getDestAddr();

	IPv6Address homeAddress = bu->getHomeAddressMN(); //confirm whether it is getHomeAddressMN() or simply homeAddress()

	uint seqNumber = bu->getSequence();//The seq Number of the recieved BU
	//uint bcSeqNumber = bc->readBCSequenceNumber(homeAddress); //The seq Number of the last recieved BU in the Binding cache
	uint bcSeqNumber = bc->readBCSequenceNumberOnlyAddr(homeAddress, seqNumber); //The seq Number of the last recieved BU in the Binding cache

	// restructured the following and removed "delete bu" - CB
	if ( !( src.isGlobal() && src.isUnicast() ) )
	{
		EV<<"BU Validation Failed: SrcAdress is not unicast Global !"<<endl;
		EV<<"Dropping unvalidated BU message"<<endl;
		bubble ("!! BU Validation Failed !!");
		return false;//result = false;
	}
	if ( ! (homeAddress.isGlobal() && homeAddress.isUnicast() ) )
	{
		EV<<"BU Validation Failed: Home Adress of MN is not unicast Global !"<<endl;
		bubble ("!! BU Validation Failed !!");
		EV<<"Dropping unvalidated BU message"<<endl;
		return false;//result = false;
	}
	/*9.5.1
	 This Sequence Number comparison MUST be performed modulo 2**16, i.e.,
	 the number is a free running counter represented modulo 65536.  A
	 Sequence Number in a received Binding Update is considered less than
	 or equal to the last received number if its value lies in the range
	 of the last received number and the preceding 32768 values, inclusive.*/
	else if ( ((bcSeqNumber % 65536) > seqNumber) ||
			  ((32768 + bcSeqNumber) % 65536 < seqNumber)
			) // update 10.9.07 - CB
	{
		EV<<"BU Validation Failed: Received Seq#: " << seqNumber << " is LESS THAN in BC: " << bcSeqNumber <<endl;
		bubble ("!! BU Validation Failed !!");
		EV<<"Dropping unvalidated BU message"<<endl;

		/*9.5.1
		  If the mobile node sends a sequence number which is not greater than
   		  the sequence number from the last valid Binding Update for this home
		  address, then the receiving node MUST send back a Binding
		  Acknowledgement with status code 135, and the last accepted sequence
		  number in the Sequence Number field of the Binding Acknowledgement.*/

		createAndSendBAMessage(destAddress, homeAddress, ctrlInfo, REGISTRATION_TYPE_CHANGE_DISALLOWED,
				bu->getBindingAuthorizationData(), bcSeqNumber, 0);


		return false;
	}

	// It was here the validation part of Auth Data
	// this is the CN validation part
	if (! bu->getHomeRegistrationFlag() )
	{

		//if ( bc->getHomeRegistration(homeAddress) != bu->getHomeRegistrationFlag() ) // update 10.9.07 - CB
		if ( bc->getHomeRegistrationOnlyAddr(homeAddress, seqNumber) != bu->getHomeRegistrationFlag() ) // update 10.9.07 - CB
		{
			/*9.5.1
			  If a binding already exists for the given home address and the home
			  registration flag has a different value than the Home Registration
			  (H) bit in the Binding Update, then the receiving node MUST send back
			  a Binding Acknowledgement with status code 139 (registration type
			  change disallowed).  The home registration flag stored in the Binding
			  Cache entry MUST NOT be changed.*/
			EV << "BU Validation Failed: home registration flag in binding cache has different value than in the binding update" << endl;
			createAndSendBAMessage(destAddress, homeAddress, ctrlInfo, REGISTRATION_TYPE_CHANGE_DISALLOWED,
					bu->getBindingAuthorizationData(), bcSeqNumber, 0,
					NULL);

			return false;
		}

		int homeToken = bc->generateHomeToken(homeAddress, 0); // TODO nonce
		int careOfToken = bc->generateCareOfToken(src, 0); // TODO nonce
		int bindAuthData = bc->generateKey(homeToken, careOfToken, src);

		// update 10.10.08 - CB
		if ( bu->getLifetime() == 0 ) // deregistration BU
		{
			EV << "homeToken=" << homeToken << ", careOfToken=" << careOfToken
				<< " , bindAuthData=" << bindAuthData << ", BU data=" << bu->getBindingAuthorizationData() << endl;

			//if ( (bu->getBindingAuthorizationData() != bindAuthData) && (bu->getBindingAuthorizationData() != homeToken) ) // this is quick and dirty -> TODO
			if ( (bu->getBindingAuthorizationData() != bindAuthData) ) // this is quick and dirty -> TODO
			{
				EV << "BU Validation Failed: Binding Authorization Data invalid!" << endl;
				return false;
			}
		}
		else // registration BU
		{
			EV << "homeToken=" << homeToken << ", careOfToken=" << careOfToken
							<< " , bindAuthData=" << bindAuthData << ", BU data=" << bu->getBindingAuthorizationData() << endl;

			if ( bu->getBindingAuthorizationData() !=  bindAuthData)
			{
				EV << "BU Validation Failed: Binding Authorization Data invalid!" << endl;
				return false;
			}
		}
	}


	//Bruno Sousa 2010/5/4
	if (!mCoA->getProhibited()){
		unsigned int ci=0;
		int nMobOpts=0;


		//It includes a BID option in the BU message
		if (bu->getMobBIDmobilityArraySize() > 0){

			/*
			 * Section 6.2
			 * When multiple Binding Identifier mobility options are present in
			 * the Binding Update, it is treated as bulk registration.  If the
			 * receiving node is a correspondent node, it MUST reject the Binding
			 * Update and return the status value set to [MCOA BULK REGISTRATION
			 * PROHIBITED] in the binding Acknowledgement.
			 *
			 * NOTE: If we use all the addresses, the CN might accept the Bulk Registration.
			 */
			if (! bu->getHomeRegistrationFlag() &&  bu->getMobBIDmobilityArraySize() > 1  && mCoA->getTypeUseMCoA() != MCOA_TUN_SINGLE_ADR_SINGLE){
				EV << "[MCOA] >>>> rcv mob OPTION CN received BULK registration with "  << bu->getMobBIDmobilityArraySize() << " BIDs" << endl;
				createAndSendBAMessage(destAddress, homeAddress, ctrlInfo, MCOA_BULK_REGISTRATION_PROHIBITED,
						bu->getBindingAuthorizationData(), bcSeqNumber, 0,
						NULL );

				return false;

			}

			/*
			 * Node is configured to not accept Bulk registrations.
			 */
			if (mCoA->getBulk_reg_prohibited()){
				EV << "[MCOA] >>>> Node is configured to not accept Bulk registrations " << endl;
				createAndSendBAMessage(destAddress, homeAddress, ctrlInfo, MCOA_BULK_REGISTRATION_PROHIBITED,
						bu->getBindingAuthorizationData(), bcSeqNumber, 0,
						NULL );

				return false;

			}


			MobilityBIDOptions* mOpts = new MobilityBIDOptions();
			MobOption_Binding_Identifier_Mobility* auxOpt;

			bool BIDOptValid;

			mOpts->setMobOptsArraySize(bu->getMobBIDmobilityArraySize());

			for (ci=0;ci < bu->getMobBIDmobilityArraySize();ci++){
				auxOpt = &bu->getMobBIDmobility(ci);
				mOpts->setMobOpts(nMobOpts, (*auxOpt) );
				nMobOpts++;

				BIDOptValid = validateBIDOption(*auxOpt, bu, ctrlInfo);
				if (!BIDOptValid) { return false; }
			}
		}
	} //else { // Regular MIPv6.

	//}

	/*
	 * Sender is using MCoA but receiver is configured to not support it.
	 *
	 * Note: Regular MIPv6 does not set Mobility BID options.
	 */
	if (bu->getMobBIDmobilityArraySize() > 0 && mCoA->getProhibited()){
		EV << "[MCOA] >>>> Node is configured to not accept MCoA registrations, sorry! " << endl;
		createAndSendBAMessage(src, homeAddress, ctrlInfo, MCOA_PROHIBITED,
				bu->getBindingAuthorizationData(), bcSeqNumber, 0,
				NULL );

		return false;
	}

	// If all the above tests are passed the Received BU is valid
	EV<<"BU validation passed"<<endl;
	if ( ev.isGUI() )
		bubble ("BU Validated");

	return true; //result;
}


bool xMIPv6::validateBUderegisterMessage(BindingUpdate *bu, IPv6ControlInfo *ctrlInfo)
{
	IPv6Address destAddr = ctrlInfo->getDestAddr();
	KeyMCoABind  auxkey;
	//HERE
	InterfaceEntry *ie =  ift -> getInterfaceById(ctrlInfo -> getInterfaceId());

	if (!mCoA->getProhibited()){
		auxkey  = KeyMCoABind(ctrlInfo->getSrcAddr(), get_and_calcBID(ctrlInfo->getSrcAddr(), ie), destAddr);
		//auxkey  = KeyMCoABind(bu->getHomeAddressMN(), get_and_calcBID(bu->getHomeAddressMN()), destAddr);
	}else {
		auxkey  =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID , destAddr);
	}


		EV << "Validating BuderesgiterMessage " << auxkey << endl;



	//}

	/*To begin processing the Binding Update, the home agent MUST perform
      the following test:

   	  o  If the receiving node has no entry marked as a home registration
      in its Binding Cache for this mobile node, then this node MUST
      reject the Binding Update and SHOULD return a Binding
      Acknowledgement to the mobile node, in which the Status field is
      set to 133 (not home agent for this mobile node).*/
	//return bc->isInBindingCache( bu->getHomeAddressMN() ) && bc->getHomeRegistration( bu->getHomeAddressMN() );

	//return bc->isInBindingCache( bu->getHomeAddressMN() ) && bc->getHomeRegistrationOnlyAddr( bu->getHomeAddressMN() , bu->getSequence()); //MCOA
    return bc->isInBindingCache( auxkey ) && bc->getHomeRegistration( auxkey); //MCOA
}


bool xMIPv6::validateBIDOption(MobOption_Binding_Identifier_Mobility& mobBID, BindingUpdate *bu, IPv6ControlInfo *ctrlInfo){

	IPv6Address& src = ctrlInfo->getSrcAddr();
	IPv6Address homeAddress = bu->getHomeAddressMN(); //confirm whether it is getHomeAddressMN() or simply homeAddress()

	uint bcSeqNumber = bc->readBCSequenceNumber(homeAddress); //The seq Number of the last recieved BU in the Binding cache

	//EV << "[MCOA] >>>> validating BID Option for " <<  homeAddress << " with BID=" << mobBID.getBindingID() << endl;

	/* Section 6.2
	 *
	 * The length value is examined.  The length value MUST be either 4,
     * 8, or 20 depending on the Care-of Address field.  If the length is
     * incorrect, the receiver MUST reject the Binding Update and return
     * the status value set to [MCOA MALFORMED].
	 */
	if (mobBID.getMobOptionLength()!= 4 && mobBID.getMobOptionLength()!= 8 && mobBID.getMobOptionLength()!= 20){
		EV << "[MCOA] >>>> rcv mob OPTION with Invalid Length " << mobBID.getMobOptionLength() <<" BID=" << mobBID.getKMCoA().getBID() << endl;
		createAndSendBAMessage(src, homeAddress, ctrlInfo, MCOA_MALFORMED,
				bu->getBindingAuthorizationData(), bcSeqNumber, 0);


		return false;
	}else{
		/*
		 * Section 6.2
		 * When the length value is either 8 or 20, the care-of address MUST
		 * be present in the Binding Identifier mobility option.  If the
         * unicast routable address [RFC3775] is not present in the Care-of
         * Address field, the receiver MUST reject the Binding Identifier
         * mobility option and return the status value set to [MCOA
         * MALFORMED].
		 */
		if (mobBID.getMobOptionLength()== 8 || mobBID.getMobOptionLength()== 20){
			if (mobBID.getKMCoA().getAddr().isUnspecified() || !mobBID.getKMCoA().getAddr().isUnicast()){
				EV << "[MCOA] >>>> rcv mob OPTION BID="<< mobBID.getKMCoA().getBID() <<" with invalid CoA address"  << endl;
				createAndSendBAMessage(src, homeAddress, ctrlInfo, MCOA_MALFORMED,
						bu->getBindingAuthorizationData(), bcSeqNumber, 0);


				return false;
			}
		}

	}
	return true;

}

void xMIPv6::createAndSendBAMessage(const IPv6Address& src, const IPv6Address& dest, IPv6ControlInfo* ctrlInfo, const BAStatus& baStatus,
		const uint baSeq, const int bindingAuthorizationData, const uint lifeTime, const simtime_t sendTime,
		MobilityBIDOptions *mBIDOpts)
{



	EV << "Entered createAndSendBAMessage() method" << endl;


	InterfaceEntry *ie = ift -> getInterfaceById(ctrlInfo -> getInterfaceId()); // To find the interface on which the BU was received

	// swapping src and destination for the ack packet
	//IPv6Address source = ie->ipv6()->linkLocalAddress();
	//IPv6Address destination = src;
	//IPv6Address src = ie ->ipv6()->linkLocalAddress();

	// uncommented the code above - we can use the swapped original src and
	// dest from the ctrlInfo as it is provided in the first two arguments
	// 4.9.07 - CB

	BindingAcknowledgement *ba = new BindingAcknowledgement("Binding Acknowledgement");
	ba -> setMobilityHeaderType(BINDING_ACKNOWLEDGEMENT);
	ba -> setStatus(baStatus);
	ba -> setSequenceNumber(baSeq); //this sequence number will correspond to the ACKed BU

	// we are providing lifetime as a parameter, 14.9.07 - CB
	ba -> setLifetime( lifeTime / 4 ); /* 6.1.8 ...in time units of 4 seconds... */

	/*9.5.4
	  If the Status field in the Binding Acknowledgement contains the value
	  136 (expired home nonce index), 137 (expired care-of nonce index), or
	  138 (expired nonces) then the message MUST NOT include the Binding
	  Authorization Data mobility option.  Otherwise, the Binding
	  Authorization Data mobility option MUST be included, and MUST meet
	  the specific authentication requirements for Binding Acknowledgements
	  as defined in Section 5.2.*/
	if ( ba->getStatus() != EXPIRED_HOME_NONCE_INDEX &&
		 ba->getStatus() != EXPIRED_CARE_OF_NONCE_INDEX &&
		 ba->getStatus() != EXPIRED_NONCES )
		ba->setBindingAuthorizationData(bindingAuthorizationData);

	/* Bruno Sousa 2010/4/29
	 * [MCOA]
	 */

	EV << "[MCOA] >>>>> BA message to send " << ba->getStatus()  << endl;


	if (ba->getStatus()== BINDING_UPDATE_ACCEPTED){

		//TODO: this code seems unsafe
		//      Also assuming all validations have been done previously.
		if (mBIDOpts!=NULL){
			int sizeOpts=0;

			//EV << "[MCOA] >>>>> BA message to include options "   << endl;
			if (mBIDOpts->getMobOptsArraySize()!=0) {

				//TODO: This option should come from Bu Options...

				// By default add Binding Authorization data.
				MobOption_Binding_AuthorizationData* aDat = new MobOption_Binding_AuthorizationData();
				aDat->setAuthenticator(bindingAuthorizationData);
				aDat->setMobOptionType(OPTION_BINDING_AUTHORIZATION_DATA);
				aDat->setMobOptionLength(LEN_BINDING_AUTHORIZATION_DATA - LEN_MOBOPTS_HEADER_FIELDS);
				aDat->setPayloadLength(LEN_BINDING_AUTHORIZATION_DATA);

				ba->setMobBindingAuthorization(*aDat);
				sizeOpts+= aDat->getPayloadLength();

				//EV << "[MCOA] >>>>> BA message including Option Authorization Data with size " << sizeOpts  << endl;



				ba->setMobBIDmobilityArraySize(mBIDOpts->getMobOptsArraySize());

				for(unsigned int ci=0; ci < mBIDOpts->getMobOptsArraySize() ; ci++ ){
					//TODO: check if this is the best approach to check if node is CN.
					if (!rt6->isHomeAgent()){ // Node is correspondent Node
						mBIDOpts->getMobOpts(ci).setStatus(0);
					}

					//TODO: implement status per Mobility Option (MCOA NOTCOMPLETE)
					// see section 6.2
					//
					ba->setMobBIDmobility(ci, mBIDOpts->getMobOpts(ci));
					sizeOpts+= mBIDOpts->getMobOpts(ci).getPayloadLength();
					//EV << "[MCOA] >>>>> BA message including Option BID with size " << sizeOpts  << endl;


				}
			}
			ba->setByteLength( SIZE_MOBILITY_HEADER + SIZE_BACK + sizeOpts );
		}else {

			// setting message size, 10.09.07 - CB
			int bindAuthSize = 0;
			if (bindingAuthorizationData != UNDEFINED_BIND_AUTH_DATA)
				bindAuthSize = SIZE_BIND_AUTH_DATA + 2; // Binding Auth. Data + 6.2.3 PadN = 16 bit

			ba->setByteLength( SIZE_MOBILITY_HEADER + SIZE_BACK + bindAuthSize );

		}
	}

	/*The rules for selecting the Destination IP address (and, if required,
	  routing header construction) for the Binding Acknowledgement to the
	  mobile node are the same as in the previous section.  When the Status
	  field in the Binding Acknowledgement is greater than or equal to 128
	  and the Source Address of the Binding Update is on the home link, the
	  home agent MUST send it to the mobile node's link layer address
	  (retrieved either from the Binding Update or through Neighbor
	  Solicitation).*/
	// TODO
	EV << "DBG-BA >>>>DEST -> " << dest << " SRC ->" << src << " lifetime " << ba->getLifetime()
	   << " BA Sequence " << ba->getSequenceNumber()
	   << endl;

	sendMobilityMessageToIPv6Module(ba, dest, src, ie->getInterfaceId(), sendTime);

	// statistic collection
	if ( rt6->isHomeAgent() )
		statVectorBAtoMN.record(1);
	else
		statVectorBAtoMN.record(2);


}


void xMIPv6::processBAMessage(BindingAcknowledgement* ba, IPv6ControlInfo* ctrlInfo)
{


	EV <<"\n<<<<<<<<<This is where BA gets processed>>>>>>>>>\n";
	//bool retransmitBU = false; // update 11.6.08 - CB
	IPv6Address& baSource = ctrlInfo->getSrcAddr();
	InterfaceEntry *ie = ift->getInterfaceById( ctrlInfo->getInterfaceId() ); //the interface on which the BAck was received


	CapMCoA capNode;

	if ( rt6->isMobileNode() )
	{
		if ( ! validateBAck(*ba, ctrlInfo) )
		{
			EV << "Discarding invalid BAck... from " << baSource <<  endl;
			delete ctrlInfo;
			delete ba;

			// statistic collection
			if ( baSource == ie->ipv6Data()->getHomeAgentAddress() )
				statVectorBAfromHA.record(3);
			else
				statVectorBAfromCN.record(3);

			return;
		}


		/*11.7.3
		  When a mobile node receives a packet carrying a valid Binding
		  Acknowledgement, the mobile node MUST examine the Status field as
		  follows:
		  o  If the Status field indicates that the Binding Update was accepted
		     (the Status field is less than 128), then the mobile node MUST
		     update the corresponding entry in its Binding Update List to
		     indicate that the Binding Update has been acknowledged; the mobile
		     node MUST then stop retransmitting the Binding Update.*/
		if ( ba->getStatus() < 128 )
		{
			// update 21.9.07 - CB
			EV << "DBG-BA Binding was accepted, with Sequence " << ba->getSequenceNumber() << endl;

			//if (!mCoA->getProhibited() && ba->getMobBIDmobilityArraySize() > 0){
			if (!mCoA->getProhibited() ){

				if (ba->getLifetime() == 0 ) { // BAck to deregistration BU
					MCOAprocessBAMessage_DeregALL(ba, ctrlInfo, ie, baSource);
				}

				unsigned int ci=0;
				int baBID, nMobOpts=0;
				MobilityBIDOptions* mOpts = new MobilityBIDOptions();
				MobOption_Binding_Identifier_Mobility* auxOpt;



				mOpts->setMobOptsArraySize(ba->getMobBIDmobilityArraySize());
				//EV << "DBG Got in BA nOpts "<< ba->getMobBIDmobilityArraySize() << endl;


				//bool run_ba_single = false;
				//bool run_ba_single_toCN = false;
				for (ci=0;ci < ba->getMobBIDmobilityArraySize(); ci++){
					//EV << "DBG processing Opt "<< ci <<" of  "  << ba->getMobBIDmobilityArraySize() << endl;


					auxOpt = &ba->getMobBIDmobility(ci);
					mOpts->setMobOpts(nMobOpts, (*auxOpt) );
					nMobOpts++;
					//baBID = auxOpt->getBindingID();

					KeyMCoABind &keyMCoA = auxOpt->getKMCoA();
					baBID = keyMCoA.getBID();

					// As the BU is obviously valid, we can remove the transmission timer for BU
					cancelTimerIfEntry(keyMCoA.getDestBID(), ie->getInterfaceId(), KEY_BU, baBID); // 11.06.08 - CB // Bruno Sousa 2010/5/13
					cancelTimerIfEntry(keyMCoA.getDestBID(), ie->getInterfaceId(), KEY_BUL_EXP, keyMCoA.getBID()); // 11.06.08 - CB // Bruno Sousa 2010/5/13

					if (ba->getLifetime() == 0 ) { // BAck to deregistration BU
						// delete the entry from the BUL
						EV << "DBG Removing entry in BUL " << keyMCoA.getAddr() << ", " << keyMCoA.getBID() << " destBID " << keyMCoA.getDestBID() << endl;

						//bul->prtBindings();
						if (bul->isInBindingUpdateList(keyMCoA)){

							clear_and_remove_Binding(keyMCoA, ie);

							perform_clean_coa(keyMCoA, baSource == ie->ipv6Data()->getHomeAgentAddress());


						}else{
							EV << "Trying to delete an entry in BUL that does not exist !" << endl;
						}
						// remove all timers related to this BA address
						removeTimerEntries2(keyMCoA.getDestBID(), ctrlInfo->getInterfaceId()); // update 10.10.08 - CB

						//Missing Statistics

					}else {
						// binding with lifeTime >0 was accepted
						MCOAprocessBAMessage_Normal(ba,ctrlInfo,ie, baSource, keyMCoA, ci);
					}
					//bul->prtBindings();
				}// end for
				//}//lifetime=0

				//clean up operation
				delete mOpts;

				//Update was sucessful BA Source node supports everything regarding MCoA!
				capNode.mCoA_support = true;
				capNode.m_prohibited = false;
				capNode.m_bulk_reg_prohibited = false;
				capNode.mc_sim_home_and_foreign_prohibited = false;
				capNode.FlagOverwrite = false;
				addCapabilitiesNode(baSource, capNode);

			}else {
				/*
				 *  ------------------------------------
				 *  Regular MiPV6 binding
				 *  ------------------------------------
				 */
				KeyMCoABind keyMCoA =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, baSource);

				// As the BU is obviously valid, we can remove the transmission timer for BU
				cancelTimerIfEntry(keyMCoA.getDestBID(), ie->getInterfaceId(), KEY_BU, keyMCoA.getBID()); // 11.06.08 - CB // Bruno Sousa 2010/5/13
				cancelTimerIfEntry(keyMCoA.getDestBID(), ie->getInterfaceId(), KEY_BUL_EXP, keyMCoA.getBID()); // 11.06.08 - CB // Bruno Sousa 2010/5/13

				if ( ba->getLifetime() == 0 ) // BAck to deregistration BU
				{
					EV << "PERFORMING DEREGISTRATION " << endl;
					if ( baSource == ie->ipv6Data()->getHomeAgentAddress() )
					{
						/*11.5.4
						  After receiving the Binding Acknowledgement for its Binding Update to
						  its home agent, the mobile node MUST multicast onto the home link (to
						  the all-nodes multicast address) a Neighbor Advertisement [12], to
						  advertise the mobile node's own link-layer address for its own home
						  address.*/
						ipv6nd->sendUnsolicitedNA(ie);

						// statistic collection
						statVectorBAfromHA.record(2);

					}else{
						deleteCnList(baSource, keyMCoA.getBID());
						statVectorBAfromCN.record(2);
					}

					removeCoAEntries();
					/*
					BindingUpdateList::BindingUpdateListEntry* entry = bul->lookup( keyMCoA);
					ASSERT(entry!=NULL);

					EV << "Destroying tunnel between MN and" << entry->careOfAddress << " dest tunnel " << baSource << endl;
					tunneling->destroyTunnel(entry->careOfAddress, baSource);
					*/

					// delete the entry from the BUL
					clear_and_remove_Binding(keyMCoA, ie);
					// remove all timers related to this BA address
					removeTimerEntries2(baSource, ctrlInfo->getInterfaceId()); // update 10.10.08 - CB



				}
				else
				{
					// binding with lifeTime >0 was accepted

					// moved the code below from sendBU(), 21.9.07 - CB
					// retrieve the appropriate BUL entry
					BindingUpdateList::BindingUpdateListEntry* entry = bul->lookup( keyMCoA);
					ASSERT(entry!=NULL);

					// establish tunnel, but only if we have not already acked the BU before
					if (entry->BAck == false && entry->destAddress == ie->ipv6Data()->getHomeAgentAddress() ) // BA from HA
					{
						removeCoAEntries(); // TODO would be better if this is done somewhere else or in a comletely different way
						ifBID auxIf;
						auxIf.iBID = keyMCoA.getBID();
						auxIf.ifID = ie->getInterfaceId();
						//interfaceCoAList[ie->getInterfaceId()] = entry->careOfAddress;
						interfaceCoAList[auxIf] = entry->careOfAddress;

						EV << "Creating tunnel between MN and HA CoA=" << entry->careOfAddress << " dest tunnel " << entry->destAddress << endl;
						tunneling->createTunnel( IPv6Tunneling::NORMAL, entry->careOfAddress, entry->destAddress ); // update 10.06.08 - CB
						//bubble("Established tunnel to home agent.");

						/**11.5.1
							After updating its home registration, the mobile
							node then updates associated mobility bindings in correspondent nodes
							that it is performing route optimization with as specified in Section
							11.7.2.*/
						// initiate RR for the CNs
						//for (itCNList = cnList.begin(); itCNList != cnList.end(); itCNList++) // run an iterator through the CN map
						for (CNListBIDs::iterator it = cnListBIDs.begin();
								 it != cnListBIDs.end();
								 it++)

						{
							IPv6Address cnDest = (*it).first;

							//entry->state = BindingUpdateList::RR;
							//if ( !bul->isValidBinding(cnDest) ) // to initiate HoTI/CoTI resending
							triggerRouteOptimization(cnDest, entry->careOfAddress, MCOA_UNSIGNED_BID, ie->ipv6Data()->getMNHomeAddress(), ie); // update 10.06.08 - CB
						}

						// statistic collection
						statVectorBAfromHA.record(1);
					}
					else if ( entry->BAck == false ) // BA from CN
					{
						//update List of BIDs for CN
						updateCnList(entry->destAddress, keyMCoA.getBID());

						tunneling->destroyTunnelForExitAndTrigger(entry->homeAddress, baSource);
						EV << "Create tunnel in CN with HA_OPT " << entry->careOfAddress << endl;
						tunneling->createTunnel(IPv6Tunneling::HA_OPT, entry->careOfAddress, entry->homeAddress, baSource); // update 10.06.08 - CB
						//tunneling->createPseudoTunnel(CoA, bu->getHomeAddressMN(), dest, TUNNEL_HA_OPT);
						//bubble("Established Type 2 Routing Header path to CN.");

						// statistic collection
						statVectorBAfromCN.record(1);

						// fire event to MIH subscribers
						nb->fireChangeNotification(NF_MIPv6_RO_COMPLETED, NULL);
					}

					// set BAck flag in BUL
					entry->BAck = true;

					// set mobility state in BUL
					entry->state = BindingUpdateList::REGISTERED;

					/*11.7.3
					  In addition, if the value specified in the Lifetime field in the
					  Binding Acknowledgement is less than the Lifetime value sent in
					  the Binding Update being acknowledged, the mobile node MUST
					  subtract the difference between these two Lifetime values from the
					  remaining lifetime for the binding as maintained in the
					  corresponding Binding Update List entry (with a minimum value for
					  the Binding Update List entry lifetime of 0).  That is, if the
					  Lifetime value sent in the Binding Update was L_update, the
					  Lifetime value received in the Binding Acknowledgement was L_ack,
					  and the current remaining lifetime of the Binding Update List
					  entry is L_remain, then the new value for the remaining lifetime
					  of the Binding Update List entry should be
						 max((L_remain - (L_update - L_ack)), 0)
					  where max(X, Y) is the maximum of X and Y.*/
					int l_ack = ba->getLifetime() * 4; /* 6.1.7 One time unit is 4 seconds. */
					int l_update = entry->bindingLifetime;
					int l_remain = (int) ( entry->bindingLifetime - ( SIMTIME_DBL(simTime() - entry->sentTime) ) );
					int x = l_remain - (l_update - l_ack);
					entry->bindingLifetime = x > 0 ? x : 0;
					entry->bindingExpiry = simTime() + entry->bindingLifetime;
					// we schedule the timer that manages the BUL entry expiration
					// TODO currently we schedule the expiry message some seconds (PRE_BINDING_EXPIRY)
					// 	    before the actual expiration. Can be improved.
					simtime_t scheduledTime = entry->bindingExpiry - PRE_BINDING_EXPIRY;
					scheduledTime = scheduledTime > 0 ? scheduledTime : 0;

					/*EV << "l_ack=" << l_ack << ", l_update=" << l_update << ", l_remain=" << l_remain << ", x=" << x << endl;
					EV << "entry->bindingLifetime=" << entry->bindingLifetime << " and entry->bindingExpiry=" << entry->bindingExpiry << endl;*/

					if (entry->bindingLifetime == 0 || scheduledTime ==0 || scheduledTime < simTime()){
						scheduledTime = entry->bindingExpiry + PRE_BINDING_EXPIRY;
						entry->bindingLifetime = PRE_BINDING_EXPIRY * PRE_BINDING_EXPIRY;
						entry->bindingExpiry = simTime() + entry->bindingLifetime;
						EV << "[MCOA] MODIFIED THE SCHEDULE TIME OF BUL ENTRY EXPIRE " << keyMCoA <<" to " << scheduledTime << endl;

					}


					EV << "Scheduling BULEntryExpiryTimer for " << scheduledTime << endl;

					createBULEntryExpiryTimer(keyMCoA, entry, ie, scheduledTime);

					// 11.06.08 - CB: rescheduling changed. Handled by BUL entry expiry.
					/*// reschedule the message if the BA is from a CN and not from the HA
					retransmitBU = (entry->destAddress != ie->ipv6()->getHomeAgentAddress());*/

					/*if ( baSource == ie->ipv6()->getHomeAgentAddress() )
					{
						// initiate RR for CNs moved to above
					}*/
				}

			}//Regular MIPv6 Binding
		}
		/*o  If the Status field indicates that the Binding Update was rejected
		     (the Status field is greater than or equal to 128), then the
		     mobile node can take steps to correct the cause of the error and
		     retransmit the Binding Update (with a new Sequence Number value),
		     subject to the rate limiting restriction specified in Section
		     11.8.  If this is not done or it fails, then the mobile node
		     SHOULD record in its Binding Update List that future Binding
		     Updates SHOULD NOT be sent to this destination.*/
		else
		{
			EV << "Binding was rejected.\n";
			if (!mCoA->getProhibited()){
				switch (ba->getStatus()){
					case MCOA_PROHIBITED:
						capNode.mCoA_support = false;
						capNode.m_prohibited = true;
						capNode.m_bulk_reg_prohibited = true;
						capNode.mc_sim_home_and_foreign_prohibited = true;
						capNode.FlagOverwrite = false;
						addCapabilitiesNode(baSource, capNode);

						/* RFC5648 5.7
						 * If the status value is [MCOA PROHIBITED], the mobile node MUST
						 *  stop registering multiple bindings with the node that sent the
						 *  Binding Acknowledgement.
						 */
						//TODO: Bruno Remove all BuifTranmit Timers!

						break;

					case MCOA_BULK_REGISTRATION_PROHIBITED:
						capNode.mCoA_support = true;
						capNode.m_prohibited = false;
						capNode.m_bulk_reg_prohibited = true;
						capNode.mc_sim_home_and_foreign_prohibited = false;
						capNode.FlagOverwrite = false;
						addCapabilitiesNode(baSource, capNode);
						/*
						 * If the status value is [MCOA BULK REGISTRATION PROHIBITED], the
						 *  mobile node needs to stop using bulk registrations with the node
						 * that sent the Binding Acknowledgement.  It should assume that none
						 * of the attempted registrations were successful.
						 */
						//TODO: Bruno Implement a method to transform the multiple registrations
						//     into multiple BU messages.
						// Remove timers.

						break;

					case MCOA_MALFORMED:
						capNode.mCoA_support = true;
						capNode.m_prohibited = false;
						capNode.m_bulk_reg_prohibited = false;
						capNode.mc_sim_home_and_foreign_prohibited = false;
						capNode.FlagOverwrite = false;
						addCapabilitiesNode(baSource, capNode);
						/*
						 * If [MCOA MALFORMED] is specified, it indicates that the Binding
						   Identifier mobility option is formatted wrong, presumably due to a
						   programming error or major packet corruption.
						 */
						//TODO: Bruno How Can I correct address !?

						break;

					case MCOA_NON_MCOA_BINDING_EXISTS:
						capNode.mCoA_support = true;
						capNode.m_prohibited = false;
						capNode.m_bulk_reg_prohibited = false;
						capNode.mc_sim_home_and_foreign_prohibited = false;
						capNode.FlagOverwrite = true;
						addCapabilitiesNode(baSource, capNode);

						/*
						 * If [MCOA NON-MCOA BINDING EXISTS] is specified, it means that
						 *  there is a non-MCoA binding entry in the receiver.  The mobile
						 * node MUST set 'O' flag so that all the registered bindings are
					     * replaced by an MCoA registration as described in Section 5.9.
						 */

						//TODO: Bruno Implement code in sending functions so that overwrite flag behviour
						//      is implemented.

						break;

					case MCOA_UNKOWN_COA:
						capNode.mCoA_support = true;
						capNode.m_prohibited = false;
						capNode.m_bulk_reg_prohibited = false;
						capNode.mc_sim_home_and_foreign_prohibited = false;
						capNode.FlagOverwrite = false;
						addCapabilitiesNode(baSource, capNode);
						/*
						 * If [MCOA UNKNOWN COA] is specified, it means that the mobile node
						 *  sent a Binding Identifier mobility option without a Care-of
						 * Address field, but the receiver could not find an entry for the
						 * BID indicated.  If the mobile node is trying to de-register a BID,
						 * it need not do anything further.  If the mobile node is trying to
						 * refresh a binding, it SHOULD send a Binding Identifier mobility
						 * option including the Care-of Address field.
						 */
						//TODO: Bruno Check This error should not occur.
						//      every BID Option include CoA, even if not mandatory.
						break;

				}
			}
			/*11.7.1
			  If the home agent rejects the value, it sends back a
			  Binding Acknowledgement with a status code 135, and the last accepted
			  sequence number in the Sequence Number field of the Binding
			  Acknowledgement.  The mobile node MUST store this information and use
			  the next Sequence Number value for the next Binding Update it sends.*/

			// retransmission is performed anyway as timers are not deleted
			// TODO store DO_NOT_SEND_BU in BUL
		}
	}



	// update 11.6.08 - CB: rescheduling of BU is now handled by BUL entry expiry
	// update 13.9.07 - CB
	// for now, we delete the BU transmission timer irrelevant of the status of the BA
	// TODO catch BA failure case
	/*
	int interfaceID = ctrlInfo->interfaceId();
	if (retransmitBU)
		resetBUIfEntry(baSource, interfaceID, retransmissionTime); // add bindingLifetime
	else
		cancelTransmitIfEntry(baSource, interfaceID, KEY_BU);
	*/



	delete ctrlInfo;
	delete ba;
}

bool xMIPv6::validateBAck(const BindingAcknowledgement& ba, const IPv6ControlInfo* ctrlInfo)
{
	/*11.7.3
	  Upon receiving a packet carrying a Binding Acknowledgement, a mobile
	  node MUST validate the packet according to the following tests:

	  o  The packet meets the authentication requirements for Binding
	     Acknowledgements defined in Section 6.1.8 and Section 5.  That is,
	     if the Binding Update was sent to the home agent, underlying IPsec
	     protection is used.  If the Binding Update was sent to the
	     correspondent node, the Binding Authorization Data mobility option
	     MUST be present and have a valid value.*/
	IPv6Address cnAddress = ctrlInfo->getSrcAddr();
	IPv6Address destAddress  = ctrlInfo->getDestAddr();
	InterfaceEntry *ie = ift->getInterfaceById( ctrlInfo->getInterfaceId() );

	if ( cnAddress != ie->ipv6Data()->getHomeAgentAddress() ) // BAck comes from a CN and not from the HA
	{
		if ( ba.getBindingAuthorizationData() == UNDEFINED_BIND_AUTH_DATA )
		{
			EV << "BA Validation Failed: Binding Authorization Data invalid !"<<endl;
			return false;
		}
	}


	if (!mCoA->getProhibited()){
		unsigned int ci=0;
		int nMobOpts = 0;
		int baBID;
		bool resSeq=false;

		if (ba.getMobBIDmobilityArraySize() > 0){
			MobilityBIDOptions* mOpts = new MobilityBIDOptions();
			const MobOption_Binding_Identifier_Mobility* auxOpt;

			mOpts->setMobOptsArraySize(ba.getMobBIDmobilityArraySize());

			for (ci=0;ci < ba.getMobBIDmobilityArraySize();ci++){
				auxOpt = &(ba.getMobBIDmobility(ci));
				mOpts->setMobOpts(nMobOpts, (*auxOpt) );
				nMobOpts++;
				KeyMCoABind keyMCoA = auxOpt->getKMCoA();
				baBID = keyMCoA.getBID();

				//baBID = auxOpt->getBindingID();
				//keyMCoA->setBID(baBID);
				//keyMCoA->setAddr(auxOpt->getCoA());
				//EV << "[MCOA] >>>>> rcv (VALIDATING) BID in BU " << baBID <<  " with LEN " << auxOpt->getMobOptionLength()  << endl;

				if (auxOpt->getMobOptionLength()!= 4 && auxOpt->getMobOptionLength()!= 8 && auxOpt->getMobOptionLength()!= 20){
					EV << "[MCOA] >>>> rcv mob OPTION with Invalid Length in BA" << auxOpt->getMobOptionLength() <<" BID=" << baBID << endl;

					//TODO: Check what should be done. Remove from BUL?!
					return false;
				}


				EV << "[MCOA] searching for sequenceNumber of " << keyMCoA << " gor in BUL " << bul->getSequenceNumber(keyMCoA) << " and got in ba " << ba.getSequenceNumber() << endl;
				//The sequence  number qhen coming from the CN seem to be very different from those in BUL...
				//if ( bul->getSequenceNumber(keyMCoA) == ba.getSequenceNumber() || cnAddress != ie->ipv6Data()->getHomeAgentAddress()  )
				if ( bul->getSequenceNumber(keyMCoA) == ba.getSequenceNumber()  )
				{
					resSeq = true;
				}
			}
			if (!resSeq){ // Ate least one option should have the same sequence.
				EV << "BA Validation Failed: Sequence number from BA does not match the one from the BUL!!"<<endl;
				return false;
			}

			delete mOpts;

		}else{
			if (ba.getMobBIDmobilityArraySize() == 0) {

				if (ba.getLifetime() == 0) {
					EV << "[MCOA-BA] MN received BA without options and with lifetime=0, it's OK " << endl;
					return true;
				}else {
					EV << "[MCOA-BA] MN received BA without options and with lifetime !=0, NOT OK " << endl;
					return false;
				}

			}
		}
	}else {
		/*
		 *  ------------------------------------
		 *  Regular MiPV6 binding
		 *  ------------------------------------
		 */

		/*o  The Sequence Number field matches the Sequence Number sent by the
			 mobile node to this destination address in an outstanding Binding
			 Update.*/
		// 24.9.07 - CB
		KeyMCoABind keyMCoA =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, cnAddress);

		/*
		 * When the network has multiple addresses advertised it seems that simple condition fails.
		 *
		 * If BA from CN are not received tunnels are not destroyed...
		 * From CN we accept anything....   this is a rude way of doing things
		 *
		 * TODO: Improve this condition
		 */
		//if ( bul->getSequenceNumber(keyMCoA) != ba.getSequenceNumber() ) // Original Code
		if ( bul->getSequenceNumber(keyMCoA) != ba.getSequenceNumber() && cnAddress == ie->ipv6Data()->getHomeAgentAddress() )
		{
			EV << "BA Validation Failed: Sequence number from BA does not match the one from the BUL!!"<<endl;
			EV << "Seq in BUL "<< bul->getSequenceNumber(keyMCoA) << " and SEQ in BA" <<ba.getSequenceNumber() << endl;

			return false;
		}
	}

	return true;
}



void xMIPv6::MCOAprocessBAMessage_DeregALL(BindingAcknowledgement * ba, IPv6ControlInfo * ctrlInfo, InterfaceEntry *ie, IPv6Address &baSource)
{
	if ( baSource == ie->ipv6Data()->getHomeAgentAddress() )
	{
		EV << "[MCOA-BA] removing all bindings in HA for addr " << baSource << endl;

		if (mCoA->getDeregisterALL() == MCoA::DEREGISTER_ALL_SIMULTANEOUSLY){
			bul->removeBindingByDest(baSource);
			EV << "[MCOA-BA] removed all bindings in HA  " << endl;
			//bul->prtBindings();
			removeTimerEntries2(baSource, ctrlInfo->getInterfaceId());

			// statistic collection
			statVectorBAfromHA.record(2);
		}

		/*11.5.4
		  After receiving the Binding Acknowledgement for its Binding Update to
		  its home agent, the mobile node MUST multicast onto the home link (to
		  the all-nodes multicast address) a Neighbor Advertisement [12], to
		  advertise the mobile node's own link-layer address for its own home
		  address.*/

		/* RFC5648 5.6.3
		 * According to [RFC3775], the mobile node MUST start responding to
		 *  Neighbor Solicitation for its home address right after it sends the
		 *  de-registration Binding Update to the home agent.  However, in this
		 * specification, the mobile node MUST NOT respond to Neighbor
		 * Solicitation before receiving a Binding Acknowledgement, since the
		 *  home agent may continue proxying for the home address.  If the mobile
		   * node receives [MCOA RETURNHOME WO/NDP (5)] status value in the
		   * received Binding Acknowledgment, it MUST NOT respond to Neighbor
		   * Solicitation even after the Binding Acknowledgement.
		 *
		 */
		if (ba->getStatus() == MCOA_RETURNHOME_WO_NDP){
			ipv6nd->setReplyToNSmsg(false);

		}
		//else {
			//EV << "sending UnsolicitedNA message " << ie->ipv6Data()->info();
			//ipv6nd->sendUnsolicitedNA(ie);
		//}


	}else {
		EV << "[MCOA-BA] removing all bindings in CN for addr " << baSource << endl;

		if (mCoA->getDeregisterALL() == MCoA::DEREGISTER_ALL_SIMULTANEOUSLY){
			bul->removeBindingByDest(baSource);
			EV << "[MCOA-BA] removed all bindings in CN  " << endl;
			//bul->prtBindings();
			removeTimerEntries2(baSource, ctrlInfo->getInterfaceId());

			// statistic collection
			statVectorBAfromCN.record(2);
		}
	}


	if (ba->getLifetime() == 0  && mCoA->getDeregisterALL() == MCoA::DEREGISTER_ALL_SIMULTANEOUSLY)
	{
		//If there are no more bindings
		if (bul->isEmpty()){
			EV << "[MCOA-BA] Clear ALL BIDs" << endl;
			CoABIDs.clear();
			removeAllTimerEntries(ctrlInfo->getInterfaceId()); //Remove all timers for this interface
			interfaceCoAList.clear();

			//On a next move... MN knows the capabilities of other nodes
			//nodesMCoACaps.clear();
			cnListBIDs.clear();
		}
	}

}


void xMIPv6::MCOAprocessBAMessage_Normal(BindingAcknowledgement * ba, IPv6ControlInfo * ctrlInfo, InterfaceEntry *ie, IPv6Address &baSource, KeyMCoABind &keyMCoA, int ci)
{
	EV << "DBG-LOOKING FOR " << keyMCoA << endl;
	//bul->prtBindings();

	BindingUpdateList::BindingUpdateListEntry* entry = bul->lookup2( keyMCoA);
	ASSERT(entry!=NULL);

	//FIXME:
	//if (entry->BAck && ((simTime() - entry->sentTime) < 0.5) ){
	//	EV << "Entry in BUL has already been acknowledge recently" << endl;
	//	return true;
	//}

	// establish tunnel, but only if we have not already acked the BU before
	if (entry->BAck == false && entry->destAddress == ie->ipv6Data()->getHomeAgentAddress() ) // BA from HA
	{
		//cancelEntries(ie->getInterfaceId(), entry->careOfAddress, keyMCoA.getBID());
		ifBID auxIf;
		auxIf.iBID = keyMCoA.getBID();
		auxIf.ifID = ie->getInterfaceId();
		interfaceCoAList[auxIf] = entry->careOfAddress;


		if (tunneling->findTunnel(entry->careOfAddress, entry->destAddress, entry->destAddress)){
			EV << "in MN Tunnel exists for HA already doing nothing " << endl;
		}else {
			EV << "Creating tunnel in processBA " << entry->careOfAddress << endl;
			tunneling->createTunnel( IPv6Tunneling::NORMAL, entry->careOfAddress, entry->destAddress, entry->destAddress ); // update 10.06.08 - CB
		}

		if (ci==0){
			// statistic collection
			statVectorBAfromHA.record(1);
		}


		// initiate RR for the CNs
		//for (itCNList = cnList.begin(); itCNList != cnList.end(); itCNList++) // run an iterator through the CN map
		for (CNListBIDs::iterator it = cnListBIDs.begin();
						 it != cnListBIDs.end();
						 it++)
		{
			IPv6Address cnDest = (*it).first;
			std::vector<int> aBIDs = (*it).second;
			std::vector<int>::iterator bit;

			KeyMCoABind key_auxCn ;

			//TODO: Check if the CN has the registered BID...
			//for (bit = aBIDs.begin(); bit < aBIDs.end(); bit++){
			int auxBID = keyMCoA.getBID();

			IPv6Address auxCoA = get_adr_from_bid(auxBID);
			if (auxCoA != IPv6Address::UNSPECIFIED_ADDRESS){
					key_auxCn.setAddr(auxCoA);
					key_auxCn.setBID(auxBID);
					key_auxCn.setDestBID(cnDest);
					EV << "Dbg TRiggering Route Optimization to " << cnDest << ", for "  << key_auxCn.getAddr() << ", " << key_auxCn.getBID() << endl;
					triggerRouteOptimization(cnDest, key_auxCn.getAddr(), auxBID, ie->ipv6Data()->getMNHomeAddress(), ie); // update 10.06.08 - CB
			}else {
				EV << "Not Performing Route Optimization for BID = " << auxBID << " CoA " << auxCoA << " for dest " << cnDest << endl;
			}

		}


		// statistic collection
		/*statVectorBAfromHA.record(1);*/
	}
	else if ( entry->BAck == false ) // BA from CN
	{
		if (ci==0){
			// statistic collection
			statVectorBAfromCN.record(1);
		}

		/*
		 * Establishes all the tunnels
		 *
		 * Applications or MIPv6 decide how to use.
		 */
		if (mCoA->getTypeUseMCoA()== MCOA_TUN_ALL_ADR_ALL ||
			mCoA->getTypeUseMCoA()== MCOA_TUN_ALL_ADR_SINGLE_FIRST ||
			mCoA->getTypeUseMCoA()== MCOA_TUN_ALL_ADR_SINGLE_RR
			)
		{

			if (tunneling->findTunnel(entry->careOfAddress, entry->homeAddress, baSource) != 0){
				EV << "in MN Tunnel exists for CN already doing nothing " << endl;
			}else {
				tunneling->destroyTunnel( entry->careOfAddress, entry->homeAddress, baSource); // update 10.06.08 - CB
				EV << "creating tunnel with HA_OPT " << entry->careOfAddress << endl;
				tunneling->createTunnel(IPv6Tunneling::HA_OPT, entry->careOfAddress, entry->homeAddress, baSource); // update 10.06.08 - CB
			}
		}else {
			// Other type of uses go here
		}


		// fire event to MIH subscribers
		nb->fireChangeNotification(NF_MIPv6_RO_COMPLETED, NULL);
	}

	// set BAck flag in BUL
	entry->BAck = true;

	// set mobility state in BUL
	entry->state = BindingUpdateList::REGISTERED;

	//Update the last BA Sequence (Bruno Sousa)
	entry->lastBAseqNumber = ba->getSequenceNumber();


	int l_ack = ba->getLifetime() * 4; /* 6.1.7 One time unit is 4 seconds. */
	int l_update = entry->bindingLifetime;
	int l_remain = (int) ( entry->bindingLifetime - ( SIMTIME_DBL(simTime() - entry->sentTime) ));
	int x = l_remain - (l_update - l_ack);
	entry->bindingLifetime = x > 0 ? x : 0;
	entry->bindingExpiry = simTime() + entry->bindingLifetime;
	// we schedule the timer that manages the BUL entry expiration
	// TODO currently we schedule the expiry message some seconds (PRE_BINDING_EXPIRY)
	// 	    before the actual expiration. Can be improved.
	simtime_t scheduledTime = entry->bindingExpiry - PRE_BINDING_EXPIRY;
	scheduledTime = scheduledTime > 0 ? scheduledTime : 0;

	if (entry->bindingLifetime == 0 || scheduledTime ==0 || scheduledTime < simTime()){
		scheduledTime = entry->bindingExpiry + PRE_BINDING_EXPIRY;
		entry->bindingLifetime = PRE_BINDING_EXPIRY * PRE_BINDING_EXPIRY;
		entry->bindingExpiry = simTime() + entry->bindingLifetime;
		EV << "[MCOA] MODIFIED THE SCHEDULE TIME OF BUL ENTRY EXPIRE " << keyMCoA <<" to " << scheduledTime << endl;

	}

	createBULEntryExpiryTimer(keyMCoA, entry, ie, scheduledTime);


}









/**
  * Alain Tigyo, 21.03.2008
  * The following code is used for triggering RO to a CN.
  */
void xMIPv6::triggerRouteOptimization(const IPv6Address& destAddress, const IPv6Address& amCoA, const  int iBID, const IPv6Address& HoA, InterfaceEntry* ie)
{
	//Initially the CN does not have any information of the MN
	// regarding its CoA...
	IPv6Address aCoA;
	int aBID;

	/* Bruno
	 * Check if address is of a CN already registered if MIPv6 was triggered
	 *
	 * TODO: This limit the non addition of CNs after the movement of MN....
	 *
	 * FIXME: I did not caught the reason for this to happen...
	 * Packets enter on a tunnel from the HA towards the MN but why??
	 */

	if (mipv6sm->getMIPv6triggered() && cnListBIDs.size() >= 1 ){
		CNListBIDs::iterator it = cnListBIDs.find(destAddress);
		if (it == cnListBIDs.end()){
			EV << "xMIPv6 trying to perform routing optimization to a node that is not registered as a CN !" << destAddress << endl;
			return;
		}
	}

	if (amCoA.isUnspecified() && iBID == MCOA_UNSIGNED_BID ){

		EV << "amCoA is Unspecified  " << amCoA << " and BID = " << iBID << endl;
		if (!mCoA->getProhibited()){
			aCoA = ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::CoA);
		}else {
			//
			// In MIPv6 the CoA registered in CN must be equal to the one registered in the CNs
			//
			if (mipv6sm->getSetPreferedAddr()){
				aCoA = mipv6sm->getMIPv6preferredAddr();
				EV << " IN triggerRouteOptimization preferred address is already set " << aCoA << endl;
			}else{
				aCoA = ie->ipv6Data()->getGlobalAddressReverse(IPv6InterfaceData::CoA);
				mipv6sm->setMIPv6preferredAddr(aCoA);
				mipv6sm->setSetPreferedAddr(true);
				EV << " IN triggerRouteOptimization set preferred address = " << aCoA << endl;
			}
		}
		EV << "amCoA is now CoA = " << aCoA << endl;
		aBID = get_and_calcBID(aCoA, ie);

	}else {
		aBID = iBID;
		aCoA = amCoA;
	}



	if (!mCoA->getProhibited() &&
			(mCoA->getTypeUseMCoA() == MCOA_TUN_ALL_ADR_ALL ||
					mCoA->getTypeUseMCoA()==MCOA_TUN_ALL_ADR_SINGLE_FIRST || mCoA->getTypeUseMCoA()==MCOA_TUN_ALL_ADR_SINGLE_RR)
	   ){
		if (!ie->ipv6Data()->hasAddress(mipv6sm->getMIPv6preferredAddr())){
			mipv6sm->setMIPv6preferredAddr(ie->ipv6Data()->getPreferredAddress());
		}
	}

	EV << "DBG triggerRouteOptimization  CoA " << aCoA  << " BID " << aBID  << " destAdress " << destAddress << endl;

	KeyMCoABind  keyMCoA;
	if (!mCoA->getProhibited()){
		keyMCoA =  KeyMCoABind(aCoA, aBID, destAddress);
	}else {
		keyMCoA =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, destAddress);
	}



	if ( bul->getMobilityState(keyMCoA) == BindingUpdateList::NONE)
		bul->setMobilityState(keyMCoA, BindingUpdateList::RR);

	int vIndex = tunneling->getVIfIndexForDest(destAddress, IPv6Tunneling::MOBILITY); // update 10.06.08 - CB

	if ( vIndex > ift->getNumInterfaces() )
	{
		EV << "Route Optimization for: " << destAddress <<" already triggered";

		// we have to check whether our current CoA is different from the one saved in the BUL
		// (this would mean we have moved to a new access network on this interface)
		//if ( (bul->getCoA(keyMCoA) != ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::CoA)) || bul->getMobilityState(keyMCoA) == BindingUpdateList::NONE )
		if ( bul->getMobilityState(keyMCoA) == BindingUpdateList::NONE )
		{
			// we have a new CoA compared to BUL entry -> redo RO
			initReturnRoutability(destAddress, ie, keyMCoA);
			EV << " ...moved to new network. Initializing RO.";
		}

		EV << endl;
	}
	else
	{
		if ( (!bul->isInBindingUpdateList(keyMCoA, HoA)) || (bul->getMobilityState(keyMCoA) == BindingUpdateList::RR) )
		{

			if (mCoA->getProhibited()) //Standard MIPv6
			  updateCnList(destAddress, aBID);

			initReturnRoutability(destAddress, ie, keyMCoA);
		}
	}

}


void xMIPv6::initReturnRoutability( const IPv6Address& cnDest, InterfaceEntry* ie,  KeyMCoABind &keyMCoA)
{
	EV <<"Initiating Return Routability... for " << keyMCoA  << endl;
	Enter_Method("initReturnRoutability()");

	// update 12.9.07 - CB
	bool sendHoTI = true, sendCoTI = true;

	/*
	 * // TODO: Bruno Check the correct validation for this.
	if (keyMCoA==NULL){
		keyMCoA.setAddr(cnDest);
		keyMCoA.setBID(MCOA_UNSIGNED_BID);
	}*/
	/*11.6.1
	  A mobile node that initiates a return routability procedure MUST send
	  (in parallel) a Home Test Init message and a Care-of Test Init
	  messages. However, if the mobile node has recently received (see
	  Section 5.2.7) one or both home or care-of keygen tokens, and
	  associated nonce indices for the desired addresses, it MAY reuse
	  them.  Therefore, the return routability procedure may in some cases
	  be completed with only one message pair.  It may even be completed
	  without any messages at all, if the mobile node has a recent home
	  keygen token and has previously visited the same care-of address so
	  that it also has a recent care-of keygen token.*/



	BindingUpdateList::BindingUpdateListEntry* cnEntry = bul->fetch(keyMCoA, cnDest);
	ASSERT(cnEntry);
	cnEntry->state = BindingUpdateList::RR;

	/*A Home Test Init message MUST be created as described in Section
	  6.1.3.*/
	//if ( cnEntry != NULL )
	//{
		// if there exists an entry in the BUL, check whether we already
		// have valid home and care-of tokens

		// check whether the last received home token is still valid
		//if ( (cnEntry->tokenH != UNDEFINED_TOKEN) && ( cnEntry->sentHoTI + ie->ipv6()->_maxTokenLifeTime() > simTime() ) )

		if ( bul->isHomeTokenAvailable(keyMCoA, ie) )
		{
			EV << "Valid home token available - sending HoTI later." << endl;
			sendHoTI = false;
		}
		//else
		//	delete HoTI;

		/*if ( (cnEntry->tokenC != UNDEFINED_TOKEN) && ( cnEntry->sentCoTI + ie->ipv6()->_maxTokenLifeTime() > simTime() ) )*/
		if ( bul->isCareOfTokenAvailable(keyMCoA, ie) )
		{
			EV << "Valid care-of token available - sending CoTI later." << endl;

			// we already have a care-of token
			sendCoTI = false;
		}
		//else
		//	delete CoTI;

		if ( !sendHoTI && !sendCoTI ) // cnEntry can not be NULL as a consequence of the other two flag's values
		{
			// we already had a valid home and care-of token
			// -> no need for sending HoTI/CoTI; we can
			// immediately continue with sending a BU
			cnEntry->state = BindingUpdateList::RR_COMPLETE;

			sendBUtoCN(keyMCoA, *cnEntry, ie);
		}
	//}


	if ( sendHoTI && !bul->recentlySentHOTI(keyMCoA, ie) )
	{
		// no entry for this CN available: create Home Test Init message to be sent via HA
		EV << "DBG INIT RR for HoTI " << keyMCoA.getAddr() << " BID " << keyMCoA.getBID() << " dest " << keyMCoA.getDestBID()  << endl;

		createAndSendHoTIMessage( cnDest, ie, keyMCoA);
	}

	if ( sendCoTI && !bul->recentlySentCOTI(keyMCoA, ie) )
	{
		/*A Care-of Test Init message MUST be created as described in Section
		  6.1.4.*/
		// Care-of Test Init Message to CN

		EV << "DBG INIT RR for CoTI " << keyMCoA.getAddr() << " BID " << keyMCoA.getBID() << " dest " << keyMCoA.getDestBID()  << endl;

		createAndSendCoTIMessage(cnDest, ie, keyMCoA);
	}
}


void xMIPv6::createTestInitTimer(MobilityHeader* testInit, const IPv6Address& dest, InterfaceEntry* ie,  KeyMCoABind &keyMCoA, simtime_t sendTime)
{
	EV<<"\n++++++++++TEST INIT TIMER CREATED AT SIM TIME: "<<simTime()<<" seconds+++++++++++++++++ \n";
	cMessage *testInitTriggerMsg = new cMessage("sendTestInit", MK_SEND_TEST_INIT);

	/*11.8
	  When the mobile node sends a Mobile Prefix Solicitation, Home Test
	  Init, Care-of Test Init or Binding Update for which it expects a
	  response, the mobile node has to determine a value for the initial
	  retransmission timer:*/
	// update 13.9.07 - CB
	// check if there already exists a testInitTimer entry for this key
	int msgType;
	if ( dynamic_cast<HomeTestInit*>(testInit) )
		msgType = KEY_HI;
	else
		msgType = KEY_CI;

	// TODO refactor the code below, as it is also used in createBUTimer
	//KeyTimer key(dest, ie->getInterfaceId(), msgType, MCOA_UNSIGNED_BID);
	KeyTimer key(keyMCoA.getDestBID(), ie->getInterfaceId(), msgType, keyMCoA.getBID());
	EV << "DBG createTestINITmsg key " << keyMCoA.getAddr() << "  for " << dest  << " BID " << keyMCoA.getBID() << endl;


	// fetch a valid TimerIfEntry obect
	TestInitTransmitIfEntry* tiIfEntry = (TestInitTransmitIfEntry*) getTimerIfEntry(key, TRANSMIT_TYPE_TI);
	//delete tiIfEntry->testInitMsg;
	cancelAndDelete(tiIfEntry->timer);

	tiIfEntry->timer = testInitTriggerMsg;

	tiIfEntry->dest = dest;
	tiIfEntry->ifEntry = ie;
	tiIfEntry->testInitMsg = testInit;
	/*o  Otherwise, the mobile node should use the specified value of
      	 INITIAL_BINDACK_TIMEOUT for the initial retransmission timer.*/
	tiIfEntry->ackTimeout = ie->ipv6Data()->_initialBindAckTimeout();
	tiIfEntry->nextScheduledTime = simTime() ; // we send the HoTI/CoTI now

	tiIfEntry->adrCoA = keyMCoA.getAddr(); //MCoA Bruno Sousa
	tiIfEntry->BID    = keyMCoA.getBID();

	testInitTriggerMsg->setContextPointer(tiIfEntry); // attach the Test Init If Entry to this message

	// scheduling a message which will trigger the Test Init for sendTime seconds
	// if not called with a parameter for sendTime, the message will be scheduled for NOW
	scheduleAt(simTime()+sendTime, testInitTriggerMsg);
}


void xMIPv6::sendTestInit(cMessage* msg)
{


	// FIXME the following line is unsafe, rewrite it
	TestInitTransmitIfEntry* tiIfEntry = (TestInitTransmitIfEntry*) msg->getContextPointer(); //check_and_cast<TestInitTransmitIfEntry*>( (TestInitTransmitIfEntry*) msg->contextPointer() );
	InterfaceEntry* ie =  tiIfEntry->ifEntry;




	/*11.6.1
	  When sending a Home Test Init or Care-of Test Init message
	  the mobile node MUST record in its Binding Update List the following
	  fields from the messages:
	   o  The IP address of the node to which the message was sent.
	   o  The home address of the mobile node.  This value will appear in
	      the Source Address field of the Home Test Init message.  When
	      sending the Care-of Test Init message, this address does not
	      appear in the message, but represents the home address for which
	      the binding is desired.
	   o  The time at which each of these messages was sent.
	   o  The cookies used in the messages.
	   Note that a single Care-of Test Init message may be sufficient even
	   when there are multiple home addresses.  In this case the mobile node
	   MAY record the same information in multiple Binding Update List
	   entries.*/

	// retrieve the cookie from the Test Init message
	if ( dynamic_cast<HomeTestInit*>(tiIfEntry->testInitMsg) )
	{
		// 24.07.08 - CB
		// moved the following two lines to here
		IPv6Address HoA = ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::HoA);
		ASSERT( !HoA.isUnspecified() );

		HomeTestInit* HoTI = new HomeTestInit( * check_and_cast<HomeTestInit*>( tiIfEntry->testInitMsg ) );

		KeyMCoABind  auxKey;
		if (!mCoA->getProhibited()){
			auxKey =  KeyMCoABind(tiIfEntry->adrCoA, tiIfEntry->BID, tiIfEntry->dest);
		}else {
			auxKey = KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, tiIfEntry->dest);
		}

		EV << "DBG in sendTestINIT for " << auxKey << endl;


		// update cache
		bul->addOrUpdateBUL(auxKey, tiIfEntry->dest, HoA, simTime(), HoTI->getHomeInitCookie(), true);
		// mark the current home token as invalid - update 10.01.08 CB
		bul->resetHomeToken(auxKey, HoA);
		// and send message
		sendMobilityMessageToIPv6Module(HoTI, tiIfEntry->dest, HoA, ie->getInterfaceId());

		// statistic collection
		statVectorHoTItoCN.record(1);


	}
	else // must be of type CareOfTestInit*
	{
		IPv6Address CoA = getMIPv6CoA(ie, tiIfEntry->dest); //Modifications performed by Bruno


		EV << "DBG sending for CoTI msg  with CoA = " << CoA ;

		EV << "" << endl;

		ASSERT( !CoA.isUnspecified() );

		//TODO: Bruno Sousa modify to send the different CoAs.
		CareOfTestInit* CoTI = new CareOfTestInit( * check_and_cast<CareOfTestInit*>(tiIfEntry->testInitMsg) );

		//TODO: Bruno FIXME for  dymanic size
		//KeyMCoABind & auxKey = CoTI->getMobBIDmobility(CoTI->getMobBIDmobilityArraySize()).getKMCoA();
		KeyMCoABind  auxKey;
		if (!mCoA->getProhibited()){
			auxKey = &(CoTI->getMobBIDmobility(0).getKMCoA());
		}else { //standard MIPv6
			//auxKey = KeyMCoABind(tiIfEntry->adrCoA, tiIfEntry->BID, tiIfEntry->dest);
			auxKey =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, tiIfEntry->dest);
		}

		EV << "DBG in sendTestINIT CoTI " << auxKey << endl;

		// update cache
		bul->addOrUpdateBUL(auxKey, tiIfEntry->dest, CoA, simTime(), CoTI->getCareOfInitCookie(), false);
		// mark the current care-of token as invalid - update 10.01.08 CB
		bul->resetCareOfToken(auxKey, CoA);
		// and send message
		sendMobilityMessageToIPv6Module(CoTI, tiIfEntry->dest, CoA, ie->getInterfaceId());

		// statistic collection
		statVectorCoTItoCN.record(1);


	}

	// update 13.9.07 - CB
	/*11.8
	  If the mobile node fails to receive a valid matching response within
   	  the selected initial retransmission interval, the mobile node SHOULD
  	  retransmit the message until a response is received.*/
	tiIfEntry->nextScheduledTime = tiIfEntry->ackTimeout + simTime();

	/*The retransmissions by the mobile node MUST use an exponential back-
   	  off process in which the timeout period is doubled upon each
   	  retransmission, until either the node receives a response or the
   	  timeout period reaches the value MAX_BINDACK_TIMEOUT. The mobile
   	  node MAY continue to send these messages at this slower rate
   	  indefinitely.*/
	tiIfEntry->ackTimeout = tiIfEntry->ackTimeout * 2;
	if (! (tiIfEntry->ackTimeout < ie->ipv6Data()->_maxBindAckTimeout()) )
		tiIfEntry->ackTimeout = ie->ipv6Data()->_maxBindAckTimeout();

	msg->setContextPointer(tiIfEntry);
	scheduleAt(tiIfEntry->nextScheduledTime, msg);

	EV << "Scheduled next HoTI/CoTI for time=" << tiIfEntry->nextScheduledTime
	   << " with timeout=" << tiIfEntry->ackTimeout << " for dest="
	   << tiIfEntry->dest << endl;

	//delete tiIfEntry;
	//delete msg;
}


/*void xMIPv6::resetTestInitIfEntry(const IPv6Address& dest, int interfaceID, int msgType)
{
	ASSERT(msgType == KEY_HI || msgType == KEY_CI);

	Key key(dest, interfaceID, msgType);
	TransmitIfList::iterator pos = transmitIfList.find(key);

	if ( pos == transmitIfList.end()  )
	{
		//EV << "+++ No corresponding TimerIfEntry found! +++\n";
		return;
	}

	TimerIfEntry* entry = (pos->second);
	ASSERT(entry);

	// first we cancel the current retransmission timer
	cancelEvent(entry->timer);
	// then we reset the timeout value to the initial value
	entry->ackTimeout = entry->ifEntry->ipv6()->_initialBindAckTimeout();
	// and then we reschedule again for the time when the token expires
	entry->nextScheduledTime = simTime() + MAX_TOKEN_LIFETIME * TEST_INIT_RETRANS_FACTOR;
	scheduleAt(entry->nextScheduledTime, entry->timer);


	EV << "Updated TestTransmitIfEntry and corresponding timer.\n";

	// TODO check for token expiry in BUL
}*/


/*void xMIPv6::resetTestInitIfEntry(const IPv6Address& dest, int msgType)
{
	ASSERT(msgType == KEY_HI || msgType == KEY_CI);

	TransmitIfList::iterator pos;
	for (pos = transmitIfList.begin(); pos != transmitIfList.end(); ++pos)
	{
		if ( pos->first.type == msgType && pos->first.dest == dest)
			break;
	}

	if ( pos == transmitIfList.end() )
		return;

	// TODO refactor: call resetTestInitIfEntry(const IPv6Address& dest, int interfaceID, int msgType)
	TimerIfEntry* entry = (pos->second);
	ASSERT(entry);

	// first we cancel the current retransmission timer
	cancelEvent(entry->timer);
	// then we reset the timeout value to the initial value
	entry->ackTimeout = entry->ifEntry->ipv6()->_initialBindAckTimeout();
	// and then we reschedule again for the time when the token expires
	entry->nextScheduledTime = simTime() + MAX_TOKEN_LIFETIME * TEST_INIT_RETRANS_FACTOR;
	scheduleAt(entry->nextScheduledTime, entry->timer);


	EV << "Updated TestTransmitIfEntry and corresponding timer.\n";

	// TODO check for token expiry in BUL
}*/


void xMIPv6::resetBUIfEntry(const IPv6Address& dest, int interfaceID, simtime_t retransmissionTime)
{
	/*ASSERT(msgType == KEY_BU);
	Key key(dest, interfaceID, msgType);*/ // update 11.6.08 - CB

	//TODO: BRUNO-FIX-ME FIXME
	// TOIMPLEMENT

	KeyTimer key(dest, interfaceID, KEY_BU, 0 );
	//EV << "DBG resetBUIfEntry key " << "  for " << dest  << endl;



	TransmitIfList::iterator pos = ftimer(key);

	if ( pos == transmitIfList.end()  )
	{
		//EV << "DBGTimer ### No corresponding TimerIfEntry for BU found in resetBUIfEntry! ###\n";
		return;
	}

	TimerIfEntry* entry = (pos->second);
	ASSERT(entry);

	// first we cancel the current retransmission timer
	cancelEvent(entry->timer);
	// then we reset the timeout value to the initial value
	entry->ackTimeout = entry->ifEntry->ipv6Data()->_initialBindAckTimeout();
	// and then we reschedule again for BU expiry time
	// (with correct offset for scheduling)
	entry->nextScheduledTime = retransmissionTime;

	scheduleAt(entry->nextScheduledTime, entry->timer);

	//EV << "Updated BUTransmitIfEntry and corresponding timer.\n";
}

/*
 * Bruno Sousa
 *
 * MCoA does not specify nothing for HoTI, regarding the mobility options.
 * Herein they are sent just to enable keeping track of BIDs.
 */
void xMIPv6::createAndSendHoTIMessage(const IPv6Address& cnDest,  InterfaceEntry* ie, KeyMCoABind &keyMCoA, const IPv6Address &CoA)
{


	HomeTestInit* HoTI = new HomeTestInit("HoTI");
	HoTI->setMobilityHeaderType(HOME_TEST_INIT);
	HoTI->setHomeInitCookie(HO_COOKIE);
	// setting message size, 10.09.07 - CB

	int nOptsBID=0, sizeOpts=0;
	//CN does not support Bulk registration in RFC5648
	if (!mCoA->getProhibited()){

		// TODO: Bruno implement correct validation code
		//if (keyMCoA == NULL){
		//	keyMCoA =  KeyMCoABind(cnDest, MCOA_UNSIGNED_BID);
		//}


		EV << "[MCOA] >>>>>> MCoA is configured setting respective mobility options to include in HoTI " <<endl;

		MobOption_Binding_Identifier_Mobility* aux = new MobOption_Binding_Identifier_Mobility();
		aux->setKMCoA(keyMCoA);
		ASSERT(!keyMCoA.Addr.isUnspecified()); //Myassert

		EV << "[MCOA] >>>>>> HoTI sending " << aux->getKMCoA().getAddr() << " BID "<< aux->getKMCoA().getBID() <<endl;

		//aux->setBindingID(  (bul->getBID(CoA)==0)?bul->calcBID() : bul->getBID(CoA) );
		aux->setPayloadLength(LEN_BID_WITH_COA);
		aux->setMobOptionType(OPTION_BINDING_IDENTIFIER_MOBILITY);
		aux->setMobOptionLength(LEN_BID_WITH_COA - LEN_MOBOPTS_HEADER_FIELDS);
		HoTI->setMobBIDmobilityArraySize(1); // No bulk registration supported
		HoTI->setMobBIDmobility(nOptsBID, *aux);

		nOptsBID++;
		//EV << "[MCOA] >>>>>> send BID message with in HoTI with BID " << aux->getBindingID()  <<endl ;
		sizeOpts += aux->getPayloadLength();

	}

	HoTI->setByteLength( SIZE_MOBILITY_HEADER + SIZE_HOTI  + sizeOpts );

	createTestInitTimer(HoTI, cnDest, ie, keyMCoA);


}


void xMIPv6::createAndSendCoTIMessage(const IPv6Address& cnDest, InterfaceEntry* ie ,KeyMCoABind &keyMCoA, const IPv6Address &CoA)
{


	EV << "DBG inside createAndSendCoTIMessage "  << cnDest << endl;

	CareOfTestInit* CoTI = new CareOfTestInit("CoTI");
	CoTI->setMobilityHeaderType(CARE_OF_TEST_INIT);
	CoTI->setCareOfInitCookie(CO_COOKIE);
	// setting message size, 10.09.07 - CB
	int nOptsBID=0, sizeOpts=0;
	//CN does not support Bulk registration in RFC5648
	if (!mCoA->getProhibited()){

		// TODO: Bruno implement correct validation code
		//if (keyMCoA == NULL){
		//	keyMCoA =  KeyMCoABind(cnDest, MCOA_UNSIGNED_BID);
		//}
		EV << "[MCOA] >>>>>> MCoA is configured setting respective mobility options to include in CoTI " <<endl;

		MobOption_Binding_Identifier_Mobility* aux = new MobOption_Binding_Identifier_Mobility();
		if (CoA == IPv6Address::UNSPECIFIED_ADDRESS){
			//KeyMCoABind keyaux =  KeyMCoABind(bul->getCoA(keyMCoA));
			//aux->setKMCoA(keyaux);
			aux->setKMCoA(keyMCoA);
		}else{
			KeyMCoABind  keyaux =  KeyMCoABind(CoA, get_and_calcBID(CoA, ie), cnDest);
			//aux->setCoA(CoA);
			aux->setKMCoA(keyaux);
		}
		EV << "[MCOA] >>>>>> CoTI sending " << aux->getKMCoA().getAddr() << " BID "<< aux->getKMCoA().getBID() <<endl;

		//aux->setBindingID(  (bul->getBID(CoA)==0)?bul->calcBID() : bul->getBID(CoA) );
		aux->setPayloadLength(LEN_BID_WITH_COA);
		aux->setMobOptionType(OPTION_BINDING_IDENTIFIER_MOBILITY);
		aux->setMobOptionLength(LEN_BID_WITH_COA - LEN_MOBOPTS_HEADER_FIELDS);
		CoTI->setMobBIDmobilityArraySize(1); // No bulk registration supported
		CoTI->setMobBIDmobility(nOptsBID, *aux);

		nOptsBID++;
		//EV << "[MCOA] >>>>>> send BID message with in HoTI with BID " << aux->getBindingID()  <<endl ;
		sizeOpts += aux->getPayloadLength();
	}

	CoTI->setByteLength( SIZE_MOBILITY_HEADER + SIZE_COTI + sizeOpts );

	createTestInitTimer(CoTI, cnDest, ie, keyMCoA);


}


void xMIPv6::processHoTIMessage(HomeTestInit* HoTI, IPv6ControlInfo* ctrlInfo)
{


	// 9.4.1 & 9.4.3
	IPv6Address& HoA = ctrlInfo->getDestAddr();

	HomeTest* HoT = new HomeTest("HoT");
	HoT->setMobilityHeaderType(HOME_TEST);
	HoT->setHomeInitCookie( HoTI->getHomeInitCookie() );
	HoT->setHomeKeyGenToken( bc->generateHomeToken(HoA, 0) ); // TODO nonce

	// 2010/6/7 Bruno Sousa
	int nOpts=0, sizeOpts=0;
	if (!mCoA->getProhibited()){
		MobOption_Binding_Identifier_Mobility* aux = new MobOption_Binding_Identifier_Mobility();
		aux->setKMCoA(HoTI->getMobBIDmobility(0).getKMCoA());
		HoT->setMobBIDmobilityArraySize(1);
		HoT->setMobBIDmobility(nOpts, *aux );
		sizeOpts+= HoTI->getMobBIDmobility(0).getPayloadLength();

		EV << "DBG ProcessHoTI " << aux->getKMCoA().getAddr() << " BID " << aux->getKMCoA().getBID() << endl;

	}
	// setting message size, 10.09.07 - CB
	HoT->setByteLength( SIZE_MOBILITY_HEADER + SIZE_HOT + sizeOpts );

	EV <<"\n<<======HoT MESSAGE FORMED; APPENDING CONTROL INFO=====>>\n";
	sendMobilityMessageToIPv6Module( HoT, ctrlInfo->getSrcAddr(), ctrlInfo->getDestAddr() );

	// statistic collection
	statVectorHoTtoMN.record(1);



	delete HoTI;
	delete ctrlInfo;
}


void xMIPv6::processCoTIMessage(CareOfTestInit* CoTI, IPv6ControlInfo* ctrlInfo)
{


	// 9.4.2 & 9.4.4
	IPv6Address& CoA = ctrlInfo->getDestAddr();

	CareOfTest* CoT = new CareOfTest("CoT");
	CoT->setMobilityHeaderType(CARE_OF_TEST);
	CoT->setCareOfInitCookie( CoTI->getCareOfInitCookie() );
	CoT->setCareOfKeyGenToken( bc->generateCareOfToken( CoA, 0 ) ); // TODO nonce
	// 2010/6/7 Bruno Sousa
	int nOpts=0, sizeOpts=0;
	if (!mCoA->getProhibited()){
		MobOption_Binding_Identifier_Mobility* aux = new MobOption_Binding_Identifier_Mobility();
		aux->setKMCoA(CoTI->getMobBIDmobility(0).getKMCoA());
		CoT->setMobBIDmobilityArraySize(1);
		//CoT->setMobBIDmobility(nOpts, CoTI->getMobBIDmobility(0) );
		CoT->setMobBIDmobility(nOpts, *aux );
		sizeOpts+= CoTI->getMobBIDmobility(0).getPayloadLength();

		EV << "DBG ProcessCoTI " << aux->getKMCoA().getAddr() << " BID " << aux->getKMCoA().getBID() << endl;

	}
	// setting message size, 10.09.07 - CB
	CoT->setByteLength( SIZE_MOBILITY_HEADER + SIZE_COT );

	EV <<"\n<<======CoT MESSAGE FORMED; APPENDING CONTROL INFO=====>>\n";
	sendMobilityMessageToIPv6Module( CoT, ctrlInfo->getSrcAddr(), ctrlInfo->getDestAddr() );

	// statistic collection
	statVectorCoTtoMN.record(1);




	delete CoTI;
	delete ctrlInfo;
}


void xMIPv6::processHoTMessage(HomeTest* HoT, IPv6ControlInfo* ctrlInfo)
{


	int interfaceID = ctrlInfo->getInterfaceId();
	InterfaceEntry* ie = ift->getInterfaceById(interfaceID);
	if (! validateHoTMessage(*HoT, ctrlInfo, ie) )
		EV << "HoT validation not passed: dropping message" << endl;
	else
	{
		EV << "HoT validation passed: updating BUL" << endl;

		IPv6Address& srcAddr = ctrlInfo->getSrcAddr();
		//IPv6Address& destAddr = ctrlInfo->getDestAddr();

		//KeyMCoABind keyAux =  KeyMCoABind(srcAddr);
		KeyMCoABind keyMCoA;
		if (!mCoA->getProhibited()){
			keyMCoA = HoT->getMobBIDmobility(0).getKMCoA();
		}else {
			//keyMCoA = KeyMCoABind(destAddr, MCOA_UNSIGNED_BID, srcAddr);
			keyMCoA = KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, srcAddr);
		}

		EV << "DBG processHoT Key " << keyMCoA.getAddr() << " BID " << keyMCoA.getBID() << endl;

		if (bul->isInBindingUpdateList(keyMCoA)){
		BindingUpdateList::BindingUpdateListEntry* bulEntry = bul->lookup(keyMCoA);
		ASSERT(bulEntry!=NULL);

		// cancel the existing HoTI retransmission timer
		//cancelTimerIfEntry(srcAddr, interfaceID, KEY_HI, MCOA_UNSIGNED_BID);
		cancelTimerIfEntry(keyMCoA.getDestBID(), interfaceID, KEY_HI, keyMCoA.getBID());

		// set the home keygen token
		bulEntry->tokenH = HoT->getHomeKeyGenToken();

		// 10.07.08 - CB
		// set token expiry appropriately
		createHomeTokenEntryExpiryTimer( srcAddr, ift->getInterfaceById(interfaceID), simTime() + ie->ipv6Data()->_maxTokenLifeTime(), keyMCoA );

		// if we have the care-of token as well, we can send the BU to the CN now
		// but only if we have not already sent or are about to send a BU, 26.10.07
		// 21.07.08 - CB
		// call method that potentially sends a BU now
		checkForBUtoCN(keyMCoA, *bulEntry, ie);

		// gather statistics
		statVectorHoTfromCN.record(1);
		}else {
			EV << "TRYING to process HoT for key non existent " << keyMCoA << endl;
		}
	}



	delete HoT;
	delete ctrlInfo;
}


bool xMIPv6::validateHoTMessage(const HomeTest& HoT, const IPv6ControlInfo* ctrlInfo, InterfaceEntry* ie)
{
	// RFC - 11.6.2
	IPv6Address srcAddr = ctrlInfo->getSrcAddr();
	IPv6Address destAddr = ctrlInfo->getDestAddr();
	//int interfaceID = ctrlInfo->interfaceId();

	KeyMCoABind keyMCoA;
	BindingUpdateList::BindingUpdateListEntry* bulEntry=NULL;
	if (!mCoA->getProhibited()){
		keyMCoA  = HoT.getMobBIDmobility(0).getKMCoA();
		bulEntry = bul->lookup2(keyMCoA);

	}else {
		//IPv6Address CoA = ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::CoA);
		keyMCoA =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, srcAddr);

		bulEntry = bul->lookup(keyMCoA);
	}


	/* The Source Address of the packet belongs to a correspondent node
       for which the mobile node has a Binding Update List entry with a
       state indicating that return routability procedure is in progress.
       Note that there may be multiple such entries. */

	if ( bulEntry == NULL )
	{
		EV << "Invalid HoT: No entry in BUL" << endl;
		return false; // no entry in BUL
	}


	/* The Binding Update List indicates that no home keygen token has
	   been received yet. */
	// TODO reactivate this code as soon as token expiry is available in the BUL
	/*if ( bulEntry->tokenH != UNDEFINED_TOKEN)
	{
		EV << "Invalid HoT: Home keygen token already exists." << endl;
		return false; // 0 is expected to indicate "undefined"
	}*/


	/* The Destination Address of the packet has the home address of the
	   mobile node, and the packet has been received in a tunnel from the
	   home agent. */
	// TODO check whether it is necessary to check HoA exlusively for the
	// interface the message was received on.
	if (! rt6->isHomeAddress(destAddr) )
	{
		EV << "Invalid HoT: Destination Address not HoA." << endl;
		return false; // TODO check whether packet was received from HA tunnel
	}


	/* The Home Init Cookie field in the message matches the value stored
	   in the Binding Update List. */
	if ( bulEntry->cookieHoTI != HoT.getHomeInitCookie() )
	{
		EV << "Invalid HoT: Cookie value different from the stored one." << endl;
		return false;
	}


	// if we have come that far, the HoT is valid
	return true;
}


void xMIPv6::processCoTMessage(CareOfTest* CoT, IPv6ControlInfo* ctrlInfo)
{


	int interfaceID = ctrlInfo->getInterfaceId();
	InterfaceEntry* ie = ift->getInterfaceById(interfaceID);

	if (! validateCoTMessage(*CoT, ctrlInfo, ie) )
		EV << "CoT validation not passed: dropping message" << endl;
	else
	{
		EV << "CoT validation passed: updating BUL" << endl;

		IPv6Address& srcAddr = ctrlInfo->getSrcAddr();
		//IPv6Address& destAddr = ctrlInfo->getDestAddr();

		KeyMCoABind keyMCoA;
		if (!mCoA->getProhibited()){
			keyMCoA  =(CoT->getMobBIDmobility(0).getKMCoA());
		}else{
			keyMCoA = KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, srcAddr);
		}
		EV << "DBG processCoT Key " << keyMCoA.getDestBID() << " BID " << keyMCoA.getBID() << " with CoA " << keyMCoA.getAddr() << endl;


		BindingUpdateList::BindingUpdateListEntry* bulEntry = bul->lookup(keyMCoA);
		ASSERT(bulEntry!=NULL);

		// cancel the existing CoTI retransmission timer
		//cancelTimerIfEntry(srcAddr, interfaceID, KEY_CI, keyMCoA.getBID());
		cancelTimerIfEntry(keyMCoA.getDestBID(), interfaceID, KEY_CI, keyMCoA.getBID());

		//Bruno Sousa cancel tokenn Exp
		//cancelTimerIfEntry(keyMCoA.getDestBID(), interfaceID, KEY_CTOKEN_EXP, keyMCoA.getBID());

		// set the care-of keygen token
		bulEntry->tokenC = CoT->getCareOfKeyGenToken();

		// 10.07.08 - CB
		// set token expiry appropriately
		createCareOfTokenEntryExpiryTimer(srcAddr, ift->getInterfaceById(interfaceID), simTime() + ie->ipv6Data()->_maxTokenLifeTime(), keyMCoA);

		// if we have the home token as well, we can send the BU to the CN now
		// but only if we have already sent or are about to send a BU, 26.10.07

		// call method that potentially sends BU now
		checkForBUtoCN(keyMCoA, *bulEntry, ie);

		// reset the CoTI timer for the time the token expires
		//resetTestInitIfEntry(srcAddr, interfaceID, KEY_CI);

		/*// delete the CoT retransmission timer
		cancelTimerIfEntry(srcAddr, interfaceID, KEY_CI);*/

		// gather statistics
		statVectorCoTfromCN.record(1);
	}



	delete CoT;
	delete ctrlInfo;
}


bool xMIPv6::validateCoTMessage(const CareOfTest& CoT, const IPv6ControlInfo* ctrlInfo, InterfaceEntry *ie)
{
	// RFC - 11.6.2
	IPv6Address srcAddr = ctrlInfo->getSrcAddr();
	IPv6Address destAddr = ctrlInfo->getDestAddr();
	//int interfaceID = ctrlInfo->getInterfaceId();

	//TODO: Bruno Change to include BID. How can the search be performed in the CoT messages.
	KeyMCoABind keyMCoA;
	BindingUpdateList::BindingUpdateListEntry* bulEntry;

	if (!mCoA->getProhibited()){
		keyMCoA  = CoT.getMobBIDmobility(0).getKMCoA();
		bulEntry  = bul->lookup(keyMCoA);
	}else{
		//IPv6Address CoA = ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::CoA);
		keyMCoA = KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, srcAddr);

		bulEntry = bul->lookup(keyMCoA);

	}

	/* The Source Address of the packet belongs to a correspondent node
       for which the mobile node has a Binding Update List entry with a
       state indicating that return routability procedure is in progress.
       Note that there may be multiple such entries. */

	if ( bulEntry == NULL )
	{
		EV << "Invalid CoT: No entry in BUL" << endl;
		return false; // no entry in BUL
	}
	if ( bulEntry->sentHoTI == 0 && bulEntry->sentCoTI == 0 )
	{
		EV << "Invalid CoT: No RR procedure initialized for this CN." << endl;
		return false; // no RR procedure started for this entry
	}


	/* The Binding Update List indicates that no care-of keygen token has
       been received yet.. */
	// TODO reactive this code as soon as token expiry is available in the BUL
	/*if ( bulEntry->tokenC != UNDEFINED_TOKEN)
	{
		EV << "Invalid CoT: Already received a care-of keygen token." << endl;
		return false; // 0 is expected to indicate "undefined"
	}*/


	/* The Destination Address of the packet is the current care-of
       address of the mobile node. */
	if (mCoA->getTypeUseMCoA()!= MCOA_TUN_SINGLE_ADR_SINGLE && !mCoA->getProhibited()){
		if ( destAddr != mipv6sm->getMIPv6preferredAddr() ){
			EV << "Invalid CoT: CoA not valid anymore different from the one preferred." << endl;
			return false;
		}
	}else {
		if ( destAddr != ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::CoA) )
		{
			EV << "Invalid CoT: CoA not valid anymore." << endl;
			return false;
		}
	}



	/* The Care-of Init Cookie field in the message matches the value
       stored in the Binding Update List. */
	if ( bulEntry->cookieCoTI != (int) CoT.getCareOfInitCookie() )
	{
		EV << "Invalid CoT: Cookie value different from the stored one." << endl;
		return false;
	}


	// if we have come that far, the CoT is valid
	return true;
}


bool xMIPv6::checkForBUtoCN(KeyMCoABind &keyMCoA, BindingUpdateList::BindingUpdateListEntry& bulEntry, InterfaceEntry *ie)
{
	EV << "Checking whether a new BU has to be sent to CN." << endl;

	if ( bulEntry.state == BindingUpdateList::DEREGISTER )
	{
		// we are supposed to send a deregistration BU

		//if ( ! bul->isValidBinding(bulEntry.destAddress) )
		if ( ! bul->isValidBinding(keyMCoA) )
		{
			// no valid binding existing; nothing to do
			// TODO cleanup operations?
			return false;
		}

		// we need a valid home keygen token for deregistration
		//if ( bul->isHomeTokenAvailable(bulEntry.destAddress, ie) )
		if ( bul->isHomeTokenAvailable(keyMCoA, ie) )
		{
			sendBUtoCN(keyMCoA, bulEntry, ie);
			return true;
		}
		else
		{
			EV << "[MCOA] Token is not available for  "<< keyMCoA << endl;
			//bul->prtBindings();

			// no token available
			// send HoTI
			EV << "DBG checkBUtoCN  before HoTI" << keyMCoA.getAddr() << " BID " << keyMCoA.getBID() <<  " and dest " << keyMCoA.getDestBID() << endl;

			createAndSendHoTIMessage(bulEntry.destAddress, ie, keyMCoA);
			return false;
		}
	}
	else // case REGISTER, REGISTERED and anything else
	{
		// for a registration BU we need both valid care-of and home keygen tokens
		if ( ! bul->isCareOfTokenAvailable(keyMCoA, ie) )
		{
			if ( bul->recentlySentCOTI(keyMCoA, ie) )
				return false;

			EV << "DBG checkBUtoCN  before CoTI" << keyMCoA.getAddr() << " BID " << keyMCoA.getBID() << endl;

			createAndSendCoTIMessage(bulEntry.destAddress, ie, keyMCoA);
			return false;
		}

		if ( ! bul->isHomeTokenAvailable(keyMCoA, ie) )
		{
			if ( bul->recentlySentHOTI(keyMCoA, ie))
				return false;


			EV << "DBG checkBUtoCN0  before HoTI" << keyMCoA.getAddr() << " BID " << keyMCoA.getBID() <<  " and dest " << keyMCoA.getDestBID() << endl;

			createAndSendHoTIMessage(bulEntry.destAddress, ie, keyMCoA );
			return false;
		}

		bulEntry.state = BindingUpdateList::RR_COMPLETE;

		// tokens are available: now we also need the case that the binding is about to expire or we have no valid binding at all
		if ( (bul->isBindingAboutToExpire(keyMCoA) || !bul->isValidBinding(keyMCoA))
		     && bulEntry.state != BindingUpdateList::REGISTER && bulEntry.state != BindingUpdateList::NONE ) // update CB - 26.11.2008
		{
			sendBUtoCN(keyMCoA, bulEntry, ie);
			return true;
		}
		else
			return false;
	}
}


void xMIPv6::sendBUtoCN(KeyMCoABind &keyMCoA, BindingUpdateList::BindingUpdateListEntry& bulEntry, InterfaceEntry *ie)
{
	/*11.7.2
	  Upon successfully completing the return routability procedure, and
	  after receiving a successful Binding Acknowledgement from the Home
	  Agent, a Binding Update MAY be sent to the correspondent node.*/
	EV << "DBG Sending BU to CN " << bulEntry.destAddress << endl;


	/*
	// 10.07.08 - CB
	// The createBU method requires information on the interface. This is not available in the
	// bul entry though. Hence we just fetch a token expiry timer to retrieve this information.
	TimerIfEntry* transmitEntry = searchTimerIfEntry(bulEntry.destAddress, 	KEY_HTOKEN_EXP); // we could also use a care-of keygen token of course...
	ASSERT(transmitEntry!=NULL);
	InterfaceEntry* ie = transmitEntry->ifEntry;*/

	if ( bulEntry.state != BindingUpdateList::DEREGISTER ){
		bulEntry.state = BindingUpdateList::REGISTER;
		//Bruno Sousa
		/*
		 * BUs are sent on a one per one basis for the CN.
		 */
		createBUTimer(keyMCoA, bulEntry.destAddress, ie); // update 07.09.07 - CB

	}else{
		//Bruno Sousa
		if (bulEntry.state == BindingUpdateList::DEREGISTER){

			EV << "[MCOA] sending deregister BU in CN " << keyMCoA << endl;
			createBUTimer(keyMCoA, bulEntry.destAddress, ie); // update 07.09.07 - CB
		}
	}
}


void xMIPv6::processType2RH(IPv6Datagram* datagram, IPv6RoutingHeader* rh)
{
	//EV << "Processing RH2..." << endl;

	if ( ! validateType2RH(*datagram, *rh) )
	{
		delete rh;
		delete datagram;
		return;
	}


	bool validRH2 = false;
	IPv6Address& HoA = rh->getAddress(0);

	/*11.3.3
	  A node receiving a packet addressed to itself (i.e., one of the
	  node's addresses is in the IPv6 destination field) follows the next
	  header chain of headers and processes them.  When it encounters a
	  type 2 routing header during this processing, it performs the
	  following checks.  If any of these checks fail, the node MUST
	  silently discard the packet.*/

	/*The length field in the routing header is exactly 2.*/
	// omitted

	/*The segments left field in the routing header is 1 on the wire.*/
	if ( rh->getSegmentsLeft() != 1 )
	{
		EV << "Invalid RH2 - segments left field must be 1. Dropping packet." << endl;
		delete datagram;
		return;
	}


	// probably datagram from CN to MN

	/*The Home Address field in the routing header is one of the node's
	  home addresses, if the segments left field was 1.  Thus, in
	  particular the address field is required to be a unicast routable
	  address.*/
	if ( rt6->isHomeAddress(HoA) )
	{
		/*Once the above checks have been performed, the node swaps the IPv6
		  destination field with the Home Address field in the routing header,
		  decrements segments left by one from the value it had on the wire,
		  and resubmits the packet to IP for processing the next header.*/
		datagram->setDestAddress(HoA);
		validRH2 = true;
	}
	else
	{
		/*If any of these checks fail, the node MUST
		  silently discard the packet.*/
		//delete datagram; // update 12.09.07 - CB
		EV << "Invalid RH2 - not a HoA. Dropping packet." << endl;
	}


	delete rh;

	if ( validRH2 )
	{
		EV << "Valid RH2 - copied address from RH2 to datagram" << endl;
		send(datagram, "toIPv6");
	}
	else // update 12.09.07 - CB
		delete datagram;
}


bool xMIPv6::validateType2RH(const IPv6Datagram& datagram, const IPv6RoutingHeader& rh)
{
	// cf. RFC 3775 - 6.4

	if ( rh.getAddressArraySize() != 1)
	{
		EV << "Invalid RH2 header: no HoA provided!" << endl;
		return false;
	}


	IPv6Address CoA = datagram.getSrcAddress();
	IPv6Address HoA = rh.getAddress(0);

	/* The IP address contained in the routing header, since it is the mobile
	   node's home address, MUST be a unicast routable address. */
	if ( ! HoA.isUnicast() )
	{
		EV << "Invalid RH2 header: address in RH2 is not a unicast routable address!" << endl;
		return false;
	}

	/* Furthermore, if the scope of the home address is smaller than the
	   scope of the care-of address, the mobile node MUST discard the packet */
	if ( HoA.getScope() < CoA.getScope() )
	{
		EV << "Invalid RH2 header: scope of Address in RH2 is smaller than the source address of the datagram!" << endl;
		return false;
	}

	return true;
}


void xMIPv6::processHoAOpt(IPv6Datagram* datagram, HomeAddressOption* hoaOpt)
{
	// datagram from MN to CN
	bool validHoAOpt = false;
	IPv6Address& HoA = hoaOpt->getHomeAddress();
	IPv6Address& CoA = datagram->getSrcAddress();

	IPv6Address& destCoA = datagram->getDestAddress();

	/*9.3.1
	  Packets containing a
	  Home Address option MUST be dropped if there is no corresponding
	  Binding Cache entry.  A corresponding Binding Cache entry MUST have
	  the same home address as appears in the Home Address destination
	  option, and the currently registered care-of address MUST be equal to
	  the source address of the packet.*/
	ASSERT(bc!=NULL);
	KeyMCoABind keyaux;
	if (!mCoA->getProhibited()){
		keyaux =  KeyMCoABind(HoA, get_and_calcBID(CoA, NULL), destCoA);
	}else {
		keyaux =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, destCoA);
	}




	//if ( bc->isInBindingCache(HoA, CoA) )
	if ( bc->isInBindingCache(keyaux) )
	{
		datagram->setSrcAddress(HoA);
		validHoAOpt = true;
	}
	else
	{
		EV << "Invalid RH2 destination - no entry in binding cache. Dropping packet." << endl;

		/*If the packet is dropped due the above tests, the correspondent node
		  MUST send the Binding Error message as described in Section 9.3.3.
		  The Status field in this message should be set to 1 (unknown binding
		  for Home Address destination option).*/
		// update 12.9.07 - CB
		// previous code was erroneous, as destination from packet is probably
		// not a valid address of the interfaces of this node
		BEStatus status = UNKNOWN_BINDING_FOR_HOME_ADDRESS_DEST_OPTION;
		createAndSendBEMessage(CoA, status);
	}


	delete hoaOpt;

	if ( validHoAOpt )
	{
		EV << "Valid HoA Option - copied address from HoA Option to datagram" << endl;
		send(datagram, "toIPv6");
	}
	else
		delete datagram;
}


void xMIPv6::createAndSendBEMessage(const IPv6Address& dest, const BEStatus& beStatus) // update 12.09.07 - CB
{


	EV <<"\n<<<<<<<<< Entered createAndSendBEMessage() Function>>>>>>>\n";

	BindingError *be = new BindingError("BError");
	be->setMobilityHeaderType(BINDING_ERROR);
	be->setStatus(beStatus);

	// setting message size
	be->setByteLength( SIZE_MOBILITY_HEADER + SIZE_BE );

	sendMobilityMessageToIPv6Module(be, dest); // update 12.09.07 - CB


}


bool xMIPv6::cancelTimerIfEntry(const IPv6Address& dest, int interfaceID, int msgType, int bid)
{
	bool res;
	KeyTimer key(dest, interfaceID, msgType, bid);
	//EV << "DBG cancelTimerIfEntry searching for " << dest << ", " << bid << " if " << interfaceID << " msgType " << msgType << endl ;
	TransmitIfList::iterator pos = ftimer(key);
	res= cancelTimerIfEntry2(pos);

	return res;
}


bool xMIPv6::cancelTimerIfEntry2(TransmitIfList::iterator& pos)
{

	if ( pos == transmitIfList.end()  )
	{
		//EV << " NOT FOUND \n";

		return false;
	}else {

		//prtTimers();
		TimerIfEntry* entry = (pos->second);
		//EV << "Entry in TimerIfEntry found! >" << entry->timer << endl;

		try{
			if ( dynamic_cast<TestInitTransmitIfEntry*>(entry) ){
				delete ((TestInitTransmitIfEntry*) entry)->testInitMsg;
				//EV << "DBGTimer ### Entry in TimerIfEntry found a TESTINIT Transmit! ### > "<< endl;
			}
		}catch(std::bad_cast){
			EV << "Invalid cast with entry " << entry->dest << " with if " << entry->ifEntry << endl;

		}

		if (entry->timer!=NULL){
			KeyTimer key = pos->first;
			//EV << "TO DELETE dest " << key.dest << " bid " << key.BID << " type= " << key.type  << endl;
			cMessage* aux = cancelEvent(entry->timer);


			if (dynamic_cast<BUTransmitIfEntry*>(entry)){
				BUTransmitIfEntry *buIfEntry = (BUTransmitIfEntry*) entry;
				//EV << "DELETED BU WITH SEQ " << buIfEntry->buSequenceNumber << endl;
			}

			if (dynamic_cast<TokenExpiryIfEntry*>(entry)){
				TokenExpiryIfEntry *tokEntry = (TokenExpiryIfEntry*) entry;
				//EV << "DELETED TokenExpiry " << tokEntry->dest << " BID " << tokEntry->BID << " " << tokEntry->adrCoA << endl;
			}
			//delete aux;
		}

		cancelAndDelete(entry->timer); // cancels the retransmission timer
		entry->timer = NULL;


		TransmitIfList::iterator auxit = pos;

		if (pos != transmitIfList.begin()){
			--pos;
			transmitIfList.erase(auxit); // remove entry from list
			++pos;
		}else {
			transmitIfList.erase(auxit); // remove entry from list
			pos = transmitIfList.begin();
		}
		//transmitIfList.erase(pos++); // remove entry from list

		delete entry; // free memory

		//EV << "Deleted TimerIfEntry2 and corresponding timer." << endl;


		return true;
	}
}








/*
 * Bruno Sousa
bool xMIPv6::pendingTimerIfEntry(IPv6Address& dest, int interfaceID, int msgType)
{
	Key key(dest, interfaceID, msgType);
	TransmitIfList::iterator pos = transmitIfList.find(key);

	// return true if there is an entry
	// and false otherwise
	return pos != transmitIfList.end();
}
*/

xMIPv6::TimerIfEntry* xMIPv6::getTimerIfEntry(KeyTimer& key, int timerType)
{
	TimerIfEntry* ifEntry;
	//Option 1
	//TransmitIfList::iterator pos = transmitIfList.find(key);

	//Option 2
	TransmitIfList::iterator pos = ftimer(key);

	if ( pos != transmitIfList.end() )
	{

		// there already exists an unACKed retransmission timer for that entry
		// -> overwrite the old with the new one
		if ( dynamic_cast<TestInitTransmitIfEntry*>(pos->second) )
		{
			TestInitTransmitIfEntry* testInitIfEntry = (TestInitTransmitIfEntry*) pos->second;
			cancelEvent(testInitIfEntry->timer);
			cancelAndDelete(testInitIfEntry->timer); // delete the corresponding timer
			delete testInitIfEntry->testInitMsg; // delete old HoTI/CoTI, 21.9.07 - CB
			testInitIfEntry->testInitMsg = NULL;

			ifEntry = testInitIfEntry;
		}
		else if ( dynamic_cast<BUTransmitIfEntry*>(pos->second) )
		{
			BUTransmitIfEntry* buIfEntry = (BUTransmitIfEntry*) pos->second;
			EV << "TO CANCEL MESSAGE WITH SEQ " << buIfEntry->buSequenceNumber << endl;
			cancelEvent(buIfEntry->timer);
			cancelAndDelete(buIfEntry->timer); // delete the corresponding timer

			ifEntry = buIfEntry;
		}
		else if ( dynamic_cast<BULExpiryIfEntry*>(pos->second) )
		{
			BULExpiryIfEntry* bulExpIfEntry = (BULExpiryIfEntry*) pos->second;
			cancelEvent(bulExpIfEntry->timer);
			cancelAndDelete(bulExpIfEntry->timer); // delete the corresponding timer

			ifEntry = bulExpIfEntry;
		}
		else if ( dynamic_cast<BCExpiryIfEntry*>(pos->second) )
		{
			BCExpiryIfEntry* bcExpIfEntry = (BCExpiryIfEntry*) pos->second;
			cancelEvent(bcExpIfEntry->timer);
			cancelAndDelete(bcExpIfEntry->timer); // delete the corresponding timer

			ifEntry = bcExpIfEntry;
		}
		else if ( dynamic_cast<TokenExpiryIfEntry*>(pos->second) )
		{
			TokenExpiryIfEntry* tokenExpIfEntry = (TokenExpiryIfEntry*) pos->second;
			cancelEvent(tokenExpIfEntry->timer);
			cancelAndDelete(tokenExpIfEntry->timer); // delete the corresponding timer
			tokenExpIfEntry->timer = NULL;
			EV << "TO CLEAN TOKENEXPIRY " << tokenExpIfEntry->dest <<  " with BID " << tokenExpIfEntry->BID  << " " <<  tokenExpIfEntry->adrCoA << endl;

			ifEntry = tokenExpIfEntry;
		}
		else
			opp_error("Expected a subclass of TimerIfEntry!");

		ifEntry->timer = NULL;

	}
	else
	{
		// we do not yet have an entry -> create a new one
		switch (timerType)
		{
			case TRANSMIT_TYPE_BU:
				ifEntry = new BUTransmitIfEntry();
				break;
			case TRANSMIT_TYPE_TI:
				ifEntry = new TestInitTransmitIfEntry();
				break;
			case EXPIRY_TYPE_BUL:
				ifEntry = new BULExpiryIfEntry();
				break;
			case EXPIRY_TYPE_BC:
				ifEntry = new BCExpiryIfEntry();
				break;
			case EXPIRY_TYPE_TOKEN:
				ifEntry = new TokenExpiryIfEntry();
				break;
			default:
				opp_error("Expected a valid TimerIfEntry type!");
				break;
		}

		ifEntry->timer = NULL;
		ifEntry->ifEntry = NULL;

		transmitIfList.insert( std::make_pair(key, ifEntry) );
	}

	return ifEntry;
}


xMIPv6::TimerIfEntry* xMIPv6::searchTimerIfEntry(IPv6Address& dest, int timerType)
{
	//TimerIfEntry* ifEntry;
	TransmitIfList::iterator pos;

	for (pos = transmitIfList.begin(); pos != transmitIfList.end(); ++pos)
	{
		if ( pos->first.type == timerType && pos->first.dest == dest)
			return pos->second;
	}

	return NULL;
}


void xMIPv6::removeTimerEntries(const IPv6Address& dest, int interfaceId )
{
	if ( rt6->isMobileNode() )
	{
		// HoTI
		//cancelTimerIfEntry(dest, interfaceId, KEY_HI, MCOA_UNSIGNED_BID);

		TransmitIfList::iterator it = transmitIfList.begin();

			while ( it != transmitIfList.end() )
			{
				KeyTimer key = it->first;


				//EV << "DBG RemovingTimerEntry with type " << key.type << " with BID  " << key.BID << " for dest " << dest
				//		<< " and list size " << transmitIfList.size() << endl;


				switch(key.type){
					case KEY_HI:
						// HoTI
						cancelTimerIfEntry(dest, interfaceId, KEY_HI, key.BID); // Bruno Sousa
						break;

					case KEY_CI:
						// CoTI
						cancelTimerIfEntry(dest, interfaceId, KEY_CI, key.BID);
						break;

					case KEY_BU:
						// BU
						cancelTimerIfEntry(dest, interfaceId, KEY_BU, key.BID);
						break;

					case KEY_BR:
						// BRR
						cancelTimerIfEntry(dest, interfaceId, KEY_BR, key.BID);
						break;

					case KEY_BUL_EXP:
						// BUL expiry
						cancelTimerIfEntry(dest, interfaceId, KEY_BUL_EXP, key.BID);
						break;

					case KEY_HTOKEN_EXP: // Bruno Sousa
						cancelTimerIfEntry(dest, interfaceId, KEY_HTOKEN_EXP, key.BID);
						break;

					case KEY_CTOKEN_EXP: // Bruno Sousa
						cancelTimerIfEntry(dest, interfaceId, KEY_CTOKEN_EXP, key.BID);
						break;
				}
				// advance pointer to make sure it does not become invalid
				// after the cancel() call
				++it;


			}

		// token expiry // Commented Bruno Sousa
		//cancelTimerIfEntry(dest, interfaceId, KEY_HTOKEN_EXP, MCOA_UNSIGNED_BID);
		//cancelTimerIfEntry(dest, interfaceId, KEY_CTOKEN_EXP, MCOA_UNSIGNED_BID);
	}
	else if ( rt6->isHomeAgent() )
	{
		TransmitIfList::iterator it = transmitIfList.begin();

			while ( it != transmitIfList.end() )
			{
				KeyTimer key = it->first;
				switch(key.type){
				case KEY_BC_EXP:
					cancelTimerIfEntry(key.dest, interfaceId, KEY_BC_EXP, key.BID);
					break;
				}
				++it;
			}

	}
	else // CN
	{
		TransmitIfList::iterator it = transmitIfList.begin();
		while ( it != transmitIfList.end() )
		{
			KeyTimer key = it->first;
			switch(key.type){
			case KEY_BC_EXP:
				cancelTimerIfEntry(key.dest, interfaceId, KEY_BC_EXP, key.BID);
				break;
			}
			++it;
		}

	}
}


/*
 * Trying to follow the logic in
 * http://www.openoffice.org/issues/show_bug.cgi?id=107271
 */
void xMIPv6::removeTimerEntries2(const IPv6Address& dest, int interfaceId )
{
	EV << "Before Clearing size= " << transmitIfList.size() << endl;
	if ( rt6->isMobileNode() )
	{

		TransmitIfList::iterator it = transmitIfList.begin();

			while ( it != transmitIfList.end() )
			{
				//KeyTimer key = it->first;

				if (it->first.dest == dest &&  it->first.interfaceID == interfaceId ){
					cancelTimerIfEntry2(it);
					continue;
				}else {
					++it;
					continue;
				}
			}

	}else if ( rt6->isHomeAgent() ){
		TransmitIfList::iterator it = transmitIfList.begin();

			while ( it != transmitIfList.end() )
			{
				if (it->first.dest == dest &&  it->first.interfaceID == interfaceId ){
					cancelTimerIfEntry2(it);
				}else {
					++it;
				}
			}

	}else{ // CN
		TransmitIfList::iterator it = transmitIfList.begin();
		while ( it != transmitIfList.end() )
		{
			if (it->first.dest == dest &&  it->first.interfaceID == interfaceId ){
				cancelTimerIfEntry2(it);
			}else {
				++it;
			}
		}

	}

	EV << "After Clearing size= " << transmitIfList.size() << endl;
}

void xMIPv6::cancelEntries(int interfaceId, IPv6Address& CoA, int iBID)
{
	//EV << "DBG cancelTimer in cancelEntries  by if " << interfaceId << " CoA " << CoA << " BID " << iBID << endl;


	InterfaceEntry* ie = ift->getInterfaceById(interfaceId);

	// we have to cancel all existing timers

	// ...first for the HA
	IPv6Address HA = ie->ipv6Data()->getHomeAgentAddress();
	//IPv6Address HoA = ie->ipv6()->getMNHomeAddress();

	if (cancelTimerIfEntry(HA, interfaceId, KEY_BU, iBID)){
		//cancelTimerIfEntryByOldKey(HA, interfaceId, KEY_BU);
		//tunneling->destroyTunnel(CoA, HA);
	}
	tunneling->destroyTunnel(CoA, HA);

	// ...and then for the CNs
	for (TransmitIfList::iterator it=transmitIfList.begin(); it!=transmitIfList.end(); )
	{
		if ( (*it).first.interfaceID == interfaceId )
		{
			//EV<< "DBG cancelTimer in cancelEntries  by if " << interfaceId << " dest " << (*it).first.dest << endl;


			TransmitIfList::iterator oldIt = it++;

			// destroy tunnel (if we have a BU entry here)
			if ( (*oldIt).first.type == KEY_BU )
				tunneling->destroyTunnelForEntryAndTrigger(CoA, (*oldIt).first.dest);

			// then cancel the pending event
			cancelTimerIfEntry( (*oldIt).first.dest, (*oldIt).first.interfaceID, (*oldIt).first.type, (*oldIt).first.BID);
		}
		else
			++it;
	}
}



void xMIPv6::removeAllTimerEntries( int interfaceId )
{
	if ( rt6->isMobileNode() )
	{


		TransmitIfList::iterator it = transmitIfList.begin();

			while ( it != transmitIfList.end() )
			{
				KeyTimer key = it->first;
				IPv6Address dest = key.dest;

				EV << " DBG RemovingALLTimerEntry with type " << key.type << " with BID  " << key.BID << " for dest " << dest
						<< " and list size " << transmitIfList.size() << endl;


				if  (key.interfaceID == interfaceId){

							cancelTimerIfEntry(dest, interfaceId, key.type, key.BID); // Bruno Sousa

				}

				++it;


			}


	}
	else if ( rt6->isHomeAgent() )
	{
		TransmitIfList::iterator it = transmitIfList.begin();

			while ( it != transmitIfList.end() )
			{
				KeyTimer key = it->first;
				IPv6Address dest = key.dest;
				if  (key.interfaceID == interfaceId){
					cancelTimerIfEntry(dest, interfaceId, key.type, key.BID); // Bruno Sousa
				}
				++it;
			}

	}
	else // CN
	{
		TransmitIfList::iterator it = transmitIfList.begin();
		while ( it != transmitIfList.end() )
		{
			KeyTimer key = it->first;
			IPv6Address dest = key.dest;
			if  (key.interfaceID == interfaceId){
				cancelTimerIfEntry(dest, interfaceId, key.type, key.BID); // Bruno Sousa
			}
			++it;
		}

	}
}








void xMIPv6::removeCoAEntries()
{
	ifBID auxIf;

	for (InterfaceCoAList::iterator it=interfaceCoAList.begin(); it!=interfaceCoAList.end(); ++it)
	{
		//if ( it->first == ie->interfaceId() )
		auxIf = it->first;
		//EV << "Cancelling timers for ifID=" << it->first << " and CoA=" << it->second << endl;
		//cancelEntries((it->first).ifID, it->second, (it->first).ifBID);
		EV << "Cancelling timers for ifID=" << auxIf.ifID << " and CoA=" << it->second << endl;
		cancelEntries(auxIf.ifID,
				it->second,
				auxIf.iBID);

	}

	// delete all entries after cleanup
	interfaceCoAList.clear();
}


void xMIPv6::createBRRTimer(const IPv6Address& brDest, InterfaceEntry* ie, const uint scheduledTime, KeyMCoABind& keyMCoA)
{
	 /*9.5.5
	   If the sender knows that the Binding Cache entry is still in active
	   use, it MAY send a Binding Refresh Request message to the mobile node
	   in an attempt to avoid this overhead and latency due to deleting and
	   recreating the Binding Cache entry.  This message is always sent to
	   the home address of the mobile node.*/

	Enter_Method("createBRRTimer()");
	cMessage *brTriggerMsg = new cMessage("sendPeriodicBRR", MK_SEND_PERIODIC_BR);

	// check if there already exists a BRTimer entry for this key
	//TOIMPLEMENT
	//KeyTimer key( brDest, ie->getInterfaceId(), KEY_BR, keyMCoA.getBID());


	KeyTimer key( brDest, ie->getInterfaceId(), KEY_BR, keyMCoA.getBID());
	EV << "DBG createBRRTimer key " <<  brDest << " BID " << keyMCoA.getBID()  << endl;


	BRTransmitIfEntry* brIfEntry;
	TransmitIfList::iterator pos = ftimer(key);
	if ( pos != transmitIfList.end() )
	{
		// there already exists an unACKed retransmission timer for that entry
		// -> overwrite the old with the new one
		if (dynamic_cast<BRTransmitIfEntry*>(pos->second) )
		{
			brIfEntry = (BRTransmitIfEntry*) pos->second;
			cancelAndDelete(brIfEntry->timer); // delete the corresponding timer
		}
		else
			opp_error("Expected BRTransmitIfEntry* !");
	}
	else
	{
		// we do not yet have an entry -> create a new one
		brIfEntry = new BRTransmitIfEntry();
		transmitIfList.insert( std::make_pair(key, brIfEntry) );
	}


	brIfEntry->dest = brDest;
	brIfEntry->ifEntry = ie;
	brIfEntry->timer = brTriggerMsg;

	brIfEntry->retries = 0;

	brIfEntry->adrCoA = keyMCoA.getAddr();
	brIfEntry->BID    = keyMCoA.getBID();
	brIfEntry->adrCN  = keyMCoA.getDestBID();

	brTriggerMsg->setContextPointer(brIfEntry); // attaching the brIfEntry info corresponding to a particular address ith message

	// Scheduling a message which will trigger a BRR towards brIfEntry->dest
	scheduleAt(simTime()+scheduledTime, brTriggerMsg);
	EV<<"\n++++++++++BRR TIMER CREATED FOR SIM TIME: "<<simTime()+scheduledTime<<" seconds+++++++++++++++++ to " << brIfEntry->dest  << " and BID=" << brIfEntry->BID << " with CoA= " << brIfEntry->adrCoA << endl;
}


void xMIPv6::sendPeriodicBRR(cMessage *msg)
{
	EV <<"\n<<====== Periodic BRR MESSAGE at time: "<<simTime()<<" seconds =====>>\n";
	BRTransmitIfEntry *brIfEntry = (BRTransmitIfEntry*) msg->getContextPointer(); //detaching the corresponding brIfEntry pointer
	InterfaceEntry *ie = brIfEntry->ifEntry;
	IPv6Address& brDest = brIfEntry->dest;

	KeyMCoABind  keyMCoA;
	if (!mCoA->getProhibited()){
		keyMCoA =  KeyMCoABind(brIfEntry->adrCoA, brIfEntry->BID, brIfEntry->adrCN);
	}else{
		keyMCoA =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, brDest);
	}



	/*9.5.5
	  The correspondent node MAY retransmit Binding Refresh Request
	  messages as long as the rate limitation is applied.  The
	  correspondent node MUST stop retransmitting when it receives a
	  Binding Update.*/
	if ( brIfEntry->retries < BRR_RETRIES ) // we'll not retransmit infinite times
	{
		brIfEntry->retries++;

		createAndSendBRRMessage(brDest, ie, keyMCoA);

		// retransmit the Binding Refresh Message
		scheduleAt(simTime() + BRR_TIMEOUT_THRESHOLD, msg);
	}
	else
	{
		// we've tried often enough - remove the timer
		//cancelTimerIfEntry(brDest, ie->getInterfaceId(), KEY_BR, MCOA_UNSIGNED_BID);
		cancelTimerIfEntry(brDest, ie->getInterfaceId(), KEY_BR, keyMCoA.getBID()); //TODO: BRUNO FIX-ME

		//Bruno
		// clean entry from BC?
	}

}


void xMIPv6::createAndSendBRRMessage(const IPv6Address& dest, InterfaceEntry* ie, KeyMCoABind& keyMCoA)
{
	EV <<"\n<<======THIS IS THE ROUTINE FOR CREATING AND SENDING BRR MESSAGE =====>>\n";

	BindingRefreshRequest* brr = new BindingRefreshRequest("Binding Refresh Request");

	/*6.1.2
	  The Binding Refresh Request message uses the MH Type value 0.  When
	  this value is indicated in the MH Type field, the format of the
	  Message Data field in the Mobility Header is as follows:*/
	brr->setMobilityHeaderType(BINDING_REFRESH_REQUEST);


	int nOptsBID=0, sizeOpts=0;
	//CN does not support Bulk registration in RFC5648
	if (!mCoA->getProhibited()){

		EV << "[MCOA] >>>>>> MCoA is configured setting respective mobility options to include in BRR " <<endl;

		MobOption_Binding_Identifier_Mobility* aux = new MobOption_Binding_Identifier_Mobility();
		aux->setKMCoA(keyMCoA);

		EV << "[MCOA] >>>>>> BRR sending " << aux->getKMCoA().getAddr() << " BID "<< aux->getKMCoA().getBID() <<endl;


		aux->setPayloadLength(LEN_BID_WITH_COA);
		aux->setMobOptionType(OPTION_BINDING_IDENTIFIER_MOBILITY);
		aux->setMobOptionLength(LEN_BID_WITH_COA - LEN_MOBOPTS_HEADER_FIELDS);
		brr->setMobBIDmobilityArraySize(1); // No bulk registration supported
		brr->setMobBIDmobility(nOptsBID, *aux);

		nOptsBID++;
		sizeOpts += aux->getPayloadLength();

	}

	brr->setByteLength( SIZE_MOBILITY_HEADER + SIZE_BRR + sizeOpts);

	EV <<"\n<<======BRR MESSAGE FORMED; APPENDING CONTROL INFO=====>>\n";
	IPv6Address CoA;
	if (!mCoA->getProhibited()){
		//CoA  = keyMCoA.getAddr();
		CoA = keyMCoA.getDestBID(); // Address of CN
	}else {
		CoA = ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::CoA);
		//CoA = getMIPv6CoA(ie, dest);
	}


	ASSERT( !CoA.isUnspecified() );
	sendMobilityMessageToIPv6Module(brr, dest, CoA, ie->getInterfaceId());


}


void xMIPv6::processBRRMessage(BindingRefreshRequest* brr, IPv6ControlInfo* ctrlInfo)
{

	/*11.7.4
	  When a mobile node receives a packet containing a Binding Refresh
   	  Request message, the mobile node has a Binding Update List entry for
   	  the source of the Binding Refresh Request, and the mobile node wants
   	  to retain its binding cache entry at the correspondent node, then the
   	  mobile node should start a return routability procedure.*/
	IPv6Address cnAddress = ctrlInfo->getSrcAddr();
	IPv6Address& HoA = ctrlInfo->getDestAddr();

	//TODO: Bruno-todo Need to get MobityOption
	// 2010/6/7 Bruno Sousa
	MobOption_Binding_Identifier_Mobility* aux = new MobOption_Binding_Identifier_Mobility();
	if (!mCoA->getProhibited()){

		aux->setKMCoA(brr->getMobBIDmobility(0).getKMCoA());

		EV << "DBG ProcessBRR " << aux->getKMCoA().getAddr() << " BID " << aux->getKMCoA().getBID() << " destBID " <<  aux->getKMCoA().getDestBID() << "?=" << cnAddress  << endl;

	}

	KeyMCoABind  keyMCoA;
	if (!mCoA->getProhibited()){
		keyMCoA =  KeyMCoABind(aux->getKMCoA().getAddr(), aux->getKMCoA().getBID(), aux->getKMCoA().getDestBID() );
	}else {
		keyMCoA =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, cnAddress );
	}





	if (! bul->isInBindingUpdateList(keyMCoA, HoA) )
	{
		EV << "BRR not accepted - no binding for this CN. Dropping message." << endl;
	}
	else
	{
		//Bruno Sousa
		if (bul->getMobilityState(keyMCoA) == BindingUpdateList::DEREGISTER ) {
			EV << "BRR not accepted - binding is being removed. Dropping message." << endl;
		}else{
			InterfaceEntry *ie = ift->getInterfaceById( ctrlInfo->getInterfaceId() );
			initReturnRoutability( cnAddress, ie, keyMCoA);
		}
	}



	delete brr;
	delete ctrlInfo;


}


void xMIPv6::createBULEntryExpiryTimer(KeyMCoABind &keyMCoA, BindingUpdateList::BindingUpdateListEntry* entry, InterfaceEntry* ie, simtime_t scheduledTime)
{



	//Enter_Method("createBULEntryExpiryTimer()");
	//EV << "Creating BUL entry expiry timer for sim time: " << entry->bindingExpiry <<" seconds." << endl;
	cMessage* bulExpiryMsg = new cMessage("BULEntryExpiry", MK_BUL_EXPIRY);

	// we are able to associate the BUL entry later on based on HoA, CoA and destination (=HA address)
	IPv6Address& HoA = entry->homeAddress;
	IPv6Address& CoA = entry->careOfAddress;
	IPv6Address& HA = entry->destAddress;

	KeyTimer key(keyMCoA.getDestBID(), ie->getInterfaceId(), KEY_BUL_EXP, keyMCoA.getBID() );
	EV << "DBG createBULEntryExpiryTimer key " << keyMCoA.getAddr() << " | " << CoA << "  for " << HA << " BID " << keyMCoA.getBID() << endl;


	// fetch a valid TimerIfEntry obect
	BULExpiryIfEntry* bulExpIfEntry = (BULExpiryIfEntry*) getTimerIfEntry(key, EXPIRY_TYPE_BUL);

	bulExpIfEntry->dest = HA;
	bulExpIfEntry->HoA = HoA;
	bulExpIfEntry->CoA = CoA;
	bulExpIfEntry->ifEntry = ie;
	bulExpIfEntry->timer = bulExpiryMsg;

	bulExpIfEntry->BID = keyMCoA.getBID(); // Bruno Sousa

	bulExpiryMsg->setContextPointer(bulExpIfEntry); // information in the bulExpIfEntry is required for handler when message fires

	/*BULExpiryIfEntry* bulExpIfEntry = createBULEntryExpiryTimer(key, HA, HoA, CoA, ie);*/

	scheduleAt(scheduledTime, bulExpiryMsg);

	// WAS SCHEDULED FOR EXPIRY, NOT 2 SECONDS BEFORE!?!?!?
}


/*BULExpiryIfEntry* xMIPv6::createBULEntryExpiryTimer(Key& key, IPv6Adress& dest, IPv6Adress& HoA, IPv6Adress& CoA, InterfaceEntry* ie, cMessage* bulExpiryMsg)
{
	BULExpiryIfEntry* bulExpIfEntry = (BULExpiryIfEntry*) getTimerIfEntry(key, EXPIRY_TYPE_BUL);

	bulExpIfEntry->dest = HA;
	bulExpIfEntry->HoA = HoA;
	bulExpIfEntry->CoA = CoA;
	bulExpIfEntry->ifEntry = ie;
	bulExpIfEntry->timer = bulExpiryMsg;

	bulExpiryMsg->setContextPointer(bulExpIfEntry); // information in the bulExpIfEntry is required for handler when message fires

	return bulExpIfEntry;
}*/


void xMIPv6::handleBULExpiry(cMessage* msg)
{
	/*11.7.1
	  Also, if the mobile node wants the services of the home agent beyond
	  the current registration period, the mobile node should send a new
	  Binding Update to it well before the expiration of this period, even
	  if it is not changing its primary care-of address.*/
	BULExpiryIfEntry *bulExpIfEntry = (BULExpiryIfEntry*) msg->getContextPointer(); //detaching the corresponding bulExpIfEntry pointer
	ASSERT(bulExpIfEntry!=NULL);

	// we fetch the BUL entry that belongs to this expiration timer

	KeyMCoABind keyMCoA;
	if (!mCoA->getProhibited()){
		keyMCoA =  KeyMCoABind(bulExpIfEntry->CoA, bulExpIfEntry->BID, bulExpIfEntry->dest );
	}else {
		keyMCoA =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, bulExpIfEntry->dest );
	}





	BindingUpdateList::BindingUpdateListEntry* entry = bul->lookup2(keyMCoA);
	ASSERT(entry!=NULL);



	// A timer usually can appear for two times:
	// 1. Entry is shortly before expiration -> send new BU
	// 2. Entry expired -> remove
	if ( simTime() < entry->bindingExpiry )
	{
		EV << "BUL entry about to expire - creating new BU timer..." << endl;


		// we have to store the pointer to the InterfaceIdentifier as the BUL expiry timer
		// will be canceled/deleted by createBUTimer(...)
		InterfaceEntry* ie = bulExpIfEntry->ifEntry;

		// send new BU
		// we immediately create a new BU transmission timer for BU to HA
		// but we only trigger BU creation for transmission to CN
		if ( bulExpIfEntry->dest == ie->ipv6Data()->getHomeAgentAddress() ){

			createBUTimer(keyMCoA, bulExpIfEntry->dest, bulExpIfEntry->ifEntry);
		}else{
			//BindingUpdateList::BindingUpdateListEntry* entry = bul->lookup(bulExpIfEntry->dest);
			//BindingUpdateList::BindingUpdateListEntry* entry = bul->lookup(keyMCoA);
			checkForBUtoCN(keyMCoA, *entry, ie);
		}

		// we reschedule the expiration timer for expiry time
		EV<< "Resetting expiry timer... " << entry->bindingExpiry << endl;

		createBULEntryExpiryTimer(keyMCoA, entry, ie, entry->bindingExpiry);

		// ...and that's it.
		// createBUTimer will take care of cancelling/overwriting the current BU timer.
		// As soon as we receive a valid BA to this BU the BUL expiry timer will be reset.


	}
	else
	{
		EV << "DBGTimer BUL entry has expired - removing entry and associated structures..." << keyMCoA.getAddr() << endl;
		EV << "evMIPv6_FailureDetection" << simTime() << "entry expired " << keyMCoA.getAddr() << endl;



		// TODO group everything from below in a purgeMobilityState() method

		entry->state = BindingUpdateList::NONE; // UPDATE CB, 26.11.2008
		// remove binding
		//bul->removeBinding(keyMCoA);
		clear_and_remove_Binding(keyMCoA, bulExpIfEntry->ifEntry);

		// remove all timers
		int interfaceID = bulExpIfEntry->ifEntry->getInterfaceId();
		removeTimerEntries2(bulExpIfEntry->dest, interfaceID);

		// destroy tunnel
		tunneling->destroyTunnel(bulExpIfEntry->CoA, bulExpIfEntry->dest);

		// and remove entry from list
		cancelTimerIfEntry(bulExpIfEntry->dest, interfaceID, KEY_BUL_EXP, keyMCoA.getBID());

		// deletion of the message already takes place in the cancelTimerIfEntry(.., KEY_BUL_EXP);
		//delete msg;

	}

}


void xMIPv6::createBCEntryExpiryTimer(KeyMCoABind &keyMCoA, IPv6Address HoA, InterfaceEntry* ie, simtime_t scheduledTime)
{
	cMessage* bcExpiryMsg = new cMessage("BCEntryExpiry", MK_BC_EXPIRY);

	//Key key(HoA, ie->getInterfaceId(), KEY_BC_EXP, keyMCoA->getBID());
	KeyTimer key(keyMCoA.getDestBID(), ie->getInterfaceId(), KEY_BC_EXP, keyMCoA.getBID());
	//EV << "DBG createBCEntryExpiryTimer key " << keyMCoA.getAddr() << "  for " << HoA << " BID " << keyMCoA.getBID() << endl;


	// fetch a valid TimerIfEntry obect
	BCExpiryIfEntry* bcExpIfEntry = (BCExpiryIfEntry*) getTimerIfEntry(key, EXPIRY_TYPE_BC);

	bcExpIfEntry->dest = HoA;
	bcExpIfEntry->HoA = HoA;
	bcExpIfEntry->ifEntry = ie;
	bcExpIfEntry->timer = bcExpiryMsg;

	bcExpIfEntry->BID   = keyMCoA.getBID(); // Bruno Sousa

	bcExpiryMsg->setContextPointer(bcExpIfEntry); // information in the bulExpIfEntry is required for handler when message fires

	scheduleAt(scheduledTime, bcExpiryMsg);
	EV << "Scheduled BC expiry for time " << scheduledTime << "s" << endl;
}


void xMIPv6::handleBCExpiry(cMessage* msg)
{

	/*10.3.1
	  The home agent MAY further decrease the specified lifetime for the
	  binding, for example based on a local policy.  The resulting
	  lifetime is stored by the home agent in the Binding Cache entry,
	  and this Binding Cache entry MUST be deleted by the home agent
	  after the expiration of this lifetime.*/
	/*9.5.2
	  Any Binding Cache entry MUST be deleted after the expiration of its lifetime.*/
	EV << "BC entry has expired - removing entry and associated structures..." << endl;

	BCExpiryIfEntry* bcExpIfEntry = (BCExpiryIfEntry*) msg->getContextPointer(); //detaching the corresponding bulExpIfEntry pointer
	ASSERT(bcExpIfEntry!=NULL);

	KeyMCoABind auxKey;
	if (!mCoA->getProhibited()){
		auxKey =  KeyMCoABind(bcExpIfEntry->HoA, bcExpIfEntry->BID, bcExpIfEntry->dest);
	}else {
		auxKey =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, bcExpIfEntry->dest);
	}
	// remove binding from BC
	bc->deleteEntry(auxKey);
	EV <<  "DBGBC - Deleting " << auxKey.getBID() << ", " << auxKey.getAddr() << endl;

	// and remove the tunnel
	tunneling->destroyTunnelFromTrigger(bcExpIfEntry->HoA);

	// and remove entry from list
	cancelTimerIfEntry(bcExpIfEntry->dest, bcExpIfEntry->ifEntry->getInterfaceId(), KEY_BC_EXP, bcExpIfEntry->BID);
	// deletion of the message already takes place in the cancelTimerIfEntry(.., KEY_BC_EXP);

	// TODO
	// in the future we might send a Binding Refresh Request shortly before the expiration of the BCE


}


void xMIPv6::createTokenEntryExpiryTimer(IPv6Address& cnAddr, InterfaceEntry* ie, simtime_t scheduledTime, int tokenType, KeyMCoABind& keyMCoA)
{
	cMessage* tokenExpiryMsg = new cMessage("TokenEntryExpiry", MK_TOKEN_EXPIRY);

	//KeyTimer key(cnAddr, ie->getInterfaceId(), tokenType, MCOA_UNSIGNED_BID);
	KeyTimer key(keyMCoA.getDestBID(), ie->getInterfaceId(), tokenType, keyMCoA.getBID());

	//EV << "DBG createTokenEntryExpiryTimer key " << keyMCoA.getAddr() << "  for " << cnAddr << " BID" << keyMCoA.getBID() << endl;


	// fetch a valid TimerIfEntry obect
	TokenExpiryIfEntry* tokenExpIfEntry = (TokenExpiryIfEntry*) getTimerIfEntry(key, EXPIRY_TYPE_TOKEN);

	tokenExpIfEntry->cnAddr = cnAddr;
	tokenExpIfEntry->ifEntry = ie;
	tokenExpIfEntry->timer = tokenExpiryMsg;

	tokenExpIfEntry->tokenType = tokenType;

	tokenExpIfEntry->dest   = cnAddr;
	tokenExpIfEntry->adrCoA = keyMCoA.getAddr();
	tokenExpIfEntry->BID    = keyMCoA.getBID();

	tokenExpiryMsg->setContextPointer(tokenExpIfEntry);

	scheduleAt(scheduledTime, tokenExpiryMsg);
	EV << "Scheduled token expiry for time " << scheduledTime << "s" << endl;
}


void xMIPv6::handleTokenExpiry(cMessage* msg)
{
	TokenExpiryIfEntry* tokenExpIfEntry = (TokenExpiryIfEntry*) msg->getContextPointer(); //detaching the corresponding tokenExpIfEntry pointer
	ASSERT(tokenExpIfEntry!=NULL);

	//TODO: Bruno fixme CoTI may contain several prefixes.

	KeyMCoABind keyMCoA;
	if (!mCoA->getProhibited()){
		keyMCoA = KeyMCoABind(tokenExpIfEntry->adrCoA, tokenExpIfEntry->BID, tokenExpIfEntry->dest);
	}else {
		keyMCoA =  KeyMCoABind(IPv6Address::UNSPECIFIED_ADDRESS, MCOA_UNSIGNED_BID, tokenExpIfEntry->dest);
	}

	if ( tokenExpIfEntry->tokenType == KEY_CTOKEN_EXP )
	{
		EV<< "Care-of keygen token for CN=" << keyMCoA.getDestBID() << " BID " << keyMCoA.getBID() << " CoA=" << keyMCoA.getAddr()   << " expired";

		bul->resetCareOfToken( keyMCoA, tokenExpIfEntry->ifEntry->ipv6Data()->getMNHomeAddress() );
	}
	else if ( tokenExpIfEntry->tokenType == KEY_HTOKEN_EXP )
	{
		EV << "Home keygen token for CN=" << keyMCoA.getAddr() << " BID " << keyMCoA.getBID()   << " expired";
		bul->resetHomeToken( keyMCoA, tokenExpIfEntry->ifEntry->ipv6Data()->getMNHomeAddress() );
	}
	else
		opp_error("Unkown value for tokenType!");

	EV << "...removed token from BUL." << endl;

	if (bul->getMobilityState(keyMCoA) == BindingUpdateList::RR_COMPLETE)
		bul->setMobilityState(keyMCoA, BindingUpdateList::RR);

	//cancelTimerIfEntry(tokenExpIfEntry->cnAddr, tokenExpIfEntry->ifEntry->getInterfaceId(), tokenExpIfEntry->tokenType, MCOA_UNSIGNED_BID);
	cancelTimerIfEntry(keyMCoA.getDestBID(), tokenExpIfEntry->ifEntry->getInterfaceId(), tokenExpIfEntry->tokenType, keyMCoA.getBID());

	// and now send a Test Init message to retrieve a new token
	if ( tokenExpIfEntry->tokenType == KEY_CTOKEN_EXP ){
		EV << "DBG handleBULExpiry bef CoTI" << keyMCoA.getAddr() << "  BID " << keyMCoA.getBID() << endl;

		createAndSendCoTIMessage(tokenExpIfEntry->cnAddr, tokenExpIfEntry->ifEntry, keyMCoA);
	}else{

		EV << "DBG handleBULExpiry before HoTI" << keyMCoA.getAddr() << " BID " << keyMCoA.getBID() <<  " and dest " << keyMCoA.getDestBID() << endl;

		createAndSendHoTIMessage(tokenExpIfEntry->cnAddr, tokenExpIfEntry->ifEntry, keyMCoA);
	}
	//delete msg;


}


int xMIPv6::get_and_calcBID(const IPv6Address inadr, InterfaceEntry *ie){

	int bidaux;
	ASSERT(!inadr.isUnspecified());

	/*
	 * CoA can not be HoA.
	 */
	if (ie != NULL){
		//When MIPv6 has not been initiated
		if (ie->ipv6Data()->getMNHomeAddress().isUnspecified() && !mipv6sm->getMIPv6triggered() ){
			EV << "xMIPv6 trying to include HoA in the BID list... (ignoring) MIPv6 not triggered yet!" << inadr << endl;
			return MCOA_HOA_AS_BID;
		}

		if (ie->ipv6Data()->getMNHomeAddress() == inadr ){
			EV << "xMIPv6 trying to include HoA in the BID list... (ignoring) " << inadr << endl;
			return MCOA_HOA_AS_BID;
		}
	}else {
		// Assume that it is on the home network
		EV << "xMIPv6 trying to include HoA in the BID list... (ignoring) NULL interface " << inadr << endl;
		return MCOA_HOA_AS_BID;
	}

	if(!inadr.isUnspecified()) {
		if (!mCoA->getProhibited()){
			if (CoABIDs.size()==0){

				CoABIDs[inadr] = 1;
				EV << "[MCOA] NEW ADR ADDED " << inadr <<" with BID=1" <<  endl;

				return 1;

			}else {
				CoABIDList::iterator it = CoABIDs.find(inadr);
				if (it!=CoABIDs.end()){
					return (it->second);
				}else{
					bidaux=(CoABIDs.size()+1)% 65536;
					CoABIDs[inadr]= bidaux;
					EV << "[MCOA] NEW ADR ADDED " << inadr <<" with BID=" << bidaux <<  endl;

					return bidaux;
				}
			}
		}else { // Standard MIPv6
			return MCOA_UNSIGNED_BID;
		}
	}else {
		EV << "not added a non specified address " << inadr << endl;
		return MCOA_UNSIGNED_BID;
	}
}

IPv6Address xMIPv6::get_adr_from_bid(const int bid){

	for (CoABIDList::iterator it = CoABIDs.begin(); it != CoABIDs.end(); it++){
		if (it->second == bid){
			return (it->first);
		}
	}
	return NULL;
}


bool xMIPv6::eraseBID(const IPv6Address &inadr){

	CoABIDList::iterator it = CoABIDs.find(inadr);
	if (it != CoABIDs.end()){
		CoABIDs.erase(it);
		return true;
	}
	return false;
}
void xMIPv6::prtTimers(void){


	EV << "[MCOA] TIMERS CONTENTS " << endl;
	for (TransmitIfList::iterator it = transmitIfList.begin();
			it != transmitIfList.end(); it++){
		KeyTimer aux = (*it).first;
		TimerIfEntry * tif = (*it).second;
		EV << "<KEY> " << aux.type << ","<< aux.BID << ", "<< aux.dest << " if>" << aux.interfaceID  << " <VALUE> " << tif->dest << endl;
	}

}

void xMIPv6::addCapabilitiesNode(IPv6Address adrNode, CapMCoA capNode){
	NodesMCoACap::iterator it = nodesMCoACaps.find(adrNode);
	if (it != nodesMCoACaps.end()){
		it->second.mCoA_support 						= capNode.mCoA_support;
		it->second.m_prohibited 						= capNode.m_prohibited;
		it->second.m_bulk_reg_prohibited 				= capNode.m_bulk_reg_prohibited;
		it->second.mc_sim_home_and_foreign_prohibited 	= capNode.mc_sim_home_and_foreign_prohibited;
	}else {
		nodesMCoACaps[adrNode] = capNode;
	}

}

bool xMIPv6::delCapabilitiesNode(IPv6Address adrNode){
	NodesMCoACap::iterator it = nodesMCoACaps.find(adrNode);
	if (it != nodesMCoACaps.end()){
		nodesMCoACaps.erase(it);
		return true;
	}else {
		return false;
	}

}

bool xMIPv6::updateCnList(const IPv6Address &destAddress, int iBID){
	CNListBIDs::iterator it = cnListBIDs.find(destAddress);


	//EV << "updateCNList " << destAddress  << " with BID " << iBID << endl;
	bool notinvec = true;

	std::vector<int> aux;
	if (iBID != MCOA_HOA_AS_BID){
		EV << "updateCNList " << destAddress  << " with BID " << iBID << endl;
		aux.push_back(iBID);
	}else {
		EV << "updateCNList " << destAddress  << " only adding destination address and no BID" << endl;
	}


	if (it == cnListBIDs.end()){
		cnListBIDs.insert(std::make_pair(destAddress, aux));
	}else{
		for (uint i=0; i < ((*it).second).size(); i++){
			if ( ((*it).second).at(i)==iBID  ){
				notinvec = false;
				break;
			}
		}

		if (notinvec && iBID != MCOA_HOA_AS_BID)
		  ((*it).second).push_back(iBID);
	}

	return true;
}

bool xMIPv6::deleteCnList(const IPv6Address &destAddress, int iBID){
	CNListBIDs::iterator it = cnListBIDs.find(destAddress);

	if (it != cnListBIDs.end()){
		(*it).second.clear();
		cnListBIDs.erase(it);
	}else{
		return false;
	}

	return true;
}


bool xMIPv6::delBIDCnList(const IPv6Address &destAddress, int iBID){
	CNListBIDs::iterator it = cnListBIDs.find(destAddress);
	if (it != cnListBIDs.end()){
		//cnBIDs auxvec = (*it).second;
		cnBIDs::iterator CRiterator = find((*it).second.begin(), (*it).second.end(), iBID);
		if ( CRiterator != (*it).second.end() ){
			(*it).second.erase(CRiterator);
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}

	return true;

}



bool xMIPv6::clear_and_remove_Binding(KeyMCoABind &key, InterfaceEntry* ie ){

	//EV << " Removing entry in Binding Update List and clear timer" << endl;
	cancelTimerIfEntry(key.getDestBID(), ie->getInterfaceId(), KEY_BU, key.getBID()); // 11.06.08 - CB

	cancelTimerIfEntry(key.getDestBID(), ie->getInterfaceId(), KEY_BUL_EXP, key.getBID()); // Bruno Sousa 2010/5/13

	cancelTimerIfEntry(key.getDestBID(), ie->getInterfaceId(), KEY_CTOKEN_EXP, key.getBID()); // Bruno Sousa 2010/5/13
	cancelTimerIfEntry(key.getDestBID(), ie->getInterfaceId(), KEY_HTOKEN_EXP, key.getBID()); // Bruno Sousa 2010/5/13
	bool res =bul->removeBinding(key);

	return res;

}

IPv6Address xMIPv6::get_addr_randomly_from_BIDS(InterfaceEntry* ie )
{
	IPv6Address ret = IPv6Address::UNSPECIFIED_ADDRESS;

	int idx = 1 + (int)intrand(CoABIDs.size()); //intrand generates values in the interval [0, size -1 ]
	int cnt=1;

	EV << "Index " << idx  << " of size " << CoABIDs.size() << endl;
	for (CoABIDList::iterator it = CoABIDs.begin();
		 it != CoABIDs.end();
		 it++)
	{
		/*
		if (it->second == idx){
			ret = it->first;
			break;
		}
		*/
		if (idx == cnt){
			ret = it->first;
			break;
		}
		cnt++;
	}

	ASSERT(!ret.isUnspecified()); //Myassert
	while (ie->ipv6Data()->getMNHomeAddress() == ret){
		 EV << "PREFERED ADDRESS CANNOT BE HOME ADDRESS "<< ret << endl;
		 ret = get_addr_randomly_from_BIDS(ie);
		 EV << "And Now "<< ret << endl;
	 }

	return ret;

}


IPv6Address xMIPv6::getMIPv6CoA(InterfaceEntry *ie, IPv6Address dest){

	IPv6Address CoA = IPv6Address::UNSPECIFIED_ADDRESS;

	if (mipv6sm->getReturnedHome()){

		CoA = mipv6sm->getMIPv6preferredAddr();
	}else {


		if (!mCoA->getProhibited()){
				CoA = ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::CoA); // source address of MN
				if (mCoA->getTypeUseMCoA()==MCOA_TUN_SINGLE_ADR_SINGLE){
						CoA = ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::CoA); // source address of MN

				}else{
					if( dest != ie->ipv6Data()->getHomeAgentAddress()){  //for CNs
						CoA = mipv6sm->getMIPv6preferredAddr();
					}
				}

				EV << "GETMIPv6 MCOA --> setting new address " << CoA << endl;
		}else {
			/*
			 * When there are multiple CoAs in the node, we must always choose the same, otherwise MIPv6 won't work.
			 */
			if (!mipv6sm->getSetPreferedAddr()){
				CoA = ie->ipv6Data()->getGlobalAddressReverse(IPv6InterfaceData::CoA); // source address of MN To chose the first one CoA
				EV << "GETMIPv6COA --> setting new address " << CoA << endl;
				mipv6sm->setMIPv6preferredAddr(CoA);
				mipv6sm->setSetPreferedAddr(true);
			}else{
				if (mipv6sm->getReturnedHome()){ // when returning home MN should use its HoA.
					CoA = ie->ipv6Data()->getMNHomeAddress();
				}else{
					CoA = mipv6sm->getMIPv6preferredAddr();
				}
			}
		}
	}
	if (CoA.isUnspecified()){
		CoA = ie->ipv6Data()->getMNHomeAddress();
	}

	//to avoid chosing values non-existent
	if (!ie->ipv6Data()->hasAddress(CoA)){
		EV << "SYNC Address in getMIPv6CoA" << endl;

		ie->ipv6Data()->resetPreferredAddress();
		CoA = ie->ipv6Data()->getPreferredAddress();
		mipv6sm->setMIPv6preferredAddr(CoA);
	}
	EV << "SET PREFERED ADDRESS => " << CoA  << endl;
	return CoA;
}

void xMIPv6::perform_clean_coa(KeyMCoABind &key, bool isHA){

	BindingUpdateList::BindingUpdateListEntry *entry = bul->BIDlookup(key.BID, key);

	if (entry == NULL){
		if (eraseBID(key.getAddr())){
			EV << "Clean from BID " << key.getAddr() << endl;
		}

		if (!isHA){
			delBIDCnList(key.destBID, key.BID);
		}
	}
}

void xMIPv6::receiveChangeNotification(int category, const cPolymorphic *details)
{
    if (simulation.getContextType()==CTX_INITIALIZE)
        return;  // ignore notifications during initialize

    Enter_Method_Silent();
    printNotificationBanner(category, details);

    if (category==NF_MIPv6_MN_RETURNED_HOME)
    {
    	//TODO:
    	uint delay_clean_at_home = 2;
    	cMessage *clean_at_home = new cMessage("MIPv6_MN_RETURNED_HOME", MK_MCOA_CLEAN_AT_HOME);

    	scheduleAt(simTime()+delay_clean_at_home, clean_at_home  );
    	EV << "Finally at home performing a force clean" << endl;


    }
}

void xMIPv6::perform_clean_at_home(cMessage *msg){

	EV << "doing a clean at " << simTime() << endl;

	bubble("TO perform clean, I'm at home");

	//Bu Timers
	//TODO:  iterate by each item and call cancelAndDrop method to perform a clean destroy messages
	prtTimers();
	//transmitIfList.clear();

	bul->prtBindings();
	// bul

	// Are there any tunnels ??
	tunneling->prtTunnels();

	/*
	if (rt6->isMobileNode())
		bul->removeALLBindings();
	*/

	// CoABIDS
	//CoABIDs.clear();

	// cnList
	cnListBIDs.clear();

	//nodes capabilities -- NOT SURE
	//nodesMCoACaps.clear();

	//initialize the state machine
	mipv6sm->initialize();

	//initialize CoAs per interface
	interfaceCoAList.clear();

	delete msg;
}




std::map<xMIPv6::KeyTimer,xMIPv6::TimerIfEntry*>::iterator xMIPv6::ftimer(KeyTimer key){
	TransmitIfList::iterator pos = transmitIfList.begin();

	for (pos; pos != transmitIfList.end(); pos++){
		if (pos->first.type == key.type && pos->first.dest == key.dest
			&& pos->first.BID == key.BID && pos->first.interfaceID == key.interfaceID	){
			//EV << "FOUND FOUND " << endl;
			break;
		}
	}
	return pos;
}


bool xMIPv6::sync_preferred_address(IPv6Address CoA_del, InterfaceEntry *ie){

	bool res=false;
	if (CoA_del== mipv6sm->getMIPv6preferredAddr()){
		 ie->ipv6Data()->resetPreferredAddress();
		 IPv6Address newCoA = ie->ipv6Data()->getPreferredAddress();
		 mipv6sm->setMIPv6preferredAddr(newCoA);
		 res = true;
		 EV << "SYNC Address "<< CoA_del  << " was synced to " << newCoA << endl;
	}
	return res;
}
