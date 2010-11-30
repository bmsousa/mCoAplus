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

#include "XMIPv6SM.h"

XMIPv6SM::XMIPv6SM() {
	// TODO Auto-generated constructor stub
	setPreferedAddr = false;
	MIPv6preferredAddr = IPv6Address::UNSPECIFIED_ADDRESS;

	returnedHome = false;
	MIPv6triggered = false;


}

XMIPv6SM::~XMIPv6SM() {
	// TODO Auto-generated destructor stub
}


bool XMIPv6SM::getSetPreferedAddr() const
{
   return setPreferedAddr;
}

void XMIPv6SM::setSetPreferedAddr(bool setPreferedAddr)
{
   this->setPreferedAddr = setPreferedAddr;
}


IPv6Address XMIPv6SM::getMIPv6preferredAddr() const
{
	return MIPv6preferredAddr;
}

void XMIPv6SM::setMIPv6preferredAddr(IPv6Address MIPv6preferredAddr)
{
	if(!MIPv6preferredAddr.isUnspecified()) {
		this->MIPv6preferredAddr = MIPv6preferredAddr;
		EV << "XMIPv6SM SET preferred Address to " << MIPv6preferredAddr << endl;
	}
}


bool XMIPv6SM::getReturnedHome() const
{
	return returnedHome;
}

void XMIPv6SM::setReturnedHome(bool returnedHome)
{
	this->returnedHome = returnedHome;
}


bool XMIPv6SM::getMIPv6triggered() const
{
	return MIPv6triggered;
}

void XMIPv6SM::setMIPv6triggered(bool MIPv6triggered)
{
	this->MIPv6triggered = MIPv6triggered;
}


IPv6Address XMIPv6SM::getAppPreferedAddress() const
{
	return AppPreferedAddress;
}

bool XMIPv6SM::getIsAppPrefAdrSet() const
{
	return isAppPrefAdrSet;
}

void XMIPv6SM::setAppPreferedAddress(IPv6Address AppPreferedAddress)
{
	this->AppPreferedAddress = AppPreferedAddress;
}

void XMIPv6SM::setIsAppPrefAdrSet(bool isAppPrefAdrSet)
{
	this->isAppPrefAdrSet = isAppPrefAdrSet;
}


void XMIPv6SM::TRG_MIPv6init(){
	EV << "XMIPv6SM Trigger init MIPv6 " << endl;
	setPreferedAddr = false;
	MIPv6preferredAddr = IPv6Address::UNSPECIFIED_ADDRESS;
	returnedHome = false;
	MIPv6triggered = true;
}

/*
 * When returning home the preferred address can be the HoA
 */
void XMIPv6SM::TRG_returnHome(IPv6Address inpreferredAddr){
	setPreferedAddr = true;
	//MIPv6preferredAddr = inpreferredAddr;
	setMIPv6preferredAddr(inpreferredAddr);
	returnedHome = true;
	MIPv6triggered = false;

}

void XMIPv6SM::initialize(){
	setPreferedAddr = false;
	MIPv6preferredAddr = AppPreferedAddress = IPv6Address::UNSPECIFIED_ADDRESS;

	returnedHome = false;
	MIPv6triggered = false;

	isAppPrefAdrSet = false;

	nb = NotificationBoardAccess().get();

	nb->subscribe(this, NF_MCOA_APP_PREFERED_ADDRESS);
}

/**
 * Called by the NotificationBoard whenever a change of a category
 * occurs to which this client has subscribed.
 */
void XMIPv6SM::receiveChangeNotification(int category, const cPolymorphic *details){

	 if (simulation.getContextType()==CTX_INITIALIZE)
				return;  // ignore notifications during initialize

	Enter_Method_Silent();
	printNotificationBanner(category, details);

	if (category == NF_MCOA_APP_PREFERED_ADDRESS){
		IPv6PrefAdr *ippref =check_and_cast<IPv6PrefAdr*>(details);

		AppPreferedAddress = ippref->getPrefAdr();
		isAppPrefAdrSet = true;

	}
}
