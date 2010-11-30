//
// Copyright (C) 2010
// Bruno Sousa
// Laboratory and Communications and Telematics (LCT), University of Coimbra, Portugal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package inet.networklayer.mcoa;

simple MCoA
{
    parameters:
        //
		//Implies that the multiple care-of addresses registration is
    	//administratively prohibited.
	 	//
        bool m_prohibited;

        //*
	  	//Bulk binding registration is either not permitted or not
      	//supported.  Note that the bulk registration is an optional
      	//procedure and might not be available on a home agent.
	 	//*/
        bool m_bulk_reg_prohibited;


        //*
		//Simultaneous home and foreign attachment is neither supported nor
    	//permitted.
		//*/
        bool mc_sim_home_and_foreign_prohibited;
        
        //
        // Parameter to specify the use of Multiple Care of Addresses.
        // Possible values:
        //   = singleFirst  --> Use first registered CoA;
        //   = singleRandom --> Use CoA select by  a round Robin mechanism;
        //   = all          --> Use all the CoAs simultaneously;
        string TypeUseMCoA = default("ALL"); 
        
        
        //
        // Parameter to specify how to deregister CoAs when tyoe of use = ALL
        // Possible Values:
        //  = 0 --> deregister all (not fully implemted on 2010/6/23)
        //  = 1 --> deregister one by one
        //
        int deregisterALL = default(1);
        @display("i=block/segm");
}
