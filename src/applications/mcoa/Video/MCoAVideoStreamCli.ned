//
// Copyright (C) 2005 Andras Varga
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
package inet.applications.mcoa.Video;

//
// Video streaming client.
//
// @see UDPVideoStreamSvr
//
simple MCoAVideoStreamCli like MCoAUDPBase
{
    parameters:
        
        //string serverAddress;
        int destPort;
        double startTime @unit("s") = default(1s);
        
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

