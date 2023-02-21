//
//  INRelativeSettingResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INRelativeSetting.h>

NS_ASSUME_NONNULL_BEGIN

@interface INRelativeSettingResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INRelativeSetting)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INRelativeSetting)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
