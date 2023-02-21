//
//  ADClient.h
//  iAd
//
//  Copyright 2013 Apple, Inc. All rights reserved.
//
//

#import <Foundation/Foundation.h>

NS_CLASS_AVAILABLE_IOS(7_1) @interface ADClient : NSObject

/*!
 * @method sharedClient
 *
 * @return
 * The shared singleton instance of ADClient.
 *
 * @discussion
 * ADClient is a singleton object.
 */
+ (ADClient *)sharedClient NS_AVAILABLE_IOS(7_1);

/*!
 * @method determineAppInstallationAttributionWithCompletionHandler:
 *
 * @param completionHandler
 * A block accepting one BOOL argument that will be called when app installation
 * attribution status has been determined. If this installation of the app is
 * attributed to an iAd impression, the completion handler will be called with
 * YES. Otherwise, or if the user has enabled Limit Ad Tracking, the completion
 * handler will be called with NO.
 *
 * The handler will be called on an arbitrary queue.
 *
 * @discussion
 * Provides a way for an app to determine if it was installed by the user in
 * response to seeing an iAd for the app.
 */
- (void)determineAppInstallationAttributionWithCompletionHandler:(void (^)(BOOL appInstallationWasAttributedToiAd))completionHandler NS_AVAILABLE_IOS(7_1);

@end
