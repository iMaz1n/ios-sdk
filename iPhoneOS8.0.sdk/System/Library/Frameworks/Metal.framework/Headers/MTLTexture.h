//
//  MTLTexture.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLResource.h>
#import <Metal/MTLDevice.h>
#import <Metal/MTLBuffer.h>
#import <Metal/MTLTypes.h>

/*!
 @enum MTLTextureType
 @abstract MTLTextureType describes the dimensionality of each image, and if multiple images are arranged into an array or cube.
 */
typedef NS_ENUM(NSUInteger, MTLTextureType)
{
    MTLTextureType1D = 0,
    MTLTextureType1DArray = 1,
    MTLTextureType2D = 2,
    MTLTextureType2DArray = 3,
    MTLTextureType2DMultisample = 4,
    MTLTextureTypeCube = 5,
    MTLTextureType3D = 7,
} NS_ENUM_AVAILABLE_IOS(8_0);

NS_CLASS_AVAILABLE_IOS(8_0)
@interface MTLTextureDescriptor : NSObject <NSCopying>

/*!
 @method texture2DDescriptorWithPixelFormat:width:height:mipmapped:
 @abstract Create a TextureDescriptor for a common 2D texture.
 */
+ (MTLTextureDescriptor*)texture2DDescriptorWithPixelFormat:(MTLPixelFormat)pixelFormat width:(NSUInteger)width height:(NSUInteger)height mipmapped:(BOOL)mipmapped;

/*!
 @method textureCubeDescriptorWithPixelFormat:size:mipmapped:
 @abstract Create a TextureDescriptor for a common Cube texture.
 */
+ (MTLTextureDescriptor*)textureCubeDescriptorWithPixelFormat:(MTLPixelFormat)pixelFormat size:(NSUInteger)size mipmapped:(BOOL)mipmapped;

/*!
 @property type
 @abstract The overall type of the texture to be created. The default value is MTLTextureType2D.
 */
@property (readwrite, nonatomic) MTLTextureType textureType;

/*!
 @property pixelFormat
 @abstract The pixel format to use when allocating this texture. This is also the pixel format that will be used to when the caller writes or reads pixels from this texture. The default value is MTLPixelFormatRGBA8Unorm.
 */
@property (readwrite, nonatomic) MTLPixelFormat pixelFormat;

/*!
 @property width
 @abstract The width of the texture to create. The default value is 1.
 */
@property (readwrite, nonatomic) NSUInteger width;

/*!
 @property height
 @abstract The height of the texture to create. The default value is 1.
 @discussion height If allocating a 1D texture, height must be 1.
 */
@property (readwrite, nonatomic) NSUInteger height;

/*!
 @property depth
 @abstract The depth of the texture to create. The default value is 1.
 @discussion depth When allocating any texture types other than 3D, depth must be 1.
 */
@property (readwrite, nonatomic) NSUInteger depth;

/*!
 @property mipmapLevelCount
 @abstract The number of mipmap levels to allocate. The default value is 1.
 @discussion When creating Buffer and Multisample textures, mipmapLevelCount must be 1.
 */
@property (readwrite, nonatomic) NSUInteger mipmapLevelCount;

/*!
 @property sampleCount
 @abstract The number of samples in the texture to create. The default value is 1.
 @discussion When creating Buffer and Array textures, sampleCount must be 1. Implementations may round sample counts up to the next supported value.
 */
@property (readwrite, nonatomic) NSUInteger sampleCount;

/*!
 @property arrayLength
 @abstract The number of array elements to allocate. The default value is 1.
 @discussion When allocating any non-Array texture type, arrayLength has to be 1. Otherwise it must be set to something greater than 1 and less than 2048.
 */
@property (readwrite, nonatomic) NSUInteger arrayLength;

/*!
 @property resourceOptions
 @abstract Options to control memory allocation parameters, etc.
 */
@property (readwrite, nonatomic) MTLResourceOptions resourceOptions;

@end

/*!
 @protocol MTLTexture
 @abstract MTLTexture represents a collection of 1D, 2D, or 3D images.
 @discussion
 Each image in a texture is a 1D, 2D, 2DMultisample, or 3D image. The texture contains one or more images arranged in a mipmap stack. If there are multiple mipmap stacks, each one is referred to as a slice of the texture. 1D, 2D, 2DMultisample, and 3D textures have a single slice. In 1DArray and 2DArray textures, every slice is an array element. A Cube texture always has 6 slices, one for each face. In a CubeArray texture, each set of six slices is one element in the array.
 
 Most APIs that operate on individual images in a texture address those images via a tuple of a Slice, and Mipmap Level within that slice.
 */
NS_AVAILABLE_IOS(8_0)
@protocol MTLTexture <MTLResource>

/*!
 @property rootResource
 @abstract The resource this texture was created from. It may be a texture or a buffer. If this texture is not reusing storage of another MTLResource, then nil is returned.
 */
@property (readonly) id <MTLResource> rootResource;

/*!
 @property type
 @abstract The type of this texture.
 */
@property (readonly) MTLTextureType textureType;


/*!
 @property pixelFormat
 @abstract The MTLPixelFormat that is used to interpret this texture's contents.
 */
@property (readonly) MTLPixelFormat pixelFormat;


/*!
 @property width
 @abstract The width of the MTLTexture instance in pixels.
 */
@property (readonly) NSUInteger width;


/*!
 @property height
 @abstract The height of the MTLTexture instance in pixels.
 @discussion. height is 1 if the texture is 1D.
 */
@property (readonly) NSUInteger height;


/*!
 @property depth
 @abstract The depth of this MTLTexture instance in pixels.
 @discussion If this MTLTexture is not a 3D texture, the depth is 1
 */
@property (readonly) NSUInteger depth;


/*!
 @property mipmapLevels
 @abstract The number of mipmap levels in each slice of this MTLTexture.
 */
@property (readonly) NSUInteger mipmapLevelCount;


/*!
 @property samples
 @abstract The number of samples in each pixel of this MTLTexture.
 @discussion If this texture is any type other than 2DMultisample, samples is 1.
 */
@property (readonly) NSUInteger sampleCount;


/*!
 @property arrayLength
 @abstract The number of array elements in this MTLTexture.
 @discussion For non-Array texture types, arrayLength is 1.
 */
@property (readonly) NSUInteger arrayLength;


/*!
 @property framebufferOnly
 @abstract If YES, this texture can only be used with a MTLAttachmentDescriptor, and cannot be used as a texture argument for MTLRenderCommandEncoder, MTLBlitCommandEncoder, or MTLComputeCommandEncoder. Furthermore, when this property's value is YES, readPixels/writePixels may not be used with this texture.
 @discussion Textures obtained from CAMetalDrawables may have this property set to YES, depending on the value of renderOnly passed to their parent CAMetalLayer. Textures created directly by the application will not have any restrictions.
 */
@property (readonly, getter = isFramebufferOnly) BOOL framebufferOnly;

/*!
 @method getBytes:bytesPerRow:bytesPerImage:fromRegion:mipmapLevel:slice:
 @abstract Copies a block of pixels from a texture slice into the application's memory.
 */
- (void)getBytes:(void *)pixelBytes bytesPerRow:(NSUInteger)bytesPerRow bytesPerImage:(NSUInteger)bytesPerImage fromRegion:(MTLRegion)region mipmapLevel:(NSUInteger)level slice:(NSUInteger)slice;

/*!
 @method replaceRegion:mipmapLevel:slice:withBytes:bytesPerRow:bytesPerImage:
 @abstract Copy a block of pixel data from the caller's pointer into a texture slice.
 */
- (void)replaceRegion:(MTLRegion)region mipmapLevel:(NSUInteger)level slice:(NSUInteger)slice withBytes:(const void *)pixelBytes bytesPerRow:(NSUInteger)bytesPerRow bytesPerImage:(NSUInteger)bytesPerImage;

/*!
 @method getBytes:bytesPerRow:fromRegion:mipmapLevel:
 @abstract Convenience for getBytes:bytesPerRow:bytesPerImage:fromRegion:mipmapLevel:slice: that doesn't require slice related arguments
 */
- (void)getBytes:(void *)pixelBytes bytesPerRow:(NSUInteger)bytesPerRow fromRegion:(MTLRegion)region mipmapLevel:(NSUInteger)level;

/*!
 @method replaceRegion:mipmapLevel:withBytes:bytesPerRow:
 @abstract Convenience for replaceRegion:mipmapLevel:slice:withBytes:bytesPerRow:bytesPerImage: that doesn't require slice related arguments
 */
- (void)replaceRegion:(MTLRegion)region mipmapLevel:(NSUInteger)level withBytes:(const void *)pixelBytes bytesPerRow:(NSUInteger)bytesPerRow;


/*!
 @method newTextureViewWithPixelFormat:
 @abstract Create a new texture which shares the same storage as the source texture, but with a different (but compatible) pixel format.
 */
- (id<MTLTexture>)newTextureViewWithPixelFormat:(MTLPixelFormat)pixelFormat;

@end

