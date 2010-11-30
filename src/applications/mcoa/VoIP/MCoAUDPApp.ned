//
// Copyright (C) 2005 Andras Babos
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

import inet.applications.udpapp.UDPApp;
import inet.applications.mcoa.udpbase.MCoAUDPBase;
package inet.applications.mcoa.VoIP;


//
// Similar to UDPBasicApp, but it sends back the packet after reception.
//
simple MCoAUDPApp like MCoAUDPBase
{
    parameters:
        
        int destPort;
        volatile int messageLength @unit("B") = default(10B);  // length of messages to generate, int bytes
        volatile double messageFreq @unit("s") = default(1s); // should usually be a random value, e.g. exponential(1)
        
        double startTime @unit("s") = default(1s);
        
        bool getRequest = default(false); // if it is to be echoed?
        int nRequests = default(0);
        double stopTime @unit("s") = default(0s); //
        
        //From interface
        int localPort;
        string useMode;// = default("SINGLERANDOM"); //Should have values in MCoADefs.h
    	bool useMCoA ;// to use MCoA?
    	string destAddresses = default(""); // list of \IP addresses, separated by spaces
    	bool isDestiny = default(true); //If it is destiny (ony replies to messages).
    gates:
        input udpIn;
        output udpOut;
}



