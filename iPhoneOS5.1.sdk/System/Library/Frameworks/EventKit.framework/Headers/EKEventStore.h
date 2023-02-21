//
//  EKEventStore.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>

@class EKCalendar, EKEvent, EKSource;

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

typedef void (^EKEventSearchCallback)(EKEvent *event, BOOL *stop);

/*!
    @class       EKEventStore
    @abstract    The EKEventStore class provides an interface for accessing and manipulating calendar events.
    @discussion  The EKEventStore class is the main point of contact for accessing Calendar data. You must
                 create a EKEventStore object in order to retrieve/add/delete events from the Calendar database.
                 
                 Events and Calendar objects gotten from an event store cannot be used with any other event
                 store. It is generally best to hold onto a long-lived instance of an event store, most
                 likely as a singleton instance in your application.
*/

EVENTKIT_CLASS_AVAILABLE(4_0)
@interface EKEventStore : NSObject

/*!
    @property   uniqueIdentifier
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
- (NSArray *)sources __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @method     sourceWithIdentifier:
    @abstract   Returns a source with a specified identifier.
*/
- (EKSource *)sourceWithIdentifier:(NSString *)identifier __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

//----------------------------------------------------
// CALENDARS
//----------------------------------------------------

/*!
     @method     defaultCalendarForNewEvents
     @abstract   While this returns an array, the calendars are unordered.
*/
@property(nonatomic, readonly) NSArray *calendars;

/*!
     @method     defaultCalendarForNewEvents
     @abstract   Returns the calendar that events should be added to by default, as set in the Settings application.
*/

@property(nonatomic, readonly) EKCalendar *defaultCalendarForNewEvents;

/*!
    @method     calendarWithIdentifier:
    @abstract   Returns a calendar with a specified identifier.
*/
- (EKCalendar *)calendarWithIdentifier:(NSString *)identifier __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

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

- (BOOL)saveCalendar:(EKCalendar *)calendar commit:(BOOL)commit error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

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

- (BOOL)removeCalendar:(EKCalendar *)calendar commit:(BOOL)commit error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

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
- (BOOL)saveEvent:(EKEvent *)event span:(EKSpan)span error:(NSError **)error;

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
- (BOOL)removeEvent:(EKEvent *)event span:(EKSpan)span error:(NSError **)error;

// These variants of the above allow you to batch changes by passing NO to commit. You can commit
// all changes later with [EKEventStore commit:]
- (BOOL)saveEvent:(EKEvent *)event span:(EKSpan)span commit:(BOOL)commit error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
- (BOOL)removeEvent:(EKEvent *)event span:(EKSpan)span commit:(BOOL)commit error:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @method     eventWithIdentifier:
    @abstract   Returns the first occurrence of an event matching the given event identifier.
 
    @param      identifier   The uid to search for.
    @result     An EKEvent object, or nil if not found.
*/
- (EKEvent *)eventWithIdentifier:(NSString *)identifier;

/*!
    @method     eventsMatchingPredicate:
    @abstract   Searches for events that match the given predicate.
    @discussion This call executes a search for the events indicated by the predicate passed to it.
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
                the block specified in the callback parameter for each event. This method is synchronous.
                If you want async behavior, you should either use dispatch_async or NSOperation to run the
                query someplace other than the main thread.
 
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
// COMMIT, RESET, ROLLBACK
//----------------------------------------------------

/*!
    @method     commit:
    @abstract   Commits pending changes to the database.
    @discussion If you use saveCalendar/saveEvent/removeCalendar/removeEvent, etc. and you pass NO to their
                parameter, you are batching changes for a later commit. This method does that commit. This
                allows you to save the database only once for many additions or changes.
 
                This method will return YES as long as nothing went awry, even if nothing was actually
                committed. If it returns NO, error should contain the reason it became unhappy.
*/
- (BOOL)commit:(NSError **)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);


/*!
    @method     reset
    @abstract   Resets the event store.
    @discussion You can use this method to forget ALL changes made to the event store (all additions, all
                fetched objects, etc.). It essentially is as if you released the store and then created a
                new one. It brings it back to its initial state. All objects ever created/fetched, etc.
                using this store are no longer connected to it and are considered invalid.
*/
- (void)reset __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @method     refreshSourcesIfNecessary
    @abstract   Cause a sync to occur if one is deemed necessary.
    @discussion You can call this method to try to pull new data from remote sources if we're out of date.
*/

- (void)refreshSourcesIfNecessary __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

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
*/
EVENTKIT_EXTERN NSString *const EKEventStoreChangedNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

