//
//  INStringResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INStringResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given string. The resolvedString need not be identical to the input string. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedString:(NSString *)resolvedString NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided strings.
+ (instancetype)disambiguationWithStringsToDisambiguate:(NSArray<NSString *> *)stringsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the string with which the user wants to continue.
+ (instancetype)confirmationRequiredWithStringToConfirm:(nullable NSString *)stringToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
