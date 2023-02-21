//
//  INPaymentStatus.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INPaymentStatus_h
#define INPaymentStatus_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INPaymentStatus) {
    INPaymentStatusUnknown = 0,
    INPaymentStatusPending,
    INPaymentStatusCompleted,
    INPaymentStatusCanceled,
    INPaymentStatusFailed,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

#endif // INPaymentStatus_h
