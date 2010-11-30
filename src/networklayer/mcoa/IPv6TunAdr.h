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


#ifndef IPV6TUNADR_H_
#define IPV6TUNADR_H_

#include <omnetpp.h>
#include "INETDefs.h"
#include "IPv6Address.h"


class INET_API IPv6TunAdr: public cPolymorphic {
protected:
	// entry point of tunnel
	IPv6Address entry;
	// exit point of tunnel
	IPv6Address exit;
	IPv6Address destTrigger;

public:
	IPv6TunAdr();
	IPv6TunAdr(IPv6Address _en, IPv6Address _ex, IPv6Address _dest);

	virtual ~IPv6TunAdr();

    IPv6Address getDestTrigger() const;
    IPv6Address getEntry() const;
    IPv6Address getExit() const;
    void setDestTrigger(IPv6Address destTrigger);

    void setEntry(IPv6Address entry);
    void setExit(IPv6Address exit);

};

#endif /* IPV6TUNADR_H_ */
