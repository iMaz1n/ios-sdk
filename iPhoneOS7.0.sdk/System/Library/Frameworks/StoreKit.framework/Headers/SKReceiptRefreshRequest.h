//
//  SKReceiptRefreshRequest.h
//  StoreKit
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/SKRequest.h>
#import <StoreKit/StoreKitDefines.h>

SK_EXTERN_CLASS_AVAILABLE(7_0) @interface SKReceiptRefreshRequest : SKRequest

- (id)initWithReceiptProperties:(NSDictionary *)properties __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
@property (nonatomic, readonly) NSDictionary *receiptProperties __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

@end


// Receipt properties for sandbox testing:
SK_EXTERN NSString * const SKReceiptPropertyIsExpired __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsRevoked __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsVolumePurchase __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);  // NSNumber BOOL, defaults to NO
