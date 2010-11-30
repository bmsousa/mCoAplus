//
// Copyright (C) 2010 Bruno Sousa
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

#ifndef MCOAVIDEOSTREAMSERVER_H_
#define MCOAVIDEOSTREAMSERVER_H_

#include <vector>
#include <omnetpp.h>
#include "MCoAUDPBase.h"
#include "MCoAVideoStreaming_m.h"

class INET_API MCoAVideoStreamServer : public MCoAUDPBase
{
public:
	 /**
	 * Stores information on a video stream
	 */
	struct VideoStreamData
	{
		IPvXAddress clientAddr;   ///< client address
		int clientPort;           ///< client UDP port
		long videoSize;           ///< total size of video
		long bytesLeft;           ///< bytes left to transmit
		long numPkSent;           ///< number of packets sent
		long seqTx;				 // Sequence transmitted
	};

protected:
    typedef std::vector<VideoStreamData *> VideoStreamVector;
    VideoStreamVector streamVector;

    // module parameters
    int localPort;
    cPar *waitInterval;
    cPar *packetLen;
    cPar *videoSize;

    cOutVector PktSent;
public:

	MCoAVideoStreamServer();
	virtual ~MCoAVideoStreamServer();

protected:
    // process stream request from client
    virtual void processStreamRequest(cMessage *msg);

    // send a packet of the given video stream
    virtual void sendStreamData(cMessage *timer);

    ///@name Overidden cSimpleModule functions
    //@{
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage* msg);
    //@}

};

#endif /* MCOAVIDEOSTREAMSERVER_H_ */
