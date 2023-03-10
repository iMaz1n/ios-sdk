//
//  TWTweetComposeViewController.h
//  Twitter
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

// This class has been  deprecated in iOS 6. Please use SLComposeViewController (in the Social framework) instead.

#import <UIKit/UIKit.h>
#import <Social/SLComposeViewController.h>

enum {
    TWTweetComposeViewControllerResultCancelled = SLComposeViewControllerResultCancelled,
    TWTweetComposeViewControllerResultDone = SLComposeViewControllerResultDone
};

typedef SLComposeViewControllerResult TWTweetComposeViewControllerResult;   // available in iPhone 5.0

// Completion handler for TWTweetComposeViewController
typedef SLComposeViewControllerCompletionHandler TWTweetComposeViewControllerCompletionHandler;

// Although you may perform requests on behalf of the user, you cannot append
// text, images, or URLs without the user's knowledge. Hence, you can set the
// initial text and other content before presenting the view to the user, but
// cannot change the content after the user views it. All of the methods used
// to set the content return a Boolean value. The methods return NO if the
// content doesn't fit or if the view was already presented to the user and the
// content can no longer be changed.

NS_DEPRECATED(NA, NA, 5_0, 6_0) __attribute__((visibility("default")))
@interface TWTweetComposeViewController : UIViewController

// Returns if Twitter is accessible and at least one account has been setup.
+ (BOOL)canSendTweet;

// Sets the initial text to be tweeted. Returns NO if the specified text will
// not fit within the character space currently available, or if the sheet
// has already been presented to the user.
- (BOOL)setInitialText:(NSString *)text;

// Adds an image to the tweet. Returns NO if the additional image will not fit
// within the character space currently available, or if the sheet has already
// been presented to the user.
- (BOOL)addImage:(UIImage *)image;

// Removes all images from the tweet. Returns NO and does not perform an operation
// if the sheet has already been presented to the user. 
- (BOOL)removeAllImages;

// Adds a URL to the tweet. Returns NO if the additional URL will not fit
// within the character space currently available, or if the sheet has already
// been presented to the user.
- (BOOL)addURL:(NSURL *)url;

// Removes all URLs from the tweet. Returns NO and does not perform an operation
// if the sheet has already been presented to the user.
- (BOOL)removeAllURLs;

// Specify a block to be called when the user is finished. This block is not guaranteed
// to be called on any particular thread. It is cleared after being called.
@property (nonatomic, copy) TWTweetComposeViewControllerCompletionHandler completionHandler;

@end
