//
//  INPaymentMethodType.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INPaymentMethodType_h
#define INPaymentMethodType_h

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INPaymentMethodType) {
    INPaymentMethodTypeUnknown = 0,
    INPaymentMethodTypeChecking,
    INPaymentMethodTypeSavings,
    INPaymentMethodTypeBrokerage,
    INPaymentMethodTypeDebit,
    INPaymentMethodTypeCredit,
    INPaymentMethodTypePrepaid,
    INPaymentMethodTypeStore,
    INPaymentMethodTypeApplePay,
};

#endif // INPaymentMethodType_h
