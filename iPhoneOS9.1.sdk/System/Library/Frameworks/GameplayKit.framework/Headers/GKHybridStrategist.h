//
//  GKHybridStrategist.h
//  GameplayKit
//
//  Created by Ross Dexter on 8/19/15.
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GKStrategist.h>


NS_ASSUME_NONNULL_BEGIN

GK_BASE_AVAILABILITY @interface GKHybridStrategist : NSObject <GKStrategist>

/**
 * The maximum number of samples that will be processed when searching for a move.
 */
@property (nonatomic, assign) NSUInteger budget;

@property (nonatomic, assign) NSUInteger explorationParameter;

@property (nonatomic, assign) NSUInteger maxLookAheadDepth;

@end

NS_ASSUME_NONNULL_END
