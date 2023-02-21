//
//  EKEventStore.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>
#import <EventKit/EKTypes.h>

@class EKCalendar, EKEvent, EKSource, EKReminder, EKCalendarItem;

/*!
    @enum           EKSpan
    @abstract       Values for controlling what occurrences to affect in a recurring event.
    @discussion     This enumerated type is used to indicate the scope of a change being made to a repeating event. EKSpanThisEvent 
                    indicates the changes should apply only to this event, EKSpanFutureEvents indicates the changes should apply to 
                    this event and all future events in the pattern.
    @constant       EKSpanThisEvent        Affect this event only.
    @constant       EKSpanFutureEvents     Affect this event and all after it.
*/

typedef enum {
    EKSpanThisEvent,
    EKSpanFutureEvents
} EKSpan;


/*!
    @enum       EKAuthorizationStatus
    @abstract   This enumerated type is used to indicate the currently granted authorization status for a specific
                entity type.
    @constant   EKAuthorizationStatusNotDetermined  The user has not yet made a choice regarding whether this application
                                                    may access the service.
    @constant   EKAuthorizationStatusRestricted     This application is not authorized to access the service.
                                                    The user cannot change this application’s status, possibly due to
                                                    active restrictions such as parental controls being in place.
    @constant   EKAuthorizationStatusDenied         The user explicitly denied access to the service for this application.
    @constant   EKAuthorizationStatusAuthorized     This application is authorized to access the service.
*/
typedef NS_ENUM(NSInteger, EKAuthorizationStatus) {
    EKAuthorizationStatusNotDetermined = 0,
    EKAuthorizationStatusRestricted,
    EKAuthorizationStatusDenied,
    EKAuthorizationStatusAuthorized,
} __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);


typedef void (^EKEventSearchCallback)(EKEvent *event, BOOL *stop);

/*!
    @class       EKEventStore
    @abstract    The EKEventStore class provides an interface for accessing and manipulating calendar events and reminders.
    @discussion  The EKEventStore class is the main point of contact for accessing Calendar data. You must
                 create a EKEventStore object in order to retrieve/add/delete events or reminders from the Calendar database.
                 
                 Events, Reminders, and Calendar objects retrieved from an event store cannot be used with any other event
                 store. It is generally best to hold onto a long-lived instance of an event store, most
                 likely as a singleton instance in your application.
*/
EVENTKIT_CLASS_AVAILABLE(10_8, 4_0)
@interface EKEventStore : NSObject

/*!
    @method     authorizationStatusForEntityType:
    @discussion Returns the authorization status for the given entity type
 */
+ (EKAuthorizationStatus)authorizationStatusForEntityType:(EKEntityType)entityType __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);


typedef void(^EKEventStoreRequestAccessCompletionHandler)(BOOL granted, NSError *error);

/*!
    @method     requestAccessToEntityType:completion:
    @discussion Users are able to grant or deny access to event and reminder data on a per-app basis. To request access to
                event and/or reminder data, call -requestAccessToEntityType:completion:. This will not block the app while
                the user is being asked to grant or deny access.
                
                Until access has been granted for an entity type, the event store will not contain any calendars for that
                entity type, and any attempt to save will fail. The user will only be prompted the first time access is
                requested; any subsequent instantiations of EKEventStore will use the existing permissions. When the user
                taps to grant or deny access, the completion handler will be called on an arbitrary queue.
*/
- (void)requestAccessToEntityType:(EKEntityType)entityType completion:(EKEventStoreRequestAccessCompletionHandler)completion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

/*!
    @property   eventStoreIdentifier
    @abstract   Returns a unique identifier string representing this calendar store.
*/
@property(nonatomic, readonly) NSString *eventStoreIdentifier;

//----------------------------------------------------
// SOURCES
//----------------------------------------------------

/*!
    @method     sources
    @abstract   Returns an unordered array of sources.
*/
- (NSArray *)sources __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

/*!
    @method     sourceWithIdentifier:
    @abstract   Returns a source with a specified identifier.
*/
- (EKSource *)sourceWithIdentifier:(NSString *)identifier __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

//----------------------------------------------------
// CALENDARS
//----------------------------------------------------

/*!
    @method     calendars
    @abstract   While this returns an array, the calendars are unordered. This call is deprecated
                 and only returns calendars that support events. If you want reminder calendars
                 you should use calendarsForEntityType:
*/
@property(nonatomic, readonly) NSArray *calendars __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_4_0,__IPHONE_6_0);

/*!
    @method     calendarsForEntityType
    @abstract   Returns calendars that support a given entity type (reminders, events)
 */
- (NSArray *)calendarsForEntityType:(EKEntityType)entityType __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

/*!
    @method     defaultCalendarForNewEvents
    @abstract   Returns the calendar that events should be added to by default, as set in the Settings application.
*/
@property(nonatomic, readonly) EKCalendar *defaultCalendarForNewEvents;

/*!
    @method     defaultCalendarForNewReminders
    @abstract   Returns the calendar that reminders should be added to by default, as set in the Settings application.
*/
- (EKCalendar *)defaultCalendarForNewReminders __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

/*!
    @method     calendarWithIdentifier:
    @abstract   Returns a calendar with a specified identifier.
*/
- (EKCalendar *)calendarWithIdentifier:(NSString *)identifier __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

/*!
    @method     saveCalendar:commit:error:
    @abstract   Saves changes to a calendar, or adds a new calendar to the database.
    @discussion This method attempts to save the given calendar to the calendar database. It
                returns YES if successful and NO otherwise. Passing a calendar fetched from
                another EKEventStore instance into this function will raise an exception.

    @param      calendar    The calendar to save.
    @param      commit      Pass YES to cause the database to save. You can pass NO to save multiple
                            calendars and then call commit: to save them all at once.
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/

- (BOOL)saveCalendar:(EKCalendar *)calendar commit:(BOOL)commit error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

/*!
    @method     removeCalendar:commit:error:
    @abstract   Removes a calendar from the database.
    @discussion This method attempts to delete the given calendar from the calendar database. It
                returns YES if successful and NO otherwise. Passing a calendar fetched from
                another EKEventStore instance into this function will raise an exception.

    @param      calendar    The calendar to delete.
    @param      commit      Pass YES to cause the database to save. You can pass NO to batch multiple
                            changes and then call commit: to save them all at once.
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/

- (BOOL)removeCalendar:(EKCalendar *)calendar commit:(BOOL)commit error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

//----------------------------------------------------
// CALENDAR ITEMS (apply to both reminders and events)
//----------------------------------------------------

/*!
    @method     calendarItemWithIdentifier:
    @abstract   Returns either a reminder or the first occurrence of an event.
*/
- (EKCalendarItem *)calendarItemWithIdentifier:(NSString *)identifier __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

/*!
    @method     calendarItemsWithExternalIdentifier:
    @abstract   Returns either matching reminders or the first occurrences of any events matching
                the given external identifier.
    @discussion This method returns a set of EKEvents or EKReminders with the given external identifier.
                Due to reasons discussed in -[EKCalendarItem calendarItemExternalIdentifier], there may be
                more than one matching calendar item.
 
    @param      externalIdentifier  The value obtained from EKCalendarItem's
                calendarItemExternalIdentifier property
    @result     An unsorted array of EKCalendarItem instances
*/
- (NSArray *)calendarItemsWithExternalIdentifier:(NSString *)externalIdentifier __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

//----------------------------------------------------
// EVENTS
//----------------------------------------------------

/*!
    @method     saveEvent:span:error:
    @abstract   Saves changes to an event permanently.
    @discussion This method attempts to save the event to the calendar database. It returns YES if
                successful and NO otherwise. It's possible for this method to return NO, and error
                will be set to nil. This occurs if the event wasn't dirty and didn't need saving. This
                means the correct way to detect failure is a result of NO and a non-nil error parameter.
                Passing an event fetched from another EKEventStore instance into this function will
                raise an exception.
                
                After an event is successfully saved, it is also put into sync with the database, meaning
                that all fields you did not change will be updated to the latest values. If you save the
                event, but it was deleted by a different store/process, you will effectively recreate the
                event as a new event.
 
    @param      event       The event to save.
    @param      span        The span to use (this event, or this and future events).
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/
- (BOOL)saveEvent:(EKEvent *)event span:(EKSpan)span error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

/*!
    @method     removeEvent:span:error:
    @abstract   Removes an event from the calendar store.
    @discussion This method attempts to remove the event from the calendar database. It returns YES if
                successful and NO otherwise. It's possible for this method to return NO, and error
                will be set to nil. This occurs if the event wasn't ever added and didn't need removing. This
                means the correct way to detect failure is a result of NO and a non-nil error parameter.
                Passing an event from another CalendarStore into this function will raise an exception. After
                an event is removed, it is no longer tied to this calendar store, and all data in the event
                is cleared except for the eventIdentifier.
 
    @param      event       The event to save.
    @param      span        The span to use (this event, or this and future events).
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/
- (BOOL)removeEvent:(EKEvent *)event span:(EKSpan)span error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

// These variants of the above allow you to batch changes by passing NO to commit. You can commit
// all changes later with [EKEventStore commit:]
- (BOOL)saveEvent:(EKEvent *)event span:(EKSpan)span commit:(BOOL)commit error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);
- (BOOL)removeEvent:(EKEvent *)event span:(EKSpan)span commit:(BOOL)commit error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

/*!
    @method     eventWithIdentifier:
    @abstract   Returns the first occurrence of an event matching the given event identifier.
 
    @param      identifier   The eventIdentifier to search for.
    @result     An EKEvent object, or nil if not found.
*/
- (EKEvent *)eventWithIdentifier:(NSString *)identifier;

/*!
    @method     eventsMatchingPredicate:
    @abstract   Searches for events that match the given predicate.
    @discussion This call executes a search for the events indicated by the predicate passed to it.
                It only includes events which have been committed (e.g. those saved using 
                saveEvent:commit:NO are not included until commit: is called.)
 
                It is synchronous. If you want async behavior, you should either use dispatch_async or
                NSOperation to run the query someplace other than the main thread, and then funnel the
                array back to the main thread.
 
    @param      predicate   The predicate to invoke. If this predicate was not created with the predicate
                            creation functions in this class, an exception is raised.
    @result     An array of EKEvent objects, or nil. There is no guaranteed order to the events.
*/
- (NSArray *)eventsMatchingPredicate:(NSPredicate *)predicate;

/*!
    @method     enumerateEventsMatchingPredicate:usingBlock:
    @abstract   Searches for events that match the given predicate.
    @discussion This call executes a search for the events indicated by the predicate passed to it, calling
                the block specified in the callback parameter for each event. It only includes events which 
                have been committed (e.g. those saved using saveEvent:commit:NO are not included until commit: is called.)
 
                This method is synchronous. If you want async behavior, you should either use dispatch_async or
                NSOperation to run the query someplace other than the main thread.
 
    @param      predicate   The predicate to invoke. If this predicate was not created with the predicate
                            creation functions in this class, an exception is raised.
    @param      block       The block to call for each event. Your block should return YES in the stop
                            parameter to stop iterating.
*/
- (void)enumerateEventsMatchingPredicate:(NSPredicate *)predicate usingBlock:(EKEventSearchCallback)block;

/*!
    @method     predicateForEventsWithStartDate:endDate:calendars:
    @abstract   Creates a predicate for use with eventsMatchingPredicate or enumerateEventsMatchingPredicate:usingBlock:.
    @discussion Creates a simple query predicate to search for events within a certain date range. At present,
                this will return events in the default time zone ([NSTimeZone defaultTimeZone]).
 
    @param      startDate   The start date.
    @param      endDate     The end date.
    @param      calendars   The calendars to search for events in, or nil to search all calendars.
*/
- (NSPredicate *)predicateForEventsWithStartDate:(NSDate *)startDate endDate:(NSDate *)endDate calendars:(NSArray *)calendars;

//----------------------------------------------------
// REMINDERS
//----------------------------------------------------

/*!
    @method     saveReminder:commit:error:
    @abstract   Saves changes to a reminder.
    @discussion This method attempts to save the reminder to the event store database. It returns YES if
                successful and NO otherwise. Passing a reminder fetched from another EKEventStore instance
                into this function will raise an exception.

                After a reminder is successfully saved, its fields are updated to the latest values in
                the database.

    @param      reminder    The reminder to save.
    @param      commit      Whether to save to the database or not. Pass NO to batch changes together and
                            commit with [EKEventStore commit:].
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/
- (BOOL)saveReminder:(EKReminder *)reminder commit:(BOOL)commit error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

/*!
    @method     removeReminder:commit:error:
    @abstract   Removes a reminder from the event store.
    @discussion This method attempts to remove the reminder from the event store database. It returns YES if
                successful and NO otherwise. Passing a reminder from another EKEventStore into this function
                will raise an exception. After a reminder is removed, it is no longer tied to this event store.

    @param      reminder    The reminder to save.
    @param      commit      Whether to save to the database or not. Pass NO to batch changes together and
                            commit with [EKEventStore commit:].
    @param      error       If an error occurs, this will contain a valid NSError object on exit.
*/
- (BOOL)removeReminder:(EKReminder *)reminder commit:(BOOL)commit error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

/*!
    @method     fetchRemindersMatchingPredicate:completion:
    @abstract   Fetches reminders asynchronously.
    @discussion This method fetches reminders asynchronously and returns a value which can be
                used in cancelFetchRequest: to cancel the request later if desired. The completion
                block is called with an array of reminders that match the given predicate (or potentially nil).
                This only includes reminders which have been committed (e.g. those saved using 
                saveReminder:commit:NO are not included until commit: is called.)
*/
- (id)fetchRemindersMatchingPredicate:(NSPredicate *)predicate completion:(void (^)(NSArray *))completion __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

/*!
    @method     cancelFetchRequest:
    @discussion Given a value returned from fetchRemindersMatchingPredicate, this method can be used to
                cancel the request. Once called, the completion block specified in fetchReminders... will
                not be called.
*/
- (void)cancelFetchRequest:(id)fetchIdentifier __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

/*!
    @method     predicateForRemindersInCalendars:
    @abstract   Fetch all reminders in a set of calendars.
*/
- (NSPredicate *)predicateForRemindersInCalendars:(NSArray *)calendars __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

/*!
    @method     predicateForIncompleteRemindersWithDueDateStarting:ending:calendars:
    @abstract   Fetch incomplete reminders in a set of calendars.
    @discussion You can use this method to search for incomplete reminders due in a range.
                You can pass nil for start date to find all reminders due before endDate.
                You can pass nil for both start and end date to get all incomplete reminders
                in the specified calendars.
*/
- (NSPredicate *)predicateForIncompleteRemindersWithDueDateStarting:(NSDate *)startDate ending:(NSDate *)endDate calendars:(NSArray *)calendars __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);


/*!
    @method     predicateForCompletedRemindersWithCompletionDateStarting:ending:calendars:
    @abstract   Fetch completed reminders in a set of calendars.
    @discussion You can use this method to search for reminders completed between a range of dates.
                You can pass nil for start date to find all reminders completed before endDate.
                You can pass nil for both start and end date to get all completed reminders
                in the specified calendars.
*/
- (NSPredicate *)predicateForCompletedRemindersWithCompletionDateStarting:(NSDate *)startDate ending:(NSDate *)endDate calendars:(NSArray *)calendars __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

//----------------------------------------------------
// COMMIT, RESET, ROLLBACK
//----------------------------------------------------

/*!
    @method     commit:
    @abstract   Commits pending changes to the database.
    @discussion If you use saveCalendar/saveEvent/removeCalendar/removeEvent, etc. and you pass NO to their
                parameter, you are batching changes for a later commit. This method does that commit. This
                allows you to save the database only once for many additions or changes.  If you pass
                YES to methods' commit parameter, then you don't need to call this method.
 
                This method will return YES as long as nothing went awry, even if nothing was actually
                committed. If it returns NO, error should contain the reason it became unhappy.
*/
- (BOOL)commit:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

/*!
    @method     reset
    @abstract   Resets the event store.
    @discussion You can use this method to forget ALL changes made to the event store (all additions, all
                fetched objects, etc.). It essentially is as if you released the store and then created a
                new one. It brings it back to its initial state. All objects ever created/fetched, etc.
                using this store are no longer connected to it and are considered invalid.
*/
- (void)reset __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

/*!
    @method     refreshSourcesIfNecessary
    @abstract   Cause a sync to potentially occur taking into account the necessity of it.
    @discussion You can call this method to pull new data from remote sources.  
                This only updates the event store's data.  If you want to update your objects after 
                refreshing the sources, you should call refresh on each of them afterwards.
                On iOS, this sync only occurs if deemed necessary.  
                On OS X, this will occur regardless of necessity, but may change in a future release to match the iOS behavior.
 */
- (void)refreshSourcesIfNecessary __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

@end

/*!
    @constant   EKEventStoreChangedNotification
    @discussion Notification name sent out when the database is changed by either an external process,
                another event store in the same process, or by calling saveEvent: or removeEvent: on a
                store you are managing. When you receive this notification, you should consider all EKEvent
                instances you have to be invalid. If you had selected events for a date range using
                eventsMatchingPredicate, etc. for display, you should release them and re-fetch the events
                again. If you have an event you are actively using (e.g. you are currently viewing details
                for it or editing it), you can call [EKEvent refresh] to try to revalidate it against the
                latest state of the database. If that method returns YES, you can continue to use the event,
                otherwise, you should release it and abandon what you were doing with it. The view
                controllers provided by EventKitUI automatically deal with this for you.
                This notification will also be posted if access to events or reminders is changed by the user.
*/
EVENTKIT_EXTERN NSString *const EKEventStoreChangedNotification __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_4_0);

