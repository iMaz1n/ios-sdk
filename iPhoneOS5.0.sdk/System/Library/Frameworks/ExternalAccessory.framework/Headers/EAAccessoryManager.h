//
//  EAAccessoryManager.h
//  ExternalAccessory
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

// EAAccessoryManager Notifications
EA_EXTERN NSString *const EAAccessoryDidConnectNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
EA_EXTERN NSString *const EAAccessoryDidDisconnectNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
// Keys in the EAAccessoryDidConnectNotification/EAAccessoryDidDisconnectNotification userInfo
EA_EXTERN NSString *const EAAccessoryKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // EAAccessory

@class EAAccessory;

EA_EXTERN_CLASS_AVAILABLE(3_0) @interface EAAccessoryManager : NSObject {
@private
    NSMutableArray *_connectedAccessories;
}

+ (EAAccessoryManager *)sharedAccessoryManager __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

- (void)registerForLocalNotifications __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)unregisterForLocalNotifications __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@property (nonatomic, readonly) NSArray *connectedAccessories __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end
