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
// Video stream server. To be used with UDPVideoStreamCli.
//
// The server will wait for incoming "video streaming requests".
// When a request arrives, it draws a random video stream size
// using the videoSize parameter, and starts streaming to the client.
// During streaming, it will send \UDP packets of size packetLen at every
// waitInterval, until videoSize is reached. The parameters packetLen
// and waitInterval can be set to constant values to create CBR traffic,
// or to random values (e.g. waitInterval=uniform(1e-6, 1.01e-6)) to
// accomodate jitter.
//
// The server can serve several clients, and several streams per client.
//
// @see UDPVideoStreamCli
//
simple MCoAVideoStreamServer like MCoAUDPBase
{
    parameters:
        int destPort; // port to listen on
        volatile double waitInterval @unit("s"); // interval between sending video stream packets
        volatile int packetLen @unit("B");
        volatile int videoSize @unit("B");
        
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

