/*
 *  GKAchievementViewController.h
 *  GameKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>
#import <GameKit/GKGameCenterViewController.h>

@protocol GKAchievementViewControllerDelegate;

// View controller that provides the standard user interface for achievements. Present modally from the top view controller.
__OSX_AVAILABLE_BUT_DEPRECATED_MSG(NA, NA, __IPHONE_4_1, __IPHONE_7_0, "Use GKGameCenterViewController instead")
@interface GKAchievementViewController : GKGameCenterViewController

// Optional delegate
@property (nonatomic, assign) id<GKAchievementViewControllerDelegate> achievementDelegate;

@end

// Optional delegate
NS_DEPRECATED_IOS(4_1, 7_0)
@protocol GKAchievementViewControllerDelegate <NSObject>
@required
// The achievement view has finished
- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController;
@end


