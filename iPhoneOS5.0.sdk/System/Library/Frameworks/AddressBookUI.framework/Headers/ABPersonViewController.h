//
//  ABPersonViewController.h
//  AddressBookUI
//
//  Copyright (c) 2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>
#import <AddressBook/AddressBook.h>

@protocol ABPersonViewControllerDelegate;

NS_CLASS_AVAILABLE(NA, 2_0)
@interface ABPersonViewController : UIViewController
{
    @private
        id<ABPersonViewControllerDelegate> _personViewDelegate;
        
        id                                 _helper;
        id                                 _internal;
        BOOL                               _internal2;
}

@property(nonatomic,assign)    id<ABPersonViewControllerDelegate> personViewDelegate;

    // The Address Book to use. Any contact returned will be from this ABAddressBook instance.
    // If not set, a new ABAddressBook will be created the first time the property is accessed.
@property(nonatomic,readwrite) ABAddressBookRef                   addressBook;

    // If displayedPerson has been added to an ABAddressBook, then the addressBook
    // property will be updated to use the displayedPerson's ABAddressBook.
@property(nonatomic,readwrite) ABRecordRef                        displayedPerson;


    // An array of NSNumber instances representing the properties (ABPropertyID) that should
    // be visible when viewing the person. Note that all the properties are visible when
    // editing a person.
@property(nonatomic,copy)      NSArray                           *displayedProperties;

    // Indicates whether an edit/save button should be shown.
@property(nonatomic)           BOOL                               allowsEditing;

    // Specifies whether buttons appear to let the user perform actions such as sharing the contact,
    // initiating a FaceTime call, or sending a text message.
@property(nonatomic)           BOOL                               allowsActions __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

    // Indicates whether to show data from people linked to the displayedPerson, defaults to NO
@property(nonatomic)           BOOL                               shouldShowLinkedPeople __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

	// Indicates whether to highlight a certain value for the displayedPerson,
    // if a single value property is specified, identifier will be ignored.
- (void)setHighlightedItemForProperty:(ABPropertyID)property withIdentifier:(ABMultiValueIdentifier)identifier;

@end

@protocol ABPersonViewControllerDelegate <NSObject>

    // Called when the user selects an individual value in the Person view, identifier will be kABMultiValueInvalidIdentifier if a single value property was selected.
    // Return NO if you do not want anything to be done or if you are handling the actions yourself.
    // Return YES if you want the ABPersonViewController to perform its default action.
- (BOOL)personViewController:(ABPersonViewController *)personViewController shouldPerformDefaultActionForPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier;

@end
