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
#ifndef MCOADEFS_H_
#define MCOADEFS_H_


/*
 * Nomenclature:
 *
 * TUN_ALL --> all tunnels
 * ADR_ALL --> all addresses
 */

/*
 * Establishes all the tunnels
 */

#define MCOA_TUN_ALL_ADR_ALL "ALL"

/*
 * Establishes all the tunnels
 *
 * But uses a single address
 */
#define MCOA_TUN_ALL_ADR_SINGLE_FIRST "SINGLEFIRST"

/*
 * Establishes all the tunnels
 *
 * But uses a single address
 */
#define MCOA_TUN_ALL_ADR_SINGLE_RR "SINGLERANDOM"


/*
 * Establishes a single tunnel
 *
 * But uses a single address
 */
#define MCOA_TUN_SINGLE_ADR_SINGLE "TUNSINGLEADRSINGLE"


#endif /* MCOADEFS_H_ */
