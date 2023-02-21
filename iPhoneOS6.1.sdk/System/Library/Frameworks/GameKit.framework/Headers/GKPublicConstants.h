/*
 GKPublicConstants.h
 GameKit
 
 Copyright 2010 Apple, Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

/* Delivery options for GKSession's -(BOOL)sendData... methods.
*/
typedef enum {
	GKSendDataReliable,		// a.s.a.p. but requires fragmentation and reassembly for large messages, may stall if network congestion occurs
    GKSendDataUnreliable,	// best effort and immediate, but no guarantees of delivery or order; will not stall.
} GKSendDataMode;

/* Specifies how GKSession behaves when it is made available.
*/
typedef enum {
    GKSessionModeServer,    // delegate will get -didReceiveConnectionRequestFromPeer callback when a client wants to connect
    GKSessionModeClient,    // delegate will get -session:peer:didChangeState: callback with GKPeerStateAvailable, or GKPeerStateUnavailable for discovered servers
    GKSessionModePeer,      // delegate will get -didReceiveConnectionRequestFromPeer when a peer wants to connect, and -session:peer:didChangeState: callback with GKPeerStateAvailable, or GKPeerStateUnavailable for discovered servers
} GKSessionMode;

/* Specifies the type of peers to return in method -peersWithConnectionState:
*/ 
typedef enum
{
	GKPeerStateAvailable,    // not connected to session, but available for connectToPeer:withTimeout:
	GKPeerStateUnavailable,  // no longer available
	GKPeerStateConnected,    // connected to the session
	GKPeerStateDisconnected, // disconnected from the session
	GKPeerStateConnecting,   // waiting for accept, or deny response
} GKPeerConnectionState;

typedef enum
{
	
	GKVoiceChatServiceInternalError = 32000,	
	GKVoiceChatServiceNoRemotePacketsError = 32001,
	GKVoiceChatServiceUnableToConnectError = 32002,
	GKVoiceChatServiceRemoteParticipantHangupError = 32003,
	GKVoiceChatServiceInvalidCallIDError = 32004,
	GKVoiceChatServiceAudioUnavailableError = 32005,
	GKVoiceChatServiceUninitializedClientError = 32006,
	GKVoiceChatServiceClientMissingRequiredMethodsError = 32007,
	GKVoiceChatServiceRemoteParticipantBusyError = 32008,
	GKVoiceChatServiceRemoteParticipantCancelledError = 32009,
	GKVoiceChatServiceRemoteParticipantResponseInvalidError = 32010,
	GKVoiceChatServiceRemoteParticipantDeclinedInviteError = 32011,
	GKVoiceChatServiceMethodCurrentlyInvalidError = 32012,
	GKVoiceChatServiceNetworkConfigurationError = 32013,
	GKVoiceChatServiceUnsupportedRemoteVersionError = 32014,
	GKVoiceChatServiceOutOfMemoryError = 32015,
	GKVoiceChatServiceInvalidParameterError = 32016
	
} GKVoiceChatServiceError;
