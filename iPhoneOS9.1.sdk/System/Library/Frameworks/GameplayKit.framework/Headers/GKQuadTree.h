//
//  GKQuadTree.h
//  GKQuadTreeTest
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

/**
 * The individual node(s) that make up a GKQuadTree.  
 * Used as a hint for faster removal via [GKQuadTree removeData:WithNode:]
 */
@interface GKQuadTreeNode : NSObject
@end


/**
 * A tree data structure where each level has 4 children that subdivide a given space into the four quadrants.
 * Stores arbitrary NSObject data via points and quads.
 */
@interface GKQuadTree : NSObject

/**
 * Creates a quad tree with a given min position, max position and minimum allowed cell size
 *
 * @param min the minimum position (lower left corner) of the bounds of this quad tree
 * @param max the maximum position (upper right corner) of the bounds of this quad tree
 * @param minCellSize the minimum allowed cell size.  The quad tree will create quadrants that have a width or height smaller than this size.
 */
+(instancetype)quadTreeWithMinPosition:(vector_float2)min maxPosition:(vector_float2)max minCellSize:(float)minCellSize;
-(instancetype)initWithMinPosition:(vector_float2)min maxPosition:(vector_float2)max minCellSize:(float)minCellSize NS_DESIGNATED_INITIALIZER;

/**
 * Adds an NSObject to this quad tree with a given point.
 * This data will always reside in the leaf node its point is in.
 *
 * @param data the data to store
 * @param point the point associated with the data you want to store
 * @return the quad tree node the data was added to
 */
-(GKQuadTreeNode*)addDataWithPoint:(NSObject*)data point:(vector_float2)point;

/**
 * Adds an NSObject to this quad tree with a given quad.
 * This data will reside in the lowest node that its quad fits in completely.
 *
 * @param data the data to store
 * @param quadOrigin the origin (lower left) of the quad associated with the data you want to store
 * @param quadSize the size (width,height) of the quad associated with the data you want to store
 * @return the quad tree node the data was added to
 */
-(GKQuadTreeNode*)addDataWithQuad:(NSObject*)data quadOrigin:(vector_float2)quadOrigin quadSize:(vector_float2)quadSize;

/**
 * Returns all of the data in the quad tree node this point would be placed in
 *
 * @param point the point to query
 * @return an NSArray of all the data found at the quad tree node this point would be placed in
 */
-(NSArray*)queryDataForPoint:(vector_float2)point;

/**
 * Returns all of the data that resides in quad tree nodes which intersect the given quad
 *
 * @param quadOrigin the origin (lower left) of the quad you want to test
 * @param quadSize the size (width,height) of the quad you want to test
 * @return an NSArray of all the data in all of the nodes that intersect the given quad
 *
 */
-(NSArray*)queryDataForQuad:(vector_float2)quadOrigin quadSize:(vector_float2)quadSize;

/**
 * Removes the given NSObject from this quad tree.
 * Note that this is an exhaustive search and is slow.
 * Cache the relevant GKQuadTreeNode and use removeData:WithNode: for better performance.
 *
 * @param data the data to be removed
 * @return returns YES if the data was removed, NO otherwise
 */
-(BOOL)removeData:(NSObject*)data;

/**
 * Removes the given NSObject from the given quad tree node
 * Note that this is not an exhaustive search and is faster than removeData:
 *
 * @param data the data to be removed
 * @param node the node in which this data resides
 * @return returns YES if the data was removed, NO otherwise
 */
-(BOOL)removeData:(NSObject*)data withNode:(GKQuadTreeNode*)node;

@end