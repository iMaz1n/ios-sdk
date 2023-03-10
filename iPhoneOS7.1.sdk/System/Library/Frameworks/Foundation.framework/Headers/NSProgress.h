/*
	NSProgress.h
	Copyright (c) 2011-2013, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDictionary, NSMutableDictionary, NSMutableSet, NSURL, NSUUID, NSXPCConnection, NSLock;

NS_CLASS_AVAILABLE(10_9, 7_0)
@interface NSProgress : NSObject {
@private
    __weak id _group;
    int64_t _reserved4;
    id _values;
    id _reserved5;
    void (^_cancellationHandler)(void);
    void (^_pausingHandler)(void);
    void (^_prioritizationHandler)(void);
    int64_t _reserved3;
    id _userInfoProxy;
    NSString *_publisherID;
    NSXPCConnection *_connection;
    NSInteger _unpublishingBlockageCount;
    NSInteger _disconnectingBlockageCount;
    NSInteger _remoteObserverCount;
    NSMutableDictionary *_acknowledgementHandlersByBundleID;
    NSMutableDictionary *_lastNotificationTimesByKey;
    NSMutableDictionary *_userInfoLastNotificationTimesByKey;
    NSLock *_lock;
    NSMutableSet *_childrenGroups;
}

/* The instance of NSProgress associated with the current thread by a previous invocation of -becomeCurrentWithPendingUnitCount:, if any. The purpose of this per-thread value is to allow code that does work to usefully report progress even when it is widely separated from the code that actually presents progress to the user, without requiring layers of intervening code to pass the instance of NSProgress through. Using the result of invoking this directly will often not be the right thing to do, because the invoking code will often not even know what units of work the current progress object deals in. Invoking +progressWithTotalUnitCount: to create a child NSProgress object and then using that to report progress makes more sense in that situation.
*/
+ (NSProgress *)currentProgress;

/* Return an instance of NSProgress that has been initialized with -initWithParent:userInfo:. The initializer is passed the current progress object, if there is one, and the value of the totalUnitCount property is set. In many cases you can simply precede code that does a substantial amount of work with an invocation of this method, with repeated invocations of -setCompletedUnitCount: and -isCancelled in the loop that does the work.

You can invoke this method on one thread and then message the returned NSProgress on another thread. For example, you can let the result of invoking this method get captured by a block passed to dispatch_async(). In that block you can invoke methods like -becomeCurrentWithPendingUnitCount: and -resignCurrent, or -setCompletedUnitCount: and -isCancelled.
*/
+ (NSProgress *)progressWithTotalUnitCount:(int64_t)unitCount;

/* The designated initializer. If a parent NSProgress object is passed then progress reporting and cancellation checking done by the receiver will notify or consult the parent. The only valid arguments to the first argument of this method are nil (indicating no parent) or [NSProgress currentProgress]. Any other value will throw an exception.
*/
- (instancetype)initWithParent:(NSProgress *)parentProgressOrNil userInfo:(NSDictionary *)userInfoOrNil;

/* Make the receiver the current thread's current progress object, returned by +currentProgress. At the same time, record how large a portion of the work represented by the receiver will be represented by the next progress object initialized by invoking -initWithParent:userInfo: in the current thread with the receiver as the parent. This will be used when that child is sent -setCompletedUnitCount: and the receiver is notified of that.
 
   With this mechanism, code that doesn't know anything about its callers can report progress accurately by using +progressWithTotalUnitCount: and -setCompletedUnitCount:. The calling code will account for the fact that the work done is only a portion of the work to be done as part of a larger operation. The unit of work in a call to -becomeCurrentWithPendingUnitCount: has to be the same unit of work as that used for the value of the totalUnitCount property, but the unit of work used by the child can be a completely different one, and often will be. You must always balance invocations of this method with invocations of -resignCurrent.
*/
- (void)becomeCurrentWithPendingUnitCount:(int64_t)unitCount;

/* Balance the most recent previous invocation of -becomeCurrentWithPendingUnitCount: on the same thread by restoring the current progress object to what it was before -becomeCurrentWithPendingUnitCount: was invoked.
*/
- (void)resignCurrent;

#pragma mark *** Reporting Progress ***

/* The size of the job whose progress is being reported, and how much of it has been completed so far, respectively. For an NSProgress with a kind of NSProgressKindFile, the unit of these properties is bytes while the NSProgressFileTotalCountKey and NSProgressFileCompletedCountKey keys in the userInfo dictionary are used for the overall count of files. For any other kind of NSProgress, the unit of measurement you use does not matter as long as you are consistent. The values may be reported to the user in the localizedDescription and localizedAdditionalDescription.
 
   If the receiver NSProgress object is a "leaf progress" (no children), then the fractionCompleted is generally completedUnitCount / totalUnitCount. If the receiver NSProgress has children, the fractionCompleted will reflect progress made in child objects in addition to its own completedUnitCount. As children finish, the completedUnitCount of the parent will be updated.
*/
@property int64_t totalUnitCount;
@property int64_t completedUnitCount;

/* A description of what progress is being made, fit to present to the user. NSProgress is by default KVO-compliant for this property, with the notifications always being sent on thread which updates the property. The default implementation of the getter for this property does not always return the most recently set value of the property. If the most recently set value of this property is nil then NSProgress uses the value of the kind property to determine how to use the values of other properties, as well as values in the user info dictionary, to return a computed string. If it fails to do that then it returns an empty string.
  
  For example, depending on the kind of progress, the completed and total unit counts, and other parameters, these kinds of strings may be generated:
    Copying 10 files???
    30% completed
    Copying ???TextEdit??????
*/
@property (copy) NSString *localizedDescription;

/* A more specific description of what progress is being made, fit to present to the user. NSProgress is by default KVO-compliant for this property, with the notifications always being sent on thread which updates the property. The default implementation of the getter for this property does not always return the most recently set value of the property. If the most recently set value of this property is nil then NSProgress uses the value of the kind property to determine how to use the values of other properties, as well as values in the user info dictionary, to return a computed string. If it fails to do that then it returns an empty string. The difference between this and localizedDescription is that this text is meant to be more specific about what work is being done at any particular moment.

   For example, depending on the kind of progress, the completed and total unit counts, and other parameters, these kinds of strings may be generated:
    3 of 10 files
    123 KB of 789.1 MB
    3.3 MB of 103.92 GB ??? 2 minutes remaining
    1.61 GB of 3.22 GB (2 KB/sec) ??? 2 minutes remaining
    1 minute remaining (1 KB/sec)

*/
@property (copy) NSString *localizedAdditionalDescription;

/* Whether the work being done can be cancelled or paused, respectively. By default NSProgresses are cancellable but not pausable. NSProgress is by default KVO-compliant for these properties, with the notifications always being sent on the thread which updates the property. These properties are for communicating whether controls for cancelling and pausing should appear in a progress reporting user interface. NSProgress itself does not do anything with these properties other than help pass their values from progress reporters to progress observers. It is valid for the values of these properties to change in virtually any way during the lifetime of an NSProgress. Of course, if an NSProgress is cancellable you should actually implement cancellability by setting a cancellation handler or by making your code poll the result of invoking -isCancelled. Likewise for pausability.
*/
@property (getter=isCancellable) BOOL cancellable;
@property (getter=isPausable) BOOL pausable;

/* Whether the work being done has been cancelled or paused, respectively. NSProgress is by default KVO-compliant for these properties, with the notifications always being sent on the thread which updates the property. Instances of NSProgress that have parents are at least as cancelled or paused as their parents.
*/
@property (readonly, getter=isCancelled) BOOL cancelled;
@property (readonly, getter=isPaused) BOOL paused;

/* A block to be invoked when -cancel or -pause is invoked, respectively. The block will be invoked even when the method is invoked on an ancestor of the receiver, or an instance of NSProgress in another process that resulted from publishing the receiver or an ancestor of the receiver. Your block won't be invoked on any particular queue. If it must do work on a specific queue then it should schedule that work on that queue.
*/
@property (copy) void (^cancellationHandler)(void);
@property (copy) void (^pausingHandler)(void);

/* Set a value in the dictionary returned by invocations of -userInfo, with appropriate KVO notification for properties whose values can depend on values in the user info dictionary, like localizedDescription. If a nil value is passed then the dictionary entry is removed.
*/
- (void)setUserInfoObject:(id)objectOrNil forKey:(NSString *)key;

#pragma mark *** Observing and Controlling Progress ***

/* The localizedDescription and localizedAdditionalDescription properties described above are meant to be observed as well as set. So are the cancellable and pausable properties. totalUnitCount and completedUnitCount on the other hand are often not the best properties to observe when presenting progress to the user. For example, you should observe fractionCompleted instead of observing totalUnitCount and completedUnitCount and doing your own calculation. NSProgress' default implementation of -fractionCompleted does fairly sophisticated things like taking child NSProgresses into account.
*/

/* Whether the progress being made is indeterminate. -isIndeterminate returns YES when the value of the totalUnitCount or completedUnitCount property is less than zero. Zero values for both of those properties indicates that there turned out to not be any work to do after all; -isIndeterminate returns NO and -fractionCompleted returns 1.0 in that case. NSProgress is by default KVO-compliant for these properties, with the notifications always being sent on the thread which updates the property.
*/
@property (readonly, getter=isIndeterminate) BOOL indeterminate;

/* The fraction of the overall work completed by this progress object, including work done by any children it may have.
*/
@property (readonly) double fractionCompleted;

/* Invoke the block registered with -setCancellationHandler:, if there is one, and make subsequent invocations of -isCancelled return YES. Do this for the receiver, any descendants of the receiver, the instance of NSProgress that was published in another process to make the receiver if that's the case, and any descendants of such a published instance of NSProgress.
*/
- (void)cancel;

/* Invoke the block registered with -setPausingHandler:, if there is one, and make subsequent invocations of -isPaused return YES. Do this for the receiver, any descendants of the receiver, the instance of NSProgress that was published in another process to make the receiver if that's the case, and any descendants of such a published instance of NSProgress.
*/
- (void)pause;

/* Arbitrary values associated with the receiver. Returns a KVO-compliant dictionary that changes as -setUserInfoObject:forKey: is sent to the receiver. The dictionary will send all of its KVO notifications on the thread which updates the property. Some entries have meanings that are recognized by the NSProgress class itself. See the NSProgress...Key string constants listed below.
*/
- (NSDictionary *)userInfo;

/* Either a string identifying what kind of progress is being made, like NSProgressKindFile, or nil. If the value of the localizedDescription property has not been set to a non-nil value then the default implementation of -localizedDescription uses the progress kind to determine how to use the values of other properties, as well as values in the user info dictionary, to create a string that is presentable to the user. This is most useful when -localizedDescription is actually being invoked in another process, whose localization language may be different, as a result of using the publish and subscribe mechanism described here.
*/
@property (copy) NSString *kind;

#pragma mark *** Reporting Progress to Other Processes (OS X Only) ***

/* Make the NSProgress observable by other processes. Whether or not another process can discover the NSProgress to observe it, and how it would do that, depends on entries in the user info dictionary. For example, an NSProgressFileURLKey entry makes an NSProgress discoverable by corresponding invokers of +addSubscriberForFileURL:withPublishingHandler:.

When you make an NSProgress observable by other processes you must ensure that at least -localizedDescription, -isIndeterminate, and -fractionCompleted always work when sent to proxies of your NSProgress in other processes. You make -isIndeterminate and -fractionCompleted always work by accurately setting the total and completed unit counts of the progress. You make -localizedDescription always work by setting the value of the kind property to something valid, like NSProgressKindFile, and then fulfilling the requirements for that specific kind of progress. (You can instead set the value of localizedDescription directly but that is not perfectly reliable because other processes might be using different localization languages than yours.)

You can publish an instance of NSProgress at most once.
*/
- (void)publish NS_AVAILABLE(10_9, NA);

/* Make the NSProgress no longer observable by other processes.
*/
- (void)unpublish NS_AVAILABLE(10_9, NA);

#pragma mark *** Observing and Controlling File Progress by Other Processes (OS X Only) ***

typedef void (^NSProgressUnpublishingHandler)(void);
typedef NSProgressUnpublishingHandler (^NSProgressPublishingHandler)(NSProgress *progress);

/* Register to hear about file progress. The passed-in block will be invoked when -publish has been sent to an NSProgress whose NSProgressFileURLKey user info dictionary entry is an NSURL locating the same item located by the passed-in NSURL, or an item directly contained by it. The NSProgress passed to your block will be a proxy of the one that was published. The passed-in block may return another block. If it does, then that returned block will be invoked when the corresponding invocation of -unpublish is made, or the publishing process terminates, or +removeSubscriber: is invoked. Your blocks will be invoked on the main thread.
*/
+ (id)addSubscriberForFileURL:(NSURL *)url withPublishingHandler:(NSProgressPublishingHandler)publishingHandler NS_AVAILABLE(10_9, NA);

/* Given the object returned by a previous invocation of -addSubscriberForFileURL:withPublishingHandler:, deregister.
*/
+ (void)removeSubscriber:(id)subscriber NS_AVAILABLE(10_9, NA);

/* Return YES if the receiver represents progress that was published before the invocation of +addSubscriberForFileURL:withPublishingHandler: that resulted in the receiver appearing in this process, NO otherwise. The publish and subscribe mechanism described here is generally "level triggered," in that when you invoke +addSubscriberForFileURL:withPublishingHandler: your block will be invoked for every relevant NSProgress that has already been published and not yet unpublished. Sometimes however you need to implement "edge triggered" behavior, in which you do something either exactly when new progress begins or not at all. In the example described above, the Dock does not animate file icon flying when this method returns YES.

Note that there is no reliable definition of "before" in this case, which involves multiple processes in a preemptively scheduled system. You should not use this method for anything more important than best efforts at animating perfectly in the face of processes coming and going due to unpredictable user actions. Continuing with our example, the Dock invokes -acknowledgeWithSuccess: regardless of what this method returns.
*/
@property (readonly, getter=isOld) BOOL old NS_AVAILABLE(10_9, NA);

@end

#pragma mark *** Details of General Progress ***

/* How much time is probably left in the operation, as an NSNumber containing a number of seconds.
*/
FOUNDATION_EXPORT NSString *const NSProgressEstimatedTimeRemainingKey NS_AVAILABLE(10_9, 7_0);

/* How fast data is being processed, as an NSNumber containing bytes per second.
*/
FOUNDATION_EXPORT NSString *const NSProgressThroughputKey NS_AVAILABLE(10_9, 7_0);

#pragma mark *** Details of File Progress ***

/* The value for the kind property that indicates that the work being done is one of the kind of file operations listed below. NSProgress of this kind is assumed to use bytes as the unit of work being done and the default implementation of -localizedDescription takes advantage of that to return more specific text than it could otherwise. The NSProgressFileTotalCountKey and NSProgressFileCompletedCountKey keys in the userInfo dictionary are used for the overall count of files.
*/
FOUNDATION_EXPORT NSString *const NSProgressKindFile NS_AVAILABLE(10_9, 7_0);

/* A user info dictionary key, for an entry that is required when the value for the kind property is NSProgressKindFile. The value must be one of the strings listed in the next section. The default implementations of of -localizedDescription and -localizedItemDescription use this value to determine the text that they return.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileOperationKindKey NS_AVAILABLE(10_9, 7_0);

/* Possible values for NSProgressFileOperationKindKey entries.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileOperationKindDownloading NS_AVAILABLE(10_9, 7_0);
FOUNDATION_EXPORT NSString *const NSProgressFileOperationKindDecompressingAfterDownloading NS_AVAILABLE(10_9, 7_0);
FOUNDATION_EXPORT NSString *const NSProgressFileOperationKindReceiving NS_AVAILABLE(10_9, 7_0);
FOUNDATION_EXPORT NSString *const NSProgressFileOperationKindCopying NS_AVAILABLE(10_9, 7_0);

/* A user info dictionary key. The value must be an NSURL identifying the item on which progress is being made. This is required for any NSProgress that is published using -publish to be reported to subscribers registered with +addSubscriberForFileURL:withPublishingHandler:.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileURLKey NS_AVAILABLE(10_9, 7_0);

/* User info dictionary keys. The values must be NSNumbers containing integers. These entries are optional but if they are both present then the default implementation of -localizedAdditionalDescription uses them to determine the text that it returns.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileTotalCountKey NS_AVAILABLE(10_9, 7_0);
FOUNDATION_EXPORT NSString *const NSProgressFileCompletedCountKey NS_AVAILABLE(10_9, 7_0);

/* User info dictionary keys. The value for the first entry must be an NSImage, typically an icon. The value for the second entry must be an NSValue containing an NSRect, in screen coordinates, locating the image where it initially appears on the screen. These entries are optional but, if they are both present and the Dock has an item for the folder containing the file on which progress is being made, like the Downloads folder, the Dock will use them to show an animation of the file flying into the Dock, and then invoke -acknowledgeWithSuccess:.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileAnimationImageKey NS_AVAILABLE(10_9, NA);
FOUNDATION_EXPORT NSString *const NSProgressFileAnimationImageOriginalRectKey NS_AVAILABLE(10_9, NA);

/* A user info dictionary key. The value must be an NSImage containing an icon. This entry is optional but, if it is present, the Finder will use it to show the icon of a file while progress is being made on that file. For example, the App Store uses this to specify an icon for an application being downloaded before the icon can be gotten from the application bundle itself.
*/
FOUNDATION_EXPORT NSString *const NSProgressFileIconKey NS_AVAILABLE(10_9, NA);
