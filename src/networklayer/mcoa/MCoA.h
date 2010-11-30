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

#ifndef __MCOA_H__
#define __MCOA_H__


#include "INETDefs.h"
#include "MCoADefs.h"


using namespace std;


class MCoA : public cSimpleModule
{
public:
	enum deregister_type
	{
		DEREGISTER_ALL_SIMULTANEOUSLY = 0,
		DEREGISTER_ONE_BY_ONE,
	};


protected:
    bool m_prohibited;
    bool m_bulk_reg_prohibited;
    bool mc_sim_home_and_foreign_prohibited;
    string TypeUseMCoA;
    int deregisterALL;

    virtual void initialize();
    virtual void finish();
public:
    MCoA();
    bool getProhibited() const;
    void setProhibited(bool m_prohibited);
    bool getBulk_reg_prohibited() const;
    void setBulk_reg_prohibited(bool m_bulk_reg_prohibited);
    bool getMc_sim_home_and_foreign_prohibited() const;
    void setMc_sim_home_and_foreign_prohibited(bool mc_sim_home_and_foreign_prohibited);

    string getTypeUseMCoA() const;
    void setTypeUseMCoA(string TypeUseMCoA);
    int getDeregisterALL() const;
    void setDeregisterALL(int deregisterALL);


};

#endif //__MCOA_H__
