//
//  UIAccessibilityConstants.h
//  UIKit
//
//  Copyright (c) 2009-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*
 Accessibility Traits
 
 Traits are combined in a mask to help assistive applications understand
 the meaning and intended use of a particular accessibility element.
 
 UIKit applies appropriate traits to all standard controls, however the
 following traits may be used in conjunction with custom controls.
 
 When setting accessiblity traits, combine custom traits with 
 [super accessibilityTraits]. An incorrect combination of custom traits
 will cause accessibility clients to incorrectly interpret the element.
 Use common sense when combining traits.
 */
typedef uint64_t UIAccessibilityTraits;

// Used when the element has no traits.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitNone;

// Used when the element should be treated as a button.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitButton;

// Used when the element should be treated as a link.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitLink;

// Used when an element acts as a header for a content section (e.g. the title of a navigation bar).
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitHeader NS_AVAILABLE_IOS(6_0);

// Used when the text field element should also be treated as a search field.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitSearchField;

// Used when the element should be treated as an image. Can be combined with button or link, for example.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitImage;

/*
 Used when the element is selected.
 For example, a selected row in a table or a selected button within a segmented control.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitSelected;

// Used when the element plays its own sound when activated.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitPlaysSound;

// Used when the element acts as a keyboard key.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitKeyboardKey;

// Used when the element should be treated as static text that cannot change.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitStaticText;

/*
 Used when an element can be used to provide a quick summary of current 
 conditions in the app when the app first launches.  For example, when Weather
 first launches, the element with today's weather conditions is marked with
 this trait.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitSummaryElement;

// Used when the control is not enabled and does not respond to user input.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitNotEnabled;

/*
 Used when the element frequently updates its label or value, but too often to send notifications. 
 Allows an accessibility client to poll for changes. A stopwatch would be an example.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitUpdatesFrequently;

/*
 Used when activating an element starts a media session (e.g. playing a movie, recording audio) 
 that should not be interrupted by output from an assistive technology, like VoiceOver.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitStartsMediaSession NS_AVAILABLE_IOS(4_0);

/*
 Used when an element can be "adjusted" (e.g. a slider). The element must also 
 implement accessibilityIncrement and accessibilityDecrement.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitAdjustable NS_AVAILABLE_IOS(4_0);

// Used when an element allows direct touch interaction for VoiceOver users (for example, a view representing a piano keyboard).
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitAllowsDirectInteraction NS_AVAILABLE_IOS(5_0);

/*
 Informs VoiceOver that it should scroll to the next page when it finishes reading the contents of the
 element. VoiceOver will scroll by calling accessibilityScroll: with UIAccessibilityScrollDirectionNext and will 
 stop scrolling when it detects the content has not changed.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitCausesPageTurn NS_AVAILABLE_IOS(5_0);

/*
 Accessibility Notifications
 
 UIKit posts notifications for standard events as appropriate, however the
 following notifications may be posted to accommodate custom controls
 and events.
 */
typedef uint32_t UIAccessibilityNotifications;

/*
 Should be posted when a new view appears that encompasses a major portion of the screen.
 Optionally, pass the element that VoiceOver should move to after processing the notification.
 */
UIKIT_EXTERN UIAccessibilityNotifications UIAccessibilityScreenChangedNotification;

/*
 Should be posted when the layout of a screen changes, for example when an individual
 element appears or disappears.
 Optionally, pass the element that VoiceOver should move to after processing the notification.
 */
UIKIT_EXTERN UIAccessibilityNotifications UIAccessibilityLayoutChangedNotification;

/*
 Should be posted when an announcement needs to be conveyed to VoiceOver. 
 VoiceOver will output the announcement string that is used as the argument.
 The argument is a NSString.
 */
UIKIT_EXTERN UIAccessibilityNotifications UIAccessibilityAnnouncementNotification NS_AVAILABLE_IOS(4_0);

/*
 Listen for this notification to know when VoiceOver finishes outputting an announcement. 
 The userInfo dictionary contains UIAccessibilityAnnouncementKeyString and UIAccessibilityAnnouncementKeyWasSuccessful.
 */
UIKIT_EXTERN NSString *const UIAccessibilityAnnouncementDidFinishNotification NS_AVAILABLE_IOS(6_0);

// The corresponding value is the string that was used for the announcement.
UIKIT_EXTERN NSString *const UIAccessibilityAnnouncementKeyStringValue NS_AVAILABLE_IOS(6_0);

// The corresponding value is an NSNumber representing whether VoiceOver successfully outputted the announcement.
UIKIT_EXTERN NSString *const UIAccessibilityAnnouncementKeyWasSuccessful NS_AVAILABLE_IOS(6_0);


// In order to know when an assistive technology has focused on an element listen to this notification
// The newly focused element will be referenced by UIAccessibilityElementFocusedKeyElement in the userInfo dictionary.
UIKIT_EXTERN NSString *const UIAccessibilityElementFocusedNotification NS_AVAILABLE_IOS(9_0);

// The corresponding value is the element that is now focused by the assistive technology.
UIKIT_EXTERN NSString *const UIAccessibilityFocusedElementKey NS_AVAILABLE_IOS(9_0);

// The corresponding value is the element that had previously been focused by the assistive technology.
UIKIT_EXTERN NSString *const UIAccessibilityUnfocusedElementKey NS_AVAILABLE_IOS(9_0);

// The corresponding value is the identifier of the assistive technology
UIKIT_EXTERN NSString *const UIAccessibilityAssistiveTechnologyKey NS_AVAILABLE_IOS(9_0);

/*
 Should be posted after accessibilityScroll: is called and the scrolling action has completed. 
 A string representing the status of the new scroll position should be used as the argument 
 (e.g. "Page 2 of 5"). If the same status is used repeatedly, the assistive technology will 
 indicate a border has been reached.
 The argument is a NSString.
 */
UIKIT_EXTERN UIAccessibilityNotifications UIAccessibilityPageScrolledNotification NS_AVAILABLE_IOS(4_2);

/*
 Should be posted to pause an assistive technology's operations temporarily.
 For example, you may want to pause scanning in Switch Control while your app plays an animation.
 An identifier representing the assistive technology should be used as the argument.
 Currently, these notifications only apply to Switch Control.
 The notifications must be balanced.  That is, every UIAccessibilityPauseAssistiveTechnologyNotification
 should be followed by a matching UIAccessibilityResumeAssistiveTechnologyNotification with the same argument.
 If the user performs an action that requires the assistive technology to resume operations,
 it may do so before it receives the corresponding UIAccessibilityResumeAssistiveTechnologyNotification.
 The argument is a NSString.
 */
UIKIT_EXTERN UIAccessibilityNotifications UIAccessibilityPauseAssistiveTechnologyNotification NS_AVAILABLE_IOS(8_0);
UIKIT_EXTERN UIAccessibilityNotifications UIAccessibilityResumeAssistiveTechnologyNotification NS_AVAILABLE_IOS(8_0);

/*
 The following identifier should be used as the argument when posting a UIAccessibilityPauseAssistiveTechnologyNotification
 or a UIAccessibilityResumeAssistiveTechnologyNotification.
 */
UIKIT_EXTERN NSString *const UIAccessibilityNotificationSwitchControlIdentifier NS_AVAILABLE_IOS(8_0);

// Used to identify VoiceOver as the assistive technology.
UIKIT_EXTERN NSString *const UIAccessibilityNotificationVoiceOverIdentifier NS_AVAILABLE_IOS(9_0);


/*
 The following values describe how the receiver's elements should be navigated by an assistive technology.
 */
typedef NS_ENUM(NSInteger, UIAccessibilityNavigationStyle) {
    /*
     The assistive technology will automatically determine how the receiver's elements should be navigated.
     This is the default value.
     */
    UIAccessibilityNavigationStyleAutomatic = 0,
    
    /*
     The receiver's elements should be navigated as separate elements.
     */
    UIAccessibilityNavigationStyleSeparate = 1,
    
    /*
     The receiver???s elements should be combined and navigated as a single item.
     When the combined item has been selected, the assistive technology will navigate each element separately.
     */
    UIAccessibilityNavigationStyleCombined = 2,
} NS_ENUM_AVAILABLE_IOS(8_0);

/*
 Accessibility Speech Attributes
 
 The following attributes can be used in an NSAttributedString to modify how
 an assistive technology like VoiceOver will pronounce the string.
 */

// Use an NSNumber with a YES or NO value.
// If YES, then all punctuation will be spoken (e.g. when displaying code).
// If NO, then no punctuation will be spoken.
// By default, if this attribute is not present, the user's settings will be used.
UIKIT_EXTERN NSString *const UIAccessibilitySpeechAttributePunctuation NS_AVAILABLE_IOS(7_0);

// Use an NSString with a BCP-47 language code to identify the language of a segment of a string.
UIKIT_EXTERN NSString *const UIAccessibilitySpeechAttributeLanguage NS_AVAILABLE_IOS(7_0);

// Use an NSNumber with a value between [0-2] that specifies the pitch.
// For example, you may want to lower the pitch when an object is deleted, or raise the pitch if an object is inserted.
// Default value == 1.0f.
UIKIT_EXTERN NSString *const UIAccessibilitySpeechAttributePitch NS_AVAILABLE_IOS(7_0);

NS_ASSUME_NONNULL_END

