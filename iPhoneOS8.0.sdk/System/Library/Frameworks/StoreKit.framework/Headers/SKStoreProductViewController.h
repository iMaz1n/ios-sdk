//
//  SKStoreProductViewController.h
//  StoreKit
//
//  Copyright (c) 2012 Apple, Inc. All rights reserved.
//

#import <StoreKit/StoreKitDefines.h>
#import <UIKit/UIKit.h>

@protocol SKStoreProductViewControllerDelegate;

/* View controller to display iTunes Store product information */
SK_EXTERN_CLASS_AVAILABLE(6_0) @interface SKStoreProductViewController : UIViewController

// Delegate for product page events
@property(nonatomic, assign) id <SKStoreProductViewControllerDelegate> delegate NS_AVAILABLE_IOS(6_0);

// Load product view for the product with the given parameters.  See below for parameters (SKStoreProductParameter*).
// Block is invoked when the load finishes.
- (void)loadProductWithParameters:(NSDictionary *)parameters completionBlock:(void(^)(BOOL result, NSError *error))block NS_AVAILABLE_IOS(6_0);

@end


@protocol SKStoreProductViewControllerDelegate <NSObject>

@optional

// Sent if the user requests that the page be dismissed
- (void)productViewControllerDidFinish:(SKStoreProductViewController *)viewController NS_AVAILABLE_IOS(6_0);

@end


// iTunes Store item identifier (NSNumber) of the product
SK_EXTERN NSString * const SKStoreProductParameterITunesItemIdentifier NS_AVAILABLE_IOS(6_0);

// iTunes Store affiliate token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAffiliateToken NS_AVAILABLE_IOS(8_0);

// iTunes Store affiliate campaign token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterCampaignToken NS_AVAILABLE_IOS(8_0);
