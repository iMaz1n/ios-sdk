//
//  MKPolylineView.h
//  MapKit
//
//  Copyright (c) 2010-2013, Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <MapKit/MKPolyline.h>
#import <MapKit/MKOverlayPathView.h>
#import <MapKit/MKFoundation.h>

// Prefer MKPolylineRenderer
MK_CLASS_AVAILABLE(NA, 4_0)
@interface MKPolylineView : MKOverlayPathView

- (id)initWithPolyline:(MKPolyline *)polyline NS_DEPRECATED_IOS(4_0, 7_0);

@property (nonatomic, readonly) MKPolyline *polyline NS_DEPRECATED_IOS(4_0, 7_0);

@end
