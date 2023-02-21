/*
 *  GKTurnBasedMatchmakerViewController.h
 *  GameKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>

@class GKMatchmakerViewController, GKTurnBasedMatch;

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

// View controller to manage matches, invite friends and perform auto-matching. Present modally from the top view controller.
NS_CLASS_AVAILABLE(NA, 5_0)
@interface GKTurnBasedMatchmakerViewController : UINavigationController 

@property (nonatomic, readwrite, assign) id<GKTurnBasedMatchmakerViewControllerDelegate> turnBasedMatchmakerDelegate;
@property (nonatomic, readwrite, assign) BOOL showExistingMatches; // defaults to YES

// Inherited from GKMatchmakerViewControler
- (id)initWithMatchRequest:(GKMatchRequest *)request;

@end

@protocol GKTurnBasedMatchmakerViewControllerDelegate <NSObject>
@required

// The user has cancelled
- (void)turnBasedMatchmakerViewControllerWasCancelled:(GKTurnBasedMatchmakerViewController *)viewController NS_AVAILABLE_IOS(5_0);

// Matchmaking has failed with an error
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFailWithError:(NSError *)error NS_AVAILABLE_IOS(5_0);

// A turned-based match has been found, the game should start
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFindMatch:(GKTurnBasedMatch *)match NS_AVAILABLE_IOS(5_0);

// Called when a users chooses to quit a match and that player has the current turn.  The developer should call playerQuitInTurnWithOutcome:nextPlayer:matchData:completionHandler: on the match passing in appropriate values.  They can also update matchOutcome for other players as appropriate.
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController playerQuitForMatch:(GKTurnBasedMatch *)match NS_AVAILABLE_IOS(5_0);

@end

