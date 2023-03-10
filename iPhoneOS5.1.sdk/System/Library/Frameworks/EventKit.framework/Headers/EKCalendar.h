//
//  EKCalendar.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <EventKit/EKTypes.h>

@class EKEventStore, EKSource;

/*!
    @class       EKCalendar
    @abstract    The EKCalendar class represents a calendar for events.
*/

EVENTKIT_CLASS_AVAILABLE(4_0)
@interface EKCalendar : EKObject

// Create a new calendar in the specified event store.
+ (EKCalendar*)calendarWithEventStore:(EKEventStore *)eventStore;

/*!
    @property   source
    @abstract   The source representing the 'account' this calendar belongs to.
                This is only settable when initially creating a calendar and then
                effectively read-only after that in iOS 5.0. That is, you can create
                a calendar, but you cannot move it to another source.
*/
@property(nonatomic, retain) EKSource        *source;

/*!
    @property   calendarIdentifier
    @abstract   A unique identifier for the calendar. It is not sync-proof in that a full
                sync will lose this identifier, so you should always have a back up plan for dealing
                with a calendar that is no longer fetchable by this property, e.g. by title, type, color, etc.
                Use [EKEventStore calendarWithIdentifier:] to look up the calendar by this value.
*/
@property(nonatomic, readonly) NSString         *calendarIdentifier __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @property   title
    @abstract   The title of the calendar.
*/
@property(nonatomic, copy)     NSString          *title;

/*!
    @property   type
    @abstract   The type of the calendar as a EKCalendarType. This is actually based on
                what source the calendar is in, as well as whether it is a subscribed
                calendar.
*/
@property(nonatomic, readonly)     EKCalendarType     type;


/*!
    @property   allowsContentModifications
    @abstract   Represents whether you can this add, remove, or modify items in this calendar.
*/
@property(nonatomic, readonly) BOOL allowsContentModifications;


/*!
    @property   subscribed
    @abstract   YES if this calendar is a subscribed calendar.
*/
@property(nonatomic, readonly, getter=isSubscribed) BOOL subscribed __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @property   immutable
    @abstract   If this is set to YES, it means you cannot modify any attributes of
                the calendar or delete it. It does NOT imply that you cannot add events
                to the calendar.
*/
@property(nonatomic, readonly, getter=isImmutable) BOOL immutable __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @property   color
    @abstract   Returns the calendar color as a CGColorRef.
*/
@property(nonatomic) CGColorRef      CGColor;

/*!
    @property   supportedEventAvailabilities
    @discussion Returns a bitfield of supported event availabilities, or EKCalendarEventAvailabilityNone
                if this calendar does not support setting availability on an event.
*/
@property(nonatomic, readonly) EKCalendarEventAvailabilityMask supportedEventAvailabilities;

@end
