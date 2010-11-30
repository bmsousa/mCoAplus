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


package inet.applications.mcoa.udpbase;
import inet.applications.udpapp.UDPApp;

moduleinterface MCoAUDPBase extends UDPApp
{
	parameters:
        int localPort; // if -1, app doesn't bind in UDP
        //int destPort;
        //volatile int messageLength @unit("B"); // length of messages to generate, in bytes
        //volatile double messageFreq @unit("s"); // should usually be a random value, e.g. exponential(1)
        string destAddresses; // = default(""); // list of \IP addresses, separated by spaces
    	string useMode;// = default("SINGLERANDOM"); //Should have values in MCoADefs.h
    	bool useMCoA ;// to use MCoA?
    	bool isDestiny; // Acts as receiving node or sending node traffic
    
   // gates:
   //     input udpIn;
   //     output udpOut;	
    	
    	
}    
    
 



