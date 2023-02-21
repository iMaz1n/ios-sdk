// HMTimerTrigger.h
// HomeKit
//
// Copyright (c) 2013-2014 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMTrigger.h>

/*!
 * @brief Timer based trigger.
 *
 * @discussion This class represents a trigger that is based on timers.
 */
NS_CLASS_AVAILABLE_IOS(8_0)
@interface HMTimerTrigger : HMTrigger

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initialize a new HMTimerTrigger object.
 *
 * @param name Name for the trigger.
 *
 * @param fireDate The initial fire date for the timer trigger.
 *
 * @param timeZone The time zone of the initial fire date. A value of nil indicates default timezone
 *
 * @param recurrence The recurrence interval to fire the trigger. A value of nil indicates non-recurring
 *
 * @param recurrenceCalendar The calendar corresponding to a recurring timer trigger. May be nil.
 */
- (instancetype)initWithName:(NSString *)name
                    fireDate:(NSDate *)fireDate
                    timeZone:(NSTimeZone *)timeZone
                  recurrence:(NSDateComponents *)recurrence
          recurrenceCalendar:(NSCalendar *)recurrenceCalendar NS_DESIGNATED_INITIALIZER;

/*!
 * @brief Specifies when, in an absolute time, the trigger should fire the first time.
 *
 * @discussion Timer triggers are only set at the beginning of a minute.  Seconds are
 *             not used and an error will be returned if the fire date includes a seconds
 *             value other than 0. When the timer fires, it will typically fire within 
 *             1 minute of the scheduled fire date or calculated recurrence fire date,
 *             depending on system power and resource management.
 */
@property(readonly, copy, nonatomic) NSDate *fireDate;

/*!
 * @brief Set the time zone to interpret the fire date in. 
 * 
 * @discussions If this value is nil and the user switches time zones, the time the trigger is 
 *              fired will be adjusted to account for the time zone change. If a trigger should
 *              be fired at the specified time in a specific time zone, regardless if the user
 *              switches time zones, set this value to the specific time zone. One common
 *              value may be the current time zone, e.g. to make the trigger fire at the
 *              desired time where the accessories are located, even if the user is traveling.
 */
@property(readonly, copy, nonatomic) NSTimeZone *timeZone;

/*!
 * @brief The date components that specify how a trigger is to be repeated. 
 *
 * @discussion This value may be nil if the trigger should not repeat. The date component
 *             values are relative to the initial fire date of the trigger. If the
 *             calendar value of the recurrence is nil, the current calendar
 *             will be used to calculate the repeat interval. Recurrence example: if a
 *             trigger should repeat every hour, set the 'hour' property of the
 *             recurrence to 1. The minimum repeat interval is 5 minutes and
 *             the repeat interval must be specified in multiples of whole minutes. An
 *             error will be returned if the repeat interval includes seconds. The repeat
 *             interval must be 5 weeks or less. Examples are 5 minutes, 6 minutes, 1 day, 
 *             2 weeks, and so on.
 *
 */
@property(readonly, copy, nonatomic) NSDateComponents *recurrence;

 /*!
  * @brief The calendar corresponding to a recurring timer trigger.
  */
@property(readonly, copy, nonatomic) NSCalendar *recurrenceCalendar;

/*!
 * @brief This method is used to change the fire date of a timer trigger.
 *
 * @param fireDate  New fire date for the trigger.
 *
 * @param completion  Block that is invoked once the request is processed.
 *                    The NSError provides more information on the status of the request,
 *                    error will be nil on success.
 */
- (void)updateFireDate:(NSDate *)fireDate completionHandler:(void (^)(NSError *error))completion;

/*!
 * @brief This method is used to change the time zone of the fire date of a timer trigger.
 *
 * @param timeZone New time zone for the trigger. Passing a nil indicates that the default
 *                   (system) timezone is used
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request,
 *                   error will be nil on success.
 */
- (void)updateTimeZone:(NSTimeZone *)timeZone completionHandler:(void (^)(NSError *error))completion;

/*!
 * @brief This method is used to change the recurrence interval for a timer trigger.
 *
 * @param recurrence New recurrence interval for the trigger. Passing a nil indicates that
 *                   the trigger is non-repeating
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request,
 *                   error will be nil on success.
 */
- (void)updateRecurrence:(NSDateComponents *)recurrence completionHandler:(void (^)(NSError *error))completion;

@end
