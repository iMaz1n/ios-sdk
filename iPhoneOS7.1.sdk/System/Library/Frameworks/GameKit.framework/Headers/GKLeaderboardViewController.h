//
//  GKLeaderboardViewController.h
//  GameKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GameKit/GKLeaderboard.h>
#import <GameKit/GKGameCenterViewController.h>

@protocol GKLeaderboardViewControllerDelegate;

// View controller that provides the standard user interface for leaderboards.  Present modally from the top view controller.
__OSX_AVAILABLE_BUT_DEPRECATED_MSG(NA, NA, __IPHONE_4_1, __IPHONE_7_0, "Use GKGameCenterViewController instead")
@interface GKLeaderboardViewController : GKGameCenterViewController

@property (nonatomic, assign) GKLeaderboardTimeScope timeScope;
@property (nonatomic, retain) NSString *category;
@property (nonatomic, assign) id <GKLeaderboardViewControllerDelegate> leaderboardDelegate;

@end

NS_DEPRECATED_IOS(4_1, 7_0)
@protocol GKLeaderboardViewControllerDelegate <NSObject>
@required
// The leaderboard view has finished
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;
@end
