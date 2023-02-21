//
//  INSearchForMessagesIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INConditionalOperator.h>
#import <Intents/INMessageAttributeOptions.h>

@class INPerson;
@class INPersonResolutionResult;
@class INMessageAttributeOptionsResolutionResult;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSearchForMessagesIntent : INIntent

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           senders:(nullable NSArray<INPerson *> *)senders
                       searchTerms:(nullable NSArray<NSString *> *)searchTerms
                        attributes:(INMessageAttributeOptions)attributes
                     dateTimeRange:(nullable INDateComponentsRange *)dateTimeRange
                       identifiers:(nullable NSArray<NSString *> *)identifiers
           notificationIdentifiers:(nullable NSArray<NSString *> *)notificationIdentifiers
                        groupNames:(nullable NSArray<NSString *> *)groupNames NS_DESIGNATED_INITIALIZER;

// Contact that received the messages to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *recipients;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator recipientsOperator;

// Sender of the messages to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *senders;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator sendersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *searchTerms;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator searchTermsOperator;

// Attributes of the message to be found.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMessageAttributeOptions attributes;

// Time range in which to search for the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateTimeRange;

// If available, the identifier of a particular message to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *identifiers;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator identifiersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *notificationIdentifiers;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator notificationIdentifiersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *groupNames;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator groupNamesOperator;

@end

@class INSearchForMessagesIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSearchForMessagesIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INSearchForMessagesIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSearchForMessagesIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  searchForMessagesIntent The input intent
 @param  completion The response handling block takes a INSearchForMessagesIntentResponse containing the details of the result of having executed the intent

 @see  INSearchForMessagesIntentResponse
 */

- (void)handleSearchForMessages:(INSearchForMessagesIntent *)intent
                     completion:(void (^)(INSearchForMessagesIntentResponse *response))completion NS_SWIFT_NAME(handle(searchForMessages:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  searchForMessagesIntent The input intent
 @param  completion The response block contains an INSearchForMessagesIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchForMessagesIntentResponse

 */

- (void)confirmSearchForMessages:(INSearchForMessagesIntent *)intent
                      completion:(void (^)(INSearchForMessagesIntentResponse *response))completion NS_SWIFT_NAME(confirm(searchForMessages:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  searchForMessagesIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveRecipientsForSearchForMessages:(INSearchForMessagesIntent *)intent
                               withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveRecipients(forSearchForMessages:with:));

- (void)resolveSendersForSearchForMessages:(INSearchForMessagesIntent *)intent
                            withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveSenders(forSearchForMessages:with:));

- (void)resolveAttributesForSearchForMessages:(INSearchForMessagesIntent *)intent
                               withCompletion:(void (^)(INMessageAttributeOptionsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAttributes(forSearchForMessages:with:));

- (void)resolveDateTimeRangeForSearchForMessages:(INSearchForMessagesIntent *)intent
                                  withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateTimeRange(forSearchForMessages:with:));

- (void)resolveGroupNamesForSearchForMessages:(INSearchForMessagesIntent *)intent
                               withCompletion:(void (^)(NSArray<INStringResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveGroupNames(forSearchForMessages:with:));

@end

NS_ASSUME_NONNULL_END
