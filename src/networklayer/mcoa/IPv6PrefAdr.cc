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

#include "IPv6PrefAdr.h"

IPv6PrefAdr::IPv6PrefAdr() {
	// TODO Auto-generated constructor stub

}

IPv6PrefAdr::~IPv6PrefAdr() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator<<(std::ostream& os, const IPv6PrefAdr& ip)
{
	os << " prefered Address=" << ip.getPrefAdr() << " prio=" << ip.getPreferencePriority();
	return os;
}


IPv6PrefAdr::IPv6PrefAdr(IPv6Address _en, uint prio)
{
    prefAdr = _en;
    preferencePriority = prio;
}

IPv6Address IPv6PrefAdr::getPrefAdr() const
{
	return prefAdr;
}

uint IPv6PrefAdr::getPreferencePriority() const
{
	return preferencePriority;
}

void IPv6PrefAdr::setPrefAdr(IPv6Address prefAdr)
{
	this->prefAdr = prefAdr;
}

void IPv6PrefAdr::setPreferencePriority(uint preferencePriority)
{
	this->preferencePriority = preferencePriority;
}

