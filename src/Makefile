#
# OMNeT++/OMNEST Makefile for libinet
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-so -o inet -O out
#

# Name of target to be created (-o option)
TARGET = libinet$(SHARED_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Iapplications \
    -Iapplications/ethernet \
    -Iapplications/generic \
    -Iapplications/mcoa \
    -Iapplications/mcoa/Video \
    -Iapplications/mcoa/VoIP \
    -Iapplications/mcoa/udpbase \
    -Iapplications/pingapp \
    -Iapplications/rtpapp \
    -Iapplications/sctpapp \
    -Iapplications/tcpapp \
    -Iapplications/udpapp \
    -Ibase \
    -Ilinklayer \
    -Ilinklayer/contract \
    -Ilinklayer/ethernet \
    -Ilinklayer/etherswitch \
    -Ilinklayer/ext \
    -Ilinklayer/ieee80211 \
    -Ilinklayer/ieee80211/mac \
    -Ilinklayer/ieee80211/mgmt \
    -Ilinklayer/mf80211 \
    -Ilinklayer/mf80211/macLayer \
    -Ilinklayer/mf80211/phyLayer \
    -Ilinklayer/mf80211/phyLayer/decider \
    -Ilinklayer/mf80211/phyLayer/snrEval \
    -Ilinklayer/mfcore \
    -Ilinklayer/ppp \
    -Ilinklayer/radio \
    -Imobility \
    -Inetworklayer \
    -Inetworklayer/arp \
    -Inetworklayer/autorouting \
    -Inetworklayer/common \
    -Inetworklayer/contract \
    -Inetworklayer/extras \
    -Inetworklayer/icmpv6 \
    -Inetworklayer/ipv4 \
    -Inetworklayer/ipv6 \
    -Inetworklayer/ldp \
    -Inetworklayer/mcoa \
    -Inetworklayer/mpls \
    -Inetworklayer/ospfv2 \
    -Inetworklayer/ospfv2/interface \
    -Inetworklayer/ospfv2/messagehandler \
    -Inetworklayer/ospfv2/neighbor \
    -Inetworklayer/ospfv2/router \
    -Inetworklayer/queue \
    -Inetworklayer/rsvp_te \
    -Inetworklayer/ted \
    -Inetworklayer/xmipv6 \
    -Inodes \
    -Inodes/adhoc \
    -Inodes/ethernet \
    -Inodes/inet \
    -Inodes/ipv6 \
    -Inodes/mpls \
    -Inodes/wireless \
    -Inodes/xmipv6 \
    -Itransport \
    -Itransport/contract \
    -Itransport/rtp \
    -Itransport/rtp/profiles \
    -Itransport/rtp/profiles/avprofile \
    -Itransport/sctp \
    -Itransport/tcp \
    -Itransport/tcp/flavours \
    -Itransport/tcp/queues \
    -Itransport/udp \
    -Iutil \
    -Iutil/headerserializers \
    -Iutil/headerserializers/headers \
    -Iworld

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/applications/ethernet/EtherAppCli.o \
    $O/applications/ethernet/EtherAppSrv.o \
    $O/applications/generic/IPTrafGen.o \
    $O/applications/mcoa/Video/MCoAVideoStreamServer.o \
    $O/applications/mcoa/Video/MCoAVideoStreamCli.o \
    $O/applications/mcoa/VoIP/MCoAUDPApp.o \
    $O/applications/mcoa/udpbase/MCoAUDPBase.o \
    $O/applications/pingapp/PingApp.o \
    $O/applications/rtpapp/RTPApplication.o \
    $O/applications/sctpapp/SCTPServer.o \
    $O/applications/sctpapp/SCTPClient.o \
    $O/applications/sctpapp/SCTPPeer.o \
    $O/applications/tcpapp/TCPSrvHostApp.o \
    $O/applications/tcpapp/TCPBasicClientApp.o \
    $O/applications/tcpapp/TCPEchoApp.o \
    $O/applications/tcpapp/TCPGenericSrvApp.o \
    $O/applications/tcpapp/TCPGenericSrvThread.o \
    $O/applications/tcpapp/TCPGenericCliAppBase.o \
    $O/applications/tcpapp/TCPSinkApp.o \
    $O/applications/tcpapp/TCPSessionApp.o \
    $O/applications/tcpapp/TelnetApp.o \
    $O/applications/tcpapp/TCPSpoof.o \
    $O/applications/udpapp/UDPBasicApp.o \
    $O/applications/udpapp/UDPVideoStreamCli.o \
    $O/applications/udpapp/UDPEchoApp.o \
    $O/applications/udpapp/UDPVideoStreamSvr.o \
    $O/applications/udpapp/UDPAppBase.o \
    $O/applications/udpapp/UDPSink.o \
    $O/base/Join.o \
    $O/base/ModuleAccess.o \
    $O/base/Blackboard.o \
    $O/base/NotificationBoard.o \
    $O/base/PassiveQueueBase.o \
    $O/base/AbstractQueue.o \
    $O/base/BasicModule.o \
    $O/base/ProtocolMap.o \
    $O/base/Sink.o \
    $O/base/ByteArrayMessage.o \
    $O/base/QueueWithQoS.o \
    $O/base/NotifierConsts.o \
    $O/base/QueueBase.o \
    $O/base/ReassemblyBuffer.o \
    $O/linklayer/contract/MACAddress.o \
    $O/linklayer/ethernet/EtherMACBase.o \
    $O/linklayer/ethernet/EtherHub.o \
    $O/linklayer/ethernet/EtherMAC.o \
    $O/linklayer/ethernet/EtherBus.o \
    $O/linklayer/ethernet/EtherLLC.o \
    $O/linklayer/ethernet/EtherEncap.o \
    $O/linklayer/ethernet/EtherMAC2.o \
    $O/linklayer/etherswitch/MACRelayUnitNP.o \
    $O/linklayer/etherswitch/MACRelayUnitPP.o \
    $O/linklayer/etherswitch/MACRelayUnitBase.o \
    $O/linklayer/ext/ExtInterface.o \
    $O/linklayer/ext/cSocketRTScheduler.o \
    $O/linklayer/ieee80211/mac/Ieee80211Mac.o \
    $O/linklayer/ieee80211/mgmt/Ieee80211MgmtAdhoc.o \
    $O/linklayer/ieee80211/mgmt/Ieee80211MgmtSTASimplified.o \
    $O/linklayer/ieee80211/mgmt/Ieee80211MgmtAPSimplified.o \
    $O/linklayer/ieee80211/mgmt/Ieee80211MgmtSTA.o \
    $O/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.o \
    $O/linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.o \
    $O/linklayer/ieee80211/mgmt/Ieee80211AgentSTA.o \
    $O/linklayer/ieee80211/mgmt/Ieee80211MgmtAP.o \
    $O/linklayer/mf80211/macLayer/CSMAMacLayer.o \
    $O/linklayer/mf80211/macLayer/Mac80211.o \
    $O/linklayer/mf80211/phyLayer/decider/Decider80211.o \
    $O/linklayer/mf80211/phyLayer/decider/SnrDecider.o \
    $O/linklayer/mf80211/phyLayer/decider/ErrAndCollDecider.o \
    $O/linklayer/mf80211/phyLayer/snrEval/SnrEval.o \
    $O/linklayer/mf80211/phyLayer/snrEval/GilbertElliotSnr.o \
    $O/linklayer/mf80211/phyLayer/snrEval/SnrEval80211.o \
    $O/linklayer/mfcore/WirelessMacBase.o \
    $O/linklayer/mfcore/BasicDecider.o \
    $O/linklayer/mfcore/BasicSnrEval.o \
    $O/linklayer/ppp/PPP.o \
    $O/linklayer/ppp/ThruputMeter.o \
    $O/linklayer/radio/PathLossReceptionModel.o \
    $O/linklayer/radio/GenericRadioModel.o \
    $O/linklayer/radio/GenericRadio.o \
    $O/linklayer/radio/AbstractRadio.o \
    $O/linklayer/radio/Ieee80211RadioModel.o \
    $O/linklayer/radio/Modulation.o \
    $O/linklayer/radio/Ieee80211Radio.o \
    $O/mobility/LinearMobility.o \
    $O/mobility/RectangleMobility.o \
    $O/mobility/BonnMotionMobility.o \
    $O/mobility/LineSegmentsMobilityBase.o \
    $O/mobility/BasicMobility.o \
    $O/mobility/NullMobility.o \
    $O/mobility/RandomWPMobility.o \
    $O/mobility/TurtleMobility.o \
    $O/mobility/BonnMotionFileCache.o \
    $O/mobility/MassMobility.o \
    $O/mobility/ConstSpeedMobility.o \
    $O/mobility/ANSimMobility.o \
    $O/mobility/CircleMobility.o \
    $O/networklayer/arp/ARP.o \
    $O/networklayer/autorouting/NetworkConfigurator.o \
    $O/networklayer/autorouting/MCoANetConf6.o \
    $O/networklayer/autorouting/FlatNetworkConfigurator6.o \
    $O/networklayer/autorouting/FlatNetworkConfigurator.o \
    $O/networklayer/common/InterfaceEntry.o \
    $O/networklayer/common/InterfaceTable.o \
    $O/networklayer/contract/IPControlInfo.o \
    $O/networklayer/contract/IPAddressResolver.o \
    $O/networklayer/contract/IPv6ControlInfo.o \
    $O/networklayer/contract/IPvXAddress.o \
    $O/networklayer/contract/IPAddress.o \
    $O/networklayer/contract/IPv6Address.o \
    $O/networklayer/extras/FailureManager.o \
    $O/networklayer/extras/NetworkInfo.o \
    $O/networklayer/extras/Dummy.o \
    $O/networklayer/icmpv6/IPv6NeighbourCache.o \
    $O/networklayer/icmpv6/ICMPv6.o \
    $O/networklayer/icmpv6/IPv6NeighbourDiscovery.o \
    $O/networklayer/ipv4/ErrorHandling.o \
    $O/networklayer/ipv4/RoutingTableParser.o \
    $O/networklayer/ipv4/IPv4InterfaceData.o \
    $O/networklayer/ipv4/IP.o \
    $O/networklayer/ipv4/IPRoute.o \
    $O/networklayer/ipv4/IPFragBuf.o \
    $O/networklayer/ipv4/ICMP.o \
    $O/networklayer/ipv4/RoutingTable.o \
    $O/networklayer/ipv6/IPv6Datagram.o \
    $O/networklayer/ipv6/IPv6FragBuf.o \
    $O/networklayer/ipv6/IPv6InterfaceData.o \
    $O/networklayer/ipv6/IPv6ExtensionHeaders.o \
    $O/networklayer/ipv6/IPv6.o \
    $O/networklayer/ipv6/IPv6Tunneling.o \
    $O/networklayer/ipv6/RoutingTable6.o \
    $O/networklayer/ipv6/IPv6ErrorHandling.o \
    $O/networklayer/ldp/LDP.o \
    $O/networklayer/mcoa/KeyMCoABind.o \
    $O/networklayer/mcoa/IPv6TunAdr.o \
    $O/networklayer/mcoa/XMIPv6SM.o \
    $O/networklayer/mcoa/MCoA.o \
    $O/networklayer/mcoa/KeyMCoADAD.o \
    $O/networklayer/mcoa/IPv6PrefAdr.o \
    $O/networklayer/mpls/MPLS.o \
    $O/networklayer/mpls/MPLSPacket.o \
    $O/networklayer/mpls/LIBTable.o \
    $O/networklayer/ospfv2/OSPFRouting.o \
    $O/networklayer/ospfv2/interface/OSPFInterface.o \
    $O/networklayer/ospfv2/interface/OSPFInterfaceStateWaiting.o \
    $O/networklayer/ospfv2/interface/OSPFInterfaceStatePointToPoint.o \
    $O/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.o \
    $O/networklayer/ospfv2/interface/OSPFInterfaceState.o \
    $O/networklayer/ospfv2/interface/OSPFInterfaceStateDesignatedRouter.o \
    $O/networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.o \
    $O/networklayer/ospfv2/interface/OSPFInterfaceStateBackup.o \
    $O/networklayer/ospfv2/interface/OSPFInterfaceStateDown.o \
    $O/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.o \
    $O/networklayer/ospfv2/messagehandler/HelloHandler.o \
    $O/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.o \
    $O/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.o \
    $O/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.o \
    $O/networklayer/ospfv2/messagehandler/MessageHandler.o \
    $O/networklayer/ospfv2/neighbor/OSPFNeighborStateAttempt.o \
    $O/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.o \
    $O/networklayer/ospfv2/neighbor/OSPFNeighborStateFull.o \
    $O/networklayer/ospfv2/neighbor/OSPFNeighborStateLoading.o \
    $O/networklayer/ospfv2/neighbor/OSPFNeighbor.o \
    $O/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.o \
    $O/networklayer/ospfv2/neighbor/OSPFNeighborState.o \
    $O/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.o \
    $O/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.o \
    $O/networklayer/ospfv2/neighbor/OSPFNeighborStateExchange.o \
    $O/networklayer/ospfv2/router/OSPFArea.o \
    $O/networklayer/ospfv2/router/SummaryLSA.o \
    $O/networklayer/ospfv2/router/ASExternalLSA.o \
    $O/networklayer/ospfv2/router/RouterLSA.o \
    $O/networklayer/ospfv2/router/NetworkLSA.o \
    $O/networklayer/ospfv2/router/OSPFRouter.o \
    $O/networklayer/queue/DropTailQoSQueue.o \
    $O/networklayer/queue/REDQueue.o \
    $O/networklayer/queue/DropTailQueue.o \
    $O/networklayer/queue/BasicDSCPClassifier.o \
    $O/networklayer/rsvp_te/Utils.o \
    $O/networklayer/rsvp_te/SimpleClassifier.o \
    $O/networklayer/rsvp_te/RSVP.o \
    $O/networklayer/ted/TED.o \
    $O/networklayer/ted/LinkStateRouting.o \
    $O/networklayer/xmipv6/xMIPv6.o \
    $O/networklayer/xmipv6/MobilityHeader.o \
    $O/networklayer/xmipv6/BindingCache.o \
    $O/networklayer/xmipv6/BindingUpdateList.o \
    $O/transport/contract/TCPSocketMap.o \
    $O/transport/contract/SCTPSocket.o \
    $O/transport/contract/UDPSocket.o \
    $O/transport/contract/TCPSocket.o \
    $O/transport/rtp/RTPReceiverInfo.o \
    $O/transport/rtp/RTCP.o \
    $O/transport/rtp/sdes.o \
    $O/transport/rtp/RTPInterfacePacket.o \
    $O/transport/rtp/RTPProfile.o \
    $O/transport/rtp/reports.o \
    $O/transport/rtp/RTPPayloadReceiver.o \
    $O/transport/rtp/RTPInnerPacket.o \
    $O/transport/rtp/RTP.o \
    $O/transport/rtp/RTPPacket.o \
    $O/transport/rtp/RTPParticipantInfo.o \
    $O/transport/rtp/RTPSenderInfo.o \
    $O/transport/rtp/RTCPPacket.o \
    $O/transport/rtp/RTPPayloadSender.o \
    $O/transport/rtp/profiles/avprofile/RTPAVProfile.o \
    $O/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Sender.o \
    $O/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Receiver.o \
    $O/transport/sctp/SCTPSendStream.o \
    $O/transport/sctp/SCTPAssociationBase.o \
    $O/transport/sctp/SCTPAlg.o \
    $O/transport/sctp/SCTP.o \
    $O/transport/sctp/SCTPAssociationUtil.o \
    $O/transport/sctp/SCTPAssociationEventProc.o \
    $O/transport/sctp/SCTPAssociationRcvMessage.o \
    $O/transport/sctp/SCTPSSFunctions.o \
    $O/transport/sctp/SCTPReceiveStream.o \
    $O/transport/sctp/SCTPQueue.o \
    $O/transport/sctp/SCTPCCFunctions.o \
    $O/transport/sctp/SCTPMessage.o \
    $O/transport/tcp/TCP.o \
    $O/transport/tcp/TCPConnectionRcvSegment.o \
    $O/transport/tcp/TCPConnectionEventProc.o \
    $O/transport/tcp/TCPSegment.o \
    $O/transport/tcp/TCPConnectionBase.o \
    $O/transport/tcp/TCPConnectionUtil.o \
    $O/transport/tcp/flavours/TCPReno.o \
    $O/transport/tcp/flavours/DumbTCP.o \
    $O/transport/tcp/flavours/TCPNoCongestionControl.o \
    $O/transport/tcp/flavours/TCPTahoeRenoFamily.o \
    $O/transport/tcp/flavours/TCPBaseAlg.o \
    $O/transport/tcp/flavours/TCPTahoe.o \
    $O/transport/tcp/queues/TCPMsgBasedSendQueue.o \
    $O/transport/tcp/queues/TCPVirtualDataSendQueue.o \
    $O/transport/tcp/queues/TCPVirtualDataRcvQueue.o \
    $O/transport/tcp/queues/TCPMsgBasedRcvQueue.o \
    $O/transport/udp/UDP.o \
    $O/util/opp_utils.o \
    $O/util/common.o \
    $O/util/ThruputMeteringChannel.o \
    $O/util/XMLUtils.o \
    $O/util/NAMTraceWriter.o \
    $O/util/TCPDump.o \
    $O/util/headerserializers/IPSerializer.o \
    $O/util/headerserializers/UDPSerializer.o \
    $O/util/headerserializers/TCPSerializer.o \
    $O/util/headerserializers/ICMPSerializer.o \
    $O/util/headerserializers/SCTPSerializer.o \
    $O/world/ChannelControl.o \
    $O/world/NAMTrace.o \
    $O/world/ScenarioManager.o \
    $O/world/ChannelAccess.o \
    $O/world/ChannelInstaller.o \
    $O/applications/ethernet/EtherApp_m.o \
    $O/applications/mcoa/Video/MCoAVideoStreaming_m.o \
    $O/applications/mcoa/VoIP/MCOAVoIPMsg_m.o \
    $O/applications/pingapp/PingPayload_m.o \
    $O/applications/tcpapp/GenericAppMsg_m.o \
    $O/applications/udpapp/UDPEchoAppMsg_m.o \
    $O/base/ByteArrayMessage_m.o \
    $O/linklayer/contract/Ieee802Ctrl_m.o \
    $O/linklayer/contract/PhyControlInfo_m.o \
    $O/linklayer/ethernet/EtherFrame_m.o \
    $O/linklayer/ext/ExtFrame_m.o \
    $O/linklayer/ieee80211/mac/Ieee80211Frame_m.o \
    $O/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.o \
    $O/linklayer/ieee80211/mgmt/Ieee80211Primitives_m.o \
    $O/linklayer/mf80211/macLayer/MacPkt_m.o \
    $O/linklayer/mf80211/macLayer/Mac80211Pkt_m.o \
    $O/linklayer/mfcore/SnrControlInfo_m.o \
    $O/linklayer/mfcore/AirFrame_m.o \
    $O/linklayer/mfcore/TransmComplete_m.o \
    $O/linklayer/ppp/PPPFrame_m.o \
    $O/networklayer/arp/ARPPacket_m.o \
    $O/networklayer/contract/IPControlInfo_m.o \
    $O/networklayer/contract/IPProtocolId_m.o \
    $O/networklayer/contract/IPv6ControlInfo_m.o \
    $O/networklayer/icmpv6/ICMPv6Message_m.o \
    $O/networklayer/icmpv6/IPv6NDMessage_m.o \
    $O/networklayer/ipv4/ICMPMessage_m.o \
    $O/networklayer/ipv4/ControlManetRouting_m.o \
    $O/networklayer/ipv4/IPDatagram_m.o \
    $O/networklayer/ipv6/IPv6Datagram_m.o \
    $O/networklayer/ipv6/IPv6ExtensionHeaders_m.o \
    $O/networklayer/ldp/LDPPacket_m.o \
    $O/networklayer/ospfv2/OSPFPacket_m.o \
    $O/networklayer/ospfv2/OSPFTimer_m.o \
    $O/networklayer/rsvp_te/SignallingMsg_m.o \
    $O/networklayer/rsvp_te/RSVPPacket_m.o \
    $O/networklayer/rsvp_te/RSVPResvMsg_m.o \
    $O/networklayer/rsvp_te/RSVPPathMsg_m.o \
    $O/networklayer/rsvp_te/RSVPHello_m.o \
    $O/networklayer/rsvp_te/IntServ_m.o \
    $O/networklayer/ted/LinkStatePacket_m.o \
    $O/networklayer/ted/TED_m.o \
    $O/networklayer/xmipv6/MobilityHeader_m.o \
    $O/transport/contract/TCPCommand_m.o \
    $O/transport/contract/UDPControlInfo_m.o \
    $O/transport/contract/SCTPCommand_m.o \
    $O/transport/rtp/RTPSenderStatusMessage_m.o \
    $O/transport/rtp/RTPSenderControlMessage_m.o \
    $O/transport/rtp/profiles/avprofile/RTPMpegPacket_m.o \
    $O/transport/sctp/SCTPMessage_m.o \
    $O/transport/tcp/TCPSegment_m.o \
    $O/transport/udp/UDPPacket_m.o

# Message files
MSGFILES = \
    applications/ethernet/EtherApp.msg \
    applications/mcoa/Video/MCoAVideoStreaming.msg \
    applications/mcoa/VoIP/MCOAVoIPMsg.msg \
    applications/pingapp/PingPayload.msg \
    applications/tcpapp/GenericAppMsg.msg \
    applications/udpapp/UDPEchoAppMsg.msg \
    base/ByteArrayMessage.msg \
    linklayer/contract/Ieee802Ctrl.msg \
    linklayer/contract/PhyControlInfo.msg \
    linklayer/ethernet/EtherFrame.msg \
    linklayer/ext/ExtFrame.msg \
    linklayer/ieee80211/mac/Ieee80211Frame.msg \
    linklayer/ieee80211/mgmt/Ieee80211MgmtFrames.msg \
    linklayer/ieee80211/mgmt/Ieee80211Primitives.msg \
    linklayer/mf80211/macLayer/MacPkt.msg \
    linklayer/mf80211/macLayer/Mac80211Pkt.msg \
    linklayer/mfcore/SnrControlInfo.msg \
    linklayer/mfcore/AirFrame.msg \
    linklayer/mfcore/TransmComplete.msg \
    linklayer/ppp/PPPFrame.msg \
    networklayer/arp/ARPPacket.msg \
    networklayer/contract/IPControlInfo.msg \
    networklayer/contract/IPProtocolId.msg \
    networklayer/contract/IPv6ControlInfo.msg \
    networklayer/icmpv6/ICMPv6Message.msg \
    networklayer/icmpv6/IPv6NDMessage.msg \
    networklayer/ipv4/ICMPMessage.msg \
    networklayer/ipv4/ControlManetRouting.msg \
    networklayer/ipv4/IPDatagram.msg \
    networklayer/ipv6/IPv6Datagram.msg \
    networklayer/ipv6/IPv6ExtensionHeaders.msg \
    networklayer/ldp/LDPPacket.msg \
    networklayer/ospfv2/OSPFPacket.msg \
    networklayer/ospfv2/OSPFTimer.msg \
    networklayer/rsvp_te/SignallingMsg.msg \
    networklayer/rsvp_te/RSVPPacket.msg \
    networklayer/rsvp_te/RSVPResvMsg.msg \
    networklayer/rsvp_te/RSVPPathMsg.msg \
    networklayer/rsvp_te/RSVPHello.msg \
    networklayer/rsvp_te/IntServ.msg \
    networklayer/ted/LinkStatePacket.msg \
    networklayer/ted/TED.msg \
    networklayer/xmipv6/MobilityHeader.msg \
    transport/contract/TCPCommand.msg \
    transport/contract/UDPControlInfo.msg \
    transport/contract/SCTPCommand.msg \
    transport/rtp/RTPSenderStatusMessage.msg \
    transport/rtp/RTPSenderControlMessage.msg \
    transport/rtp/profiles/avprofile/RTPMpegPacket.msg \
    transport/sctp/SCTPMessage.msg \
    transport/tcp/TCPSegment.msg \
    transport/udp/UDPPacket.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# inserted from file 'makefrag':
LIBS += $(PCAP_LIBS)

# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET)

$(TARGET) : $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(SHLIB_LD) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(LIBS) $(OMNETPP_LIBS) $(LDFLAGS)
	$(SHLIB_POSTPROCESS) $O/$(TARGET)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f inet inet.exe libinet.so libinet.a libinet.dll libinet.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f applications/*_m.cc applications/*_m.h
	-rm -f applications/ethernet/*_m.cc applications/ethernet/*_m.h
	-rm -f applications/generic/*_m.cc applications/generic/*_m.h
	-rm -f applications/mcoa/*_m.cc applications/mcoa/*_m.h
	-rm -f applications/mcoa/Video/*_m.cc applications/mcoa/Video/*_m.h
	-rm -f applications/mcoa/VoIP/*_m.cc applications/mcoa/VoIP/*_m.h
	-rm -f applications/mcoa/udpbase/*_m.cc applications/mcoa/udpbase/*_m.h
	-rm -f applications/pingapp/*_m.cc applications/pingapp/*_m.h
	-rm -f applications/rtpapp/*_m.cc applications/rtpapp/*_m.h
	-rm -f applications/sctpapp/*_m.cc applications/sctpapp/*_m.h
	-rm -f applications/tcpapp/*_m.cc applications/tcpapp/*_m.h
	-rm -f applications/udpapp/*_m.cc applications/udpapp/*_m.h
	-rm -f base/*_m.cc base/*_m.h
	-rm -f linklayer/*_m.cc linklayer/*_m.h
	-rm -f linklayer/contract/*_m.cc linklayer/contract/*_m.h
	-rm -f linklayer/ethernet/*_m.cc linklayer/ethernet/*_m.h
	-rm -f linklayer/etherswitch/*_m.cc linklayer/etherswitch/*_m.h
	-rm -f linklayer/ext/*_m.cc linklayer/ext/*_m.h
	-rm -f linklayer/ieee80211/*_m.cc linklayer/ieee80211/*_m.h
	-rm -f linklayer/ieee80211/mac/*_m.cc linklayer/ieee80211/mac/*_m.h
	-rm -f linklayer/ieee80211/mgmt/*_m.cc linklayer/ieee80211/mgmt/*_m.h
	-rm -f linklayer/mf80211/*_m.cc linklayer/mf80211/*_m.h
	-rm -f linklayer/mf80211/macLayer/*_m.cc linklayer/mf80211/macLayer/*_m.h
	-rm -f linklayer/mf80211/phyLayer/*_m.cc linklayer/mf80211/phyLayer/*_m.h
	-rm -f linklayer/mf80211/phyLayer/decider/*_m.cc linklayer/mf80211/phyLayer/decider/*_m.h
	-rm -f linklayer/mf80211/phyLayer/snrEval/*_m.cc linklayer/mf80211/phyLayer/snrEval/*_m.h
	-rm -f linklayer/mfcore/*_m.cc linklayer/mfcore/*_m.h
	-rm -f linklayer/ppp/*_m.cc linklayer/ppp/*_m.h
	-rm -f linklayer/radio/*_m.cc linklayer/radio/*_m.h
	-rm -f mobility/*_m.cc mobility/*_m.h
	-rm -f networklayer/*_m.cc networklayer/*_m.h
	-rm -f networklayer/arp/*_m.cc networklayer/arp/*_m.h
	-rm -f networklayer/autorouting/*_m.cc networklayer/autorouting/*_m.h
	-rm -f networklayer/common/*_m.cc networklayer/common/*_m.h
	-rm -f networklayer/contract/*_m.cc networklayer/contract/*_m.h
	-rm -f networklayer/extras/*_m.cc networklayer/extras/*_m.h
	-rm -f networklayer/icmpv6/*_m.cc networklayer/icmpv6/*_m.h
	-rm -f networklayer/ipv4/*_m.cc networklayer/ipv4/*_m.h
	-rm -f networklayer/ipv6/*_m.cc networklayer/ipv6/*_m.h
	-rm -f networklayer/ldp/*_m.cc networklayer/ldp/*_m.h
	-rm -f networklayer/mcoa/*_m.cc networklayer/mcoa/*_m.h
	-rm -f networklayer/mpls/*_m.cc networklayer/mpls/*_m.h
	-rm -f networklayer/ospfv2/*_m.cc networklayer/ospfv2/*_m.h
	-rm -f networklayer/ospfv2/interface/*_m.cc networklayer/ospfv2/interface/*_m.h
	-rm -f networklayer/ospfv2/messagehandler/*_m.cc networklayer/ospfv2/messagehandler/*_m.h
	-rm -f networklayer/ospfv2/neighbor/*_m.cc networklayer/ospfv2/neighbor/*_m.h
	-rm -f networklayer/ospfv2/router/*_m.cc networklayer/ospfv2/router/*_m.h
	-rm -f networklayer/queue/*_m.cc networklayer/queue/*_m.h
	-rm -f networklayer/rsvp_te/*_m.cc networklayer/rsvp_te/*_m.h
	-rm -f networklayer/ted/*_m.cc networklayer/ted/*_m.h
	-rm -f networklayer/xmipv6/*_m.cc networklayer/xmipv6/*_m.h
	-rm -f nodes/*_m.cc nodes/*_m.h
	-rm -f nodes/adhoc/*_m.cc nodes/adhoc/*_m.h
	-rm -f nodes/ethernet/*_m.cc nodes/ethernet/*_m.h
	-rm -f nodes/inet/*_m.cc nodes/inet/*_m.h
	-rm -f nodes/ipv6/*_m.cc nodes/ipv6/*_m.h
	-rm -f nodes/mpls/*_m.cc nodes/mpls/*_m.h
	-rm -f nodes/wireless/*_m.cc nodes/wireless/*_m.h
	-rm -f nodes/xmipv6/*_m.cc nodes/xmipv6/*_m.h
	-rm -f transport/*_m.cc transport/*_m.h
	-rm -f transport/contract/*_m.cc transport/contract/*_m.h
	-rm -f transport/rtp/*_m.cc transport/rtp/*_m.h
	-rm -f transport/rtp/profiles/*_m.cc transport/rtp/profiles/*_m.h
	-rm -f transport/rtp/profiles/avprofile/*_m.cc transport/rtp/profiles/avprofile/*_m.h
	-rm -f transport/sctp/*_m.cc transport/sctp/*_m.h
	-rm -f transport/tcp/*_m.cc transport/tcp/*_m.h
	-rm -f transport/tcp/flavours/*_m.cc transport/tcp/flavours/*_m.h
	-rm -f transport/tcp/queues/*_m.cc transport/tcp/queues/*_m.h
	-rm -f transport/udp/*_m.cc transport/udp/*_m.h
	-rm -f util/*_m.cc util/*_m.h
	-rm -f util/headerserializers/*_m.cc util/headerserializers/*_m.h
	-rm -f util/headerserializers/headers/*_m.cc util/headerserializers/headers/*_m.h
	-rm -f world/*_m.cc world/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc applications/*.cc applications/ethernet/*.cc applications/generic/*.cc applications/mcoa/*.cc applications/mcoa/Video/*.cc applications/mcoa/VoIP/*.cc applications/mcoa/udpbase/*.cc applications/pingapp/*.cc applications/rtpapp/*.cc applications/sctpapp/*.cc applications/tcpapp/*.cc applications/udpapp/*.cc base/*.cc linklayer/*.cc linklayer/contract/*.cc linklayer/ethernet/*.cc linklayer/etherswitch/*.cc linklayer/ext/*.cc linklayer/ieee80211/*.cc linklayer/ieee80211/mac/*.cc linklayer/ieee80211/mgmt/*.cc linklayer/mf80211/*.cc linklayer/mf80211/macLayer/*.cc linklayer/mf80211/phyLayer/*.cc linklayer/mf80211/phyLayer/decider/*.cc linklayer/mf80211/phyLayer/snrEval/*.cc linklayer/mfcore/*.cc linklayer/ppp/*.cc linklayer/radio/*.cc mobility/*.cc networklayer/*.cc networklayer/arp/*.cc networklayer/autorouting/*.cc networklayer/common/*.cc networklayer/contract/*.cc networklayer/extras/*.cc networklayer/icmpv6/*.cc networklayer/ipv4/*.cc networklayer/ipv6/*.cc networklayer/ldp/*.cc networklayer/mcoa/*.cc networklayer/mpls/*.cc networklayer/ospfv2/*.cc networklayer/ospfv2/interface/*.cc networklayer/ospfv2/messagehandler/*.cc networklayer/ospfv2/neighbor/*.cc networklayer/ospfv2/router/*.cc networklayer/queue/*.cc networklayer/rsvp_te/*.cc networklayer/ted/*.cc networklayer/xmipv6/*.cc nodes/*.cc nodes/adhoc/*.cc nodes/ethernet/*.cc nodes/inet/*.cc nodes/ipv6/*.cc nodes/mpls/*.cc nodes/wireless/*.cc nodes/xmipv6/*.cc transport/*.cc transport/contract/*.cc transport/rtp/*.cc transport/rtp/profiles/*.cc transport/rtp/profiles/avprofile/*.cc transport/sctp/*.cc transport/tcp/*.cc transport/tcp/flavours/*.cc transport/tcp/queues/*.cc transport/udp/*.cc util/*.cc util/headerserializers/*.cc util/headerserializers/headers/*.cc world/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/applications/ethernet/EtherAppCli.o: applications/ethernet/EtherAppCli.cc \
	linklayer/contract/MACAddress.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	applications/ethernet/EtherAppCli.h \
	applications/ethernet/EtherApp_m.h \
	base/INETDefs.h
$O/applications/ethernet/EtherAppSrv.o: applications/ethernet/EtherAppSrv.cc \
	linklayer/contract/MACAddress.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	applications/ethernet/EtherApp_m.h \
	base/INETDefs.h \
	applications/ethernet/EtherAppSrv.h
$O/applications/ethernet/EtherApp_m.o: applications/ethernet/EtherApp_m.cc \
	applications/ethernet/EtherApp_m.h \
	base/INETDefs.h
$O/applications/generic/IPTrafGen.o: applications/generic/IPTrafGen.cc \
	networklayer/contract/IPv6ControlInfo.h \
	applications/generic/IPTrafGen.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddressResolver.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/applications/mcoa/Video/MCoAVideoStreaming_m.o: applications/mcoa/Video/MCoAVideoStreaming_m.cc \
	applications/mcoa/Video/MCoAVideoStreaming_m.h \
	base/INETDefs.h
$O/applications/mcoa/Video/MCoAVideoStreamCli.o: applications/mcoa/Video/MCoAVideoStreamCli.cc \
	base/NotificationBoard.h \
	applications/mcoa/udpbase/MCoAUDPBase.h \
	networklayer/contract/IPvXAddress.h \
	base/MCoADefs.h \
	base/ModuleAccess.h \
	networklayer/contract/IPv6Address.h \
	networklayer/mcoa/IPv6PrefAdr.h \
	networklayer/mcoa/IPv6TunAdr.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	applications/mcoa/Video/MCoAVideoStreamCli.h \
	applications/mcoa/Video/MCoAVideoStreaming_m.h \
	networklayer/contract/IPAddressResolver.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/applications/mcoa/Video/MCoAVideoStreamServer.o: applications/mcoa/Video/MCoAVideoStreamServer.cc \
	transport/contract/UDPControlInfo_m.h \
	base/NotificationBoard.h \
	applications/mcoa/udpbase/MCoAUDPBase.h \
	networklayer/contract/IPvXAddress.h \
	base/MCoADefs.h \
	networklayer/contract/IPv6Address.h \
	base/ModuleAccess.h \
	networklayer/mcoa/IPv6PrefAdr.h \
	applications/mcoa/Video/MCoAVideoStreamServer.h \
	networklayer/mcoa/IPv6TunAdr.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	applications/mcoa/Video/MCoAVideoStreaming_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/applications/mcoa/VoIP/MCoAUDPApp.o: applications/mcoa/VoIP/MCoAUDPApp.cc \
	applications/mcoa/VoIP/MCoAUDPApp.h \
	transport/contract/UDPControlInfo_m.h \
	base/NotificationBoard.h \
	applications/mcoa/udpbase/MCoAUDPBase.h \
	networklayer/contract/IPvXAddress.h \
	base/MCoADefs.h \
	applications/mcoa/VoIP/MCOAVoIPMsg_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/mcoa/IPv6PrefAdr.h \
	base/ModuleAccess.h \
	networklayer/mcoa/IPv6TunAdr.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/contract/IPAddressResolver.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/applications/mcoa/VoIP/MCOAVoIPMsg_m.o: applications/mcoa/VoIP/MCOAVoIPMsg_m.cc \
	applications/mcoa/VoIP/MCOAVoIPMsg_m.h \
	base/INETDefs.h
$O/applications/mcoa/udpbase/MCoAUDPBase.o: applications/mcoa/udpbase/MCoAUDPBase.cc \
	transport/contract/UDPSocket.h \
	transport/contract/UDPControlInfo_m.h \
	base/NotificationBoard.h \
	applications/mcoa/udpbase/MCoAUDPBase.h \
	networklayer/contract/IPvXAddress.h \
	base/MCoADefs.h \
	networklayer/mcoa/IPv6PrefAdr.h \
	networklayer/contract/IPv6Address.h \
	base/ModuleAccess.h \
	networklayer/mcoa/IPv6TunAdr.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/applications/pingapp/PingPayload_m.o: applications/pingapp/PingPayload_m.cc \
	applications/pingapp/PingPayload_m.h \
	base/INETDefs.h
$O/applications/pingapp/PingApp.o: applications/pingapp/PingApp.cc \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ipv6/IPv6Datagram.h \
	applications/pingapp/PingApp.h \
	applications/pingapp/PingPayload_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddressResolver.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/applications/rtpapp/RTPApplication.o: applications/rtpapp/RTPApplication.cc \
	transport/rtp/RTPInterfacePacket.h \
	applications/rtpapp/RTPApplication.h \
	transport/rtp/RTPSenderStatusMessage_m.h \
	transport/rtp/RTPSenderControlMessage_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/applications/sctpapp/SCTPClient.o: applications/sctpapp/SCTPClient.cc \
	transport/contract/SCTPCommand_m.h \
	transport/sctp/SCTPQueue.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	transport/sctp/SCTPMessage.h \
	applications/sctpapp/SCTPClient.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/sctp/SCTPReceiveStream.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/contract/SCTPCommand.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddressResolver.h \
	transport/contract/SCTPSocket.h \
	networklayer/contract/IPAddress.h
$O/applications/sctpapp/SCTPServer.o: applications/sctpapp/SCTPServer.cc \
	transport/contract/SCTPCommand_m.h \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPQueue.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	transport/sctp/SCTPMessage.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/sctp/SCTPReceiveStream.h \
	applications/sctpapp/SCTPServer.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/sctp/SCTP.h \
	transport/contract/SCTPCommand.h \
	networklayer/common/InterfaceToken.h \
	transport/contract/SCTPSocket.h \
	networklayer/contract/IPAddress.h
$O/applications/sctpapp/SCTPPeer.o: applications/sctpapp/SCTPPeer.cc \
	transport/contract/SCTPCommand_m.h \
	transport/sctp/SCTPQueue.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	transport/sctp/SCTPMessage.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	applications/sctpapp/SCTPPeer.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	transport/sctp/SCTPReceiveStream.h \
	networklayer/ipv4/RoutingTableAccess.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/contract/SCTPCommand.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddressResolver.h \
	transport/contract/SCTPSocket.h \
	networklayer/contract/IPAddress.h
$O/applications/tcpapp/GenericAppMsg_m.o: applications/tcpapp/GenericAppMsg_m.cc \
	applications/tcpapp/GenericAppMsg_m.h \
	base/INETDefs.h
$O/applications/tcpapp/TCPGenericSrvApp.o: applications/tcpapp/TCPGenericSrvApp.cc \
	networklayer/contract/IPv6Address.h \
	applications/tcpapp/GenericAppMsg_m.h \
	transport/contract/TCPSocket.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	applications/tcpapp/TCPGenericSrvApp.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/tcpapp/TelnetApp.o: applications/tcpapp/TelnetApp.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/TCPSocket.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	applications/tcpapp/TCPGenericCliAppBase.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h \
	applications/tcpapp/TelnetApp.h
$O/applications/tcpapp/TCPSrvHostApp.o: applications/tcpapp/TCPSrvHostApp.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/TCPSocket.h \
	transport/contract/TCPCommand_m.h \
	applications/tcpapp/TCPSrvHostApp.h \
	networklayer/contract/IPvXAddress.h \
	transport/contract/TCPSocketMap.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/tcpapp/TCPGenericCliAppBase.o: applications/tcpapp/TCPGenericCliAppBase.cc \
	networklayer/contract/IPv6Address.h \
	applications/tcpapp/GenericAppMsg_m.h \
	transport/contract/TCPSocket.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	applications/tcpapp/TCPGenericCliAppBase.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/tcpapp/TCPSessionApp.o: applications/tcpapp/TCPSessionApp.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/TCPSocket.h \
	transport/contract/TCPCommand_m.h \
	applications/tcpapp/TCPSessionApp.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/tcpapp/TCPEchoApp.o: applications/tcpapp/TCPEchoApp.cc \
	networklayer/contract/IPv6Address.h \
	applications/tcpapp/TCPEchoApp.h \
	transport/contract/TCPSocket.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/tcpapp/TCPBasicClientApp.o: applications/tcpapp/TCPBasicClientApp.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/TCPSocket.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	applications/tcpapp/TCPBasicClientApp.h \
	applications/tcpapp/TCPGenericCliAppBase.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/tcpapp/TCPGenericSrvThread.o: applications/tcpapp/TCPGenericSrvThread.cc \
	networklayer/contract/IPv6Address.h \
	applications/tcpapp/GenericAppMsg_m.h \
	transport/contract/TCPSocket.h \
	applications/tcpapp/TCPGenericSrvThread.h \
	applications/tcpapp/TCPSrvHostApp.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	transport/contract/TCPSocketMap.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/tcpapp/TCPSinkApp.o: applications/tcpapp/TCPSinkApp.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/TCPSocket.h \
	applications/tcpapp/TCPSinkApp.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/tcpapp/TCPSpoof.o: applications/tcpapp/TCPSpoof.cc \
	transport/tcp/TCPSegment_m.h \
	applications/tcpapp/TCPSpoof.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ipv6/IPv6Datagram.h \
	transport/tcp/TCPSegment.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/udpapp/UDPBasicApp.o: applications/udpapp/UDPBasicApp.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/UDPControlInfo_m.h \
	applications/udpapp/UDPAppBase.h \
	networklayer/contract/IPvXAddress.h \
	applications/udpapp/UDPBasicApp.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/udpapp/UDPVideoStreamCli.o: applications/udpapp/UDPVideoStreamCli.cc \
	networklayer/contract/IPv6Address.h \
	applications/udpapp/UDPAppBase.h \
	applications/udpapp/UDPVideoStreamCli.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/udpapp/UDPSink.o: applications/udpapp/UDPSink.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/UDPControlInfo_m.h \
	applications/udpapp/UDPAppBase.h \
	networklayer/contract/IPvXAddress.h \
	applications/udpapp/UDPSink.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/udpapp/UDPEchoApp.o: applications/udpapp/UDPEchoApp.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/UDPControlInfo_m.h \
	applications/udpapp/UDPAppBase.h \
	applications/udpapp/UDPEchoAppMsg_m.h \
	networklayer/contract/IPvXAddress.h \
	applications/udpapp/UDPEchoApp.h \
	applications/udpapp/UDPBasicApp.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/udpapp/UDPAppBase.o: applications/udpapp/UDPAppBase.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/UDPControlInfo_m.h \
	transport/contract/UDPSocket.h \
	applications/udpapp/UDPAppBase.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/applications/udpapp/UDPEchoAppMsg_m.o: applications/udpapp/UDPEchoAppMsg_m.cc \
	applications/udpapp/UDPEchoAppMsg_m.h \
	base/INETDefs.h
$O/applications/udpapp/UDPVideoStreamSvr.o: applications/udpapp/UDPVideoStreamSvr.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/UDPControlInfo_m.h \
	applications/udpapp/UDPAppBase.h \
	networklayer/contract/IPvXAddress.h \
	applications/udpapp/UDPVideoStreamSvr.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/base/BasicModule.o: base/BasicModule.cc \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	base/INETDefs.h
$O/base/AbstractQueue.o: base/AbstractQueue.cc \
	base/AbstractQueue.h \
	base/INETDefs.h
$O/base/ByteArrayMessage.o: base/ByteArrayMessage.cc \
	base/ByteArrayMessage.h \
	base/ByteArrayMessage_m.h \
	base/INETDefs.h
$O/base/NotificationBoard.o: base/NotificationBoard.cc \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/NotificationBoard.h \
	base/INETDefs.h
$O/base/ReassemblyBuffer.o: base/ReassemblyBuffer.cc \
	base/ReassemblyBuffer.h \
	base/INETDefs.h
$O/base/NotifierConsts.o: base/NotifierConsts.cc \
	base/NotifierConsts.h \
	base/INETDefs.h
$O/base/PassiveQueueBase.o: base/PassiveQueueBase.cc \
	base/PassiveQueueBase.h \
	base/INETDefs.h \
	base/IPassiveQueue.h
$O/base/Sink.o: base/Sink.cc \
	base/Sink.h \
	base/INETDefs.h
$O/base/Join.o: base/Join.cc \
	base/INETDefs.h
$O/base/ByteArrayMessage_m.o: base/ByteArrayMessage_m.cc \
	base/ByteArrayMessage_m.h \
	base/INETDefs.h
$O/base/Blackboard.o: base/Blackboard.cc \
	base/ModuleAccess.h \
	base/Blackboard.h \
	base/INETDefs.h
$O/base/ProtocolMap.o: base/ProtocolMap.cc \
	base/ProtocolMap.h \
	base/INETDefs.h
$O/base/QueueWithQoS.o: base/QueueWithQoS.cc \
	base/AbstractQueue.h \
	base/EnqueueHook.h \
	base/QueueWithQoS.h \
	base/INETDefs.h
$O/base/ModuleAccess.o: base/ModuleAccess.cc \
	base/ModuleAccess.h \
	base/INETDefs.h
$O/base/QueueBase.o: base/QueueBase.cc \
	base/AbstractQueue.h \
	base/QueueBase.h \
	base/INETDefs.h
$O/linklayer/contract/PhyControlInfo_m.o: linklayer/contract/PhyControlInfo_m.cc \
	linklayer/contract/PhyControlInfo_m.h \
	base/INETDefs.h
$O/linklayer/contract/MACAddress.o: linklayer/contract/MACAddress.cc \
	linklayer/contract/MACAddress.h \
	networklayer/common/InterfaceToken.h \
	base/INETDefs.h
$O/linklayer/contract/Ieee802Ctrl_m.o: linklayer/contract/Ieee802Ctrl_m.cc \
	linklayer/contract/MACAddress.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	base/INETDefs.h
$O/linklayer/ethernet/EtherBus.o: linklayer/ethernet/EtherBus.cc \
	linklayer/ethernet/Ethernet.h \
	linklayer/contract/MACAddress.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	linklayer/ethernet/EtherBus.h \
	linklayer/ethernet/EtherFrame_m.h \
	base/INETDefs.h
$O/linklayer/ethernet/EtherMACBase.o: linklayer/ethernet/EtherMACBase.cc \
	linklayer/ethernet/Ethernet.h \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	linklayer/ethernet/EtherFrame_m.h \
	base/ModuleAccess.h \
	linklayer/ethernet/EtherMACBase.h \
	linklayer/contract/TxNotifDetails.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/common/InterfaceToken.h \
	base/IPassiveQueue.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h
$O/linklayer/ethernet/EtherMAC2.o: linklayer/ethernet/EtherMAC2.cc \
	linklayer/contract/MACAddress.h \
	linklayer/ethernet/Ethernet.h \
	base/NotificationBoard.h \
	linklayer/ethernet/EtherFrame_m.h \
	linklayer/ethernet/EtherMAC2.h \
	base/ModuleAccess.h \
	linklayer/ethernet/EtherMACBase.h \
	base/INotifiable.h \
	linklayer/contract/TxNotifDetails.h \
	base/NotifierConsts.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceToken.h \
	base/IPassiveQueue.h \
	base/INETDefs.h
$O/linklayer/ethernet/EtherLLC.o: linklayer/ethernet/EtherLLC.cc \
	linklayer/ethernet/Ethernet.h \
	linklayer/contract/MACAddress.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	linklayer/ethernet/EtherLLC.h \
	linklayer/ethernet/EtherFrame_m.h \
	base/INETDefs.h
$O/linklayer/ethernet/EtherHub.o: linklayer/ethernet/EtherHub.cc \
	linklayer/ethernet/Ethernet.h \
	linklayer/contract/MACAddress.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	linklayer/ethernet/EtherFrame_m.h \
	linklayer/ethernet/EtherHub.h \
	base/INETDefs.h
$O/linklayer/ethernet/EtherMAC.o: linklayer/ethernet/EtherMAC.cc \
	linklayer/contract/MACAddress.h \
	linklayer/ethernet/Ethernet.h \
	base/NotificationBoard.h \
	linklayer/ethernet/EtherFrame_m.h \
	base/ModuleAccess.h \
	linklayer/ethernet/EtherMACBase.h \
	base/INotifiable.h \
	linklayer/contract/TxNotifDetails.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	linklayer/ethernet/EtherMAC.h \
	networklayer/common/InterfaceToken.h \
	base/IPassiveQueue.h \
	base/INETDefs.h
$O/linklayer/ethernet/EtherFrame_m.o: linklayer/ethernet/EtherFrame_m.cc \
	linklayer/ethernet/Ethernet.h \
	linklayer/contract/MACAddress.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	linklayer/ethernet/EtherFrame_m.h \
	base/INETDefs.h
$O/linklayer/ethernet/EtherEncap.o: linklayer/ethernet/EtherEncap.cc \
	linklayer/contract/MACAddress.h \
	linklayer/ethernet/Ethernet.h \
	base/NotificationBoard.h \
	linklayer/ethernet/EtherFrame_m.h \
	base/ModuleAccess.h \
	linklayer/ethernet/EtherMACBase.h \
	linklayer/contract/TxNotifDetails.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	linklayer/ethernet/EtherMAC.h \
	linklayer/ethernet/EtherEncap.h \
	networklayer/common/InterfaceToken.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h
$O/linklayer/etherswitch/MACRelayUnitNP.o: linklayer/etherswitch/MACRelayUnitNP.cc \
	linklayer/contract/MACAddress.h \
	linklayer/ethernet/Ethernet.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	linklayer/etherswitch/MACRelayUnitBase.h \
	linklayer/ethernet/EtherFrame_m.h \
	base/INETDefs.h \
	linklayer/etherswitch/MACRelayUnitNP.h
$O/linklayer/etherswitch/MACRelayUnitBase.o: linklayer/etherswitch/MACRelayUnitBase.cc \
	linklayer/ethernet/Ethernet.h \
	linklayer/contract/MACAddress.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	linklayer/etherswitch/MACRelayUnitBase.h \
	linklayer/ethernet/EtherFrame_m.h \
	base/INETDefs.h
$O/linklayer/etherswitch/MACRelayUnitPP.o: linklayer/etherswitch/MACRelayUnitPP.cc \
	linklayer/contract/MACAddress.h \
	linklayer/ethernet/Ethernet.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	linklayer/etherswitch/MACRelayUnitBase.h \
	linklayer/etherswitch/MACRelayUnitPP.h \
	linklayer/ethernet/EtherFrame_m.h \
	base/INETDefs.h
$O/linklayer/ext/ExtInterface.o: linklayer/ext/ExtInterface.cc \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	linklayer/ext/ExtFrame_m.h \
	linklayer/ext/cSocketRTScheduler.h \
	linklayer/ext/ExtInterface.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	networklayer/common/InterfaceTable.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	util/headerserializers/IPSerializer.h \
	util/headerserializers/headers/bsdint.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h
$O/linklayer/ext/ExtFrame_m.o: linklayer/ext/ExtFrame_m.cc \
	linklayer/ext/ExtFrame_m.h
$O/linklayer/ext/cSocketRTScheduler.o: linklayer/ext/cSocketRTScheduler.cc \
	linklayer/ext/ExtFrame_m.h \
	util/headerserializers/headers/bsdint.h \
	linklayer/ext/cSocketRTScheduler.h \
	util/headerserializers/headers/ethernet.h \
	base/INETDefs.h
$O/linklayer/ieee80211/mac/Ieee80211Frame_m.o: linklayer/ieee80211/mac/Ieee80211Frame_m.cc \
	linklayer/contract/MACAddress.h \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	base/INETDefs.h
$O/linklayer/ieee80211/mac/Ieee80211Mac.o: linklayer/ieee80211/mac/Ieee80211Mac.cc \
	linklayer/contract/MACAddress.h \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	base/NotificationBoard.h \
	linklayer/ieee80211/mac/Ieee80211Mac.h \
	linklayer/contract/PhyControlInfo_m.h \
	linklayer/ieee80211/mac/Ieee80211Consts.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	linklayer/mfcore/WirelessMacBase.h \
	networklayer/common/InterfaceEntry.h \
	base/FSMA.h \
	networklayer/common/InterfaceTableAccess.h \
	linklayer/contract/RadioState.h \
	networklayer/common/InterfaceToken.h \
	base/IPassiveQueue.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h
$O/linklayer/ieee80211/mgmt/Ieee80211Primitives_m.o: linklayer/ieee80211/mgmt/Ieee80211Primitives_m.cc \
	linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	linklayer/contract/MACAddress.h \
	linklayer/ieee80211/mgmt/Ieee80211Primitives_m.h \
	base/INETDefs.h
$O/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.o: linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.cc \
	linklayer/contract/MACAddress.h \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	base/INETDefs.h
$O/linklayer/ieee80211/mgmt/Ieee80211MgmtSTASimplified.o: linklayer/ieee80211/mgmt/Ieee80211MgmtSTASimplified.cc \
	linklayer/contract/MACAddress.h \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	base/NotificationBoard.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtSTASimplified.h \
	base/ModuleAccess.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	base/INotifiable.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	base/NotifierConsts.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	base/PassiveQueueBase.h \
	base/INETDefs.h \
	base/IPassiveQueue.h
$O/linklayer/ieee80211/mgmt/Ieee80211MgmtAdhoc.o: linklayer/ieee80211/mgmt/Ieee80211MgmtAdhoc.cc \
	linklayer/contract/MACAddress.h \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	base/NotificationBoard.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtAdhoc.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	base/NotifierConsts.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	base/PassiveQueueBase.h \
	base/INETDefs.h \
	base/IPassiveQueue.h
$O/linklayer/ieee80211/mgmt/Ieee80211MgmtSTA.o: linklayer/ieee80211/mgmt/Ieee80211MgmtSTA.cc \
	util/FWMath.h \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	linklayer/ieee80211/mgmt/Ieee80211Primitives_m.h \
	linklayer/contract/PhyControlInfo_m.h \
	world/ChannelControl.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	base/NotifierConsts.h \
	base/Coord.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	linklayer/contract/RadioState.h \
	linklayer/mfcore/AirFrame_m.h \
	base/PassiveQueueBase.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtSTA.h \
	base/IPassiveQueue.h \
	base/INETDefs.h
$O/linklayer/ieee80211/mgmt/Ieee80211MgmtAP.o: linklayer/ieee80211/mgmt/Ieee80211MgmtAP.cc \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	linklayer/contract/MACAddress.h \
	linklayer/ethernet/Ethernet.h \
	base/NotificationBoard.h \
	linklayer/ethernet/EtherFrame_m.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtAP.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	base/NotifierConsts.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.h \
	linklayer/contract/RadioState.h \
	base/PassiveQueueBase.h \
	base/IPassiveQueue.h \
	base/INETDefs.h
$O/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.o: linklayer/ieee80211/mgmt/Ieee80211MgmtBase.cc \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	base/ModuleAccess.h \
	linklayer/contract/MACAddress.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	base/NotificationBoard.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	base/PassiveQueueBase.h \
	base/IPassiveQueue.h \
	base/INETDefs.h
$O/linklayer/ieee80211/mgmt/Ieee80211AgentSTA.o: linklayer/ieee80211/mgmt/Ieee80211AgentSTA.cc \
	base/ModuleAccess.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	linklayer/contract/MACAddress.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/NotificationBoard.h \
	linklayer/ieee80211/mgmt/Ieee80211Primitives_m.h \
	linklayer/ieee80211/mgmt/Ieee80211AgentSTA.h \
	base/INETDefs.h
$O/linklayer/ieee80211/mgmt/Ieee80211MgmtAPSimplified.o: linklayer/ieee80211/mgmt/Ieee80211MgmtAPSimplified.cc \
	linklayer/ethernet/Ethernet.h \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	linklayer/contract/MACAddress.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtAPSimplified.h \
	base/NotificationBoard.h \
	linklayer/ethernet/EtherFrame_m.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	base/NotifierConsts.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.h \
	base/PassiveQueueBase.h \
	base/IPassiveQueue.h \
	base/INETDefs.h
$O/linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.o: linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.cc \
	linklayer/contract/MACAddress.h \
	linklayer/ethernet/Ethernet.h \
	linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	base/NotificationBoard.h \
	linklayer/ethernet/EtherFrame_m.h \
	base/ModuleAccess.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h \
	base/INotifiable.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	base/NotifierConsts.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h \
	linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.h \
	base/PassiveQueueBase.h \
	base/IPassiveQueue.h \
	base/INETDefs.h
$O/linklayer/mf80211/macLayer/CSMAMacLayer.o: linklayer/mf80211/macLayer/CSMAMacLayer.cc \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	linklayer/mf80211/macLayer/CSMAMacLayer.h \
	linklayer/mf80211/macLayer/MacPkt_m.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	base/NotifierConsts.h \
	linklayer/mfcore/WirelessMacBase.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	linklayer/contract/RadioState.h \
	networklayer/common/InterfaceToken.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h
$O/linklayer/mf80211/macLayer/Mac80211.o: linklayer/mf80211/macLayer/Mac80211.cc \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	linklayer/mf80211/macLayer/MacPkt_m.h \
	linklayer/mf80211/macLayer/Mac80211Pkt_m.h \
	linklayer/mf80211/macLayer/Mac80211.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	linklayer/mfcore/WirelessMacBase.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	linklayer/mf80211/macLayer/Consts80211.h \
	linklayer/contract/RadioState.h \
	networklayer/common/InterfaceToken.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h
$O/linklayer/mf80211/macLayer/MacPkt_m.o: linklayer/mf80211/macLayer/MacPkt_m.cc \
	linklayer/contract/MACAddress.h \
	linklayer/mf80211/macLayer/MacPkt_m.h \
	base/INETDefs.h
$O/linklayer/mf80211/macLayer/Mac80211Pkt_m.o: linklayer/mf80211/macLayer/Mac80211Pkt_m.cc \
	linklayer/contract/MACAddress.h \
	linklayer/mf80211/macLayer/MacPkt_m.h \
	linklayer/mf80211/macLayer/Mac80211Pkt_m.h \
	base/INETDefs.h
$O/linklayer/mf80211/phyLayer/decider/Decider80211.o: linklayer/mf80211/phyLayer/decider/Decider80211.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	linklayer/mfcore/BasicDecider.h \
	base/ModuleAccess.h \
	linklayer/mfcore/SnrList.h \
	base/INotifiable.h \
	base/Coord.h \
	base/NotifierConsts.h \
	linklayer/mfcore/SnrControlInfo_m.h \
	linklayer/mf80211/phyLayer/decider/Decider80211.h \
	linklayer/mf80211/macLayer/Consts80211.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/linklayer/mf80211/phyLayer/decider/SnrDecider.o: linklayer/mf80211/phyLayer/decider/SnrDecider.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	linklayer/mf80211/phyLayer/decider/SnrDecider.h \
	linklayer/mfcore/BasicDecider.h \
	base/ModuleAccess.h \
	linklayer/mfcore/SnrList.h \
	base/INotifiable.h \
	base/Coord.h \
	base/NotifierConsts.h \
	linklayer/mfcore/SnrControlInfo_m.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/linklayer/mf80211/phyLayer/decider/ErrAndCollDecider.o: linklayer/mf80211/phyLayer/decider/ErrAndCollDecider.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	linklayer/mfcore/BasicDecider.h \
	linklayer/mf80211/phyLayer/decider/SnrDecider.h \
	linklayer/mf80211/phyLayer/decider/ErrAndCollDecider.h \
	base/ModuleAccess.h \
	linklayer/mfcore/SnrList.h \
	base/INotifiable.h \
	base/Coord.h \
	base/NotifierConsts.h \
	linklayer/mfcore/SnrControlInfo_m.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/linklayer/mf80211/phyLayer/snrEval/SnrEval80211.o: linklayer/mf80211/phyLayer/snrEval/SnrEval80211.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	linklayer/mfcore/BasicSnrEval.h \
	base/BasicModule.h \
	linklayer/contract/PhyControlInfo_m.h \
	world/ChannelAccess.h \
	world/ChannelControl.h \
	linklayer/mf80211/phyLayer/snrEval/SnrEval.h \
	base/ModuleAccess.h \
	linklayer/mfcore/SnrList.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	linklayer/mfcore/SnrControlInfo_m.h \
	linklayer/mf80211/macLayer/Consts80211.h \
	linklayer/contract/RadioState.h \
	linklayer/mf80211/phyLayer/snrEval/SnrEval80211.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/linklayer/mf80211/phyLayer/snrEval/GilbertElliotSnr.o: linklayer/mf80211/phyLayer/snrEval/GilbertElliotSnr.cc \
	linklayer/mf80211/phyLayer/snrEval/GilbertElliotSnr.h \
	util/FWMath.h \
	base/NotificationBoard.h \
	linklayer/mfcore/BasicSnrEval.h \
	base/BasicModule.h \
	linklayer/contract/PhyControlInfo_m.h \
	world/ChannelAccess.h \
	world/ChannelControl.h \
	linklayer/mf80211/phyLayer/snrEval/SnrEval.h \
	base/ModuleAccess.h \
	linklayer/mfcore/SnrList.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	linklayer/mfcore/SnrControlInfo_m.h \
	linklayer/mfcore/AirFrame_m.h \
	linklayer/contract/RadioState.h \
	base/INETDefs.h
$O/linklayer/mf80211/phyLayer/snrEval/SnrEval.o: linklayer/mf80211/phyLayer/snrEval/SnrEval.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	linklayer/mfcore/BasicSnrEval.h \
	base/BasicModule.h \
	linklayer/contract/PhyControlInfo_m.h \
	world/ChannelAccess.h \
	world/ChannelControl.h \
	linklayer/mf80211/phyLayer/snrEval/SnrEval.h \
	base/ModuleAccess.h \
	linklayer/mfcore/SnrList.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	linklayer/mfcore/SnrControlInfo_m.h \
	linklayer/contract/RadioState.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/linklayer/mfcore/SnrControlInfo_m.o: linklayer/mfcore/SnrControlInfo_m.cc \
	linklayer/mfcore/SnrList.h \
	linklayer/mfcore/SnrControlInfo_m.h \
	base/INETDefs.h
$O/linklayer/mfcore/BasicDecider.o: linklayer/mfcore/BasicDecider.cc \
	util/FWMath.h \
	base/ModuleAccess.h \
	linklayer/mfcore/SnrList.h \
	base/INotifiable.h \
	base/Coord.h \
	base/NotifierConsts.h \
	base/NotificationBoard.h \
	linklayer/mfcore/SnrControlInfo_m.h \
	base/BasicModule.h \
	linklayer/mfcore/BasicDecider.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/linklayer/mfcore/AirFrame_m.o: linklayer/mfcore/AirFrame_m.cc \
	util/FWMath.h \
	base/Coord.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/linklayer/mfcore/BasicSnrEval.o: linklayer/mfcore/BasicSnrEval.cc \
	util/FWMath.h \
	linklayer/mfcore/BasicSnrEval.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	linklayer/mfcore/TransmComplete_m.h \
	world/ChannelAccess.h \
	world/ChannelControl.h \
	base/ModuleAccess.h \
	linklayer/mfcore/SnrList.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	linklayer/mfcore/SnrControlInfo_m.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/linklayer/mfcore/WirelessMacBase.o: linklayer/mfcore/WirelessMacBase.cc \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/NotificationBoard.h \
	linklayer/mfcore/WirelessMacBase.h \
	base/INETDefs.h
$O/linklayer/mfcore/TransmComplete_m.o: linklayer/mfcore/TransmComplete_m.cc \
	linklayer/mfcore/TransmComplete_m.h \
	base/INETDefs.h
$O/linklayer/ppp/PPPFrame_m.o: linklayer/ppp/PPPFrame_m.cc \
	linklayer/ppp/PPPFrame_m.h \
	base/INETDefs.h
$O/linklayer/ppp/PPP.o: linklayer/ppp/PPP.cc \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	linklayer/ppp/PPPFrame_m.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	linklayer/contract/TxNotifDetails.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	linklayer/ppp/PPP.h \
	networklayer/common/InterfaceToken.h \
	networklayer/common/IInterfaceTable.h \
	base/IPassiveQueue.h \
	base/INETDefs.h
$O/linklayer/ppp/ThruputMeter.o: linklayer/ppp/ThruputMeter.cc \
	linklayer/ppp/ThruputMeter.h \
	base/INETDefs.h
$O/linklayer/radio/AbstractRadio.o: linklayer/radio/AbstractRadio.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	linklayer/contract/PhyControlInfo_m.h \
	linklayer/radio/AbstractRadio.h \
	world/ChannelAccess.h \
	world/ChannelControl.h \
	linklayer/ieee80211/mac/Ieee80211Consts.h \
	base/ModuleAccess.h \
	linklayer/mfcore/SnrList.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	linklayer/mfcore/AirFrame_m.h \
	linklayer/contract/RadioState.h \
	linklayer/radio/IReceptionModel.h \
	linklayer/radio/IRadioModel.h \
	base/INETDefs.h
$O/linklayer/radio/PathLossReceptionModel.o: linklayer/radio/PathLossReceptionModel.cc \
	util/FWMath.h \
	linklayer/radio/PathLossReceptionModel.h \
	base/Coord.h \
	linklayer/mfcore/AirFrame_m.h \
	linklayer/radio/IReceptionModel.h \
	world/ChannelControl.h \
	base/INETDefs.h
$O/linklayer/radio/Modulation.o: linklayer/radio/Modulation.cc \
	linklayer/radio/Modulation.h \
	linklayer/radio/IModulation.h \
	base/INETDefs.h
$O/linklayer/radio/Ieee80211RadioModel.o: linklayer/radio/Ieee80211RadioModel.cc \
	util/FWMath.h \
	linklayer/mfcore/SnrList.h \
	base/Coord.h \
	linklayer/mfcore/AirFrame_m.h \
	linklayer/radio/Ieee80211RadioModel.h \
	linklayer/radio/IRadioModel.h \
	base/INETDefs.h \
	linklayer/ieee80211/mac/Ieee80211Consts.h
$O/linklayer/radio/Ieee80211Radio.o: linklayer/radio/Ieee80211Radio.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	linklayer/radio/Ieee80211Radio.h \
	world/ChannelAccess.h \
	linklayer/radio/AbstractRadio.h \
	world/ChannelControl.h \
	base/ModuleAccess.h \
	linklayer/mfcore/SnrList.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	linklayer/contract/RadioState.h \
	linklayer/mfcore/AirFrame_m.h \
	linklayer/radio/IReceptionModel.h \
	linklayer/radio/IRadioModel.h \
	base/INETDefs.h
$O/linklayer/radio/GenericRadio.o: linklayer/radio/GenericRadio.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	linklayer/radio/AbstractRadio.h \
	world/ChannelAccess.h \
	world/ChannelControl.h \
	base/ModuleAccess.h \
	linklayer/radio/GenericRadio.h \
	linklayer/mfcore/SnrList.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	linklayer/contract/RadioState.h \
	linklayer/mfcore/AirFrame_m.h \
	linklayer/radio/IReceptionModel.h \
	linklayer/radio/IRadioModel.h \
	base/INETDefs.h
$O/linklayer/radio/GenericRadioModel.o: linklayer/radio/GenericRadioModel.cc \
	util/FWMath.h \
	linklayer/mfcore/SnrList.h \
	linklayer/radio/GenericRadioModel.h \
	base/Coord.h \
	linklayer/mfcore/AirFrame_m.h \
	linklayer/radio/Modulation.h \
	linklayer/radio/IRadioModel.h \
	linklayer/radio/IModulation.h \
	base/INETDefs.h
$O/mobility/BonnMotionFileCache.o: mobility/BonnMotionFileCache.cc \
	base/ModuleAccess.h \
	util/FWMath.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	base/NotificationBoard.h \
	mobility/BasicMobility.h \
	base/BasicModule.h \
	mobility/BonnMotionFileCache.h \
	linklayer/mfcore/AirFrame_m.h \
	world/ChannelControl.h \
	base/INETDefs.h
$O/mobility/BasicMobility.o: mobility/BasicMobility.cc \
	base/ModuleAccess.h \
	util/FWMath.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	mobility/BasicMobility.h \
	linklayer/mfcore/AirFrame_m.h \
	world/ChannelControl.h \
	base/INETDefs.h
$O/mobility/NullMobility.o: mobility/NullMobility.cc \
	util/FWMath.h \
	base/ModuleAccess.h \
	mobility/NullMobility.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	base/NotificationBoard.h \
	mobility/BasicMobility.h \
	base/BasicModule.h \
	linklayer/mfcore/AirFrame_m.h \
	world/ChannelControl.h \
	base/INETDefs.h
$O/mobility/ConstSpeedMobility.o: mobility/ConstSpeedMobility.cc \
	base/ModuleAccess.h \
	util/FWMath.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	base/NotificationBoard.h \
	mobility/BasicMobility.h \
	base/BasicModule.h \
	mobility/ConstSpeedMobility.h \
	linklayer/mfcore/AirFrame_m.h \
	world/ChannelControl.h \
	base/INETDefs.h
$O/mobility/TurtleMobility.o: mobility/TurtleMobility.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	mobility/LineSegmentsMobilityBase.h \
	world/ChannelControl.h \
	mobility/TurtleMobility.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	mobility/BasicMobility.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/mobility/CircleMobility.o: mobility/CircleMobility.cc \
	base/ModuleAccess.h \
	util/FWMath.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	base/NotificationBoard.h \
	mobility/CircleMobility.h \
	base/BasicModule.h \
	mobility/BasicMobility.h \
	linklayer/mfcore/AirFrame_m.h \
	world/ChannelControl.h \
	base/INETDefs.h
$O/mobility/BonnMotionMobility.o: mobility/BonnMotionMobility.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	mobility/BonnMotionMobility.h \
	base/BasicModule.h \
	mobility/LineSegmentsMobilityBase.h \
	world/ChannelControl.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/Coord.h \
	base/NotifierConsts.h \
	mobility/BonnMotionFileCache.h \
	mobility/BasicMobility.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/mobility/RectangleMobility.o: mobility/RectangleMobility.cc \
	base/ModuleAccess.h \
	util/FWMath.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	base/Coord.h \
	base/NotificationBoard.h \
	mobility/RectangleMobility.h \
	mobility/BasicMobility.h \
	base/BasicModule.h \
	linklayer/mfcore/AirFrame_m.h \
	world/ChannelControl.h \
	base/INETDefs.h
$O/mobility/LinearMobility.o: mobility/LinearMobility.cc \
	base/ModuleAccess.h \
	util/FWMath.h \
	base/INotifiable.h \
	base/Coord.h \
	base/NotifierConsts.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	mobility/BasicMobility.h \
	linklayer/mfcore/AirFrame_m.h \
	mobility/LinearMobility.h \
	world/ChannelControl.h \
	base/INETDefs.h
$O/mobility/ANSimMobility.o: mobility/ANSimMobility.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	mobility/LineSegmentsMobilityBase.h \
	world/ChannelControl.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/Coord.h \
	base/NotifierConsts.h \
	mobility/ANSimMobility.h \
	mobility/BasicMobility.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/mobility/MassMobility.o: mobility/MassMobility.cc \
	base/ModuleAccess.h \
	util/FWMath.h \
	base/INotifiable.h \
	base/Coord.h \
	base/NotifierConsts.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	mobility/BasicMobility.h \
	linklayer/mfcore/AirFrame_m.h \
	world/ChannelControl.h \
	mobility/MassMobility.h \
	base/INETDefs.h
$O/mobility/LineSegmentsMobilityBase.o: mobility/LineSegmentsMobilityBase.cc \
	base/ModuleAccess.h \
	util/FWMath.h \
	base/INotifiable.h \
	base/Coord.h \
	base/NotifierConsts.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	mobility/BasicMobility.h \
	linklayer/mfcore/AirFrame_m.h \
	mobility/LineSegmentsMobilityBase.h \
	world/ChannelControl.h \
	base/INETDefs.h
$O/mobility/RandomWPMobility.o: mobility/RandomWPMobility.cc \
	util/FWMath.h \
	base/NotificationBoard.h \
	mobility/RandomWPMobility.h \
	base/BasicModule.h \
	mobility/LineSegmentsMobilityBase.h \
	world/ChannelControl.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/Coord.h \
	base/NotifierConsts.h \
	mobility/BasicMobility.h \
	linklayer/mfcore/AirFrame_m.h \
	base/INETDefs.h
$O/networklayer/arp/ARP.o: networklayer/arp/ARP.cc \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ipv4/RoutingTableAccess.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ipv4/IPDatagram.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	base/NotifierConsts.h \
	networklayer/arp/ARPPacket_m.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/InterfaceToken.h \
	networklayer/arp/ARP.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/arp/ARPPacket_m.o: networklayer/arp/ARPPacket_m.cc \
	linklayer/contract/MACAddress.h \
	networklayer/arp/ARPPacket_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/autorouting/MCoANetConf6.o: networklayer/autorouting/MCoANetConf6.cc \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/autorouting/MCoANetConf6.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6Datagram.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	networklayer/contract/IPAddress.h
$O/networklayer/autorouting/NetworkConfigurator.o: networklayer/autorouting/NetworkConfigurator.cc \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/contract/IPv6Address.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/autorouting/NetworkConfigurator.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/autorouting/FlatNetworkConfigurator6.o: networklayer/autorouting/FlatNetworkConfigurator6.cc \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6Datagram.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	networklayer/autorouting/FlatNetworkConfigurator6.h \
	networklayer/contract/IPAddress.h
$O/networklayer/autorouting/FlatNetworkConfigurator.o: networklayer/autorouting/FlatNetworkConfigurator.cc \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/autorouting/FlatNetworkConfigurator.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/contract/IPv6Address.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/common/InterfaceEntry.o: networklayer/common/InterfaceEntry.cc \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	networklayer/contract/IPAddress.h
$O/networklayer/common/InterfaceTable.o: networklayer/common/InterfaceTable.cc \
	base/ModuleAccess.h \
	linklayer/contract/MACAddress.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	base/NotificationBoard.h \
	networklayer/common/InterfaceToken.h \
	networklayer/common/InterfaceTable.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h
$O/networklayer/contract/IPControlInfo_m.o: networklayer/contract/IPControlInfo_m.cc \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/contract/IPProtocolId_m.o: networklayer/contract/IPProtocolId_m.cc \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h
$O/networklayer/contract/IPControlInfo.o: networklayer/contract/IPControlInfo.cc \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ipv4/IPDatagram.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/contract/IPvXAddress.o: networklayer/contract/IPvXAddress.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPvXAddress.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/contract/IPv6Address.o: networklayer/contract/IPv6Address.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/common/InterfaceToken.h \
	base/INETDefs.h
$O/networklayer/contract/IPAddress.o: networklayer/contract/IPAddress.cc \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/contract/IPv6ControlInfo_m.o: networklayer/contract/IPv6ControlInfo_m.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	base/INETDefs.h
$O/networklayer/contract/IPv6ControlInfo.o: networklayer/contract/IPv6ControlInfo.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	base/INETDefs.h
$O/networklayer/contract/IPAddressResolver.o: networklayer/contract/IPAddressResolver.cc \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h
$O/networklayer/extras/FailureManager.o: networklayer/extras/FailureManager.cc \
	networklayer/extras/FailureManager.h \
	base/IScriptable.h \
	base/INETDefs.h
$O/networklayer/extras/NetworkInfo.o: networklayer/extras/NetworkInfo.cc \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	base/IScriptable.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/contract/IPv6Address.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/extras/NetworkInfo.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/extras/Dummy.o: networklayer/extras/Dummy.cc
$O/networklayer/icmpv6/ICMPv6Message_m.o: networklayer/icmpv6/ICMPv6Message_m.cc \
	networklayer/icmpv6/ICMPv6Message_m.h \
	base/INETDefs.h
$O/networklayer/icmpv6/IPv6NDMessage_m.o: networklayer/icmpv6/IPv6NDMessage_m.cc \
	networklayer/contract/IPv6Address.h \
	linklayer/contract/MACAddress.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	base/INETDefs.h
$O/networklayer/icmpv6/IPv6NeighbourDiscovery.o: networklayer/icmpv6/IPv6NeighbourDiscovery.cc \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/contract/IPv6Address.h \
	networklayer/xmipv6/xMIPv6.h \
	networklayer/xmipv6/BindingCacheAccess.h \
	networklayer/mcoa/XMIPv6SM.h \
	networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	networklayer/xmipv6/MobilityHeader.h \
	networklayer/mcoa/MCoA.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	networklayer/xmipv6/BindingUpdateListAccess.h \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/common/InterfaceTable.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/xmipv6/BindingCache.h \
	base/INETDefs.h \
	networklayer/mcoa/MCoAAccess.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv6/IPv6Tunneling.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	base/MCoADefs.h \
	networklayer/xmipv6/BindingUpdateList.h \
	networklayer/mcoa/IPv6PrefAdr.h \
	networklayer/mcoa/IPv6TunAdr.h \
	networklayer/ipv6/IPv6TunnelingAccess.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6Datagram.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/xmipv6/xMIPv6Access.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddress.h
$O/networklayer/icmpv6/IPv6NeighbourCache.o: networklayer/icmpv6/IPv6NeighbourCache.cc \
	networklayer/contract/IPv6Address.h \
	linklayer/contract/MACAddress.h \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	base/INETDefs.h
$O/networklayer/icmpv6/ICMPv6.o: networklayer/icmpv6/ICMPv6.cc \
	linklayer/contract/MACAddress.h \
	networklayer/contract/IPv6ControlInfo.h \
	base/NotificationBoard.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h
$O/networklayer/ipv4/RoutingTable.o: networklayer/ipv4/RoutingTable.cc \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/RoutingTable.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	base/NotificationBoard.h \
	networklayer/ipv4/IPRoute.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv4/RoutingTableParser.h \
	networklayer/common/InterfaceToken.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/ipv4/ErrorHandling.o: networklayer/ipv4/ErrorHandling.cc \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ipv4/ICMPMessage_m.h \
	networklayer/ipv4/ICMPMessage.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ipv4/IPDatagram.h \
	networklayer/ipv4/ErrorHandling.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/ipv4/IPRoute.o: networklayer/ipv4/IPRoute.cc \
	linklayer/contract/MACAddress.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/ipv4/IPFragBuf.o: networklayer/ipv4/IPFragBuf.cc \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/ICMPMessage_m.h \
	networklayer/ipv4/IPFragBuf.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ipv4/ICMP.h \
	networklayer/ipv4/RoutingTableAccess.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	base/ModuleAccess.h \
	base/ReassemblyBuffer.h \
	networklayer/ipv4/ICMPMessage.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ipv4/IPv4InterfaceData.o: networklayer/ipv4/IPv4InterfaceData.cc \
	linklayer/contract/MACAddress.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/common/InterfaceToken.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ipv4/IP.o: networklayer/ipv4/IP.cc \
	base/AbstractQueue.h \
	networklayer/ipv4/ICMPAccess.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ipv4/ICMP.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	networklayer/ipv4/ICMPMessage.h \
	base/QueueBase.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	base/ProtocolMap.h \
	networklayer/ipv4/ICMPMessage_m.h \
	networklayer/ipv4/IPFragBuf.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/ipv4/RoutingTableAccess.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/NotifierConsts.h \
	networklayer/arp/ARPPacket_m.h \
	networklayer/common/InterfaceEntry.h \
	base/ReassemblyBuffer.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv4/IP.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ipv4/ICMPMessage_m.o: networklayer/ipv4/ICMPMessage_m.cc \
	networklayer/ipv4/ICMPMessage_m.h \
	base/INETDefs.h
$O/networklayer/ipv4/ControlManetRouting_m.o: networklayer/ipv4/ControlManetRouting_m.cc \
	networklayer/ipv4/ControlManetRouting_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/ipv4/IPDatagram_m.o: networklayer/ipv4/IPDatagram_m.cc \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/ipv4/ICMP.o: networklayer/ipv4/ICMP.cc \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/ICMPMessage_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ipv4/ICMP.h \
	networklayer/ipv4/RoutingTableAccess.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ipv4/ICMPMessage.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ipv4/RoutingTableParser.o: networklayer/ipv4/RoutingTableParser.cc \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/RoutingTable.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	base/NotificationBoard.h \
	networklayer/ipv4/IPRoute.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/ipv4/RoutingTableParser.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h
$O/networklayer/ipv6/IPv6ExtensionHeaders_m.o: networklayer/ipv6/IPv6ExtensionHeaders_m.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	base/INETDefs.h
$O/networklayer/ipv6/IPv6Datagram.o: networklayer/ipv6/IPv6Datagram.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/INETDefs.h
$O/networklayer/ipv6/IPv6InterfaceData.o: networklayer/ipv6/IPv6InterfaceData.cc \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6Datagram.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h
$O/networklayer/ipv6/IPv6FragBuf.o: networklayer/ipv6/IPv6FragBuf.cc \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	networklayer/ipv6/IPv6FragBuf.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6Datagram.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	base/ReassemblyBuffer.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h
$O/networklayer/ipv6/IPv6ExtensionHeaders.o: networklayer/ipv6/IPv6ExtensionHeaders.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	base/INETDefs.h
$O/networklayer/ipv6/RoutingTable6.o: networklayer/ipv6/RoutingTable6.cc \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	util/opp_utils.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv6/IPv6Tunneling.h \
	base/NotificationBoard.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/mcoa/IPv6TunAdr.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6TunnelingAccess.h \
	networklayer/ipv6/IPv6Datagram.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/xmipv6/MobilityHeader.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h
$O/networklayer/ipv6/IPv6ErrorHandling.o: networklayer/ipv6/IPv6ErrorHandling.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/ipv6/IPv6ErrorHandling.h \
	base/INETDefs.h
$O/networklayer/ipv6/IPv6Tunneling.o: networklayer/ipv6/IPv6Tunneling.cc \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/contract/IPv6Address.h \
	networklayer/xmipv6/xMIPv6.h \
	networklayer/mcoa/XMIPv6SM.h \
	networklayer/xmipv6/BindingCacheAccess.h \
	networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	networklayer/xmipv6/MobilityHeader.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/mcoa/MCoA.h \
	networklayer/common/InterfaceToken.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	networklayer/xmipv6/BindingUpdateListAccess.h \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/common/InterfaceTable.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/xmipv6/BindingCache.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/mcoa/MCoAAccess.h \
	networklayer/ipv6/IPv6Tunneling.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	base/MCoADefs.h \
	networklayer/xmipv6/BindingUpdateList.h \
	networklayer/mcoa/IPv6PrefAdr.h \
	networklayer/mcoa/IPv6TunAdr.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6TunnelingAccess.h \
	networklayer/ipv6/IPv6Datagram.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/xmipv6/xMIPv6Access.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ipv6/IPv6.o: networklayer/ipv6/IPv6.cc \
	base/AbstractQueue.h \
	base/IScriptable.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/contract/IPv6Address.h \
	networklayer/xmipv6/xMIPv6.h \
	networklayer/xmipv6/BindingCacheAccess.h \
	networklayer/mcoa/XMIPv6SM.h \
	networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	base/ProtocolMap.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/ipv6/IPv6.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	linklayer/contract/Ieee802Ctrl_m.h \
	networklayer/xmipv6/MobilityHeader.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/mcoa/MCoA.h \
	networklayer/common/InterfaceToken.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	networklayer/xmipv6/BindingUpdateListAccess.h \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/common/InterfaceTable.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/icmpv6/ICMPv6Access.h \
	base/QueueBase.h \
	networklayer/xmipv6/BindingCache.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/mcoa/MCoAAccess.h \
	networklayer/ipv6/IPv6Tunneling.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv6/IPv6FragBuf.h \
	base/MCoADefs.h \
	networklayer/xmipv6/BindingUpdateList.h \
	networklayer/mcoa/IPv6PrefAdr.h \
	networklayer/mcoa/IPv6TunAdr.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6TunnelingAccess.h \
	base/NotifierConsts.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/common/InterfaceEntry.h \
	base/ReassemblyBuffer.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/xmipv6/xMIPv6Access.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ipv6/IPv6Datagram_m.o: networklayer/ipv6/IPv6Datagram_m.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	base/INETDefs.h
$O/networklayer/ldp/LDPPacket_m.o: networklayer/ldp/LDPPacket_m.cc \
	networklayer/ldp/LDPPacket_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ldp/LDP.o: networklayer/ldp/LDP.cc \
	transport/contract/UDPSocket.h \
	networklayer/mpls/LIBTableAccess.h \
	networklayer/ldp/LDP.h \
	networklayer/mpls/IClassifier.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	networklayer/contract/IPv6Address.h \
	networklayer/ted/TED_m.h \
	networklayer/rsvp_te/IntServ_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ted/TEDAccess.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	transport/tcp/TCPSegment_m.h \
	transport/contract/UDPControlInfo_m.h \
	networklayer/ldp/LDPPacket_m.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	base/NotificationBoard.h \
	networklayer/ted/TED.h \
	networklayer/rsvp_te/IntServ.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/udp/UDPPacket_m.h \
	transport/contract/TCPSocketMap.h \
	base/ModuleAccess.h \
	networklayer/mpls/LIBTable.h \
	base/INotifiable.h \
	transport/udp/UDPPacket.h \
	base/NotifierConsts.h \
	transport/contract/TCPSocket.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/contract/TCPCommand_m.h \
	networklayer/mpls/ConstType.h \
	transport/tcp/TCPSegment.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/networklayer/mcoa/XMIPv6SM.o: networklayer/mcoa/XMIPv6SM.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/mcoa/IPv6PrefAdr.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/mcoa/XMIPv6SM.h \
	base/NotificationBoard.h \
	base/INETDefs.h
$O/networklayer/mcoa/KeyMCoABind.o: networklayer/mcoa/KeyMCoABind.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/INETDefs.h
$O/networklayer/mcoa/IPv6TunAdr.o: networklayer/mcoa/IPv6TunAdr.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/mcoa/IPv6TunAdr.h \
	base/INETDefs.h
$O/networklayer/mcoa/IPv6PrefAdr.o: networklayer/mcoa/IPv6PrefAdr.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/mcoa/IPv6PrefAdr.h \
	base/INETDefs.h
$O/networklayer/mcoa/MCoA.o: networklayer/mcoa/MCoA.cc \
	base/MCoADefs.h \
	networklayer/mcoa/MCoA.h \
	base/INETDefs.h
$O/networklayer/mcoa/KeyMCoADAD.o: networklayer/mcoa/KeyMCoADAD.cc \
	networklayer/contract/IPv6Address.h \
	linklayer/contract/MACAddress.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/common/InterfaceToken.h \
	base/INETDefs.h
$O/networklayer/mpls/LIBTable.o: networklayer/mpls/LIBTable.cc \
	base/ModuleAccess.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/mpls/LIBTable.h \
	networklayer/mpls/ConstType.h \
	util/XMLUtils.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ipv4/RoutingTableAccess.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/mpls/MPLSPacket.o: networklayer/mpls/MPLSPacket.cc \
	networklayer/mpls/MPLSPacket.h \
	base/INETDefs.h
$O/networklayer/mpls/MPLS.o: networklayer/mpls/MPLS.cc \
	transport/contract/UDPSocket.h \
	networklayer/mpls/LIBTableAccess.h \
	networklayer/ldp/LDP.h \
	networklayer/mpls/MPLSPacket.h \
	networklayer/mpls/IClassifier.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	networklayer/contract/IPv6Address.h \
	networklayer/rsvp_te/IntServ_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/rsvp_te/Utils.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	transport/tcp/TCPSegment_m.h \
	transport/contract/UDPControlInfo_m.h \
	networklayer/ldp/LDPPacket_m.h \
	base/NotificationBoard.h \
	networklayer/rsvp_te/IntServ.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/contract/TCPSocketMap.h \
	networklayer/mpls/MPLS.h \
	base/ModuleAccess.h \
	networklayer/mpls/LIBTable.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	transport/contract/TCPSocket.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/contract/TCPCommand_m.h \
	networklayer/mpls/ConstType.h \
	transport/tcp/TCPSegment.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/OSPFTimer_m.o: networklayer/ospfv2/OSPFTimer_m.cc \
	networklayer/ospfv2/OSPFTimer_m.h \
	base/INETDefs.h
$O/networklayer/ospfv2/OSPFPacket_m.o: networklayer/ospfv2/OSPFPacket_m.cc \
	networklayer/ospfv2/OSPFPacket_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/OSPFRouting.o: networklayer/ospfv2/OSPFRouting.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/OSPFRouting.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/contract/IPv6Address.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ipv4/RoutingTableAccess.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/interface/OSPFInterfaceStateWaiting.o: networklayer/ospfv2/interface/OSPFInterfaceStateWaiting.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateWaiting.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/interface/OSPFInterfaceState.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.o: networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.cc \
	networklayer/ospfv2/interface/OSPFInterfaceState.h \
	networklayer/ospfv2/router/LSA.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/ospfv2/interface/OSPFInterfaceStateBackup.o: networklayer/ospfv2/interface/OSPFInterfaceStateBackup.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateBackup.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/interface/OSPFInterfaceState.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/interface/OSPFInterface.o: networklayer/ospfv2/interface/OSPFInterface.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	base/INETDefs.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/interface/OSPFInterfaceState.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/interface/OSPFInterfaceStateDesignatedRouter.o: networklayer/ospfv2/interface/OSPFInterfaceStateDesignatedRouter.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateDesignatedRouter.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/interface/OSPFInterfaceState.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.o: networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/interface/OSPFInterfaceState.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/interface/OSPFInterfaceStatePointToPoint.o: networklayer/ospfv2/interface/OSPFInterfaceStatePointToPoint.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/interface/OSPFInterfaceStatePointToPoint.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/interface/OSPFInterfaceState.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/interface/OSPFInterfaceStateDown.o: networklayer/ospfv2/interface/OSPFInterfaceStateDown.cc \
	networklayer/ospfv2/interface/OSPFInterfaceStatePointToPoint.h \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateWaiting.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateDown.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/interface/OSPFInterfaceState.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/interface/OSPFInterfaceState.o: networklayer/ospfv2/interface/OSPFInterfaceState.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateDesignatedRouter.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	networklayer/ospfv2/interface/OSPFInterfaceStateBackup.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/interface/OSPFInterfaceState.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/messagehandler/HelloHandler.o: networklayer/ospfv2/messagehandler/HelloHandler.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.o: networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.o: networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	base/INETDefs.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.o: networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/messagehandler/MessageHandler.o: networklayer/ospfv2/messagehandler/MessageHandler.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.o: networklayer/ospfv2/messagehandler/LinkStateRequestHandler.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/neighbor/OSPFNeighborStateLoading.o: networklayer/ospfv2/neighbor/OSPFNeighborStateLoading.cc \
	networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateLoading.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateFull.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/neighbor/OSPFNeighbor.o: networklayer/ospfv2/neighbor/OSPFNeighbor.cc \
	networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/neighbor/OSPFNeighborStateFull.o: networklayer/ospfv2/neighbor/OSPFNeighborStateFull.cc \
	networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateFull.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/neighbor/OSPFNeighborState.o: networklayer/ospfv2/neighbor/OSPFNeighborState.cc \
	networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/neighbor/OSPFNeighborStateExchange.o: networklayer/ospfv2/neighbor/OSPFNeighborStateExchange.cc \
	networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateLoading.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateFull.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateExchange.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/neighbor/OSPFNeighborStateAttempt.o: networklayer/ospfv2/neighbor/OSPFNeighborStateAttempt.cc \
	networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateAttempt.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.o: networklayer/ospfv2/neighbor/OSPFNeighborStateDown.cc \
	networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateAttempt.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.o: networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.cc \
	networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/router/LSA.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateExchange.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.o: networklayer/ospfv2/neighbor/OSPFNeighborStateInit.cc \
	networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.o: networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.cc \
	networklayer/ospfv2/neighbor/OSPFNeighborState.h \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateInit.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateDown.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/router/NetworkLSA.o: networklayer/ospfv2/router/NetworkLSA.cc \
	networklayer/ospfv2/router/LSA.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/router/RouterLSA.o: networklayer/ospfv2/router/RouterLSA.cc \
	networklayer/ospfv2/router/LSA.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/router/SummaryLSA.o: networklayer/ospfv2/router/SummaryLSA.cc \
	networklayer/ospfv2/router/LSA.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/router/OSPFArea.o: networklayer/ospfv2/router/OSPFArea.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	base/INETDefs.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/router/ASExternalLSA.o: networklayer/ospfv2/router/ASExternalLSA.cc \
	networklayer/ospfv2/router/LSA.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ospfv2/router/OSPFRouter.o: networklayer/ospfv2/router/OSPFRouter.cc \
	networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	networklayer/ospfv2/OSPFPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ospfv2/OSPFTimer_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ospfv2/router/OSPFRoutingTableEntry.h \
	networklayer/ospfv2/messagehandler/LinkStateRequestHandler.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ospfv2/router/OSPFRouter.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h \
	networklayer/ospfv2/messagehandler/MessageHandler.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	networklayer/ospfv2/messagehandler/IMessageHandler.h \
	networklayer/ospfv2/neighbor/OSPFNeighbor.h \
	networklayer/ospfv2/messagehandler/HelloHandler.h \
	networklayer/ipv4/RoutingTableAccess.h \
	networklayer/ospfv2/router/OSPFcommon.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	networklayer/ospfv2/router/LSA.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ospfv2/router/OSPFArea.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ospfv2/interface/OSPFInterface.h \
	networklayer/contract/IPAddress.h
$O/networklayer/queue/DropTailQoSQueue.o: networklayer/queue/DropTailQoSQueue.cc \
	networklayer/queue/IQoSClassifier.h \
	networklayer/queue/DropTailQoSQueue.h \
	base/PassiveQueueBase.h \
	base/IPassiveQueue.h \
	base/INETDefs.h
$O/networklayer/queue/BasicDSCPClassifier.o: networklayer/queue/BasicDSCPClassifier.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/queue/IQoSClassifier.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/queue/BasicDSCPClassifier.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/queue/REDQueue.o: networklayer/queue/REDQueue.cc \
	networklayer/queue/REDQueue.h \
	base/PassiveQueueBase.h \
	base/INETDefs.h \
	base/IPassiveQueue.h
$O/networklayer/queue/DropTailQueue.o: networklayer/queue/DropTailQueue.cc \
	networklayer/queue/DropTailQueue.h \
	base/PassiveQueueBase.h \
	base/INETDefs.h \
	base/IPassiveQueue.h
$O/networklayer/rsvp_te/IntServ_m.o: networklayer/rsvp_te/IntServ_m.cc \
	networklayer/rsvp_te/IntServ_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/rsvp_te/Utils.o: networklayer/rsvp_te/Utils.cc \
	networklayer/rsvp_te/IntServ.h \
	networklayer/rsvp_te/IntServ_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h \
	networklayer/rsvp_te/Utils.h
$O/networklayer/rsvp_te/RSVPPacket_m.o: networklayer/rsvp_te/RSVPPacket_m.cc \
	networklayer/rsvp_te/RSVPPacket_m.h \
	networklayer/rsvp_te/IntServ_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/rsvp_te/RSVPHello_m.o: networklayer/rsvp_te/RSVPHello_m.cc \
	networklayer/rsvp_te/RSVPHello_m.h \
	networklayer/rsvp_te/RSVPPacket_m.h \
	networklayer/rsvp_te/IntServ_m.h \
	networklayer/rsvp_te/RSVPPacket.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/rsvp_te/RSVPPathMsg_m.o: networklayer/rsvp_te/RSVPPathMsg_m.cc \
	networklayer/rsvp_te/IntServ.h \
	networklayer/rsvp_te/RSVPPacket_m.h \
	networklayer/rsvp_te/IntServ_m.h \
	networklayer/rsvp_te/RSVPPacket.h \
	networklayer/rsvp_te/RSVPPathMsg_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/rsvp_te/RSVPResvMsg_m.o: networklayer/rsvp_te/RSVPResvMsg_m.cc \
	networklayer/rsvp_te/IntServ.h \
	networklayer/rsvp_te/RSVPPacket_m.h \
	networklayer/rsvp_te/RSVPPacket.h \
	networklayer/rsvp_te/IntServ_m.h \
	networklayer/rsvp_te/RSVPResvMsg_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/rsvp_te/RSVP.o: networklayer/rsvp_te/RSVP.cc \
	base/IScriptable.h \
	networklayer/mpls/LIBTableAccess.h \
	networklayer/mpls/IClassifier.h \
	networklayer/rsvp_te/RSVPPacket_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/rsvp_te/RSVP.h \
	networklayer/rsvp_te/RSVPHelloMsg.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ipv4/IPDatagram.h \
	networklayer/contract/IPv6Address.h \
	networklayer/ted/TED_m.h \
	networklayer/rsvp_te/SignallingMsg_m.h \
	util/common.h \
	networklayer/rsvp_te/IntServ_m.h \
	networklayer/rsvp_te/IRSVPClassifier.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ted/TEDAccess.h \
	base/INETDefs.h \
	networklayer/rsvp_te/Utils.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/rsvp_te/RSVPHello_m.h \
	base/NotificationBoard.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/rsvp_te/RSVPPathMsg.h \
	networklayer/ted/TED.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/rsvp_te/IntServ.h \
	util/XMLUtils.h \
	networklayer/ipv4/RoutingTableAccess.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/mpls/LIBTable.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/mpls/ConstType.h \
	networklayer/rsvp_te/RSVPPacket.h \
	networklayer/rsvp_te/RSVPPathMsg_m.h \
	networklayer/rsvp_te/RSVPResvMsg_m.h \
	networklayer/rsvp_te/RSVPResvMsg.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h
$O/networklayer/rsvp_te/SignallingMsg_m.o: networklayer/rsvp_te/SignallingMsg_m.cc \
	networklayer/rsvp_te/SignallingMsg_m.h \
	networklayer/rsvp_te/IntServ.h \
	networklayer/rsvp_te/IntServ_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/rsvp_te/SimpleClassifier.o: networklayer/rsvp_te/SimpleClassifier.cc \
	base/IScriptable.h \
	networklayer/mpls/LIBTableAccess.h \
	networklayer/rsvp_te/RSVPPacket_m.h \
	networklayer/mpls/IClassifier.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/rsvp_te/RSVP.h \
	networklayer/rsvp_te/RSVPHelloMsg.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	networklayer/rsvp_te/SimpleClassifier.h \
	networklayer/rsvp_te/SignallingMsg_m.h \
	networklayer/rsvp_te/IntServ_m.h \
	networklayer/rsvp_te/IRSVPClassifier.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/rsvp_te/RSVPHello_m.h \
	base/NotificationBoard.h \
	networklayer/rsvp_te/RSVPPathMsg.h \
	networklayer/rsvp_te/IntServ.h \
	util/XMLUtils.h \
	networklayer/ipv4/RoutingTableAccess.h \
	base/ModuleAccess.h \
	networklayer/mpls/LIBTable.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/mpls/ConstType.h \
	networklayer/rsvp_te/RSVPPacket.h \
	networklayer/rsvp_te/RSVPPathMsg_m.h \
	networklayer/rsvp_te/RSVPResvMsg_m.h \
	networklayer/rsvp_te/RSVPResvMsg.h \
	networklayer/rsvp_te/RSVPAccess.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ted/LinkStateRouting.o: networklayer/ted/LinkStateRouting.cc \
	networklayer/ipv4/IPRoute.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ted/TED_m.h \
	networklayer/rsvp_te/IntServ_m.h \
	networklayer/ted/LinkStateRouting.h \
	networklayer/ted/LinkStatePacket_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ted/TEDAccess.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	base/NotificationBoard.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/ted/TED.h \
	networklayer/rsvp_te/IntServ.h \
	networklayer/ipv4/RoutingTableAccess.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ted/LinkStatePacket_m.o: networklayer/ted/LinkStatePacket_m.cc \
	networklayer/ted/TED_m.h \
	networklayer/ted/LinkStatePacket_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/networklayer/ted/TED.o: networklayer/ted/TED.cc \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	base/NotificationBoard.h \
	networklayer/ted/TED.h \
	networklayer/rsvp_te/IntServ.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ipv4/RoutingTableAccess.h \
	networklayer/contract/IPControlInfo.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ted/TED_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/rsvp_te/IntServ_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/InterfaceToken.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/ted/TED_m.o: networklayer/ted/TED_m.cc \
	networklayer/ted/TED_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/networklayer/xmipv6/MobilityHeader.o: networklayer/xmipv6/MobilityHeader.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/xmipv6/MobilityHeader.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/INETDefs.h
$O/networklayer/xmipv6/BindingUpdateList.o: networklayer/xmipv6/BindingUpdateList.cc \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	util/opp_utils.h \
	networklayer/common/InterfaceTable.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/mcoa/KeyMCoABind.h \
	networklayer/xmipv6/BindingUpdateList.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6Datagram.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h
$O/networklayer/xmipv6/xMIPv6.o: networklayer/xmipv6/xMIPv6.cc \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/contract/IPv6Address.h \
	networklayer/xmipv6/xMIPv6.h \
	networklayer/xmipv6/BindingCacheAccess.h \
	networklayer/mcoa/XMIPv6SM.h \
	networklayer/icmpv6/IPv6NeighbourDiscoveryAccess.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	networklayer/xmipv6/MobilityHeader.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/mcoa/MCoA.h \
	networklayer/common/InterfaceToken.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	networklayer/xmipv6/BindingUpdateListAccess.h \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/common/InterfaceTable.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/xmipv6/BindingCache.h \
	base/INETDefs.h \
	networklayer/mcoa/MCoAAccess.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv6/IPv6Tunneling.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	base/MCoADefs.h \
	networklayer/xmipv6/BindingUpdateList.h \
	networklayer/mcoa/IPv6PrefAdr.h \
	networklayer/mcoa/IPv6TunAdr.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6TunnelingAccess.h \
	base/NotifierConsts.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h
$O/networklayer/xmipv6/MobilityHeader_m.o: networklayer/xmipv6/MobilityHeader_m.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/INETDefs.h
$O/networklayer/xmipv6/BindingCache.o: networklayer/xmipv6/BindingCache.cc \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	util/opp_utils.h \
	networklayer/common/InterfaceTable.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/xmipv6/BindingCache.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	base/NotificationBoard.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6Datagram.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h
$O/transport/contract/TCPSocketMap.o: transport/contract/TCPSocketMap.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/TCPSocket.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	transport/contract/TCPSocketMap.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/transport/contract/SCTPSocket.o: transport/contract/SCTPSocket.cc \
	transport/contract/SCTPCommand_m.h \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPQueue.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	transport/sctp/SCTPMessage.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/sctp/SCTPReceiveStream.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/sctp/SCTP.h \
	transport/contract/SCTPCommand.h \
	networklayer/common/InterfaceToken.h \
	transport/contract/SCTPSocket.h \
	networklayer/contract/IPAddress.h
$O/transport/contract/UDPSocket.o: transport/contract/UDPSocket.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/UDPControlInfo_m.h \
	transport/contract/UDPSocket.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/contract/SCTPCommand_m.o: transport/contract/SCTPCommand_m.cc \
	transport/contract/SCTPCommand_m.h \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPQueue.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	transport/sctp/SCTPMessage.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/sctp/SCTPReceiveStream.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/contract/SCTPCommand.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/transport/contract/TCPSocket.o: transport/contract/TCPSocket.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/TCPSocket.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/contract/TCPCommand_m.o: transport/contract/TCPCommand_m.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/contract/UDPControlInfo_m.o: transport/contract/UDPControlInfo_m.cc \
	networklayer/contract/IPv6Address.h \
	transport/contract/UDPControlInfo_m.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/rtp/RTPPayloadSender.o: transport/rtp/RTPPayloadSender.cc \
	transport/rtp/RTPPayloadSender.h \
	transport/rtp/RTPInnerPacket.h \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPSenderStatusMessage_m.h \
	transport/rtp/RTPSenderControlMessage_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/rtp/RTPSenderControlMessage_m.o: transport/rtp/RTPSenderControlMessage_m.cc \
	transport/rtp/RTPSenderControlMessage_m.h \
	base/INETDefs.h
$O/transport/rtp/RTPParticipantInfo.o: transport/rtp/RTPParticipantInfo.cc \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPParticipantInfo.h \
	transport/rtp/reports.h \
	transport/rtp/RTCPPacket.h \
	transport/rtp/sdes.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/transport/rtp/reports.o: transport/rtp/reports.cc \
	transport/rtp/reports.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/transport/rtp/RTCP.o: transport/rtp/RTCP.cc \
	transport/rtp/RTPReceiverInfo.h \
	transport/contract/UDPSocket.h \
	transport/contract/UDPControlInfo_m.h \
	transport/rtp/RTPInnerPacket.h \
	networklayer/contract/IPvXAddress.h \
	transport/rtp/reports.h \
	networklayer/contract/IPv6Address.h \
	transport/rtp/RTPSenderInfo.h \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPSenderStatusMessage_m.h \
	transport/rtp/RTPParticipantInfo.h \
	transport/rtp/RTPSenderControlMessage_m.h \
	transport/rtp/RTCP.h \
	transport/rtp/RTCPPacket.h \
	transport/rtp/sdes.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/rtp/RTPSenderInfo.o: transport/rtp/RTPSenderInfo.cc \
	transport/rtp/RTPSenderInfo.h \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPParticipantInfo.h \
	transport/rtp/reports.h \
	transport/rtp/RTCPPacket.h \
	transport/rtp/sdes.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/transport/rtp/RTPReceiverInfo.o: transport/rtp/RTPReceiverInfo.cc \
	transport/rtp/RTPReceiverInfo.h \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPParticipantInfo.h \
	transport/rtp/reports.h \
	transport/rtp/RTCPPacket.h \
	transport/rtp/sdes.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/rtp/sdes.o: transport/rtp/sdes.cc \
	transport/rtp/sdes.h \
	base/INETDefs.h
$O/transport/rtp/RTPProfile.o: transport/rtp/RTPProfile.cc \
	transport/rtp/RTPInnerPacket.h \
	transport/rtp/RTPProfile.h \
	transport/rtp/RTPPayloadReceiver.h \
	transport/rtp/reports.h \
	transport/rtp/RTPPayloadSender.h \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPSenderStatusMessage_m.h \
	transport/rtp/RTPParticipantInfo.h \
	transport/rtp/RTPSenderControlMessage_m.h \
	transport/rtp/RTCPPacket.h \
	transport/rtp/sdes.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/transport/rtp/RTPPayloadReceiver.o: transport/rtp/RTPPayloadReceiver.cc \
	transport/rtp/RTPInnerPacket.h \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPSenderStatusMessage_m.h \
	transport/rtp/RTPPayloadReceiver.h \
	transport/rtp/RTPSenderControlMessage_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/transport/rtp/RTP.o: transport/rtp/RTP.cc \
	transport/contract/UDPSocket.h \
	transport/contract/UDPControlInfo_m.h \
	transport/rtp/RTPInnerPacket.h \
	transport/rtp/RTP.h \
	transport/rtp/RTPInterfacePacket.h \
	transport/rtp/RTPProfile.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPv6Address.h \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPSenderStatusMessage_m.h \
	transport/rtp/RTPSenderControlMessage_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/rtp/RTPPacket.o: transport/rtp/RTPPacket.cc \
	transport/rtp/RTPPacket.h \
	base/INETDefs.h
$O/transport/rtp/RTPSenderStatusMessage_m.o: transport/rtp/RTPSenderStatusMessage_m.cc \
	transport/rtp/RTPSenderStatusMessage_m.h \
	base/INETDefs.h
$O/transport/rtp/RTPInterfacePacket.o: transport/rtp/RTPInterfacePacket.cc \
	transport/rtp/RTPInterfacePacket.h \
	transport/rtp/RTPSenderStatusMessage_m.h \
	transport/rtp/RTPSenderControlMessage_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/transport/rtp/RTCPPacket.o: transport/rtp/RTCPPacket.cc \
	transport/rtp/reports.h \
	transport/rtp/RTCPPacket.h \
	transport/rtp/sdes.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/transport/rtp/RTPInnerPacket.o: transport/rtp/RTPInnerPacket.cc \
	transport/rtp/RTPInnerPacket.h \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPSenderStatusMessage_m.h \
	transport/rtp/RTPSenderControlMessage_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/transport/rtp/profiles/avprofile/RTPAVProfile.o: transport/rtp/profiles/avprofile/RTPAVProfile.cc \
	transport/rtp/RTPInnerPacket.h \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPProfile.h \
	transport/rtp/RTPSenderStatusMessage_m.h \
	transport/rtp/profiles/avprofile/RTPAVProfile.h \
	transport/rtp/RTPSenderControlMessage_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Receiver.o: transport/rtp/profiles/avprofile/RTPAVProfilePayload32Receiver.cc \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPPayloadReceiver.h \
	transport/rtp/profiles/avprofile/RTPAVProfilePayload32Receiver.h \
	base/INETDefs.h \
	transport/rtp/profiles/avprofile/RTPMpegPacket_m.h
$O/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Sender.o: transport/rtp/profiles/avprofile/RTPAVProfilePayload32Sender.cc \
	transport/rtp/RTPPayloadSender.h \
	transport/rtp/RTPInnerPacket.h \
	transport/rtp/RTPPacket.h \
	transport/rtp/RTPSenderStatusMessage_m.h \
	transport/rtp/RTPSenderControlMessage_m.h \
	transport/rtp/profiles/avprofile/RTPAVProfilePayload32Sender.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h \
	transport/rtp/profiles/avprofile/RTPMpegPacket_m.h
$O/transport/rtp/profiles/avprofile/RTPMpegPacket_m.o: transport/rtp/profiles/avprofile/RTPMpegPacket_m.cc \
	base/INETDefs.h \
	transport/rtp/profiles/avprofile/RTPMpegPacket_m.h
$O/transport/sctp/SCTPAlg.o: transport/sctp/SCTPAlg.cc \
	transport/sctp/SCTPAlgorithm.h \
	transport/sctp/SCTPQueue.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	transport/sctp/SCTPAlg.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	transport/sctp/SCTPMessage.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	transport/sctp/SCTPReceiveStream.h \
	networklayer/ipv4/RoutingTableAccess.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/transport/sctp/SCTPAssociationRcvMessage.o: transport/sctp/SCTPAssociationRcvMessage.cc \
	transport/contract/SCTPCommand_m.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	transport/sctp/SCTPAlgorithm.h \
	networklayer/ipv6/RoutingTable6.h \
	transport/sctp/SCTPQueue.h \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	transport/sctp/SCTPMessage.h \
	networklayer/common/IInterfaceTable.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/sctp/SCTPReceiveStream.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	transport/contract/SCTPCommand.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/icmpv6/ICMPv6Access.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/sctp/SCTP.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddress.h
$O/transport/sctp/SCTPCCFunctions.o: transport/sctp/SCTPCCFunctions.cc \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPQueue.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	transport/sctp/SCTPMessage.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/sctp/SCTPReceiveStream.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/transport/sctp/SCTP.o: transport/sctp/SCTP.cc \
	transport/contract/SCTPCommand_m.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	transport/sctp/SCTPQueue.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	transport/sctp/SCTPMessage.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/RoutingTable.h \
	base/NotificationBoard.h \
	transport/sctp/SCTPAssociation.h \
	networklayer/contract/IPvXAddress.h \
	transport/sctp/SCTPReceiveStream.h \
	networklayer/ipv4/RoutingTableAccess.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	networklayer/ipv6/IPv6Datagram.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/sctp/SCTP.h \
	transport/contract/SCTPCommand.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddress.h
$O/transport/sctp/SCTPAssociationBase.o: transport/sctp/SCTPAssociationBase.cc \
	transport/contract/SCTPCommand_m.h \
	transport/sctp/SCTPAlgorithm.h \
	transport/sctp/SCTPQueue.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	transport/sctp/SCTPMessage.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/RoutingTable.h \
	base/NotificationBoard.h \
	transport/sctp/SCTPAssociation.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/sctp/SCTPReceiveStream.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/contract/SCTPCommand.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/transport/sctp/SCTPAssociationEventProc.o: transport/sctp/SCTPAssociationEventProc.cc \
	transport/contract/SCTPCommand_m.h \
	transport/sctp/SCTPAlgorithm.h \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPQueue.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	transport/sctp/SCTPMessage.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/RoutingTable.h \
	base/NotificationBoard.h \
	transport/sctp/SCTPAssociation.h \
	networklayer/contract/IPvXAddress.h \
	transport/sctp/SCTPReceiveStream.h \
	networklayer/ipv4/RoutingTableAccess.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	transport/sctp/SCTP.h \
	transport/contract/SCTPCommand.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/transport/sctp/SCTPSendStream.o: transport/sctp/SCTPSendStream.cc \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPQueue.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h \
	transport/sctp/SCTPMessage.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	transport/sctp/SCTPReceiveStream.h \
	networklayer/ipv4/RoutingTableAccess.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/transport/sctp/SCTPMessage_m.o: transport/sctp/SCTPMessage_m.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPvXAddress.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h \
	transport/sctp/SCTPMessage_m.h
$O/transport/sctp/SCTPReceiveStream.o: transport/sctp/SCTPReceiveStream.cc \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPQueue.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h \
	transport/sctp/SCTPMessage.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	transport/sctp/SCTPReceiveStream.h \
	networklayer/ipv4/RoutingTableAccess.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/transport/sctp/SCTPQueue.o: transport/sctp/SCTPQueue.cc \
	transport/sctp/SCTPQueue.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	transport/sctp/SCTPMessage.h \
	base/INETDefs.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/sctp/SCTPReceiveStream.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/transport/sctp/SCTPAssociationUtil.o: transport/sctp/SCTPAssociationUtil.cc \
	transport/contract/SCTPCommand_m.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	transport/sctp/SCTPAlgorithm.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPQueue.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/ipv6/IPv6InterfaceData.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	transport/sctp/SCTPMessage.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/IPv4InterfaceData.h \
	networklayer/mcoa/KeyMCoADAD.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/sctp/SCTPReceiveStream.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	transport/contract/SCTPCommand.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/icmpv6/IPv6NeighbourDiscovery.h \
	networklayer/icmpv6/IPv6NeighbourCache.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	networklayer/icmpv6/IPv6NDMessage_m.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/icmpv6/ICMPv6Access.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/RoutingTable.h \
	base/NotificationBoard.h \
	transport/sctp/SCTPAssociation.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/ipv6/IPv6Datagram.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddress.h
$O/transport/sctp/SCTPSSFunctions.o: transport/sctp/SCTPSSFunctions.cc \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPQueue.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	transport/sctp/SCTPMessage.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/sctp/SCTPReceiveStream.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/transport/sctp/SCTPMessage.o: transport/sctp/SCTPMessage.cc \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPQueue.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	transport/sctp/SCTPMessage.h \
	networklayer/common/IInterfaceTable.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/RoutingTable.h \
	transport/sctp/SCTPAssociation.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/sctp/SCTPReceiveStream.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/transport/tcp/TCPConnectionRcvSegment.o: transport/tcp/TCPConnectionRcvSegment.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPAlgorithm.h \
	transport/tcp/TCPReceiveQueue.h \
	transport/tcp/TCPConnection.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/TCPSegment.h \
	transport/tcp/TCPSendQueue.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/TCPSegment.o: transport/tcp/TCPSegment.cc \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPSegment.h \
	base/INETDefs.h
$O/transport/tcp/TCPConnectionEventProc.o: transport/tcp/TCPConnectionEventProc.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPAlgorithm.h \
	transport/tcp/TCPReceiveQueue.h \
	transport/tcp/TCPConnection.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/TCPSegment.h \
	transport/tcp/TCPSendQueue.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/TCPConnectionBase.o: transport/tcp/TCPConnectionBase.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPAlgorithm.h \
	transport/tcp/TCPReceiveQueue.h \
	transport/tcp/TCPConnection.h \
	transport/contract/TCPCommand_m.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/TCPSegment.h \
	transport/tcp/TCPSendQueue.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/TCPConnectionUtil.o: transport/tcp/TCPConnectionUtil.cc \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	transport/tcp/TCPSendQueue.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ipv6/IPv6Datagram.h \
	transport/tcp/TCPAlgorithm.h \
	transport/tcp/TCPConnection.h \
	transport/tcp/TCPReceiveQueue.h \
	transport/contract/TCPCommand_m.h \
	transport/tcp/TCPSegment.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/TCPSegment_m.o: transport/tcp/TCPSegment_m.cc \
	transport/tcp/TCPSegment_m.h \
	base/INETDefs.h
$O/transport/tcp/TCP.o: transport/tcp/TCP.cc \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/ipv4/ICMPMessage_m.h \
	networklayer/contract/IPvXAddress.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPControlInfo_m.h \
	networklayer/ipv6/IPv6Datagram.h \
	transport/tcp/TCPConnection.h \
	transport/contract/TCPCommand_m.h \
	transport/tcp/TCPSegment.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/transport/tcp/flavours/DumbTCP.o: transport/tcp/flavours/DumbTCP.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/flavours/DumbTCP.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPAlgorithm.h \
	transport/tcp/TCPConnection.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/TCPSegment.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/flavours/TCPNoCongestionControl.o: transport/tcp/flavours/TCPNoCongestionControl.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPAlgorithm.h \
	transport/tcp/TCPConnection.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/TCPSegment.h \
	transport/tcp/flavours/TCPBaseAlg.h \
	transport/tcp/flavours/TCPNoCongestionControl.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/flavours/TCPTahoeRenoFamily.o: transport/tcp/flavours/TCPTahoeRenoFamily.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPAlgorithm.h \
	transport/tcp/TCPConnection.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/TCPSegment.h \
	transport/tcp/flavours/TCPBaseAlg.h \
	transport/tcp/flavours/TCPTahoeRenoFamily.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/flavours/TCPTahoe.o: transport/tcp/flavours/TCPTahoe.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/flavours/TCPTahoe.h \
	transport/tcp/TCPAlgorithm.h \
	transport/tcp/TCPConnection.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/TCPSegment.h \
	transport/tcp/flavours/TCPBaseAlg.h \
	transport/tcp/flavours/TCPTahoeRenoFamily.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/flavours/TCPBaseAlg.o: transport/tcp/flavours/TCPBaseAlg.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPAlgorithm.h \
	transport/tcp/TCPConnection.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/TCPSegment.h \
	transport/tcp/flavours/TCPBaseAlg.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/flavours/TCPReno.o: transport/tcp/flavours/TCPReno.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPAlgorithm.h \
	transport/tcp/TCPConnection.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/flavours/TCPReno.h \
	transport/tcp/TCPSegment.h \
	transport/tcp/flavours/TCPBaseAlg.h \
	transport/tcp/flavours/TCPTahoeRenoFamily.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/queues/TCPVirtualDataSendQueue.o: transport/tcp/queues/TCPVirtualDataSendQueue.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPConnection.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/TCPSegment.h \
	transport/tcp/queues/TCPVirtualDataSendQueue.h \
	transport/tcp/TCPSendQueue.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/queues/TCPMsgBasedRcvQueue.o: transport/tcp/queues/TCPMsgBasedRcvQueue.cc \
	transport/tcp/TCP.h \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPConnection.h \
	transport/tcp/TCPReceiveQueue.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/queues/TCPVirtualDataRcvQueue.h \
	transport/tcp/queues/TCPMsgBasedRcvQueue.h \
	transport/tcp/TCPSegment.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/queues/TCPVirtualDataRcvQueue.o: transport/tcp/queues/TCPVirtualDataRcvQueue.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPReceiveQueue.h \
	transport/tcp/TCPConnection.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/queues/TCPVirtualDataRcvQueue.h \
	transport/tcp/TCPSegment.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/tcp/queues/TCPMsgBasedSendQueue.o: transport/tcp/queues/TCPMsgBasedSendQueue.cc \
	networklayer/contract/IPv6Address.h \
	transport/tcp/TCP.h \
	transport/tcp/queues/TCPMsgBasedSendQueue.h \
	transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPConnection.h \
	networklayer/contract/IPvXAddress.h \
	transport/tcp/TCPSegment.h \
	transport/tcp/TCPSendQueue.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/transport/udp/UDP.o: transport/udp/UDP.cc \
	networklayer/ipv4/ICMPAccess.h \
	networklayer/contract/IPv6ControlInfo.h \
	networklayer/xmipv6/MobilityHeader_m.h \
	networklayer/ipv6/RoutingTable6.h \
	networklayer/ipv6/IPv6ExtensionHeaders_m.h \
	networklayer/ipv4/IPRoute.h \
	networklayer/ipv4/ICMP.h \
	networklayer/icmpv6/ICMPv6Message_m.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/icmpv6/ICMPv6Access.h \
	networklayer/ipv4/ICMPMessage.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	transport/contract/UDPControlInfo_m.h \
	networklayer/ipv4/ICMPMessage_m.h \
	base/NotificationBoard.h \
	networklayer/contract/IPvXAddress.h \
	transport/udp/UDP.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/udp/UDPPacket_m.h \
	networklayer/mcoa/KeyMCoABind.h \
	base/ModuleAccess.h \
	networklayer/ipv6/IPv6ExtensionHeaders.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/ipv6/IPv6Datagram.h \
	transport/udp/UDPPacket.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/ipv6/RoutingTable6Access.h \
	networklayer/icmpv6/ICMPv6.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddress.h
$O/transport/udp/UDPPacket_m.o: transport/udp/UDPPacket_m.cc \
	transport/udp/UDPPacket_m.h \
	base/INETDefs.h
$O/util/XMLUtils.o: util/XMLUtils.cc \
	networklayer/contract/IPv6Address.h \
	networklayer/contract/IPvXAddress.h \
	util/XMLUtils.h \
	networklayer/contract/IPAddressResolver.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/util/NAMTraceWriter.o: util/NAMTraceWriter.cc \
	linklayer/contract/MACAddress.h \
	world/NAMTrace.h \
	base/NotificationBoard.h \
	util/NAMTraceWriter.h \
	base/ModuleAccess.h \
	linklayer/contract/TxNotifDetails.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	networklayer/common/InterfaceTableAccess.h \
	networklayer/common/InterfaceToken.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h
$O/util/ThruputMeteringChannel.o: util/ThruputMeteringChannel.cc \
	util/ThruputMeteringChannel.h \
	base/INETDefs.h
$O/util/opp_utils.o: util/opp_utils.cc \
	util/opp_utils.h \
	base/INETDefs.h
$O/util/common.o: util/common.cc \
	util/common.h \
	networklayer/rsvp_te/IntServ.h \
	networklayer/rsvp_te/IntServ_m.h \
	base/INETDefs.h \
	networklayer/contract/IPAddress.h
$O/util/TCPDump.o: util/TCPDump.cc \
	networklayer/ipv4/IPRoute.h \
	transport/sctp/SCTPQueue.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	networklayer/ipv4/ICMPMessage.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	networklayer/common/IInterfaceTable.h \
	base/INETDefs.h \
	transport/sctp/SCTPMessage.h \
	networklayer/ipv4/IRoutingTable.h \
	linklayer/contract/MACAddress.h \
	transport/tcp/TCPSegment_m.h \
	networklayer/ipv4/RoutingTable.h \
	networklayer/ipv4/ICMPMessage_m.h \
	base/NotificationBoard.h \
	transport/sctp/SCTPAssociation.h \
	networklayer/contract/IPvXAddress.h \
	transport/sctp/SCTPReceiveStream.h \
	networklayer/ipv4/RoutingTableAccess.h \
	transport/udp/UDPPacket_m.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	util/headerserializers/IPSerializer.h \
	transport/tcp/TCPSegment.h \
	util/TCPDump.h \
	networklayer/common/InterfaceToken.h \
	networklayer/ipv6/IPv6Datagram_m.h \
	networklayer/contract/IPAddress.h
$O/util/headerserializers/UDPSerializer.o: util/headerserializers/UDPSerializer.cc \
	util/headerserializers/headers/in_systm.h \
	transport/udp/UDPPacket.h \
	util/headerserializers/UDPSerializer.h \
	util/headerserializers/headers/udp.h \
	util/headerserializers/headers/bsdint.h \
	util/headerserializers/headers/defs.h \
	transport/udp/UDPPacket_m.h \
	util/headerserializers/headers/in.h \
	base/INETDefs.h
$O/util/headerserializers/ICMPSerializer.o: util/headerserializers/ICMPSerializer.cc \
	networklayer/ipv4/ICMPMessage_m.h \
	util/headerserializers/headers/ip.h \
	util/headerserializers/headers/in.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	util/headerserializers/headers/in_systm.h \
	applications/pingapp/PingPayload_m.h \
	util/headerserializers/IPSerializer.h \
	util/headerserializers/ICMPSerializer.h \
	util/headerserializers/headers/bsdint.h \
	util/headerserializers/headers/defs.h \
	networklayer/contract/IPProtocolId_m.h \
	util/headerserializers/headers/ip_icmp.h \
	networklayer/contract/IPAddress.h \
	base/INETDefs.h
$O/util/headerserializers/TCPSerializer.o: util/headerserializers/TCPSerializer.cc \
	transport/tcp/TCPSegment_m.h \
	util/headerserializers/TCPSerializer.h \
	util/headerserializers/headers/in_systm.h \
	util/headerserializers/headers/bsdint.h \
	transport/tcp/TCPSegment.h \
	util/headerserializers/headers/defs.h \
	util/headerserializers/headers/in.h \
	base/INETDefs.h \
	util/headerserializers/headers/tcp.h
$O/util/headerserializers/IPSerializer.o: util/headerserializers/IPSerializer.cc \
	util/headerserializers/SCTPSerializer.h \
	util/headerserializers/headers/ip.h \
	networklayer/ipv4/IPDatagram_m.h \
	networklayer/ipv4/IPDatagram.h \
	util/headerserializers/headers/tcp.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	util/headerserializers/TCPSerializer.h \
	util/headerserializers/UDPSerializer.h \
	util/headerserializers/headers/bsdint.h \
	networklayer/contract/IPProtocolId_m.h \
	base/INETDefs.h \
	transport/sctp/SCTPMessage.h \
	transport/tcp/TCPSegment_m.h \
	networklayer/ipv4/ICMPMessage_m.h \
	networklayer/contract/IPvXAddress.h \
	transport/udp/UDPPacket_m.h \
	util/headerserializers/headers/in.h \
	util/headerserializers/headers/in_systm.h \
	transport/udp/UDPPacket.h \
	util/headerserializers/IPSerializer.h \
	util/headerserializers/ICMPSerializer.h \
	transport/tcp/TCPSegment.h \
	util/headerserializers/headers/defs.h \
	networklayer/contract/IPAddress.h
$O/util/headerserializers/SCTPSerializer.o: util/headerserializers/SCTPSerializer.cc \
	transport/sctp/SCTPQueue.h \
	networklayer/ipv4/IPRoute.h \
	util/headerserializers/SCTPSerializer.h \
	util/headerserializers/headers/ip.h \
	networklayer/contract/IPControlInfo.h \
	networklayer/common/InterfaceTable.h \
	transport/sctp/SCTPMessage_m.h \
	networklayer/contract/IPv6Address.h \
	util/headerserializers/headers/bsdint.h \
	transport/sctp/SCTPSendStream.h \
	networklayer/contract/IPProtocolId_m.h \
	util/headerserializers/headers/sctp.h \
	networklayer/common/IInterfaceTable.h \
	transport/sctp/SCTPMessage.h \
	base/INETDefs.h \
	linklayer/contract/MACAddress.h \
	networklayer/ipv4/IRoutingTable.h \
	networklayer/ipv4/RoutingTable.h \
	base/NotificationBoard.h \
	transport/sctp/SCTPAssociation.h \
	networklayer/contract/IPvXAddress.h \
	transport/sctp/SCTPReceiveStream.h \
	networklayer/ipv4/RoutingTableAccess.h \
	util/headerserializers/headers/in.h \
	base/ModuleAccess.h \
	networklayer/contract/IPControlInfo_m.h \
	util/headerserializers/headers/in_systm.h \
	base/INotifiable.h \
	base/NotifierConsts.h \
	networklayer/common/InterfaceEntry.h \
	transport/sctp/SCTP.h \
	networklayer/common/InterfaceTableAccess.h \
	util/headerserializers/headers/defs.h \
	networklayer/common/InterfaceToken.h \
	networklayer/contract/IPAddress.h
$O/world/ScenarioManager.o: world/ScenarioManager.cc \
	base/IScriptable.h \
	world/ScenarioManager.h \
	base/INETDefs.h
$O/world/ChannelAccess.o: world/ChannelAccess.cc \
	util/FWMath.h \
	base/ModuleAccess.h \
	base/INotifiable.h \
	base/Coord.h \
	base/NotifierConsts.h \
	base/NotificationBoard.h \
	base/BasicModule.h \
	linklayer/mfcore/AirFrame_m.h \
	world/ChannelAccess.h \
	world/ChannelControl.h \
	base/INETDefs.h
$O/world/ChannelControl.o: world/ChannelControl.cc \
	util/FWMath.h \
	base/Coord.h \
	linklayer/mfcore/AirFrame_m.h \
	world/ChannelControl.h \
	base/INETDefs.h
$O/world/NAMTrace.o: world/NAMTrace.cc \
	world/NAMTrace.h \
	base/INETDefs.h
$O/world/ChannelInstaller.o: world/ChannelInstaller.cc \
	world/ChannelInstaller.h \
	base/INETDefs.h

