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



#include <limits.h>
#include <stdlib.h>
#include <iostream>

#include "MCoA.h"


Define_Module(MCoA);

/*
 * By Default only enable MCoA
 */
MCoA::MCoA(){
	this->m_prohibited = false;
	this->m_bulk_reg_prohibited = true;
	this->mc_sim_home_and_foreign_prohibited = true;
	this->deregisterALL=MCoA::DEREGISTER_ONE_BY_ONE;
}

void MCoA::initialize()
{


}

void MCoA::finish()
{



}

bool MCoA::getProhibited() const
{
	return m_prohibited;
}

void MCoA::setProhibited(bool m_prohibited)
{
	this->m_prohibited = m_prohibited;
}

bool MCoA::getBulk_reg_prohibited() const
{
	return m_bulk_reg_prohibited;
}

void MCoA::setBulk_reg_prohibited(bool m_bulk_reg_prohibited)
{
	this->m_bulk_reg_prohibited = m_bulk_reg_prohibited;
}

bool MCoA::getMc_sim_home_and_foreign_prohibited() const
{
	return mc_sim_home_and_foreign_prohibited;
}

void MCoA::setMc_sim_home_and_foreign_prohibited(bool mc_sim_home_and_foreign_prohibited)
{
	this->mc_sim_home_and_foreign_prohibited = mc_sim_home_and_foreign_prohibited;
}


string MCoA::getTypeUseMCoA() const
{
	return TypeUseMCoA;
}

void MCoA::setTypeUseMCoA(string TypeUseMCoA)
{
	//std::transform( TypeUseMCoA.begin(), TypeUseMCoA.end(), TypeUseMCoA.begin(), ::toupper) ;
	this->TypeUseMCoA = TypeUseMCoA;
}


int MCoA::getDeregisterALL() const
    {
        return deregisterALL;
    }

void MCoA::setDeregisterALL(int deregisterALL)
{
	this->deregisterALL = deregisterALL;
}

