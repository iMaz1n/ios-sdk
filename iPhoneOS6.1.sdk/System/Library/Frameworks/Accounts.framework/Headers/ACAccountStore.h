//
//  ACAccountStore.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

// Options dictionary keys for Facebook access
ACCOUNTS_EXTERN NSString * const ACFacebookAppIdKey;            // Your Facebook App ID, as it appears on the Facebook website.
ACCOUNTS_EXTERN NSString * const ACFacebookPermissionsKey;      // An array of of the permissions you're requesting. Optional.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceKey;         // Only required when posting permissions are requested.

// Options dictionary values for Facebook access
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceEveryone;    // Posts from your app are visible to everyone.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceFriends;     // Posts are visible only to friends.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceOnlyMe;      // Posts are visible to the user only.

typedef NS_ENUM(NSInteger, ACAccountCredentialRenewResult) {
    ACAccountCredentialRenewResultRenewed,  // A new credential was obtained and is now associated with the account.
    ACAccountCredentialRenewResultRejected, // Renewal failed because of a user-initiated action.
    ACAccountCredentialRenewResultFailed,   // A non-user-initiated cancel of the prompt. 
};

typedef void(^ACAccountStoreSaveCompletionHandler)(BOOL success, NSError *error);
typedef void(^ACAccountStoreRemoveCompletionHandler)(BOOL success, NSError *error);
typedef void(^ACAccountStoreRequestAccessCompletionHandler)(BOOL granted, NSError *error);
typedef void(^ACAccountStoreCredentialRenewalHandler)(ACAccountCredentialRenewResult renewResult, NSError *error);

@class ACAccount, ACAccountType;

// The ACAccountStore class provides an interface for accessing and manipulating
// accounts. You must create an ACAccountStore object to retrieve, add and delete
// accounts from the Accounts database.

ACCOUNTS_CLASS_AVAILABLE(NA, 5_0)
@interface ACAccountStore : NSObject

// An array of all the accounts in an account database
@property (readonly, weak, NS_NONATOMIC_IOSONLY) NSArray *accounts;

// Returns the account matching the given account identifier
- (ACAccount *)accountWithIdentifier:(NSString *)identifier;

// Returns the account type object matching the account type identifier. See
// ACAccountType.h for well known account type identifiers
- (ACAccountType *)accountTypeWithAccountTypeIdentifier:(NSString *)typeIdentifier;

// Returns the accounts matching a given account type.
- (NSArray *)accountsWithAccountType:(ACAccountType *)accountType;

// Saves the account to the account database. If the account is unauthenticated and the associated account
// type supports authentication, the system will attempt to authenticate with the credentials provided.
// Assuming a successful authentication, the account will be saved to the account store. The completion handler
// for this method is called on an arbitrary queue.
- (void)saveAccount:(ACAccount *)account withCompletionHandler:(ACAccountStoreSaveCompletionHandler)completionHandler;

// DEPRECATED: Please use requestAccessToAccountsWithType:options:completion: instead.
- (void)requestAccessToAccountsWithType:(ACAccountType *)accountType
                  withCompletionHandler:(ACAccountStoreRequestAccessCompletionHandler)handler NS_DEPRECATED(NA, NA, 5_0, 6_0);

// Obtains permission, if necessary, from the user to access protected properties, and utilize accounts
// of a particular type in protected operations, for example OAuth signing. The completion handler for 
// this method is called on an arbitrary queue.
// Certain account types (such as Facebook) require an options dictionary. A list of the required keys
// appears at the top of this file. This method will throw an NSInvalidArgumentException if the options
// dictionary is not provided for such account types. Conversely, if the account type does not require
// an options dictionary, the options parameter must be nil.
- (void)requestAccessToAccountsWithType:(ACAccountType *)accountType
                                options:(NSDictionary *)options
                             completion:(ACAccountStoreRequestAccessCompletionHandler)completion;

// Call this if you discover that an ACAccount's credential is no longer valid.
// For Twitter and Sina Weibo accounts, this method will prompt the user to go to Settings to re-enter their password.
// For Facebook accounts, if your access token became invalid due to regular expiration, this method will obtain a new one.
// However, if the user has deauthorized your app, this renewal request will return ACAccountCredentialRenewResultRejected.
- (void)renewCredentialsForAccount:(ACAccount *)account completion:(ACAccountStoreCredentialRenewalHandler)completionHandler;

// Removes an account from the account store. The completion handler for this method is called on an arbitrary queue.
// This call will fail if you don't have sufficient rights to remove the account in question.
- (void)removeAccount:(ACAccount *)account withCompletionHandler:(ACAccountStoreRemoveCompletionHandler)completionHandler;

@end

// Notification name sent out when the database is changed by an external process, another account store
// in the same process or by calling saveAccount: or removeAccount: on a store you are managing. When this
// notification is received, you should consider all ACAccount instances you have to be invalid. Purge current
// instances of ACAccount and obtain new instances using the account store. You may need to deal with accounts
// being removed by an external process while you are using them.
ACCOUNTS_EXTERN NSString * const ACAccountStoreDidChangeNotification NS_AVAILABLE(NA, 5_0);
