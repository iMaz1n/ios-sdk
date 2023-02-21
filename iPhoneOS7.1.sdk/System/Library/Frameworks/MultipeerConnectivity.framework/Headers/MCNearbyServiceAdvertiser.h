//
//  MCNearbyServiceAdvertiser.h
//  MultipeerConnectivity
//
//  Copyright 2013 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MCPeerID.h"
#import "MCSession.h"


@protocol MCNearbyServiceAdvertiserDelegate;

/*!
  @class MCNearbyServiceAdvertiser
  @abstract 
  MCNearbyServiceAdvertiser advertises availability of the local peer, 
  and handles invitations from nearby peers.
 
  @discussion
  To create the MCNearbyServiceAdvertiser object and start advertising 
  to nearby peers, a new MCPeerID should be created to 
  represent the local peer, and a service type needs to be specified.
 
  The serviceType parameter is a short text string used to describe the
  app's networking protocol.  It should be in the same format as a 
  Bonjour service type: up to 15 characters long and valid characters 
  include ASCII lowercase letters, numbers, and the hyphen.  A short 
  name that distinguishes itself from unrelated services is recommended; 
  for example, a text chat app made by ABC company could use the service
  type "abc-txtchat".
 
  The discoveryInfo parameter is a dictionary of string key/value pairs 
  that will be advertised for browsers to see. The content of 
  discoveryInfo will be advertised within Bonjour TXT records, and 
  keeping the dictionary small is good for keeping network traffic low.
 
  MCNearbyServiceAdvertiser must be initialized with an MCPeerID object 
  and a valid service type. The discoveryInfo parameter is optional and 
  may be nil.
 
  See Bonjour APIs https://developer.apple.com/bonjour/ for more 
  information about service types.
  */
NS_CLASS_AVAILABLE_IOS(7_0)
@interface MCNearbyServiceAdvertiser : NSObject
- (instancetype)initWithPeer:(MCPeerID *)myPeerID discoveryInfo:(NSDictionary *)info serviceType:(NSString *)serviceType;

// The methods -startAdvertisingPeer and -stopAdvertisingPeer are used to start and stop announcing presence to nearby browsing peers.
- (void)startAdvertisingPeer;
- (void)stopAdvertisingPeer;

@property (assign, NS_NONATOMIC_IOSONLY) id<MCNearbyServiceAdvertiserDelegate> delegate;

@property (readonly, NS_NONATOMIC_IOSONLY) MCPeerID *myPeerID;
@property (readonly, NS_NONATOMIC_IOSONLY) NSDictionary *discoveryInfo;
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *serviceType;

@end

@protocol MCNearbyServiceAdvertiserDelegate <NSObject>
// Incoming invitation request.  Call the invitationHandler block with YES and a valid session to connect the inviting peer to the session.
- (void)advertiser:(MCNearbyServiceAdvertiser *)advertiser didReceiveInvitationFromPeer:(MCPeerID *)peerID withContext:(NSData *)context invitationHandler:(void(^)(BOOL accept, MCSession *session))invitationHandler;

@optional
// Advertising did not start due to an error
- (void)advertiser:(MCNearbyServiceAdvertiser *)advertiser didNotStartAdvertisingPeer:(NSError *)error;

@end