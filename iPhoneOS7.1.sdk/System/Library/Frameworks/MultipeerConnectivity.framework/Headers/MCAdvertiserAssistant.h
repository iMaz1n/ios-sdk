//
//  MCAdvertiserAssistant.h
//  MultipeerConnectivity
//
//  Copyright 2013 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MCPeerID.h"
#import "MCSession.h"

@protocol MCAdvertiserAssistantDelegate;

/*!
 @class MCAdvertiserAssistant
 @abstract 
 MCAdvertiserAssistant is a convenience class that handles advertising, 
 presents incoming invitations to the user and handles user's responses.
 
 @discussion
 To create the MCAdvertiserAssistant object a new MCPeerID should be 
 created to represent the local peer, and a service type needs to be 
 specified.
 
 The serviceType parameter is a short text string used to describe the 
 app's networking protocol.  It should be in the same format as a 
 Bonjour service type: up to 15 characters long and valid characters 
 include ASCII lowercase letters, numbers, and the hyphen. A short name 
 that distinguishes itself from unrelated services is recommended; 
 for example, a text chat app made by ABC company could use the service 
 type "abc-txtchat".
 
 The discoveryInfo parameter is a dictionary of string key/value pairs 
 that will be advertised for browsers to see. The content of 
 discoveryInfo will be advertised within Bonjour TXT records, and 
 keeping the dictionary small is good for keeping network traffic low.
 
 See Bonjour APIs https://developer.apple.com/bonjour/ for more 
 information about service types.
 */
NS_CLASS_AVAILABLE_IOS(7_0)
@interface MCAdvertiserAssistant : NSObject
- (instancetype)initWithServiceType:(NSString *)serviceType discoveryInfo:(NSDictionary *)info session:(MCSession *)session;

// The methods -start and -stop are used to start and stop the assistant.
- (void)start;
- (void)stop;

@property (assign, NS_NONATOMIC_IOSONLY) id<MCAdvertiserAssistantDelegate> delegate;

@property (readonly, NS_NONATOMIC_IOSONLY) MCSession *session;
@property (readonly, NS_NONATOMIC_IOSONLY) NSDictionary *discoveryInfo;
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *serviceType;

@end

@protocol MCAdvertiserAssistantDelegate <NSObject>
@optional

// An invitation will be presented to the user
- (void)advertiserAssitantWillPresentInvitation:(MCAdvertiserAssistant *)advertiserAssistant;

// An invitation was dismissed from screen
- (void)advertiserAssistantDidDismissInvitation:(MCAdvertiserAssistant *)advertiserAssistant;

@end