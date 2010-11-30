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

#ifndef __BINDINGUPDATELIST_H__
#define __BINDINGUPDATELIST_H__

#include <vector>
#include <omnetpp.h>
#include "INETDefs.h"
#include "IPv6Address.h"
#include "InterfaceTable.h"
//added by zarrar on 12.06.07
#include "MobilityHeader_m.h"

//Bruno Sousa 2010/5/5
#include "KeyMCoABind.h"

// used for the RR tokens
#define UNDEFINED_TOKEN		0
#define UNDEFINED_COOKIE	0
#define UNDEFINED_BIND_AUTH_DATA	0
#define HO_COOKIE	11
#define HO_TOKEN	1101
#define CO_COOKIE	21
#define CO_TOKEN	2101

#define PRE_BINDING_EXPIRY	2 // amount of seconds before BUL expiry that indicate that a binding will shortly expiry

#define LASTBASEQ 0 //Last BA Sequence initialization number

class INET_API BindingUpdateList : public cSimpleModule
{
  public:
//###########################Declaration of BUL and BC added by Zarrar Yousaf @ CNI Uni Dortmund on 04.06.07######  

	// 21.07.08 - CB
	enum MobilityState
	{
		NONE = 0,
		RR,
		RR_COMPLETE,
		REGISTER,
		REGISTERED,
		DEREGISTER
	};

	struct BindingUpdateListEntry
    {
		IPv6Address destAddress; // is the address of the HA or the CN to which the MN has sent a BU message; reference to the key in the map
		IPv6Address homeAddress; // Home address of the MN for which that BU was sent. 
		IPv6Address careOfAddress; // MN's CoA. With this entry teh MN can determine whether it has sent a BU to the destination node with its CoA or not.
		uint bindingLifetime;   // the initial value of the lifetime field sent in the BU to which this entry corresponds
		simtime_t bindingExpiry; // the time at which the lifetime of the binding expires
		//uint remainingLifetime;	//initialised from bindingLifetime and is decremented until it reaches zero
		uint sequenceNumber; // the max value of the seq # sent in the previous BU. 
		simtime_t sentTime; // the time at which that particular BU was sent. recorded from simTime(). Used to implement rate limiting restrcition for sending BU.
		//simtime_t nextBUTx; // the time to send the next BU. NOT EXACTLY CLEAR
		bool BAck; //not part of RFC. Indicates whether the correpsonding BU has received a valid BAck or not. True if Ack'ed. By Default it is FALSE.

		//Bruno Sousa
		uint lastBAseqNumber; // the last seq that was Acknowledge. //Not part of RFC.

		// this part is for return routability procedure // 27.08.07 - CB
		/*	The time at which a Home Test Init or Care-of Test Init message
      		was last sent to this destination, as needed to implement the rate
      		limiting restriction for the return routability procedure. */
		simtime_t sentHoTI, sentCoTI;
		/*	The state of any retransmissions needed for this return
      		routability procedure.  This state includes the time remaining
      		until the next retransmission attempt and the current state of the
      		exponential back-off mechanism for retransmissions. */
		//simtime_t sendNext; // FIXME huh?
		/*	Cookie values used in the Home Test Init and Care-of Test Init
      		messages. */
		int cookieHoTI, cookieCoTI;
		/*	Home and care-of keygen tokens received from the correspondent
      		node.*/
      	int tokenH, tokenC;
      	/*	Home and care-of nonce indices received from the correspondent
			node. */
      	// not used
      	/*	The time at which each of the tokens and nonces were received from
			the correspondent node, as needed to implement reuse while moving. */
		// this information is stored in the retransmission timer

      	// this state information is used for CN bindings
      	MobilityState state;

      virtual ~BindingUpdateListEntry() {};
    };

    friend std::ostream& operator<<(std::ostream& os, const BindingUpdateListEntry& bul);
    /*
    typedef std::map<IPv6Address,BindingUpdateListEntry> BindingUpdateList6;
    BindingUpdateList6 bindingUpdateList;
	*/

    typedef std::map<KeyMCoABind,BindingUpdateListEntry> BindingUpdateList6;
    BindingUpdateList6 bindingUpdateList;

  public:
    BindingUpdateList();
    virtual ~BindingUpdateList();

  protected:
    virtual int numInitStages() const  {return 2;}
    virtual void initialize(int stage);

    /**
     * Raises an error.
     */
    virtual void handleMessage(cMessage *);

  public:
	/**
	 * Sets entry in the Binding Update List with provided values. If entry does not yet exist, a new one is created.
	 */
	virtual void addOrUpdateBUL(const KeyMCoABind& key, const IPv6Address& dest,  const IPv6Address& hoa, const IPv6Address& coa, const uint lifetime, const uint seq, const simtime_t buSentTime, const int iIfID);//,const simtime_t& nextBUSentTime );

	/**
	 * Creates a new entry in the BUL for the provided address.
	 */
	virtual BindingUpdateList::BindingUpdateListEntry* createBULEntry(const KeyMCoABind &keyMCoA, const IPv6Address& dest);

	/**
	 * Initializes the values of a BUL entry to initial values.
	 * Called by addOrUpdateBUL() if new entry is created.
	 */
	// 28.08.07 - CB
	// Bruno Sousa 2010/4/28
	virtual void initializeBUValues(BindingUpdateListEntry& entry);

	/**
	 * Sets HoTI and/or CoTI values (transmission time, etc.) for the BUL entry.
	 */
	virtual void addOrUpdateBUL(const KeyMCoABind& keyMCoA, const IPv6Address& dest, const IPv6Address& hoa, simtime_t sentTime, int cookie, bool isHoTI); // BU for HoTI/CoTI

	// Added Bruno Sousa 2010/04/28
	/**
	  * Returns the BUL entry for a Care of address and BID.
	  *
	  * returns: bulEntry by the search of BID+Care-of-address or only Care-of-Address
	  */
    virtual BindingUpdateList::BindingUpdateListEntry* BIDlookup(uint16 inBID, const KeyMCoABind& dest); // checks whether BU exists for given address on provided interface

	/**
	 * Returns the BUL entry for a certain destination address.
	 */
	virtual BindingUpdateList::BindingUpdateListEntry* lookup(const KeyMCoABind keyMCoA); // checks whether BU exists for given address on provided interface


	/**
	 * Returns the BUL entry for a certain destination address.
	 *
	 * Bruno Sousa
	 */
	virtual BindingUpdateList::BindingUpdateListEntry* lookup2(const KeyMCoABind &keyMCoA); // checks whether BU exists for given address on provided interface


	/**
	 * Similiar to lookup(), but with the difference that this method always returns a valid BUL entry. If none existed prior
	 * to the call, a new entry is created.
	 */
	virtual BindingUpdateList::BindingUpdateListEntry* fetch(const KeyMCoABind &keyMCoA, const IPv6Address& dest); // checks whether BU exists for given address on provided interface



	//
	// The following methods are related to RR stuff.
	//

	/**
	 * Returns the current mobility state for the CN identified by the provided IP address.
	 */
	virtual MobilityState getMobilityState(const KeyMCoABind& dest);

	/**
	 * Sets the mobility state to provided state for the CN identified by the provided IP address.
	 */
	virtual void setMobilityState(const KeyMCoABind& dest, BindingUpdateList::MobilityState state);


	/**
	 * Generates the Binding Authorization Data based on a certain destination address and CoA.
	 */
	virtual int generateBAuthData(const KeyMCoABind& dest, const IPv6Address& CoA);


	/**
	 * Generates the key Kbm from home and care-of keygen token.
	 * For now, this return the sum of both tokens.
	 */
	virtual int generateKey(int homeToken, int careOfToken, const IPv6Address& CoA);


	/**
	 * Generates a home token from the provided parameters.
	 * Returns a static value for now.
	 */
	virtual int generateHomeToken(const IPv6Address& HoA, int nonce);


	/**
	 * Generates a care-of token from the provided paramters.
	 * Returns a static value for now.
	 */
	virtual int generateCareOfToken(const IPv6Address& CoA, int nonce);


	/**
	 * Resets the token to UNDEFINED.
	 */
	virtual void resetHomeToken(const KeyMCoABind& dest, const IPv6Address& hoa);


	/**
	 * Resets the token to UNDEFINED.
	 */
	virtual void resetCareOfToken(const KeyMCoABind& dest, const IPv6Address& hoa);


	/**
	 * Returns true if a home keygen token is available.
	 */
	virtual bool isHomeTokenAvailable(const KeyMCoABind& dest, InterfaceEntry* ie);


	/**
	 * Returns true if a care-of keygen token is available.
	 */
	virtual bool isCareOfTokenAvailable(const KeyMCoABind& dest, InterfaceEntry* ie);


//
// Additional methods
//

	/**
	 * Checks whether there exists an entry in the BUL for the given
	 * destination address.
	 */
	virtual bool isInBindingUpdateList(const KeyMCoABind& dest); // 10.9.07 - CB


	/**
	 * Returns the last used sequence number for the given dest. address.
	 */
	virtual uint getSequenceNumber(const KeyMCoABind& dest); // 10.9.07 - CB

	/**
	 * Returns the BID from the home address and CoA.
	 */
	virtual uint16 getBID(const IPv6Address& homeAddr, const IPv6Address& CoA ); // Bruno Sousa 2010/4/29


	/**
	 * Retunrns the CoA in the key of BUL by BID and destBID
	 */
	virtual IPv6Address getCoA_in_key(int iBID, IPv6Address destBID); //Bruno Sousa




	/**
	 * Returns the CoA that was registered for the provided dest. address.
	 */
	virtual const IPv6Address& getCoA(const KeyMCoABind& dest); // 24.9.07 - CB


	/**
	 * Checks whether there exists an entry in the BUL for the given
	 * destination address and home address.
	 */
	virtual bool isInBindingUpdateList(const KeyMCoABind& dest, const IPv6Address& HoA); // 20.9.07 - CB


	/**
	 * Returns true if a binding has been acknowledged and it's lifetime
	 * has not yet expired.
	 */
	virtual bool isValidBinding(const KeyMCoABind& dest);




	/**
	 * Returns true if a binding is about to expire.
	 */
	virtual bool isBindingAboutToExpire(const KeyMCoABind& dest);


	/**
	 *
	 * Checks if BUL is empty
	 */
	virtual bool isEmpty();


	/**
	 * Returns true if a binding update has been sent to and acknowledged by
	 * the provided destination address and the lifetime has not yet expired.
	 */
	virtual bool sentBindingUpdate(const KeyMCoABind& dest);


	/**
	 * Deletes an entry from the binding update list for the provided
	 * destination address.
	 */
	virtual bool removeBinding(const KeyMCoABind& dest);


	virtual bool removeBindingByDest(const IPv6Address & dest);


	virtual bool removeALLBindings();

	/**
	 * Sets the state of the binding cache entry to "not usable".
	 * Resets the BAck flag to false, etc.
	 */
	virtual void suspendBinding(const KeyMCoABind& dest);


	/**
	 * These two methods indicate whether a CoTI or HoTI message
	 * has been recently sent to the CN identified by parameter dest.
	 */
	virtual bool recentlySentCOTI(const KeyMCoABind& dest, InterfaceEntry* ie);
	virtual bool recentlySentHOTI(const KeyMCoABind& dest, InterfaceEntry* ie);

	/*Bruno Sousa 2010/5/5 */
	void prtBindings(void);


//protected:
	/**
	 * Resets binding lifetime, tokens, etc. of the BUL entry.
	 */
	virtual void resetBindingCacheEntry(BindingUpdateListEntry& entry);

	/*
	 * Bruno Sousa
	 * Check if bul should be updated. For instance if it has already been sent once and
	 * not acknowledge, keep Sequence... therefore do not update entry.
	 */
	bool MCoABULentrytoUpdate(const KeyMCoABind& keyM, uint seqtoUpd, int lifeTime);

	void setLastBAseqNumber(const KeyMCoABind& keyM,  uint inSeq);
};

#endif

