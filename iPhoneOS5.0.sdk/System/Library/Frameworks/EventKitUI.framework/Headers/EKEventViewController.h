//
//  EKEventViewController.h
//  EventKitUI
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EventKitUI/EventKitUIDefines.h>

@class EKEvent, EKEventStore;

typedef enum {
    EKEventViewActionDone,                  // simply closed
    EKEventViewActionResponded,             // event invitation was responded to and saved
    EKEventViewActionDeleted,               // event was deleted
} EKEventViewAction;

/*!
    @class      EKEventViewController
    @abstract   View controller to view event detail.
    @discussion You can use this view controller to display the details of an event. You
                can also optionally choose to allow the user to edit the event by displaying
                an edit button. While you can use this view controller to display events that
                have not been saved, the edit button will not appear in this situation. If
                you have pushed this view controller onto a navigation controller stack, and
                the underlying event gets deleted, this controller will remove itself from
                the stack and clear its event property.
*/
@protocol EKEventViewDelegate;

EVENTKITUI_CLASS_AVAILABLE(4_0)
@interface EKEventViewController : UIViewController {
@private
    EKEvent                *_event;
    NSString               *_eventId;
    UIActionSheet*          _alertSheet;
    int                     _pendingStatus;
	
    id<EKEventViewDelegate> _delegate;
    id                      _editor;
    
    UIButton*               _responseButtons[3];
    UIToolbar              *_buttonBar;
    UIInterfaceOrientation  _lastOrientation;
    
    id                      _currentEditItem;
    UITableView            *_tableView;

    unsigned                _didAppear:1;
    unsigned                _autoPop:1;
    unsigned                _allowsEditing:1;
    unsigned                _allowsSubitems:1;
    unsigned                _showsPreview:1;
    unsigned                _forcePreview:1;
    unsigned                _trustsStatus:1;
    unsigned                _allowsInviteResponses:1;
    unsigned                _showsAddToCalendar:1;
    unsigned                _icsPreview:1;
    unsigned                _needsReload:1;    
    
    NSArray                *_items;
    NSArray                *_currentSections;
    
    int                     _scrollToSection;    
}

@property(nonatomic, assign) id<EKEventViewDelegate>  delegate __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_2);

/*!
    @property   event
    @abstract   Specifies the event to view.
    @discussion You must set this prior to displaying the view controller.
*/
@property(nonatomic, retain) EKEvent *event;

/*!
    @property   allowsEditing
    @abstract   Determines whether Edit button can be shown. 
    @discussion Note that even if this is enabled, the edit button may not appear if this event
                is in a read-only calendar, such as a subscribed calendar. It may also not appear
                if the event was not created by the current user (i.e. it's an event they were
                invited to). And lastly, if the event was never saved, the edit button will not
                appear.
*/
@property(nonatomic) BOOL      allowsEditing;

/*!
    @property   allowsCalendarPreview
    @abstract   Determines whether event can be shown in calendar day view preview.
    @discussion This option only affects calendar invites at present. If the event is an invite,
                and this option is set, a table cell will appear that allows the user to preview 
                the event along with their other events for the day.
*/
@property(nonatomic) BOOL      allowsCalendarPreview;

@end


@protocol EKEventViewDelegate <NSObject>
@required

/*!
 @method     eventViewController:didCompleteWithAction:
 @abstract   Called to let delegate know that an action has occurred that should cause the
             controller to be dismissed.
 @discussion If the user taps a button which deletes the event, or responds to an invite, this
             method is called on the delegate so that the delegate can decide to dismiss
             the view controller. When presented in a popover, it also reports when the Done
             button is pressed.
 
 @param      controller          the controller in question
 @param      action              the action that is triggering the dismissal
 */
- (void)eventViewController:(EKEventViewController *)controller didCompleteWithAction:(EKEventViewAction)action __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_2);

@end

