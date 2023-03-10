//
//  EKCalendarChooser.h
//  EventKitUI
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EventKitUI/EventKitUIDefines.h>
#import <EventKit/EventKit.h>

typedef enum {
    EKCalendarChooserSelectionStyleSingle,
    EKCalendarChooserSelectionStyleMultiple
} EKCalendarChooserSelectionStyle;

typedef enum {
    EKCalendarChooserDisplayAllCalendars,
    EKCalendarChooserDisplayWritableCalendarsOnly
} EKCalendarChooserDisplayStyle;

@protocol EKCalendarChooserDelegate;

EVENTKITUI_CLASS_AVAILABLE(5_0)
@interface EKCalendarChooser : UIViewController

- (id)initWithSelectionStyle:(EKCalendarChooserSelectionStyle)selectionStyle
                displayStyle:(EKCalendarChooserDisplayStyle)displayStyle
                  eventStore:(EKEventStore *)eventStore;

@property(nonatomic, readonly) EKCalendarChooserSelectionStyle    selectionStyle;

@property(nonatomic, assign) id<EKCalendarChooserDelegate>        delegate;

// When used in a navigation controller (presented modally), you can enable
// the done/cancel buttons and get informed when pressed via the delegate.
@property(nonatomic) BOOL showsDoneButton;
@property(nonatomic) BOOL showsCancelButton;

// Regardless of whether the chooser allows you to select one or multiple
// calendars, the selection is always expressed as a set.
@property(nonatomic, copy) NSSet    *selectedCalendars;

@end

@protocol EKCalendarChooserDelegate <NSObject>
@optional

// Called whenever the selection is changed by the user
- (void)calendarChooserSelectionDidChange:(EKCalendarChooser *)calendarChooser;

// These are called when the corresponding button is pressed to dismiss the
// controller. It is up to the recipient to dismiss the chooser.
- (void)calendarChooserDidFinish:(EKCalendarChooser *)calendarChooser;
- (void)calendarChooserDidCancel:(EKCalendarChooser *)calendarChooser;

@end
