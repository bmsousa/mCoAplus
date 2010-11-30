/**
 * Copyright (C) 2007
 * Faqir Zarrar Yousaf
 * Communication Networks Institute, Technical University Dortmund (TU Dortmund), Germany.
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


#include <algorithm>
#include "opp_utils.h"
#include "BindingUpdateList.h"
#include "IPv6InterfaceData.h"

// secret key used in RR by CN
#define KCN	1


Define_Module(BindingUpdateList);


std::ostream& operator<<(std::ostream& os, const BindingUpdateList::BindingUpdateListEntry& bul)
{
    os << "Destination: " <<bul.destAddress <<" HoA of MN: " << bul.homeAddress <<" CoA of MN: "<<bul.careOfAddress <<"\n"
       << "Binding Lifetime: "<<bul.bindingLifetime << " binding expiry: "<<SIMTIME_STR(bul.bindingExpiry) <<" BU Sequence#: "<<bul.sequenceNumber
       << " Sent Time: "<<SIMTIME_STR(bul.sentTime) <</*" Next_Tx_Time: "<<bul.nextBUTx <<*/" BU_Ack: "<<bul.BAck <<"\n";

    // this part will only be displayed if the BUL entry is for CN registration
    if ( bul.sentHoTI != 0 )
    {
    	os << "Sent Time HoTI: " << SIMTIME_STR(bul.sentHoTI) << " HoTI cookie: " << bul.cookieHoTI
    	   << " home token: " << bul.tokenH << "\n";
    }
    if ( bul.sentCoTI != 0 )
    {
    	os << " Sent Time CoTI: " << SIMTIME_STR(bul.sentCoTI) << " CoTI cookie: " << bul.cookieCoTI
    	   << " care-of token: " << bul.tokenC << "\n";
    }

    os << "State: ";
    switch (bul.state)
    {
	    case BindingUpdateList::NONE:
	    		os << "none";
	    		break;
	    case BindingUpdateList::RR:
	    		os << "Return Routability";
	    		break;
	    case BindingUpdateList::RR_COMPLETE:
	    		os << "Return Routability completed";
	    		break;
	    case BindingUpdateList::REGISTER:
	    		os << "Registering";
	    		break;
	    case BindingUpdateList::REGISTERED:
	    		os << "Registered";
	    		break;
	    case BindingUpdateList::DEREGISTER:
	    		os << "Deregistering";
	    		break;
	    default:
	    		os << "Unknown";
	    		break;
    }
    os << endl;

    return os;
}


BindingUpdateList::BindingUpdateList()
{
}


BindingUpdateList::~BindingUpdateList()
{
//     for (unsigned int i=0; i<bindingUpdateList.size(); i++)
//         delete bindingUpdateList[i];
}

void BindingUpdateList::initialize(int stage)
{
	if (stage==1)
	{
    	WATCH_MAP(bindingUpdateList); //added by Zarrar Yousaf
	}

}


void BindingUpdateList::handleMessage(cMessage *msg)
{
    opp_error("This module doesn't process messages");
}


void BindingUpdateList::addOrUpdateBUL(const KeyMCoABind& keyMCoA, const IPv6Address& dest, const IPv6Address& hoa, const IPv6Address& coa, const uint lifetime, const uint seq, const simtime_t buSentTime, const int iIfID)//,const simtime_t& nextBUSentTime)
{
	// modified structure - CB

	// search for entry
	BindingUpdateList::BindingUpdateListEntry* entry = lookup(keyMCoA);

	// if it is not yet existing, create it
	if (entry == NULL)
	{
		/*bindingUpdateList[dest].destAddress = dest;
		entry = & bindingUpdateList[dest];
		initializeBUValues(*entry);*/
		entry = createBULEntry(keyMCoA, dest);

	}

	//EV<<"++++++++++++++++++++Binding Update List Being Updated in Routing Table6 ++++++++++++++ " << endl;


	entry->homeAddress = hoa;
	entry->careOfAddress = coa;
	// update lifetime 11.06.08 - CB
	entry->bindingLifetime = lifetime; // for the moment a constant but then it is supposed to decrement with time.
	entry->bindingExpiry = simTime() + lifetime; // binding expires at this point in time
	//TODO bindingUpdateList[dest].remainingLifetime = ;
	entry->sentTime = buSentTime; //the time at which the BU, whose ack is awaited is sent
	//entry->nextBUTx = nextBUSentTime; //the nextScgheduledTime at which the BU will be sent in case of timeout.
	entry->sequenceNumber = seq; //seq number of the last BU sent.
	entry->BAck = false;

	EV << "[MCoA]-addOrUpdateBUL Added Adr in BUL" << dest << "," << keyMCoA.Addr << " with BID " << keyMCoA.BID  << " for " << keyMCoA.getDestBID()
			<< " Expire " << entry->bindingExpiry
			<< " with Sequence " << entry->sequenceNumber
			<< endl;


}


BindingUpdateList::BindingUpdateListEntry* BindingUpdateList::createBULEntry(const KeyMCoABind &keyMCoA, const IPv6Address &dest)
{
	BindingUpdateListEntry* entry = &bindingUpdateList[keyMCoA];
	entry->destAddress = dest;

	//bindingUpdateList[keyMCoA].destAddress = dest;

	//BindingUpdateListEntry& entry = bindingUpdateList[keyMCoA];
	////BindingUpdateList::BindingUpdateListEntry* entry = & bindingUpdateList[dest];
	initializeBUValues(*entry);
	EV << "CREATED ENTRY IN BUL "  << keyMCoA << endl;

	//return &entry;
	return entry;
}


void BindingUpdateList::initializeBUValues(BindingUpdateListEntry& entry)
{
	// normal BU values
	entry.bindingLifetime = 0;
	entry.bindingExpiry = 0;
	//TODO bindingUpdateList[dest].remainingLifetime = ;
	entry.sentTime = 0;
	//entry.nextBUTx = 0;
	entry.sequenceNumber = 0;
	entry.BAck = false;

	// RR specific values
	entry.sentHoTI = 0;
	entry.sentCoTI = 0;
	entry.cookieHoTI = UNDEFINED_COOKIE;
	entry.cookieCoTI = UNDEFINED_COOKIE;
	//entry.sendNext = 0;
	entry.tokenH = UNDEFINED_TOKEN;
	entry.tokenC = UNDEFINED_TOKEN;
	// 21.07.08 - CB
	entry.state = NONE;

	//Bruno Sousa
	entry.lastBAseqNumber = LASTBASEQ;
}


void BindingUpdateList::addOrUpdateBUL(const KeyMCoABind& keyMCoA, const IPv6Address& dest, const IPv6Address& addr, const simtime_t sentTime, const int cookie, bool HoTI = false)
{
	EV<<"\n++++++++++++++++++++Binding Update List for HoTI/CoTI Being Updated in Routing Table6 ++++++++++++++\n";


	// search for entry
	BindingUpdateList::BindingUpdateListEntry* entry = lookup(keyMCoA);

	// if it is not yet existing, create it
	if (entry == NULL)
	{
		bindingUpdateList[keyMCoA].destAddress = dest;
		entry = & bindingUpdateList[keyMCoA];
		initializeBUValues(*entry);

	}


	if (HoTI) // those values are from the HoTI message
	{
		entry->homeAddress = addr;
		entry->sentHoTI = sentTime;
		entry->cookieHoTI = cookie;
	}
	else // and those from the CoTI
	{
		entry->careOfAddress = addr;
		entry->sentCoTI = sentTime;
		entry->cookieCoTI = cookie;
	}

}

BindingUpdateList::BindingUpdateListEntry* BindingUpdateList::BIDlookup(uint16 inBID, const KeyMCoABind& dest)
{

	for (BindingUpdateList6::iterator i = bindingUpdateList.begin(); i!= bindingUpdateList.end();i++){
		if ((i->first).getBID() == inBID) {
			EV<<"mCOA FOUND record in bulEntry by Address and BID" << endl;
			return &(i->second);
		}
	}


    return lookup(dest);
}


/**
	 * Retunrns the CoA in the key of BUL by BID and destBID
	 */
IPv6Address BindingUpdateList::getCoA_in_key(int iBID, IPv6Address destBID){
	IPv6Address adr= IPv6Address::UNSPECIFIED_ADDRESS;
	for (BindingUpdateList6::iterator i = bindingUpdateList.begin(); i!= bindingUpdateList.end();i++){
		if ((i->first).getBID() == iBID && (i->first).getDestBID() == destBID) {
			adr = (i->first).Addr;

			return (adr);
		}
	}
	return adr;
}

BindingUpdateList::BindingUpdateListEntry* BindingUpdateList::lookup(const KeyMCoABind keyMCoA)
{
	BindingUpdateList6::iterator i = bindingUpdateList.find(keyMCoA);

	BindingUpdateList::BindingUpdateListEntry* entry;

	if (i == bindingUpdateList.end()){
		entry = NULL;
	}else {
		entry = &(i->second);
	}

    //return ( i == bindingUpdateList.end() ) ? NULL : &(i->second);
	return entry;
}

BindingUpdateList::BindingUpdateListEntry* BindingUpdateList::lookup2(const KeyMCoABind &keyMCoA)
{
	BindingUpdateList6::iterator i = bindingUpdateList.begin();

	KeyMCoABind keyAux;
	for (i; i!=bindingUpdateList.end(); i++ ){
		keyAux = (i->first);
		if (keyAux.getBID() == keyMCoA.getBID() &&
			keyAux.getAddr() == keyMCoA.getAddr() &&
			keyAux.getDestBID() == keyMCoA.getDestBID())
		{
			return &(i->second);
		}
	}


    return NULL;
}


BindingUpdateList::BindingUpdateListEntry* BindingUpdateList::fetch(const KeyMCoABind &keyMCoA, const IPv6Address &dest)
{
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(keyMCoA);

    if (entry == NULL)
    	return createBULEntry(keyMCoA,dest);
    else
    	return entry;
}



BindingUpdateList::MobilityState BindingUpdateList::getMobilityState(const KeyMCoABind& dest)
{
	BindingUpdateList6::iterator i = bindingUpdateList.find(dest);

    if ( i == bindingUpdateList.end() )
    	return NONE;
    else
    	return i->second.state;
}

void BindingUpdateList::setMobilityState(const KeyMCoABind& dest, BindingUpdateList::MobilityState state)
{
	BindingUpdateList6::iterator i = bindingUpdateList.find(dest);

    if ( i != bindingUpdateList.end() )
    	i->second.state = state;
}


int BindingUpdateList::generateBAuthData(const KeyMCoABind& dd, const IPv6Address& CoA)
{
	EV << " to generate Binding Authorization Data for " << dd <<  endl;
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dd);

	if ( entry == NULL )
	{
		EV << "Impossible to generate Binding Authorization Data as CN is not existing in BUL! " << dd <<  endl;

		prtBindings();

		//TODO: 2010/06/25 Bruno Sousa  commented the line has in the verification of the BU
		// this leads to a rejection in the CN
		//return 0;

		return BindingUpdateList::generateKey(HO_TOKEN, CO_TOKEN, CoA);
	}

	// generate the key
	return BindingUpdateList::generateKey(entry->tokenH, entry->tokenC, CoA);
}


int BindingUpdateList::generateKey(int homeToken, int careOfToken, const IPv6Address& CoA)
{
	// use a dummy value
	return homeToken+careOfToken;
}


int BindingUpdateList::generateHomeToken(const IPv6Address& HoA, int nonce)
{
	return HO_TOKEN;
}


int BindingUpdateList::generateCareOfToken(const IPv6Address& CoA, int nonce)
{
	return CO_TOKEN;
}


void BindingUpdateList::resetHomeToken(const KeyMCoABind& dest, const IPv6Address& hoa)
{
	prtBindings();

	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);
	ASSERT(entry != NULL);

	entry->tokenH = UNDEFINED_TOKEN;
	//entry->sentHoTI = 0;
}


void BindingUpdateList::resetCareOfToken(const KeyMCoABind& dest, const IPv6Address& hoa)
{
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);
	ASSERT(entry != NULL);

	entry->tokenC = UNDEFINED_TOKEN;
	//entry->sentCoTI = 0;
}


bool BindingUpdateList::isHomeTokenAvailable(const KeyMCoABind& dest, InterfaceEntry* ie)
{
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);
	ASSERT(entry != NULL);

	return entry->tokenH != UNDEFINED_TOKEN &&
		   (entry->sentHoTI + ie->ipv6Data()->_maxTokenLifeTime()) > simTime();
}


bool BindingUpdateList::isCareOfTokenAvailable(const KeyMCoABind& dest, InterfaceEntry* ie)
{
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);
	ASSERT(entry != NULL);

	return entry->tokenC != UNDEFINED_TOKEN &&
		   (entry->sentCoTI + ie->ipv6Data()->_maxTokenLifeTime()) > simTime();
}


bool BindingUpdateList::isInBindingUpdateList(const KeyMCoABind& dest)
{
	return bindingUpdateList.find(dest) != bindingUpdateList.end();
}


uint BindingUpdateList::getSequenceNumber(const KeyMCoABind& dest)
{
	// search for entry
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);

	if (entry == NULL)
		return 0;
	else
		return entry->sequenceNumber;
}

uint16 BindingUpdateList::getBID(const IPv6Address& homeAddr, const IPv6Address& CoA)
{
	for (BindingUpdateList6::iterator i = bindingUpdateList.begin();i!= bindingUpdateList.end();i++){
		if ((i->first).Addr == homeAddr){
			if ((i->second).careOfAddress ==CoA ){
				return ((i->first).getBID());
			}
		}

	}
	return MCOA_UNSIGNED_BID;

}



const IPv6Address& BindingUpdateList::getCoA(const KeyMCoABind& dest)
{
	// search for entry
	//BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);
	BindingUpdateList::BindingUpdateListEntry* entry = lookup(dest);

	if (entry == NULL){
		EV << "Search Key " << dest << endl << endl;
		prtBindings();
		EV << " " << endl;
		EV << " " << endl;
		EV << " " << endl;
		EV << " " << endl;
	}
	ASSERT(entry!=NULL);

	return entry->careOfAddress;
}


bool BindingUpdateList::isInBindingUpdateList(const KeyMCoABind& dest, const IPv6Address& HoA)
{
	BindingUpdateList6::iterator pos = bindingUpdateList.find(dest);

	if ( pos == bindingUpdateList.end() )
		return false;
	else
		return pos->second.homeAddress == HoA;
}


bool BindingUpdateList::isValidBinding(const KeyMCoABind& dest)
{
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);

	if (entry == NULL)
		return false;

	return entry->BAck && ( entry->bindingLifetime < SIMTIME_DBL(simTime()) );
}




bool BindingUpdateList::isBindingAboutToExpire(const KeyMCoABind& dest)
{
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);

	if (entry == NULL)
		return true;

	return entry->bindingLifetime < SIMTIME_DBL(simTime()) - PRE_BINDING_EXPIRY;
}


bool BindingUpdateList::isEmpty(){
	if (bindingUpdateList.empty()) return true;
	else return false;
}

bool BindingUpdateList::sentBindingUpdate(const KeyMCoABind& dest)
{
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);

	if (entry == NULL)
		return false;

	return (entry->BAck || (entry->tokenH != UNDEFINED_TOKEN && entry->tokenC != UNDEFINED_TOKEN) )
			&& entry->sentTime != 0;
}


bool BindingUpdateList::removeBinding(const KeyMCoABind& keyMCoA)
{


	BindingUpdateList6::iterator it = bindingUpdateList.begin();

	KeyMCoABind keyAux;
	for (it; it!=bindingUpdateList.end(); it++ ){
		keyAux = (it->first);
		if (keyAux.getBID() == keyMCoA.getBID() && keyAux.Addr == keyMCoA.Addr
				&& keyAux.getDestBID() == keyMCoA.getDestBID()){

			bindingUpdateList.erase(it);
			EV << "Binding Sucessfully removed " << keyMCoA << endl;
			return true;
		}
	}
	return false;

	/*
	BindingUpdateList::BindingUpdateListEntry* entry = lookup(dest);

	ASSERT(entry!=NULL);

	if ( (entry->tokenH != UNDEFINED_TOKEN) || (entry->tokenC != UNDEFINED_TOKEN) )
		// for CNs, we just delete all entries
		resetBindingCacheEntry(*entry);
	else
		// the BUL entry to the HA is completely deleted
		bindingUpdateList.erase(dest);
	*/
}


bool BindingUpdateList::removeBindingByDest(const IPv6Address& dest)
{
	bool res =false;



	for (BindingUpdateList6::iterator it2 = bindingUpdateList.begin(); it2!= bindingUpdateList.end(); ){

		if ((it2->first).destBID == dest){
			EV << "BUL Deleting binding with BID " << (it2->first).getBID() << endl;

			bindingUpdateList.erase(it2++);

			res = true;
		}else{
			++it2;
		}


	}

	return res;

}

bool BindingUpdateList::removeALLBindings(){

	bindingUpdateList.clear();
	return true;
}

void BindingUpdateList::suspendBinding(const KeyMCoABind& dest)
{
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);

	ASSERT(entry!=NULL);

	entry->BAck = false;
}


bool BindingUpdateList::recentlySentCOTI(const KeyMCoABind& dest, InterfaceEntry* ie)
{
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);

	ASSERT(entry!=NULL);

	//Bruno Sousa see Section RFC3775 5.2.7
	//return entry->sentCoTI + ie->ipv6Data()->_maxTokenLifeTime() / 3 > simTime();
	return entry->sentCoTI + ie->ipv6Data()->_maxTokenLifeTime() / 8 > simTime();
}


bool BindingUpdateList::recentlySentHOTI(const KeyMCoABind& dest, InterfaceEntry* ie)
{
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(dest);

	ASSERT(entry!=NULL);

	//return entry->sentHoTI + ie->ipv6Data()->_maxTokenLifeTime() / 3 > simTime();
	return entry->sentHoTI + ie->ipv6Data()->_maxTokenLifeTime() / 8 > simTime();
}


void BindingUpdateList::resetBindingCacheEntry(BindingUpdateListEntry& entry)
{
	EV << "Resetting Binding Cache Entry " << entry.careOfAddress << endl;

	entry.bindingLifetime = 0;
	entry.bindingExpiry = 0;
	//entry.remainingLifetime = 0;
	entry.sequenceNumber = 0;
	entry.sentTime = 0;
	//entry.nextBUTx = 0;
	entry.BAck = false;
	entry.state = NONE;

	// if tokens should sustain handovers then comment out the following lines of code
	// (this could eventually allow for parallel CN and HA registration)
	// Bruno Sousa decommented code bellow
	entry.sentHoTI = 0;
	entry.sentCoTI = 0;
	entry.tokenH = UNDEFINED_TOKEN;
	entry.tokenC = UNDEFINED_TOKEN;
}

void  BindingUpdateList::prtBindings()
{

	EV << "[MCOA] BINDING UPDATE LIST CONTENTS " << endl;
	for (BindingUpdateList6::iterator i = bindingUpdateList.begin(); i!= bindingUpdateList.end();i++){
		EV << "<KEY> " << (*i).first << " <VALUE> " << (*i).second << endl;
	}
	//std::cout.flush();
}


bool BindingUpdateList::MCoABULentrytoUpdate(const KeyMCoABind& keyM, uint seqtoUpd, int lifeTime){
	bool res = false;

	if (lifeTime==0){
		//when wanting to send bingings to deresgister, just send them do not wait for previous notifications.
		res=true;
		return res;
	}

	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(keyM);
	if (entry == NULL){
		res=true; // should add entry
	}else {
		// for HA and for CN conditions
		if ((entry->state == BindingUpdateList::NONE  && entry->BAck==false) ||
			 (entry->state == BindingUpdateList::RR   && entry->BAck==false)
		    )
		{
			res= false; //Entry has just been created... do not increment values until acknowledge.
		}else{
			int dif = seqtoUpd - entry->lastBAseqNumber;
			if (dif > 1){
				res = false; //we would have a binding without an acknoledgment... sorry do not update
			}else{
				res = true;
			}
		}

	}
	return res;

}

void BindingUpdateList::setLastBAseqNumber(const KeyMCoABind& keyM,  uint inSeq)
{
	BindingUpdateList::BindingUpdateListEntry* entry = lookup2(keyM);
	ASSERT(entry!=NULL);
	entry->lastBAseqNumber = inSeq;
}
