//
//  WKInterfaceDevice.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <WatchKit/WatchKit.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage;

typedef NS_ENUM(NSInteger, WKHapticType) {
	WKHapticTypeNotification,
    WKHapticTypeDirectionUp,
    WKHapticTypeDirectionDown,
    WKHapticTypeSuccess,
    WKHapticTypeFailure,
    WKHapticTypeRetry,
    WKHapticTypeStart,
    WKHapticTypeStop,
    WKHapticTypeClick
} WK_AVAILABLE_WATCHOS_ONLY(2.0);

@interface WKInterfaceDevice : NSObject

+ (WKInterfaceDevice *)currentDevice;

- (BOOL)addCachedImage:(UIImage *)image name:(NSString *)name WK_AVAILABLE_IOS_ONLY(8.2);
- (BOOL)addCachedImageWithData:(NSData *)imageData name:(NSString *)name WK_AVAILABLE_IOS_ONLY(8.2);
- (void)removeCachedImageWithName:(NSString *)name WK_AVAILABLE_IOS_ONLY(8.2);
- (void)removeAllCachedImages WK_AVAILABLE_IOS_ONLY(8.2);

@property (nonatomic, readonly) CGRect screenBounds;
@property (nonatomic, readonly) CGFloat screenScale;
@property (nonatomic, readonly, copy)  NSString *preferredContentSizeCategory;
@property (nonatomic, readonly, strong) NSDictionary<NSString*, NSNumber*> *cachedImages; // name and size of cached images

@property(nonatomic, readonly, copy) NSString *systemVersion  WK_AVAILABLE_WATCHOS_IOS(2.0,9.0); // e.g. @"2.0"
@property(nonatomic, readonly, copy) NSString *name           WK_AVAILABLE_WATCHOS_IOS(2.0,9.0); // e.g. "My Watch"
@property(nonatomic, readonly, copy) NSString *model          WK_AVAILABLE_WATCHOS_IOS(2.0,9.0); // e.g. @"Apple Watch"
@property(nonatomic, readonly, copy) NSString *localizedModel WK_AVAILABLE_WATCHOS_IOS(2.0,9.0); // localized version of model
@property(nonatomic, readonly, copy) NSString *systemName     WK_AVAILABLE_WATCHOS_IOS(2.0,9.0); // e.g. @"watchOS"

- (void)playHaptic:(WKHapticType)type WK_AVAILABLE_WATCHOS_ONLY(2.0);

@end

NS_ASSUME_NONNULL_END
