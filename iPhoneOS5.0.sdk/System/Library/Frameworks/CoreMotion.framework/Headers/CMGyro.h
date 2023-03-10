/*
 *  CMGyro.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMLogItem.h>

/*
 *  CMRotationRate
 *  
 *  Discussion:
 *    A structure containing 3-axis rotation rate data.
 *
 *  Fields:
 *    x:
 *      X-axis rotation rate in radians/second. The sign follows the right hand 
 *      rule (i.e. if the right hand is wrapped around the X axis such that the 
 *      tip of the thumb points toward positive X, a positive rotation is one 
 *      toward the tips of the other 4 fingers).
 *    y:
 *      Y-axis rotation rate in radians/second. The sign follows the right hand 
 *      rule (i.e. if the right hand is wrapped around the Y axis such that the 
 *      tip of the thumb points toward positive Y, a positive rotation is one 
 *      toward the tips of the other 4 fingers).
 *		z:
 *			Z-axis rotation rate in radians/second. The sign follows the right hand 
 *      rule (i.e. if the right hand is wrapped around the Z axis such that the 
 *      tip of the thumb points toward positive Z, a positive rotation is one 
 *      toward the tips of the other 4 fingers).
 */
typedef struct {
	double x;
	double y;
	double z;	
} CMRotationRate;

/*
 *  CMAccelerometerData
 *  
 *  Discussion:
 *    Contains a single accelerometer measurement.
 *
 */
NS_CLASS_AVAILABLE(NA,4_0)
@interface CMGyroData : CMLogItem
{
@private
	id _internal;
}

/*
 *  rotationRate
 *  
 *  Discussion:
 *    The rotation rate as measured by the gyro.
 *
 */
@property(readonly, nonatomic) CMRotationRate rotationRate;

@end