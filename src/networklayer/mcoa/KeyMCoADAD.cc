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


#include "KeyMCoADAD.h"

KeyMCoADAD::KeyMCoADAD() {
	// TODO Auto-generated constructor stub

}

KeyMCoADAD::KeyMCoADAD(IPv6Address iadr, InterfaceEntry *iie){
	this->adr = iadr;
	this->ie  = iie;
}

KeyMCoADAD::~KeyMCoADAD() {
	// TODO Auto-generated destructor stub
}



std::ostream& operator<<(std::ostream& os, const KeyMCoADAD& ip)
{
	os <<  "" << ip.adr << " ," << ip.ie->getInterfaceId();
	return os;
}

IPv6Address KeyMCoADAD::getAdr() const
{
	return adr;
}

void KeyMCoADAD::setAdr(IPv6Address adr)
{
	this->adr = adr;
}

InterfaceEntry *KeyMCoADAD::getIe() const
{
	return ie;
}

void KeyMCoADAD::setIe(InterfaceEntry *ie)
{
	this->ie = ie;
}
