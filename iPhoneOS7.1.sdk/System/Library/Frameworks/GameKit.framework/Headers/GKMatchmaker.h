//
//  GKMatchmaker.h
//  GameKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#include <Foundation/Foundation.h>

@class GKPlayer;
@class GKMatch;

// GKMatchRequest represents the parameters needed to create the match.
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKMatchRequest : NSObject {
}

@property(nonatomic, assign) NSUInteger minPlayers;     // Minimum number of players for the match
@property(nonatomic, assign) NSUInteger maxPlayers;     // Maximum number of players for the match
@property(nonatomic, assign) NSUInteger playerGroup;    // The player group identifier. Matchmaking will only take place between players in the same group.
@property(nonatomic, assign) uint32_t playerAttributes; // optional mask that specifies the role that the local player would like to play in the game.  If this value is 0 (the default), this property is ignored. If the value is nonzero, then automatching uses the value as a mask that restricts the role the player can play in the group. Automatching with player attributes matches new players into the game so that the bitwise OR of the masks of all the players in the resulting match equals 0xFFFFFFFF.
@property(nonatomic, retain) NSArray *playersToInvite;  // Array of player IDs to invite, or nil if none

// Message sent to invited players, may be modified if using GKMatchmakerViewController
@property(nonatomic, copy)   NSString *inviteMessage __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

// Default number of players to to use during matchmaking.  If not set we default to maxPlayers
@property(nonatomic, assign) NSUInteger defaultNumberOfPlayers __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

// Possible invitee responses
enum {
    GKInviteeResponseAccepted           = 0,
    GKInviteeResponseDeclined           = 1,
    GKInviteeResponseFailed             = 2,
    GKInviteeResponseIncompatible       = 3,
    GKInviteeResponseUnableToConnect    = 4,
    GKInviteeResponseNoAnswer           = 5,
};
typedef NSInteger GKInviteeResponse;

// An inviteeResponseHandler can be set in order to receive responses from programmatically invited players.
@property(nonatomic, copy) void(^inviteeResponseHandler)(NSString *playerID, GKInviteeResponse response) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

enum {
    GKMatchTypePeerToPeer,
    GKMatchTypeHosted,
    GKMatchTypeTurnBased
};
typedef NSUInteger GKMatchType;

// To determine the maximum allowed players for each type of match supported.
+ (NSUInteger)maxPlayersAllowedForMatchOfType:(GKMatchType)matchType __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

@end

// GKInvite represents an accepted game invite, it is used to create a GKMatchmakerViewController
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKInvite : NSObject
#if !__OBJC2__
{
@private
    id _internal;
    GKPlayer *_invitingPlayer;
    BOOL _hosted;
}
#endif //!__OBJC2__

@property(readonly, retain, NS_NONATOMIC_IOSONLY) NSString *inviter;
@property(readonly, getter=isHosted, NS_NONATOMIC_IOSONLY) BOOL hosted;
@property(readonly, NS_NONATOMIC_IOSONLY) NSUInteger playerGroup __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);      // player group from inviter's match request
@property(readonly, NS_NONATOMIC_IOSONLY) uint32_t playerAttributes __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);   // player attributes from inviter's match request

@end

// GKInviteEventListener uses the GKLocalPlayerListener mechanism on GKLocalPlayer to listen to the two kinds of invite events that a game must respond to
@protocol GKInviteEventListener

@optional

// player:didAcceptInvite: gets called when another player accepts the invite from the local player
- (void)player:(GKPlayer *)player didAcceptInvite:(GKInvite *)invite NS_AVAILABLE_IOS(7_0);

// player:didRequestMatchWithPlayers gets called when the player chooses to play with another player from Game Center and it launches the game to start matchmaking
- (void)player:(GKPlayer *)player didRequestMatchWithPlayers:(NSArray *)playerIDsToInvite NS_AVAILABLE_IOS(7_0);

@end

// GKMatchmaker is a singleton object to manage match creation from invites and auto-matching.
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKMatchmaker : NSObject {
}

// The shared matchmaker
+ (GKMatchmaker*)sharedMatchmaker;

// An inviteHandler must be set in order to receive game invites or respond to external requests to initiate an invite. The inviteHandler will be called when an invite or request is received. It may be called immediately if there is a pending invite or request when the application is launched. The inviteHandler may be called multiple times.
// Either acceptedInvite or playerIDsToInvite will be present, but never both.
@property(nonatomic, copy) void(^inviteHandler)(GKInvite *acceptedInvite, NSArray *playerIDsToInvite) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8,__MAC_NA,__IPHONE_4_1,__IPHONE_7_0);


// Get a match for an accepted invite
// Possible reasons for error:
// 1. Communications failure
// 2. Invite cancelled
- (void)matchForInvite:(GKInvite *)invite completionHandler:(void(^)(GKMatch *match, NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

// Auto-matching or invites to find a peer-to-peer match for the specified request. Error will be nil on success:
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
// 3. Timeout
- (void)findMatchForRequest:(GKMatchRequest *)request withCompletionHandler:(void(^)(GKMatch *match, NSError *error))completionHandler;

// Auto-matching or invites for host-client match request. This returns a list of player identifiers to be included in the match. Determination and communication with the host is not part of this API.
// When inviting, no player identifiers will be returned. Player responses will be reported via the inviteeResponseHandler.
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
// 3. Timeout
- (void)findPlayersForHostedMatchRequest:(GKMatchRequest *)request withCompletionHandler:(void(^)(NSArray *playerIDs, NSError *error))completionHandler;

// Auto-matching or invites to add additional players to a peer-to-peer match for the specified request. Error will be nil on success:
// Possible reasons for error:
// 1. Communications failure
// 2. Timeout
- (void)addPlayersToMatch:(GKMatch *)match matchRequest:(GKMatchRequest *)matchRequest completionHandler:(void (^)(NSError *error))completionHandler;

// Cancel matchmaking and any pending invites
- (void)cancel;

// Cancel a pending invitation to a player
- (void)cancelInviteToPlayer:(NSString *)playerID __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

// Call this when finished with all programmatic P2P invites/matchmaking, for compatability with connected players using GKMatchmakerViewController.
- (void)finishMatchmakingForMatch:(GKMatch *)match __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

// Query the server for recent activity in the specified player group. A larger value indicates that a given group has seen more recent activity. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
- (void)queryPlayerGroupActivity:(NSUInteger)playerGroup withCompletionHandler:(void(^)(NSInteger activity, NSError *error))completionHandler;

// Query the server for recent activity for all the player groups of that game. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
- (void)queryActivityWithCompletionHandler:(void(^)(NSInteger activity, NSError *error))completionHandler;


// Start browsing for nearby players that can be invited to a match. The reachableHandler will be called for each player found with a compatible game. It may be called more than once for the same player if that player ever becomes unreachable (e.g. moves out of range). You should call stopBrowsingForNearbyPlayers when finished browsing.
- (void)startBrowsingForNearbyPlayersWithReachableHandler:(void(^)(NSString *playerID, BOOL reachable))reachableHandler
 __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

// Stop browsing for nearby players.
- (void)stopBrowsingForNearbyPlayers __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);


@end
