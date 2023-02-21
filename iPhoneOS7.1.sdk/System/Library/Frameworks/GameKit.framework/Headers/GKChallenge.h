//
//  GKChallenge.h
//  GameKit
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKScore.h>
#import <GameKit/GKAchievement.h>

@class UIViewController;

typedef void (^GKChallengeComposeCompletionBlock)(UIViewController *composeController, BOOL didIssueChallenge, NSArray *sentPlayerIDs);

typedef NS_ENUM(NSInteger, GKChallengeState) {
    GKChallengeStateInvalid = 0,
    GKChallengeStatePending = 1, // The challenge has been issued, but neither completed nor declined
    GKChallengeStateCompleted = 2, // The challenge has been completed by the receiving player
    GKChallengeStateDeclined = 3, // The challenge has been declined by the receiving player
};

NS_CLASS_AVAILABLE(10_8, 6_0)
@interface GKChallenge : NSObject <NSCoding, NSSecureCoding>

// Query challenges for the current game issued to the local player -- equivalent GKChallenge objects are not guaranteed to be pointer equivalent across calls, but equal GKChallenge objects will have equal hashes
+ (void)loadReceivedChallengesWithCompletionHandler:(void(^)(NSArray *challenges, NSError *error))completionHandler;

// Any GKChallenge object to be declined must be in a state of GKChallengeStatePending in order to be successfully cancelled
- (void)decline;

@property (nonatomic, readonly, copy) NSString *issuingPlayerID; // The GKPlayer who issued the challenge
@property (nonatomic, readonly, copy) NSString *receivingPlayerID; // The GKPlayer who has received the challenge
@property (nonatomic, readonly, assign) GKChallengeState state; // Current state of the challenge
@property (nonatomic, readonly, retain) NSDate *issueDate; // Date the challenge was issued
@property (nonatomic, readonly, retain) NSDate *completionDate; // Date the challenge was completed or aborted
@property (nonatomic, readonly, copy) NSString *message; // The message sent to receivers of this challenge


@end

NS_CLASS_AVAILABLE(10_8, 6_0)
@interface GKScoreChallenge : GKChallenge

@property (nonatomic, readonly, retain) GKScore *score; // The score to meet to satisfy this challenge
@end

NS_CLASS_AVAILABLE(10_8, 6_0)
@interface GKAchievementChallenge : GKChallenge

@property (nonatomic, readonly, retain) GKAchievement *achievement; // The achievement to achieve to satisfy this challenge
@end


// Use the following category methods to issue GKScoreChallenges and GKAchievementChallenges to an array of playerIDs. Players may not issue challenges to themselves nor to non-friends. Please see the GameKit reference documentation for further details on these methods.

@interface GKScore (GKChallenge)

// Return a challenge compose view controller with pre-selected playerIDs and a preformatted, player-editable message. Once this view controller is displayed, and the player sends or cancels sending the challenge, the completion handler will be called. This block contains the view controller, the reason why the handler was called, as well as which (if any) playerIDs the challenge was sent to. Present modally from the top view controller. The completion handler should dismiss the view controller.
- (UIViewController *)challengeComposeControllerWithPlayers:(NSArray *)playerIDs message:(NSString *)message completionHandler:(GKChallengeComposeCompletionBlock)completionHandler __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_7_0);

// As of iOS 7.0, this will present a challenge dialogue to the player before the challenge is actually sent. Please use challengeComposeControllerWithPlayers:message:completion: instead.
- (void)issueChallengeToPlayers:(NSArray *)playerIDs message:(NSString *)message __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_8, __MAC_NA, __IPHONE_6_0, __IPHONE_7_0, "Use challengeComposeControllerWithPlayers:message:completionHandler: and present the view controller instead");

// Use this alternative to reportScores:withCompletionHandler: to allow only certain specific challenges to be completed. Pass nil to avoid completing any challenges.
+ (void)reportScores:(NSArray *)scores withEligibleChallenges:(NSArray *)challenges withCompletionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

@end

@interface GKAchievement (GKChallenge)

// If an achievement has already been earned by the receiving player, and that achievement is not marked as replayable in iTunes connect, then the challenge will not be issued to the player. If an achievement is hidden, then it will not be issued.

// Return a challenge compose view controller with pre-selected playerIDs and a preformatted, player-editable message. Once this view controller is displayed, and the player sends or cancels sending the challenge, the completion handler will be called. This block contains the view controller, the reason why the handler was called, as well as which (if any) playerIDs the challenge was sent to. Present modally from the top view controller. The completion handler should dismiss the view controller.
- (UIViewController *)challengeComposeControllerWithPlayers:(NSArray *)playerIDs message:(NSString *)message completionHandler:(GKChallengeComposeCompletionBlock)completionHandler __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_7_0);

// As of iOS 7.0, this will present a challenge dialogue to the player before the challenge is actually sent. Please use challengeComposeControllerWithPlayers:message:completion: instead.
- (void)issueChallengeToPlayers:(NSArray *)playerIDs message:(NSString *)message __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_8, __MAC_NA, __IPHONE_6_0, __IPHONE_7_0, "Use challengeComposeControllerWithPlayers:message:completionHandler: and present the view controller instead");

// Given a list of playerIDs, return a subset of that list containing only playerIDs that are eligible to receive a challenge for the achievement.
- (void)selectChallengeablePlayerIDs:(NSArray *)playerIDs withCompletionHandler:(void(^)(NSArray *challengeablePlayerIDs, NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

// Use this alternative to reportAchievements:withCompletionHandler: to allow only certain specific challenges to be completed. Pass nil to avoid completing any challenges.
+ (void)reportAchievements:(NSArray *)achievements withEligibleChallenges:(NSArray *)challenges withCompletionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_NA,__IPHONE_7_0);

@end
