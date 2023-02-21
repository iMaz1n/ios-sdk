//
//  INPauseWorkoutIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INPauseWorkoutIntent : INIntent

// Designated initializer. The `workoutName` can use `INWorkoutNameIdentifier` as its `identifier` parameter.
- (instancetype)initWithWorkoutName:(nullable INSpeakableString *)workoutName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *workoutName;

@end

@class INPauseWorkoutIntentResponse;

/*!
 @brief Protocol to declare support for handling an INPauseWorkoutIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INPauseWorkoutIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INPauseWorkoutIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  pauseWorkoutIntent The input intent
 @param  completion The response handling block takes a INPauseWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INPauseWorkoutIntentResponse
 */

- (void)handlePauseWorkout:(INPauseWorkoutIntent *)intent
                completion:(void (^)(INPauseWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(pauseWorkout:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  pauseWorkoutIntent The input intent
 @param  completion The response block contains an INPauseWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INPauseWorkoutIntentResponse

 */

- (void)confirmPauseWorkout:(INPauseWorkoutIntent *)intent
                 completion:(void (^)(INPauseWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(pauseWorkout:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  pauseWorkoutIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveWorkoutNameForPauseWorkout:(INPauseWorkoutIntent *)intent
                           withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(forPauseWorkout:with:));

@end

NS_ASSUME_NONNULL_END
