//
//  GKLocalPlayer.h
//  GameKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKPlayer.h>
#import <GameKit/GKDefines.h>
#import <GameKit/GKEventListener.h>
#import <GameKit/GKTurnBasedMatch.h>
#import <GameKit/GKMatchmaker.h>

#if TARGET_OS_IPHONE
@class UIViewController;
#else
@class NSViewController;
#endif

NS_CLASS_AVAILABLE(10_8, 4_1)
GK_EXTERN_CLASS @interface GKLocalPlayer : GKPlayer

// Obtain the GKLocalPlayer object.
// The player is only available for offline play until logged in.
// A temporary player is created if no account is set up.
+ (GKLocalPlayer *)localPlayer;

@property(readonly, getter=isAuthenticated, NS_NONATOMIC_IOSONLY)  BOOL authenticated; // Authentication state
@property(readonly, getter=isUnderage, NS_NONATOMIC_IOSONLY)       BOOL underage;      // Underage state

// The authenticate handler will be called whenever the authentication process finishes or needs to show UI. The handler may be called multiple times. Authentication will happen automatically when the handler is first set and whenever the app returns to the foreground.
// If the authentication process needs to display UI the viewController property will be non-nil. Your application should present this view controller and continue to wait for another call of the authenticateHandler.  The view controller will be dismissed automatically.
// Possible reasons for error:
// 1. Communications problem
// 2. User credentials invalid
// 3. User cancelled
@property(nonatomic, copy) void(^authenticateHandler)(UIViewController *viewController, NSError *error) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

@property(nonatomic, readonly, retain) NSArray *friends;  // Array of player identifiers of friends for the local player. Not valid until loadFriendsWithCompletionHandler: has completed.

// Asynchronously load the friends list as an array of player identifiers. Calls completionHandler when finished. Error will be nil on success.
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
- (void)loadFriendsWithCompletionHandler:(void(^)(NSArray *friendIDs, NSError *error))completionHandler;

// Set the default leaderboard for the current game
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
// 3. Leaderboard not present
- (void)setDefaultLeaderboardIdentifier:(NSString *)leaderboardIdentifier completionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_7_0);

//old terminology, please use -setDefaultLeaderboardIdentifier:completionHandler: instead
- (void)setDefaultLeaderboardCategoryID:(NSString *)catogoryID completionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_8,__MAC_NA,__IPHONE_6_0,__IPHONE_7_0,"Use setDefaultLeaderboardIdentifier:completionHandler: instead");


// Load the default leaderboard identifier for the local player
// Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
// 3. Leaderboard not present
- (void)loadDefaultLeaderboardIdentifierWithCompletionHandler:(void(^)(NSString *leaderboardIdentifier, NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_7_0);

//old terminology, please use -loadDefaultLeaderboardIdentifierWithCompletionHandler: instead
- (void)loadDefaultLeaderboardCategoryIDWithCompletionHandler:(void(^)(NSString *categoryID, NSError *error))completionHandler __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_8,__MAC_NA,__IPHONE_6_0,__IPHONE_7_0,"Use loadDefaultLeaderboardIdentifierWithCompletionHandler: instead");


// Generates a signature allowing 3rd party server to authenticate the GKLocalPlayer
//Possible reasons for error:
// 1. Communications problem
// 2. Unauthenticated player
- (void)generateIdentityVerificationSignatureWithCompletionHandler:(void (^)(NSURL *publicKeyUrl, NSData *signature, NSData *salt, uint64_t timestamp, NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_7_0);

// Deprecated, set the authenticateHandler instead. Authentication happens automatically when the handler is set and when the app returns to foreground.
- (void)authenticateWithCompletionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8, __MAC_10_8, __IPHONE_4_1, __IPHONE_6_0);

@end

@protocol GKLocalPlayerListener <GKChallengeListener, GKInviteEventListener, GKTurnBasedEventListener>
@end

@interface GKLocalPlayer (GKLocalPlayerEvents)

// A single listener may be registered once. Registering multiple times results in undefined behavior. The registered listener will receive callbacks for any selector it responds to.
- (void)registerListener:(id<GKLocalPlayerListener>)listener __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_7_0);

- (void)unregisterListener:(id<GKLocalPlayerListener>)listener __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_7_0);

- (void)unregisterAllListeners __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_7_0);

@end

// Notification will be posted whenever authentication status changes.
GK_EXTERN NSString *GKPlayerAuthenticationDidChangeNotificationName __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_4_1);

