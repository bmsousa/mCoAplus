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

#ifndef XMIPV6SM_H_
#define XMIPV6SM_H_

#include "IPv6Address.h"
#include "NotificationBoard.h"
#include "IPv6PrefAdr.h"

class XMIPv6SM: public cSimpleModule, protected INotifiable {
protected:
    bool setPreferedAddr; // states that applies to the MN and CN.
    IPv6Address MIPv6preferredAddr;

    /*
	  * When returning Home.
	  *
	  * MN deregisters all the CoA
	  *
	  * Need to avoid repetition of returningHome Procedure
	  */
    bool returnedHome;

	/*
	* When MIPv6 has been triggered
	*/
    bool MIPv6triggered;

    /*
     * Sets for the app sync (preferred Address)
     *
     */
    IPv6Address AppPreferedAddress;
    bool isAppPrefAdrSet;

    NotificationBoard * nb;

public:
    XMIPv6SM();
    virtual ~XMIPv6SM();

    bool getSetPreferedAddr() const;
    void setSetPreferedAddr(bool setPreferedAddr);

    IPv6Address getMIPv6preferredAddr() const;
    void setMIPv6preferredAddr(IPv6Address MIPv6preferredAddr);

    bool getReturnedHome() const;
    void setReturnedHome(bool returnedHome);

    bool getMIPv6triggered() const;
    void setMIPv6triggered(bool MIPv6triggered);


    void TRG_returnHome(IPv6Address MIPv6preferredAddr);
    void TRG_MIPv6init();

    void initialize();

    IPv6Address getAppPreferedAddress() const;
    bool getIsAppPrefAdrSet() const;
    void setAppPreferedAddress(IPv6Address AppPreferedAddress);
    void setIsAppPrefAdrSet(bool isAppPrefAdrSet);

protected:
  	/**
  	 * Called by the NotificationBoard whenever a change of a category
  	 * occurs to which this client has subscribed.
  	 */
  	virtual void receiveChangeNotification(int category, const cPolymorphic *details);


};

#endif /* XMIPV6SM_H_ */
