//
//  INRidePhase.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INRidePhase_h
#define INRidePhase_h

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INRidePhase) {
    INRidePhaseUnknown = 0,
    INRidePhaseReceived,
    INRidePhaseConfirmed,
    INRidePhaseOngoing,
    INRidePhaseCompleted,
    INRidePhaseApproachingPickup,
    INRidePhasePickup,
};

#endif // INRidePhase_h
