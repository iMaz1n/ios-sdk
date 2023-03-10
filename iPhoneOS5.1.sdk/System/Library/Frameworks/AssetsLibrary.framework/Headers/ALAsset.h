//
//  ALAsset.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * An ALAsset represents a photo or a video managed by the Photos application. Assets can have multiple representations, like
 * a photo which has been shot in RAW and JPG. Furthermore, representations of the same asset may have different dimensions.
 *
 */

#import <Foundation/Foundation.h>
#import <AssetsLibrary/ALAssetsLibrary.h>
#import <CoreGraphics/CoreGraphics.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

extern NSString *const ALErrorInvalidProperty __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

// Properties
extern NSString *const ALAssetPropertyType __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);             // An NSString that encodes the type of asset. One of ALAssetTypePhoto, ALAssetTypeVideo or ALAssetTypeUnknown.
extern NSString *const ALAssetPropertyLocation __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);         // CLLocation object with the location information of the asset. Only available if location services are enabled for the caller.
extern NSString *const ALAssetPropertyDuration __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);         // Play time duration of a video asset expressed as a double wrapped in an NSNumber. For photos, kALErrorInvalidProperty is returned.
extern NSString *const ALAssetPropertyOrientation __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);      // NSNumber containing an asset's orientation as defined by ALAssetOrientation.
extern NSString *const ALAssetPropertyDate __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);             // An NSDate with the asset's creation date.

// Properties related to multiple photo representations
extern NSString *const ALAssetPropertyRepresentations __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);  // Array with all the representations available for a given asset (e.g. RAW, JPEG). It is expressed as UTIs.
extern NSString *const ALAssetPropertyURLs __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);             // Dictionary that maps asset representation UTIs to URLs that uniquely identify the asset.

// Asset types
extern NSString *const ALAssetTypePhoto __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);                // The asset is a photo
extern NSString *const ALAssetTypeVideo __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);                // The asset is a video
extern NSString *const ALAssetTypeUnknown __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);              // The asset's type cannot be determined. It could be a sound file, a video or photo file that we don't know about, or something else. This is possible only for assets imported from a camera onto the device.

@class ALAssetRepresentation;

NS_CLASS_AVAILABLE(NA, 4_0)
@interface ALAsset : NSObject {
@package
    id _internal;
}

// Returns the value for a given property (as defined above). Calling it with an invalid property returns a ALErrorInvalidProperty error.
- (id)valueForProperty:(NSString *)property;

// Returns an ALAssetRepresentation object for the default representation of the ALAsset
- (ALAssetRepresentation *)defaultRepresentation;

// Returns an ALAssetRepresentation object for the given representation UTI. If the ALAsset does not
// support the representation, nil is returned.
- (ALAssetRepresentation *)representationForUTI:(NSString *)representationUTI;

// Returns a CGImage with a square thumbnail of the asset.  The size of the thumbnail is the appropriate size for the platform.  The thumbnail will be in the correct orientation.
- (CGImageRef)thumbnail;

// Returns a CGImage with an aspect ratio thumbnail of the asset.  The size of the thumbnail is the appropriate size for the platform.  The thumbnail will be in the correct orientation.
- (CGImageRef)aspectRatioThumbnail __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// Saves image data to the saved photos album as a new ALAsset that is considered a modified version of the calling ALAsset.
- (void)writeModifiedImageDataToSavedPhotosAlbum:(NSData *)imageData metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// Saves the video at the specified path to the saved photos album as a new ALAsset that is considered a modified version of the calling ALAsset.
- (void)writeModifiedVideoAtPathToSavedPhotosAlbum:(NSURL *)videoPathURL completionBlock:(ALAssetsLibraryWriteVideoCompletionBlock)completionBlock __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// Returns the original asset if the caller was saved as a modified version of an asset.
// Returns nil if the caller was not saved as a modified version of an asset.
@property (nonatomic, readonly) ALAsset *originalAsset __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// Returns YES if the application is able to edit the asset.  Returns NO if the application is not able to edit the asset.
// Applications are only allowed to edit assets that they originally wrote.
@property (nonatomic, readonly, getter=isEditable) BOOL editable __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// Replaces the image data in the calling asset with the supplied image data.
// The caller should check the editable property of the asset to see if it is possible to replace the image data.
// If the application is able to edit the asset, the completion block will return the same assetURL as the calling asset, since a new asset is not being created.
// If the application is not able to edit the asset, the completion block will return a nil assetURL and an ALAssetsLibraryWriteFailedError.
- (void)setImageData:(NSData *)imageData metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// Replaces the video data in the calling asset with the video at the specified path.
// The caller should check the editable property of the asset to see if it is possible to replace the video data.
// If the application is able to edit the asset, the completion block will return the same assetURL as the calling asset, since a new asset is not being created.
// If the application is not able to edit the asset (see the editable property on ALAsset), the completion block will return a nil assetURL and an ALAssetsLibraryWriteFailedError.
- (void)setVideoAtPath:(NSURL *)videoPathURL completionBlock:(ALAssetsLibraryWriteVideoCompletionBlock)completionBlock __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

@end

#endif
