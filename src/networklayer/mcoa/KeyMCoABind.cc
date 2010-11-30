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

#include "KeyMCoABind.h"

KeyMCoABind::KeyMCoABind() {
	// TODO Auto-generated constructor stub

	this->BID = MCOA_UNSIGNED_BID;
	this->destBID = IPv6Address::UNSPECIFIED_ADDRESS;
}

KeyMCoABind::KeyMCoABind(IPv6Address a) {
	this->Addr = a;
	this->BID = MCOA_UNSIGNED_BID;

	this->destBID = IPv6Address::UNSPECIFIED_ADDRESS;

}

KeyMCoABind::KeyMCoABind(IPv6Address a,  int b) {
	this->Addr = a;
	this->BID = b;

	this->destBID = IPv6Address::UNSPECIFIED_ADDRESS;

}

KeyMCoABind::KeyMCoABind(IPv6Address a,  int b, IPv6Address d ) {
	this->Addr = a;
	this->BID = b;
	this->destBID = d;

}


KeyMCoABind::KeyMCoABind(KeyMCoABind *i){
	this->Addr = i->getAddr();
	this->BID 	   = i->getBID();
	this->destBID = i->getDestBID();

}


KeyMCoABind::~KeyMCoABind() {
	// TODO Auto-generated destructor stub
}



std::ostream& operator<<(std::ostream& os, const KeyMCoABind& ip)
{
	os <<  ip.BID << " ," << ip.Addr << " , " << ip.destBID;
	return os;
}






IPv6Address KeyMCoABind::getAddr() const
{
   return Addr;
}

void KeyMCoABind::setAddr(IPv6Address Addr)
{
   this->Addr = Addr;

}

 int KeyMCoABind::getBID() const
{
   return BID;
}

void KeyMCoABind::setBID( int BID)
{
   this->BID = BID;
}

int KeyMCoABind::compareBID(const uint addr){

	if (BID > addr){ return 1; }
	else if (BID < addr) {return -1;}
	return 0;
}

void KeyMCoABind::setKeyMCoABind (const KeyMCoABind& iKey){
	this->Addr = iKey.Addr;
	this->BID 	   = iKey.BID;
	this->destBID  = iKey.destBID;


}

IPv6Address KeyMCoABind::getDestBID() const
{
	return destBID;
}

void KeyMCoABind::setDestBID(IPv6Address destBID)
{
	this->destBID = destBID;
}


void KeyMCoABind::prtKeyMCoABind(){
	ev << "START KeyMCoA" << endl;
	ev << "Addr: " << Addr << " BID: " << BID << " for dest = " << destBID << endl;
	ev << "END KeyMCoA" << endl;
}

