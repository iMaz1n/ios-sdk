/* CoreImage - CIFeature.h

   Copyright (c) 2011 Apple, Inc.
   All rights reserved. */

#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>


/** Generic feature found by a CIDetector. */
CORE_IMAGE_CLASS_EXPORT
@interface CIFeature : NSObject {}

/** The type of the feature. */
@property (readonly, retain) NSString *type;
/** The bounds of the feature in the image it was detected in. */
@property (readonly, assign) CGRect bounds;

@end


/** Specifies the type of a feature that is a face. */
CORE_IMAGE_EXPORT NSString* const CIFeatureTypeFace;


/** A face feature found by a CIDetector.
 All positions are relative to the original image. */
CORE_IMAGE_CLASS_EXPORT
@interface CIFaceFeature : CIFeature {}

@property (readonly, assign) BOOL hasLeftEyePosition;
@property (readonly, assign) CGPoint leftEyePosition;
@property (readonly, assign) BOOL hasRightEyePosition;
@property (readonly, assign) CGPoint rightEyePosition;
@property (readonly, assign) BOOL hasMouthPosition;
@property (readonly, assign) CGPoint mouthPosition;

@end

