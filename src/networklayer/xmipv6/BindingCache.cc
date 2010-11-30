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


#include <algorithm>
#include "opp_utils.h"
#include "BindingCache.h"
#include "IPv6InterfaceData.h"


Define_Module(BindingCache);

std::ostream& operator<<(std::ostream& os, const BindingCache::BindingCacheEntry& bce)
{
    os << "CoA of MN:" << bce.careOfAddress << " BU Lifetime: " << bce.bindingLifetime <<" Home Registeration: "<<bce.isHomeRegisteration <<" BU_Sequence#: "<<bce.sequenceNumber<<"\n";
    return os;
}


BindingCache::BindingCache()
{
}


BindingCache::~BindingCache()
{
//     for (unsigned int i=0; i<bindingUpdateList.size(); i++)
//         delete bindingUpdateList[i];
}


void BindingCache::initialize(int stage)
{
    if (stage==1)
    {
    	WATCH_MAP(bindingCache); //added by Zarrar Yousaf
    }
}


void BindingCache::handleMessage(cMessage *msg)
{
    opp_error("This module doesn't process messages");
}




void BindingCache::addOrUpdateBC(const KeyMCoABind& hoa, const IPv6Address& coa, const uint lifetime, const uint seq, bool homeReg)
{
	EV<<"\n++++++++++++++++++++Binding Cache Being Updated in Routing Table6 ++++++++++++++\n";
	bindingCache[hoa].careOfAddress = coa;
	bindingCache[hoa].bindingLifetime = lifetime;
	bindingCache[hoa].sequenceNumber = seq;
	bindingCache[hoa].isHomeRegisteration = homeReg;
}


uint BindingCache::readBCSequenceNumber(const KeyMCoABind& HoA)
{
	//Reads the sequence number of the last received BU Message
	/*IPv6Address HoA = bu->getHomeAddressMN();
	uint seqNumber = bindingCache[HoA].sequenceNumber;
	return seqNumber;*/

	// update 10.09.07 - CB
	// the code from above creates a new (empty) entry if
	// the provided HoA does not yet exist.
	BindingCache6::iterator pos = bindingCache.find(HoA);

	if ( pos == bindingCache.end() )
		return 0; // HoA not yet registered
	else
		return pos->second.sequenceNumber;
}

uint BindingCache::readBCSequenceNumberOnlyAddr(const IPv6Address& HoA, uint buSeq)
{

	BindingCache6::reverse_iterator pos = bindingCache.rbegin();

	for (pos ; pos != bindingCache.rend();pos++){
		if (pos->first.Addr == HoA && pos->second.sequenceNumber == buSeq){
			return pos->second.sequenceNumber;
		}
	}

	return 0; // HoA not yet registered

}



bool BindingCache::isInBindingCache(const KeyMCoABind& HoA, IPv6Address& CoA)
{
	BindingCache6::iterator pos = bindingCache.find(HoA);

	if ( pos == bindingCache.end() )
		return false; // if HoA is not registered then there's obviously no valid entry in the BC

	return (pos->second.careOfAddress == CoA); // if CoA corresponds to HoA, everything is fine
}


bool BindingCache::isInBindingCache(const KeyMCoABind& HoA)
{
	return bindingCache.find(HoA) != bindingCache.end();
}


bool BindingCache::isInBindingCacheOnlyBID(const uint iBID){
	BindingCache6::iterator pos = bindingCache.begin();

	KeyMCoABind* aux = new KeyMCoABind();
	for (pos; pos != bindingCache.end();pos++){
		aux->setKeyMCoABind( ((*pos).first) );
		if (aux->compareBID(iBID)==0){
			//EV<< "[MCOA] >>>> found  BID  equal without comparing with Address"<<endl;

			delete aux;
			return true;
		}

	}
	delete aux;
	return false;
}


bool BindingCache::deleteEntry(KeyMCoABind& HoA)
{
	BindingCache6::iterator pos = bindingCache.find(HoA);

	if ( pos != bindingCache.end() ){ // update 11.9.07 - CB
		bindingCache.erase(pos);
		return true;
	}else {
		return false; // not found
	}
}

bool BindingCache::deleteALLEntries()
{
	BindingCache6::iterator pos = bindingCache.begin();

	for ( pos ; pos != bindingCache.end(); pos++ ){
		bindingCache.erase(pos);
	}

	if (bindingCache.empty()) { return true; }
	else {return false; }


}


bool BindingCache::getHomeRegistration(const KeyMCoABind& HoA)
{
	BindingCache6::iterator pos = bindingCache.find( HoA );

	if ( pos == bindingCache.end() )
		return false; // HoA not yet registered; should not occur anyway
	else
		return pos->second.isHomeRegisteration;
}



bool BindingCache::getHomeRegistrationOnlyAddr(const IPv6Address& HoA, uint buSeq)
{

	BindingCache6::reverse_iterator pos = bindingCache.rbegin();

	for (pos ; pos != bindingCache.rend();pos++){
		if (pos->first.Addr == HoA && pos->second.sequenceNumber == buSeq){
			return pos->second.isHomeRegisteration;
		}
	}

	return false; // HoA not yet registered

}



uint BindingCache::getLifetime(const KeyMCoABind& HoA)
{
	BindingCache6::iterator pos = bindingCache.find( HoA );

	if ( pos == bindingCache.end() )
		return 0; // HoA not yet registered; should not occur anyway
	else
		return pos->second.bindingLifetime;
}


int BindingCache::generateHomeToken(const IPv6Address& HoA, int nonce)
{
	return HO_TOKEN;
}


int BindingCache::generateCareOfToken(const IPv6Address& CoA, int nonce)
{
	return CO_TOKEN;
}

int BindingCache::generateKey(int homeToken, int careOfToken, const IPv6Address& CoA)
{
	// use a dummy value
	return homeToken+careOfToken;
}

void  BindingCache::prtBindings()
{
	//BindingUpdateList6::iterator i = bindingUpdateList.begin();
	EV << "[MCOA] BINDING CACHE CONTENTS " << endl;
	for (BindingCache6::iterator i = bindingCache.begin(); i!= bindingCache.end();i++){
		EV << "<KEY> " << (*i).first << " <VALUE> " << (*i).second << endl;
	}
	//std::cout.flush();
}

int BindingCache::getBCSize(void){

	return bindingCache.size();
}
