/*
 *	@file CBUUID.h
 *	@framework CoreBluetooth
 *
 *  @discussion The CBUUID class represents bluetooth LE UUIDs. It automatically handles
 *     transformations of 16 and 32 bit UUIDs into 128 bit UUIDs.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>


/*!
 *  @const CBUUIDGenericAccessProfileString
 *  @discussion The string representation of the GAP UUID.
 */
CB_EXTERN NSString * const CBUUIDGenericAccessProfileString;
/*!
 *  @const CBUUIDGenericAttributeProfileString
 *  @discussion The string representation of the GATT UUID.
 */
CB_EXTERN NSString * const CBUUIDGenericAttributeProfileString;

/*!
 *  @const CBUUIDCharacteristicExtendedPropertiesString
 *  @discussion The string representation of the UUID for the extended properties descriptor.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicExtendedPropertiesString;
/*!
 *  @const CBUUIDCharacteristicUserDescriptionString
 *  @discussion The string representation of the UUID for the user description descriptor.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicUserDescriptionString;
/*!
 *  @const CBUUIDClientCharacteristicConfigurationString
 *  @discussion The string representation of the UUID for the client configuration descriptor.
 */
CB_EXTERN NSString * const CBUUIDClientCharacteristicConfigurationString;
/*!
 *  @const CBUUIDServerCharacteristicConfigurationString
 *  @discussion The string representation of the UUID for the server configuration descriptor.
 */
CB_EXTERN NSString * const CBUUIDServerCharacteristicConfigurationString;
/*!
 *  @const CBUUIDCharacteristicFormatString
 *  @discussion The string representation of the UUID for the format descriptor.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicFormatString;
/*!
 *  @const CBUUIDCharacteristicAggregateFormatString
 *  @discussion The string representation of the UUID for the aggregate descriptor.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicAggregateFormatString;

/*!
 *  @const CBUUIDDeviceNameString
 *  @discussion The string representation of the GAP device name UUID.
 */
CB_EXTERN NSString * const CBUUIDDeviceNameString;
/*!
 *  @const CBUUIDAppearanceString
 *  @discussion The string representation of the GAP appearance UUID.
 */
CB_EXTERN NSString * const CBUUIDAppearanceString;
/*!
 *  @const CBUUIDPeripheralPrivacyFlagString
 *  @discussion The string representation of the GAP privacy flag UUID.
 */
CB_EXTERN NSString * const CBUUIDPeripheralPrivacyFlagString;
/*!
 *  @const CBUUIDReconnectionAddressString
 *  @discussion The string representation of the GAP reconnection address UUID.
 */
CB_EXTERN NSString * const CBUUIDReconnectionAddressString;
/*!
 *  @const CBUUIDPeripheralPreferredConnectionParametersString
 *  @discussion The string representation of the GAP preferred connection parameter UUID.
 */
CB_EXTERN NSString * const CBUUIDPeripheralPreferredConnectionParametersString;
/*!
 *  @const CBUUIDServiceChangedString
 *  @discussion The string representation of the GATT service changed UUID.
 */
CB_EXTERN NSString * const CBUUIDServiceChangedString;



/*!
 * @class CBUUID
 *
 * @discussion
 *      A 16-bits, 32-bit, or 128 bits Bluetooth UUID.
 *      16-bits and 32-bits UUIDs are implicitely pre-filled with the Bluetooth Base UUID.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBUUID : NSObject <NSCopying>
{
@private
	NSData	*_data;
	NSRange	 _range;
}

/*!
 * @property data
 *
 *  @discussion
 *      The UUID as NSData.
 *
 */
@property(nonatomic, readonly) NSData *data;

/*!
 * @method UUIDWithString:
 *
 *  @discussion
 *      Creates a CBUUID with either a 16-bits, 32-bits, or 128-bits UUID string representation.
 *
 */
+ (CBUUID *)UUIDWithString:(NSString *)theString;

/*!
 * @method UUIDWithData:
 *
 *  @discussion
 *      Creates a CBUUID with either a 16-bits, 32-bits, or 128-bits UUID data container.
 *
 */
+ (CBUUID *)UUIDWithData:(NSData *)theData;

/*!
 * @method UUIDWithCFUUID:
 *
 *  @discussion
 *      Creates a CBUUID with a CFUUIDRef.
 *
 */
+ (CBUUID *)UUIDWithCFUUID:(CFUUIDRef)theUUID;

@end