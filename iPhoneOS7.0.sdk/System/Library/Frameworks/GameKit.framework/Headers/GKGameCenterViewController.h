//
//  GKGameCenterViewController.h
//  GameKit
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GameKit/GKLeaderboard.h>

@protocol GKGameCenterControllerDelegate;

typedef NS_ENUM(NSInteger, GKGameCenterViewControllerState) {
    GKGameCenterViewControllerStateDefault = -1,
    GKGameCenterViewControllerStateLeaderboards,
    GKGameCenterViewControllerStateAchievements,
    GKGameCenterViewControllerStateChallenges,
};

// View controller that provides the standard user interface for leaderboards, achievements, and challenges. Present modally from the top view controller.
NS_CLASS_AVAILABLE(NA, 6_0)
@interface GKGameCenterViewController : UINavigationController

@property (nonatomic, assign)   id<GKGameCenterControllerDelegate>      gameCenterDelegate;
@property (nonatomic, assign)   GKGameCenterViewControllerState         viewState;

@end

@interface GKGameCenterViewController (Leaderboards)

@property (nonatomic, assign)   GKLeaderboardTimeScope                  leaderboardTimeScope __OSX_AVAILABLE_BUT_DEPRECATED_MSG(NA, NA, __IPHONE_4_1, __IPHONE_7_0, "GKGameCenterViewController no longer supports leaderboard time scopes. Will always default to GKLeaderboardTimeScopeAllTime.");   // Show leaderboard list
@property (nonatomic, retain)   NSString                                *leaderboardIdentifier __OSX_AVAILABLE_STARTING( __MAC_NA, __IPHONE_7_0); // Showing specified leaderboard


@property (nonatomic, retain)   NSString *leaderboardCategory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8, __MAC_NA, __IPHONE_4_1, __IPHONE_7_0); // Deprecated. Use leaderboardIdentifier instead.

@end

@protocol GKGameCenterControllerDelegate <NSObject>

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController NS_AVAILABLE_IOS(6_0);

@end


