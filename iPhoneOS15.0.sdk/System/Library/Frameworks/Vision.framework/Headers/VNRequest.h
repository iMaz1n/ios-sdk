//
//  VNRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Metal/Metal.h>

#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @header VNRequest The VNRequest class is the object a client uses to describe any computer vision task to be performed by the Vision framework. They are submitted to a request handler in order to perform the task, and the resulting VNObservations are placed in the results property of the VNRequest.
 */
@class VNRequest;

/*!
 @abstract A block that is executed at the completion of a request.
 @param request The VNRequest that has been completed. The results of the request if no error was encountered are populated in the results array of the request.
 @param	error The error that caused the request to fail, or nil if completed successfully.
 */
typedef void (^VNRequestCompletionHandler)(VNRequest *request, NSError * _Nullable error);


/*!
@class VNRequest
@abstract VNRequest objects describe the operation to be performed as well as act as the recipient of the operation's resultant observations.
 
@discussion VNRequest objects are instantiated in a pre-configured nominal state. Prior to sending a VNRequest to a request handler to perform a desired operation, the default configuration can be changed by modifying the values of VNRequest properties. The VNRequest class itself acts as a base class and is not meant to be directly instantiated.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNRequest : NSObject <NSCopying>


/*!
 @abstract Creates a new VNRequest with no completion handler.
*/
- (instancetype) init;


/*!
 @abstract Creates a new VNRequest with an optional completion handler.

 @param completionHandler	The block to be invoked after the request has completed its processing. The completion handler gets executed on the same dispatch queue as the request being executed.
*/
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_DESIGNATED_INITIALIZER;


/*!
 @abstract A hint used to minimize the resource burden of the request. Memory footprint, processing footprint and/or CPU/GPU contention will be reduced (depending on the request), at the potential cost of longer execution time. This can help, for example, with ensuring UI updates and rendering are not getting blocked by Vision processing.
*/
@property (readwrite, nonatomic, assign) BOOL preferBackgroundProcessing;


/*!
 @abstract This property, if set to YES, signifies that the request should be performed exclusively on the CPU and not on the GPU. The default value is NO, which signifies that the request is free to leverage the GPU to accelerate any work the request may require.
 */
@property (readwrite, nonatomic) BOOL usesCPUOnly;

/*!
 @property results
 @abstract The collection of VNObservations generated by the processing of the request.
 @discussion The only valid time to access this property is after the request has been processed by a request handler.  If the request failed, this property will be nil; otherwise, it will be an array of zero or more VNObservation subclasses specific to the VNRequest subclass.
 */
@property (readonly, nonatomic, copy, nullable) NSArray<__kindof VNObservation*>* results;


/*!
 @property completionHandler
 @abstract The completion handler block that will be invoked after the request has completed processing.
 */
@property (readonly, nonatomic, copy, nullable) VNRequestCompletionHandler completionHandler;


/*!
 @abstract The specific algorithm or implementation revision that is to be used to perform the request.
 */
@property (readwrite, nonatomic, assign) NSUInteger revision API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));


/*!
 @abstract Provides the collection of currently-supported algorithm or implementation versions for the class of request.
 @discussion This method allows clients to introspect at runtime what capabilities are available for each class of VNRequest in the Vision framework.
 */
@property (class, readonly, nonatomic, copy) NSIndexSet* supportedRevisions API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*! @abstract Provides the revision of the request that was latest for the particular SDK that was linked with the client application. */
@property (class, readonly, nonatomic, assign) NSUInteger defaultRevision API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*! @abstract Provides the current revison supported by the request. */
@property (class, readonly, nonatomic, assign) NSUInteger currentRevision API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*!
 * @discussion Tries to abort the request as soon as possible. Results will be nil. The completionHandler (if present) will be called with an error of VNErrorRequestCancelled.
 */
- (void)cancel API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end


/*!
	@brief	A value that indicates that the request revision is either unknown or not applicable.
*/
API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNRequestRevisionUnspecified = 0;



/*!
	@brief A request that will process the contents of a reference image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageBasedRequest : VNRequest

/*!
	@brief The region of the image in which the request will be performed.  The rectangle is normalized to the dimensions of the image being processed and has its origin specified relative to the image's lower-left corner.
	
	@discussion The default value for this property is { { 0, 0 }, { 1, 1 } }.  Setting this property to a rectangle that is outside of the normalized coordinate space will be accepted but result in the request failing to be performed.
*/
@property (readwrite, nonatomic, assign) CGRect regionOfInterest;

@end



/*!
 @abstract A block that is executed at intervals during the processing of a request.
 @param request The VNRequest that has been completed. The results of the request, if no error was encountered, are populated in the results array of the request.
 @param fractionCompleted When possible the request will report its progress between 0.0 and 1.0. If the requests indeterminate property is set, then this value is undefined.
 @param    error The error that caused the request to fail, or nil if completed successfully.
 @discussion The results in the request can be populated with partial results. The progressHandler can be called on a different dispatch queue than what the request was initiated from.
 */
typedef void (^VNRequestProgressHandler)(VNRequest *request, double fractionCompleted, NSError * _Nullable error);


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@protocol VNRequestProgressProviding < NSObject >

/*!
 @brief Requests that support the VNRequestProgressProviding protocol would periodically call the progressHandler to report progress on longer running tasks.
 
 @discussion The progessHandler is optional allowing clients of the request to report progress to the user and/or display or process partial results when they become available. Note that the progressHandler can be called on a different dispatch queue than what the request was initiated from.
 */
@property (readwrite, nonatomic, copy) VNRequestProgressHandler progressHandler;


/*!
 @brief If a request cannot determine its progress in fractions completed, this property will be set.
 @discussion If this is set, it doesn't mean that the request will run forever just that the nature of the request is not broken down into identifiable fractions on which progress can be reported in increments. The progressHandler will nonetheless be called at suitable intervals.
 */
@property (readonly) BOOL indeterminate;

@end

NS_ASSUME_NONNULL_END
