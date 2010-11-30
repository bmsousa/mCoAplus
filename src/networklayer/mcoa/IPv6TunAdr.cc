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

#include "IPv6TunAdr.h"

IPv6TunAdr::IPv6TunAdr() {
	// TODO Auto-generated constructor stub

}

IPv6TunAdr::~IPv6TunAdr() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator<<(std::ostream& os, const IPv6TunAdr& ip)
{
	os << " entry=" << ip.getEntry() << " exit=" << ip.getExit() << " destTrigger=" << ip.getDestTrigger();
	return os;
}


IPv6TunAdr::IPv6TunAdr(IPv6Address _en, IPv6Address _ex, IPv6Address _dest){
		entry = _en;
		exit = _ex;
		destTrigger = _dest;
}


IPv6Address IPv6TunAdr::getDestTrigger() const
{
	return destTrigger;
}

IPv6Address IPv6TunAdr::getEntry() const
{
	return entry;
}

IPv6Address IPv6TunAdr::getExit() const
{
	return exit;
}

void IPv6TunAdr::setDestTrigger(IPv6Address destTrigger)
{
	this->destTrigger = destTrigger;
}

void IPv6TunAdr::setEntry(IPv6Address entry)
{
	this->entry = entry;
}

void IPv6TunAdr::setExit(IPv6Address exit)
{
	this->exit = exit;
}
