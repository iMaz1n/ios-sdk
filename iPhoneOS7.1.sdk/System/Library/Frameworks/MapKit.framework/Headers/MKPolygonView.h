//
//  MKPolygonView.h
//  MapKit
//
//  Copyright (c) 2010-2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKPolygon.h>
#import <MapKit/MKOverlayPathView.h>
#import <MapKit/MKFoundation.h>

// Prefer MKPolygonRenderer
MK_CLASS_AVAILABLE(NA, 4_0)
@interface MKPolygonView : MKOverlayPathView

- (id)initWithPolygon:(MKPolygon *)polygon NS_DEPRECATED_IOS(4_0, 7_0);
@property (nonatomic, readonly) MKPolygon *polygon NS_DEPRECATED_IOS(4_0, 7_0);

@end
