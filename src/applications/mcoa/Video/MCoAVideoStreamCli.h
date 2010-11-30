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


//
// based on the video streaming app of the similar name by Johnny Lai
//

#ifndef __INET_UDPVIDEOSTREAM_H
#define __INET_UDPVIDEOSTREAM_H

#include <omnetpp.h>
#include "MCoAUDPBase.h"
#include "MCoAVideoStreaming_m.h"

/**
 * A "Realtime" VideoStream client application.
 *
 * Basic video stream application. Clients connect to server and get a stream of
 * video back.
 */
class INET_API MCoAVideoStreamCli : public MCoAUDPBase
{
  protected:
    // statistics
    cOutVector PktRcv;
    cOutVector PktLost;
    cOutVector PktDelay;

    long lastSeq;

  protected:
    ///@name Overridden cSimpleModule functions
    //@{
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
    //@}

  protected:
    virtual void requestStream();
    virtual void receiveStream(cPacket *msg);
};


#endif



