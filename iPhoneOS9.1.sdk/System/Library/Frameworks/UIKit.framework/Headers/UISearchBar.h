//
//  UISearchBar.h
//  UIKit
//
//  Copyright (c) 2008-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UITextField.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIBarButtonItem.h>
#import <UIKit/UIBarCommon.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UISearchBarIcon) {
    UISearchBarIconSearch, // The magnifying glass
    UISearchBarIconClear, // The circle with an x in it
    UISearchBarIconBookmark, // The open book icon
    UISearchBarIconResultsList, // The list lozenge icon
};

typedef NS_ENUM(NSUInteger, UISearchBarStyle) {
    UISearchBarStyleDefault,    // currently UISearchBarStyleProminent
    UISearchBarStyleProminent,  // used my Mail, Messages and Contacts
    UISearchBarStyleMinimal     // used by Calendar, Notes and Music
} NS_ENUM_AVAILABLE_IOS(7_0);


@protocol UISearchBarDelegate;
@class UITextField, UILabel, UIButton, UIColor;

/*
 UISearchBar officially conformed to UITextInputTraits in iOS 8.0 and privately conformed in iOS 7.0. Prior to 7.0, UISearchBar only implemented these four traits: autocapitalizationType, autocorrectionType, spellCheckingType and keyboardType. If your deployment target is <7.0 and you are using any trait other than one of the four mentioned, you must check its availability with respondsToSelector:
 */

NS_CLASS_AVAILABLE_IOS(2_0) @interface UISearchBar : UIView <UIBarPositioning, UITextInputTraits>

- (instancetype)init __TVOS_PROHIBITED;
- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER __TVOS_PROHIBITED;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER __TVOS_PROHIBITED;

@property(nonatomic)        UIBarStyle              barStyle __TVOS_PROHIBITED;              // default is UIBarStyleDefault (blue)
@property(nullable,nonatomic,weak) id<UISearchBarDelegate> delegate;              // weak reference. default is nil
@property(nullable,nonatomic,copy)   NSString               *text;                  // current/starting search text
@property(nullable,nonatomic,copy)   NSString               *prompt;                // default is nil
@property(nullable,nonatomic,copy)   NSString               *placeholder;           // default is nil
@property(nonatomic)        BOOL                    showsBookmarkButton;   // default is NO
@property(nonatomic)        BOOL                    showsCancelButton;     // default is NO
@property(nonatomic)        BOOL                    showsSearchResultsButton NS_AVAILABLE_IOS(3_2); // default is NO
@property(nonatomic, getter=isSearchResultsButtonSelected) BOOL searchResultsButtonSelected NS_AVAILABLE_IOS(3_2); // default is NO
- (void)setShowsCancelButton:(BOOL)showsCancelButton animated:(BOOL)animated NS_AVAILABLE_IOS(3_0);

/// Use this method to modify the contents of the Unified Content Bar, shown on top of the keyboard when search is engaged.
/// You may modify the returned inputAssistantItem to add to or replace the existing items on the bar.
/// Modifications made to the returned UITextInputAssistantItem are reflected automatically.
@property (nonatomic, readonly, strong) UITextInputAssistantItem *inputAssistantItem NS_AVAILABLE_IOS(9_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*
 The behavior of tintColor for bars has changed on iOS 7.0. It no longer affects the bar's background
 and behaves as described for the tintColor property added to UIView.
 To tint the bar's background, please use -barTintColor.
 */
@property(null_resettable, nonatomic,strong) UIColor *tintColor;
@property(nullable, nonatomic,strong) UIColor *barTintColor NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR;  // default is nil

@property (nonatomic) UISearchBarStyle searchBarStyle NS_AVAILABLE_IOS(7_0);

/*
 New behavior on iOS 7.
 Default is YES.
 You may force an opaque background by setting the property to NO.
 If the search bar has a custom background image, the default is inferred
 from the alpha values of the image???YES if it has any pixel with alpha < 1.0
 If you send setTranslucent:YES to a bar with an opaque custom background image
 it will apply a system opacity less than 1.0 to the image.
 If you send setTranslucent:NO to a bar with a translucent custom background image
 it will provide an opaque background for the image using the bar's barTintColor if defined, or black
 for UIBarStyleBlack or white for UIBarStyleDefault if barTintColor is nil.
 */
@property(nonatomic,assign,getter=isTranslucent) BOOL translucent NS_AVAILABLE_IOS(3_0); // Default is NO on iOS 6 and earlier. Always YES if barStyle is set to UIBarStyleBlackTranslucent

@property(nullable, nonatomic,copy) NSArray<NSString *>   *scopeButtonTitles        NS_AVAILABLE_IOS(3_0); // array of NSStrings. no scope bar shown unless 2 or more items
@property(nonatomic)      NSInteger  selectedScopeButtonIndex NS_AVAILABLE_IOS(3_0); // index into array of scope button titles. default is 0. ignored if out of range
@property(nonatomic)      BOOL       showsScopeBar            NS_AVAILABLE_IOS(3_0); // default is NO. if YES, shows the scope bar. call sizeToFit: to update frame

/* Allow placement of an input accessory view to the keyboard for the search bar
 */
@property (nullable, nonatomic, readwrite, strong) UIView *inputAccessoryView;

// 1pt wide images and resizable images will be scaled or tiled according to the resizable area, otherwise the image will be tiled
@property(nullable, nonatomic,strong) UIImage *backgroundImage NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
@property(nullable, nonatomic,strong) UIImage *scopeBarBackgroundImage NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;


- (void)setBackgroundImage:(nullable UIImage *)backgroundImage forBarPosition:(UIBarPosition)barPosition barMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR;  // Use UIBarMetricsDefaultPrompt to set a separate backgroundImage for a search bar with a prompt
- (nullable UIImage *)backgroundImageForBarPosition:(UIBarPosition)barPosition barMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR;

/* In general, you should specify a value for the normal state to be used by other states which don't have a custom value set
 */

/* The rounded-rect search text field image. Valid states are UIControlStateNormal and UIControlStateDisabled
 */
- (void)setSearchFieldBackgroundImage:(nullable UIImage *)backgroundImage forState:(UIControlState)state NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)searchFieldBackgroundImageForState:(UIControlState)state NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

- (void)setImage:(nullable UIImage *)iconImage forSearchBarIcon:(UISearchBarIcon)icon state:(UIControlState)state NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)imageForSearchBarIcon:(UISearchBarIcon)icon state:(UIControlState)state NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

//
// Customizing the appearance of the scope bar buttons.
//

/* If backgroundImage is an image returned from -[UIImage resizableImageWithCapInsets:] the cap widths will be calculated from the edge insets, otherwise, the cap width will be calculated by subtracting one from the image's width then dividing by 2. The cap widths will also be used as the margins for text placement. To adjust the margin use the margin adjustment methods.
 */
- (void)setScopeBarButtonBackgroundImage:(nullable UIImage *)backgroundImage forState:(UIControlState)state NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR; 
- (nullable UIImage *)scopeBarButtonBackgroundImageForState:(UIControlState)state NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

/* To customize the segmented control appearance you will need to provide divider images to go between two unselected segments (leftSegmentState:UIControlStateNormal rightSegmentState:UIControlStateNormal), selected on the left and unselected on the right (leftSegmentState:UIControlStateSelected rightSegmentState:UIControlStateNormal), and unselected on the left and selected on the right (leftSegmentState:UIControlStateNormal rightSegmentState:UIControlStateSelected).
 */
- (void)setScopeBarButtonDividerImage:(nullable UIImage *)dividerImage forLeftSegmentState:(UIControlState)leftState rightSegmentState:(UIControlState)rightState NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)scopeBarButtonDividerImageForLeftSegmentState:(UIControlState)leftState rightSegmentState:(UIControlState)rightState NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

/* You may specify the font, text color, and shadow properties for the title in the text attributes dictionary, using the keys found in NSAttributedString.h.
 */
- (void)setScopeBarButtonTitleTextAttributes:(nullable NSDictionary<NSString *, id> *)attributes forState:(UIControlState)state NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
- (nullable NSDictionary<NSString *, id> *)scopeBarButtonTitleTextAttributesForState:(UIControlState)state NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

/* To nudge the position of the search text field background in the search bar
 */
@property(nonatomic) UIOffset searchFieldBackgroundPositionAdjustment NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

/* To nudge the position of the text within the search text field background
 */
@property(nonatomic) UIOffset searchTextPositionAdjustment NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

/* To nudge the position of the icon within the search text field
 */
- (void)setPositionAdjustment:(UIOffset)adjustment forSearchBarIcon:(UISearchBarIcon)icon NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
- (UIOffset)positionAdjustmentForSearchBarIcon:(UISearchBarIcon)icon NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
@end

@protocol UISearchBarDelegate <UIBarPositioningDelegate>

@optional

- (BOOL)searchBarShouldBeginEditing:(UISearchBar *)searchBar;                      // return NO to not become first responder
- (void)searchBarTextDidBeginEditing:(UISearchBar *)searchBar;                     // called when text starts editing
- (BOOL)searchBarShouldEndEditing:(UISearchBar *)searchBar;                        // return NO to not resign first responder
- (void)searchBarTextDidEndEditing:(UISearchBar *)searchBar;                       // called when text ends editing
- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText;   // called when text changes (including clear)
- (BOOL)searchBar:(UISearchBar *)searchBar shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text NS_AVAILABLE_IOS(3_0); // called before text changes

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar;                     // called when keyboard search button pressed
- (void)searchBarBookmarkButtonClicked:(UISearchBar *)searchBar;                   // called when bookmark button pressed
- (void)searchBarCancelButtonClicked:(UISearchBar *)searchBar;                     // called when cancel button pressed
- (void)searchBarResultsListButtonClicked:(UISearchBar *)searchBar NS_AVAILABLE_IOS(3_2); // called when search results button pressed

- (void)searchBar:(UISearchBar *)searchBar selectedScopeButtonIndexDidChange:(NSInteger)selectedScope NS_AVAILABLE_IOS(3_0);

@end

NS_ASSUME_NONNULL_END
