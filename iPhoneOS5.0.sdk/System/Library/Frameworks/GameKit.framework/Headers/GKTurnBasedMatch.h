/*
 *  GKTurnBasedMatch.h
 *  GameKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

@class GKMatchRequest, GKTurnBasedMatch;

// Constants that describe the state of the overall match
enum {
    GKTurnBasedMatchStatusUnknown   = 0,
    GKTurnBasedMatchStatusOpen      = 1,
    GKTurnBasedMatchStatusEnded     = 2,
    GKTurnBasedMatchStatusMatching  = 3
};
typedef NSInteger GKTurnBasedMatchStatus;


// Constants that describe the state of individual participants in the match
enum {
    // Statuses that are set by GameKit
    GKTurnBasedParticipantStatusUnknown     = 0,
    GKTurnBasedParticipantStatusInvited     = 1,    // a participant has been invited but not yet responded
    GKTurnBasedParticipantStatusDeclined    = 2,    // a participant that has declined an invite to this match
    GKTurnBasedParticipantStatusMatching    = 3,    // a participant that is waiting to be matched
    GKTurnBasedParticipantStatusActive      = 4,    // a participant that is active in this match
    GKTurnBasedParticipantStatusDone        = 5,    // a participant is done with this session
};
typedef NSInteger GKTurnBasedParticipantStatus;

// Constants that describe the game result for a given participant who has reached the done state.  The developer is free to use these constants or add additional ones

enum { 
    GKTurnBasedMatchOutcomeNone         = 0,        // Participants who are not done with a match have this state
    GKTurnBasedMatchOutcomeQuit         = 1,        // Participant quit
    GKTurnBasedMatchOutcomeWon          = 2,        // Participant won
    GKTurnBasedMatchOutcomeLost         = 3,        // Participant lost
    GKTurnBasedMatchOutcomeTied         = 4,        // Participant tied
    GKTurnBasedMatchOutcomeTimeExpired  = 5,        // Game ended due to time running out
    GKTurnBasedMatchOutcomeFirst        = 6,
    GKTurnBasedMatchOutcomeSecond       = 7,
    GKTurnBasedMatchOutcomeThird        = 8,
    GKTurnBasedMatchOutcomeFourth       = 9,
    
    GKTurnBasedMatchOutcomeCustomRange = 0x00FF0000	// game result range available for custom app use
    
};
typedef NSInteger GKTurnBasedMatchOutcome;


// GKTurnBasedMatch represents an ongoing turn-based game among the matched group of participants
// Existing matches can be shown and new matches created using GKTurnBasedMatchmakerViewController
// A list of existing matches can be retrieved using +loadMatchesWithCompletionHandler:

NS_CLASS_AVAILABLE(NA, 5_0)
@interface GKTurnBasedParticipant : NSObject {
}

@property(nonatomic, readonly, retain)  NSString                        *playerID;
@property(nonatomic, readonly, retain)  NSDate                          *lastTurnDate;
@property(nonatomic, readonly)          GKTurnBasedParticipantStatus    status;
@property(nonatomic, assign)            GKTurnBasedMatchOutcome         matchOutcome;

@end


@protocol GKTurnBasedEventHandlerDelegate
@optional

// If Game Center initiates a match the developer should create a GKTurnBasedMatch from playersToInvite and present a GKTurnbasedMatchmakerViewController.
- (void)handleInviteFromGameCenter:(NSArray *)playersToInvite;		

// handleTurnEventForMatch is called when a turn is passed to another participant.  Note this may arise from one of the following events:
//      The local participant has accepted an invite to a new match
//      The local participant has been passed the turn for an existing match
//      Another participant has made a turn in an existing match
// The application needs to be prepared to handle this even while the participant might be engaged in a different match
- (void)handleTurnEventForMatch:(GKTurnBasedMatch *)match;

// handleMatchEnded is called when the match has ended.
- (void)handleMatchEnded:(GKTurnBasedMatch *)match;

@end

NS_CLASS_AVAILABLE(NA, 5_0)
@interface GKTurnBasedEventHandler : NSObject {
}
+ (GKTurnBasedEventHandler *)sharedTurnBasedEventHandler;

@property (nonatomic, assign) 		NSObject<GKTurnBasedEventHandlerDelegate>	*delegate;

@end

NS_CLASS_AVAILABLE(NA, 5_0)
@interface GKTurnBasedMatch : NSObject {
}

@property(nonatomic, readonly, retain)  NSString                *matchID;
@property(nonatomic, readonly, retain)  NSDate                  *creationDate;
@property(nonatomic, readonly, retain)  NSArray                 *participants;          // array of GKTurnBasedParticipant objects
@property(nonatomic, readonly)          GKTurnBasedMatchStatus  status;

// This indicates the participant who has the current turn.  This is set by passing the next participant into endTurnWithNextParticipant:matchData:completionHandler:
@property(nonatomic, readonly, retain)  GKTurnBasedParticipant  *currentParticipant;

// Developer-defined data representing the current state of the game. This propery is nil until loaded by loadMatchDataWithCompletionHandler:
// The developer can submit updated matchData by passing it into endTurnWithNextParticipant:matchData:completionHandler: or endMatchInTurnWithMatchData:completionHandler:
@property(nonatomic, readonly, retain)  NSData                  *matchData;            

// If the developer wishes to display a message in GKTurnBasedMatchmakerViewController at the end of a turn or end of the match.  Only the current participant can set this.
@property(nonatomic, readwrite, copy)   NSString                *message;

// Attempt to find a turn-based match for the specified request. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
+ (void)findMatchForRequest:(GKMatchRequest *)request withCompletionHandler:(void(^)(GKTurnBasedMatch *match, NSError *error))completionHandler;

// This method retrieves the list of GKTurnBasedMatches that the current player is or has participated in. The callback???s array contains GKTurnBasedMatches
+ (void)loadMatchesWithCompletionHandler:(void(^)(NSArray *matches, NSError *error))completionHandler;

// Remove a completed match (one with a matchOutcome set) from the player's list of matches. If using the GKTurnBasedMatchmakerViewController UI, this will remove it from the finished sessions.  The developer should not do this without user input.
- (void)removeWithCompletionHandler:(void(^)(NSError *error))completionHandler;

// This method fetches the match data for this match.  This data is the state of the game at this point in time.  This may update the status and/or participant properties if they have changed.
- (void)loadMatchDataWithCompletionHandler:(void(^)(NSData *matchData, NSError *error))completionHandler;

// Ends the current participant's turn. You may update the matchOutcome for any GKTurnBasedParticipants that you wish to before ending the turn.
// This will asynchronously report error in these cases:
// 1. Communications problem
// 2. Is not current participant's turn
// 3. Session is closed
- (void)endTurnWithNextParticipant:(GKTurnBasedParticipant *)nextParticipant matchData:(NSData*)matchData completionHandler:(void(^)(NSError *error))completionHandler;

// Ends the current participant's turn by quitting the match.  The caller must indicate the next participant and pass in updated matchData (if used)
- (void)participantQuitInTurnWithOutcome:(GKTurnBasedMatchOutcome)matchOutcome nextParticipant:(GKTurnBasedParticipant *)nextParticipant matchData:(NSData*)matchData completionHandler:(void(^)(NSError *error))completionHandler;

// Abandon the match when it is not the current participant's turn.  In this there is no update to matchData and no need to set nextParticipant.
- (void)participantQuitOutOfTurnWithOutcome:(GKTurnBasedMatchOutcome)matchOutcome withCompletionHandler:(void(^)(NSError *error))completionHandler;

// This will end the match for all participants. You must set each participant???s matchOutcome before calling this method.
- (void)endMatchInTurnWithMatchData:(NSData*)matchData completionHandler:(void(^)(NSError *error))completionHandler;

@end