//
//  GLKView.h
//  GLKit
//
//  Copyright (c) 2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

/*
 Enums for color buffer formats.
 */
typedef enum
{
	GLKViewDrawableColorFormatRGBA8888 = 0,
	GLKViewDrawableColorFormatRGB565,
} GLKViewDrawableColorFormat;

/*
 Enums for depth buffer formats.
 */
typedef enum
{
	GLKViewDrawableDepthFormatNone = 0,
	GLKViewDrawableDepthFormat16,
	GLKViewDrawableDepthFormat24,
} GLKViewDrawableDepthFormat;

/*
 Enums for stencil buffer formats.
 */
typedef enum
{
	GLKViewDrawableStencilFormatNone = 0,
	GLKViewDrawableStencilFormat8,
} GLKViewDrawableStencilFormat;

/*
 Enums for MSAA.
 */
typedef enum
{
	GLKViewDrawableMultisampleNone = 0,
	GLKViewDrawableMultisample4X,
} GLKViewDrawableMultisample;

@class EAGLContext;
@protocol GLKViewDelegate;

#pragma mark -
#pragma mark GLKView
#pragma mark -

NS_CLASS_AVAILABLE(NA, 5_0)
@interface GLKView : UIView <NSCoding>
{

}

- (id)initWithFrame:(CGRect)frame context:(EAGLContext *)context;

@property (nonatomic, assign) IBOutlet id <GLKViewDelegate> delegate;

@property (nonatomic, retain) EAGLContext *context;

@property (nonatomic, readonly) NSInteger drawableWidth;
@property (nonatomic, readonly) NSInteger drawableHeight;

@property (nonatomic) GLKViewDrawableColorFormat drawableColorFormat;
@property (nonatomic) GLKViewDrawableDepthFormat drawableDepthFormat;
@property (nonatomic) GLKViewDrawableStencilFormat drawableStencilFormat;
@property (nonatomic) GLKViewDrawableMultisample drawableMultisample;

/*
 Binds the context and drawable. This needs to be called when the currently bound framebuffer
 or renderbuffer has been changed during the draw method.
 */
- (void)bindDrawable;

/*
 deleteDrawable is normally invoked by the GLKViewController when an application is backgrounded, etc.
 It is the responsibility of the developer to call deleteDrawable when a GLKViewController isn't being used.
 */
- (void)deleteDrawable;

/*
 Returns a UIImage of the resulting draw. Snapshot should never be called from within the draw method or from a
 thread other than the main thread.
 */
- (UIImage *)snapshot;

/*
 Controls whether the view responds to setNeedsDisplay. If true, then the view behaves similarily to a UIView.
 When the view has been marked for display, the draw method is called during the next drawing cycle. If false,
 the view's draw method will never be called during the next drawing cycle. It is expected that -display will be
 called directly in this case. enableSetNeedsDisplay is automatically set to false when used in conjunction with
 the GLKViewController. This value is true by default.
 */
@property (nonatomic) BOOL enableSetNeedsDisplay;

/*
 -display should be called when the view has been set to ignore calls to setNeedsDisplay. This method is used by
 the GLKViewController to invoke the draw method. It can also be used when not using a GLKViewController and custom
 control of the display loop is needed.
 */
- (void)display;

@end

#pragma mark -
#pragma mark GLKViewDelegate
#pragma mark -

@protocol GLKViewDelegate <NSObject>

@required
/*
 Required method for implementing GLKViewDelegate. This draw method variant should be used when not subclassing GLKView.
 This method will not be called if the GLKView object has been subclassed and implements -(void)drawRect:(CGRect)rect.
 */
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect;

@end
