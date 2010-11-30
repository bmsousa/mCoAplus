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


#ifndef KEYMCOABIND_H_
#define KEYMCOABIND_H_

#include <iostream>
#include "IPv6Address.h"

#define MCOA_UNSIGNED_BID -1
#define MCOA_HOA_AS_BID -2

class KeyMCoABind {
public:
	int BID;
	IPv6Address Addr;
	IPv6Address destBID;

public:
	KeyMCoABind();
	KeyMCoABind(IPv6Address a);
	KeyMCoABind(IPv6Address a,  int b);
	KeyMCoABind(IPv6Address a,  int b, IPv6Address d);
	KeyMCoABind(KeyMCoABind *);
	virtual ~KeyMCoABind();


	 bool operator>(const KeyMCoABind& addr) const {
		 bool re=false;
		 int res;

		 if (this->BID > addr.BID){
			 re= true;
		 }else {
			 if (this->BID == addr.BID ){
				 res = this->Addr.compare(addr.Addr);
				 if (res > 0) {re = true;}
				 else {
					 res = this->destBID.compare(addr.destBID);
					 if (res > 0) {re = true;}
				 }
			 }else {
				 re= false;
			 }
		 }

		 return (re );
	 }
	 bool operator<(const KeyMCoABind& addr) const {
		 bool re=false;
		 int res;

		 if (this->BID < addr.BID){
			 re= true;
		 }else {
			 if (this->BID == addr.BID ){
				 res = this->Addr.compare(addr.Addr);
				 if (res < 0) {re = true;}
				 else{
					 res = this->destBID.compare(addr.destBID);
					 if (res < 0) {re = true;}
				 }
			 }else {
				 re= false;
			 }
		 }

		 return (re );
	 }

	 bool operator==(const KeyMCoABind& addr) const {
		/*
		bool res = (Addr == addr.Addr);
		bool res1 = (destBID == addr.destBID);

		return (res==0 && BID == addr.BID && res1==0);
		*/
		 return (( Addr == addr.Addr) && BID == addr.BID
					 && (destBID == addr.destBID)
			     );
	 }





	 bool operator!=(const KeyMCoABind& addr) const {
		 return !operator==(addr);
	 }

	 friend std::ostream& operator<<(std::ostream& os, const KeyMCoABind& ip);

	 /*
	  * Compare only BID
	  * return 1 >
	  *        -1 <
	  *        0 =
	  */
	 int compareBID(const uint addr);


    IPv6Address getAddr() const ;
    void setAddr(IPv6Address Addr);
     int getBID() const;
    void setBID( int BID);

    IPv6Address getDestBID() const;
	void setDestBID(IPv6Address destBID);


    void setKeyMCoABind (const KeyMCoABind& iKey);

    void prtKeyMCoABind();


};

#endif /* KEYMCOABIND_H_ */
