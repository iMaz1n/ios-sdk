//
//  INRelativeReference.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INRelativeReference_h
#define INRelativeReference_h

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INRelativeReference) {
    INRelativeReferenceUnknown = 0,
    INRelativeReferenceNext,
    INRelativeReferencePrevious,
};

#endif // INRelativeReference_h
