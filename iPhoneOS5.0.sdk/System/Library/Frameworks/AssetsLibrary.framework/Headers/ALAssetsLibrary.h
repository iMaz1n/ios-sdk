//
//  ALAssetsLibrary.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * This class represents the set of all videos and photos that are under the control of the Photos application. This includes
 * those that are in the saved photos album and those coming from iTunes.
 * It is used to retrieve the list of all asset groups and to save images and videos into the Saved Photos album.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

@class ALAsset;
@class ALAssetsGroup;

typedef enum {
    ALAssetOrientationUp,            // default orientation
    ALAssetOrientationDown,          // 180 deg rotation
    ALAssetOrientationLeft,          // 90 deg CCW
    ALAssetOrientationRight,         // 90 deg CW
    ALAssetOrientationUpMirrored,    // as above but image mirrored along other axis. horizontal flip
    ALAssetOrientationDownMirrored,  // horizontal flip
    ALAssetOrientationLeftMirrored,  // vertical flip
    ALAssetOrientationRightMirrored, // vertical flip
} ALAssetOrientation;

enum {
    ALAssetsGroupLibrary        = (1 << 0),         // The Library group that includes all assets.
    ALAssetsGroupAlbum          = (1 << 1),         // All the albums synced from iTunes or created on the device.
    ALAssetsGroupEvent          = (1 << 2),         // All the events synced from iTunes.
    ALAssetsGroupFaces          = (1 << 3),         // All the faces albums synced from iTunes.
    ALAssetsGroupSavedPhotos    = (1 << 4),         // The Saved Photos album.
#if __IPHONE_5_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ALAssetsGroupPhotoStream    = (1 << 5),         // The PhotoStream album.
#endif
    ALAssetsGroupAll            = 0xFFFFFFFF,       // The same as ORing together all the available group types, 
                                                    // with the exception that ALAssetsGroupLibrary is not included.
};
typedef NSUInteger ALAssetsGroupType;

// This block is executed when a match is found during enumeration. The match is passed to the block in the group argument.
// When the enumeration is done, the block will be called with group set to nil.
// Setting the output argument stop to YES will finish the enumeration.
typedef void (^ALAssetsLibraryGroupsEnumerationResultsBlock)(ALAssetsGroup *group, BOOL *stop);

// This block is executed if the user has granted access to the caller to access the data managed by the framework.
// If the asset is not found, asset is nil.
typedef void (^ALAssetsLibraryAssetForURLResultBlock)(ALAsset *asset);

// This block is executed if the user has granted access to the caller to access the data managed by the framework.
// If the group is not found, group is nil.
typedef void (^ALAssetsLibraryGroupResultBlock)(ALAssetsGroup *group) __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// This block is executed if the user does not grant access to the caller to access the data managed by the framework or if the data is currently unavailable.
typedef void (^ALAssetsLibraryAccessFailureBlock)(NSError *error);

// This block is executed when saving an image by -writeImageToSavedPhotosAlbum:completionBlock: finishes. The assetURL can later be used to reference the saved image.
typedef void (^ALAssetsLibraryWriteImageCompletionBlock)(NSURL *assetURL, NSError *error);
// This block is executed when saving a video by -writeVideoAtPathToSavedPhotosAlbum:completionBlock: finishes. The assetURL can later be used to reference the saved video.
typedef void (^ALAssetsLibraryWriteVideoCompletionBlock)(NSURL *assetURL, NSError *error);


NS_CLASS_AVAILABLE(NA, 4_0)
@interface ALAssetsLibrary : NSObject {
@package
    id _internal;
    
}

// Get the list of groups that match the given types. Multiple types can be ORed together. The results are passed one by one to the caller by executing the enumeration block.
// When the enumeration is done, 'enumerationBlock' will be called with group set to nil.
// When groups are enumerated, the user may be asked to confirm the application's access to the data. If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)enumerateGroupsWithTypes:(ALAssetsGroupType)types usingBlock:(ALAssetsLibraryGroupsEnumerationResultsBlock)enumerationBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock;

// Returns an ALAsset object in the result block for a URL previously retrieved from an ALAsset object.
// When the ALAsset is requested, the user may be asked to confirm the application's access to the data. If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)assetForURL:(NSURL *)assetURL resultBlock:(ALAssetsLibraryAssetForURLResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock;

// Returns an ALAssetsGroup object in the result block for a URL previously retrieved from an ALAssetsGroup object.
// When the ALAssetsGroup is requested, the user may be asked to confirm the application's access to the data.  If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)groupForURL:(NSURL *)groupURL resultBlock:(ALAssetsLibraryGroupResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// Add a new ALAssetsGroup to the library.
// The name of the ALAssetsGroup is name and the type is ALAssetsGroupAlbum.  The editable property of this ALAssetsGroup returns YES.
// If name conflicts with another ALAssetsGroup with the same name, then the group is not created and the result block returns a nil group.
// When the ALAssetsGroup is added, the user may be asked to confirm the application's access to the data.  If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)addAssetsGroupAlbumWithName:(NSString *)name resultBlock:(ALAssetsLibraryGroupResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// These methods can be used to add photos or videos to the saved photos album.

// With a UIImage, the API user can use -[UIImage CGImage] to get a CGImageRef, and cast -[UIImage imageOrientation] to ALAssetOrientation.
- (void)writeImageToSavedPhotosAlbum:(CGImageRef)imageRef orientation:(ALAssetOrientation)orientation completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock;

// The API user will have to specify the orientation key in the metadata dictionary to preserve the orientation of the image
- (void)writeImageToSavedPhotosAlbum:(CGImageRef)imageRef metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_1);

// If there is a conflict between the metadata in the image data and the metadata dictionary, the image data metadata values will be overwritten
- (void)writeImageDataToSavedPhotosAlbum:(NSData *)imageData metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_1);

- (void)writeVideoAtPathToSavedPhotosAlbum:(NSURL *)videoPathURL completionBlock:(ALAssetsLibraryWriteVideoCompletionBlock)completionBlock;
- (BOOL)videoAtPathIsCompatibleWithSavedPhotosAlbum:(NSURL *)videoPathURL;

@end

// Notifications

// This notification will be sent when the contents of the ALAssetsLibrary have changed from under the app that is using the data.
// The API user should retain the library object to receive this notification.
// The API user should discard any cached information and query ALAssetsLibrary again. Any ALAsset, ALAssetRepresentation, or ALAssetsGroup
// the user is holding on to should be considered invalid after finishing procesing the notification.
extern NSString *const ALAssetsLibraryChangedNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); 

// Errors

// Constant used by NSError to distinguish errors belonging to the AssetsLibrary domain
extern NSString *const ALAssetsLibraryErrorDomain __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

// AssetsLibrary-related error codes
enum {
    ALAssetsLibraryUnknownError =                 -1,      // Error (reason unknown)
    
    // These errors would be returned in the ALAssetsLibraryWriteImageCompletionBlock and ALAssetsLibraryWriteVideoCompletionBlock completion blocks,
    // as well as in the completion selector for UIImageWriteToSavedPhotosAlbum() and UISaveVideoAtPathToSavedPhotosAlbum()
    ALAssetsLibraryWriteFailedError =           -3300,      // Write error (write failed)
    ALAssetsLibraryWriteBusyError =             -3301,      // Write error (writing is busy, try again)
    ALAssetsLibraryWriteInvalidDataError =      -3302,      // Write error (invalid data)
    ALAssetsLibraryWriteIncompatibleDataError = -3303,      // Write error (incompatible data)
    ALAssetsLibraryWriteDataEncodingError =     -3304,      // Write error (data has invalid encoding)
    ALAssetsLibraryWriteDiskSpaceError =        -3305,      // Write error (out of disk space)

    // This error would be returned in the ALAssetsLibraryAccessFailureBlock, ALAssetsLibraryWriteImageCompletionBlock, and ALAssetsLibraryWriteVideoCompletionBlock completion blocks,
    // as well as in the completion selector for UIImageWriteToSavedPhotosAlbum() and UISaveVideoAtPathToSavedPhotosAlbum()
    ALAssetsLibraryDataUnavailableError =       -3310,      // Data unavailable (data currently unavailable)    
    
    // These errors would be returned in the ALAssetsLibraryAccessFailureBlock
    ALAssetsLibraryAccessUserDeniedError =      -3311,      // Access error (user denied access request)
    ALAssetsLibraryAccessGloballyDeniedError =  -3312,      // Access error (access globally denied)
};

#endif
