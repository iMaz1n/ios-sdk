//
//  INSpeakableString.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INSpeakable.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSpeakableString : NSObject <INSpeakable>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithIdentifier:(NSString *)identifier
                   spokenPhrase:(NSString *)spokenPhrase
                   pronunciationHint:(nullable NSString *)pronunciationHint NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

