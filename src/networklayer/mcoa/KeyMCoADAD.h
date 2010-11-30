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


#ifndef KEYMCOADAD_H_
#define KEYMCOADAD_H_
#include "InterfaceEntry.h"
#include "IPv6Address.h"

class KeyMCoADAD {
protected:
	IPv6Address adr;
	InterfaceEntry *ie;

public:
	KeyMCoADAD();
	KeyMCoADAD(IPv6Address iadr, InterfaceEntry *iie);
	virtual ~KeyMCoADAD();


	 bool operator<(const KeyMCoADAD& addr) const {
		 IPv6Address aa = addr.getAdr();
		 int res = adr.compare(aa);
		 int iid = addr.ie->getInterfaceId();
		 int aId = ie->getInterfaceId();
		 bool re = ( (res < 0  && aId < iid) || (res == 0  && aId < iid) || (res < 0  && aId == iid) );
		 return (re );
	 }
	 bool operator>(const KeyMCoADAD& addr) const {
		 IPv6Address aa = addr.getAdr();
		 int res = adr.compare(aa);
		 int iid = addr.ie->getInterfaceId();
		 int aId = ie->getInterfaceId();
		 bool re = ( (res > 0  && aId > iid) || (res == 0  && aId > iid) || (res > 0  && aId == iid) );
		 return (re );
	 }

	 bool operator==(const KeyMCoADAD& addr) const {
		 IPv6Address aa = addr.getAdr();
		 bool res = (adr == aa);
		 if (res) EV << "BRUNO-DBGDAD addresses are equal "<< adr << " and " << aa << endl;
		 int iid = addr.ie->getInterfaceId();
		 int aId = ie->getInterfaceId();
		 bool re = ( aId == iid) ;
		 if (re) EV << "BRUNO-DBGDAD same interfaceID "<< aId << " and " << iid << endl;
		 return (res && re);
	 }

	 bool operator!=(const KeyMCoADAD& addr) const {
		 return !operator==(addr);
	 }


	 friend std::ostream& operator<<(std::ostream& os, const KeyMCoADAD& ie);



    IPv6Address getAdr() const;
    void setAdr(IPv6Address adr);

    InterfaceEntry *getIe() const;
    void setIe(InterfaceEntry *ie);

};

#endif /* KEYMCOADAD_H_ */
