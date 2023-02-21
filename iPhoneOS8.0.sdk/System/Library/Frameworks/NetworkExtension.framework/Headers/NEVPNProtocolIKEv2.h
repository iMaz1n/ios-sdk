/*
 * Copyright (c) 2014 Apple Inc.
 * All rights reserved.
 */

#import <NetworkExtension/NEVPNProtocolIPSec.h>

/*!
 * @typedef NEVPNIKEv2EncryptionAlgorithm
 * @abstract IKEv2 Encryption Algorithms
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2EncryptionAlgorithm) {
	/*! @const NEVPNIKEv2EncryptionAlgorithmDES Data Encryption Standard (DES) */
	NEVPNIKEv2EncryptionAlgorithmDES = 1,
	/*! @const NEVPNIKEv2EncryptionAlgorithm3DES Triple Data Encryption Algorithm (aka 3DES) */
	NEVPNIKEv2EncryptionAlgorithm3DES = 2,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES128 Advanced Encryption Standard 128 bit (AES128) */
	NEVPNIKEv2EncryptionAlgorithmAES128 = 3,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES256 Advanced Encryption Standard 256 bit (AES256) */
	NEVPNIKEv2EncryptionAlgorithmAES256 = 4,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @typedef NEVPNIKEv2IntegrityAlgorithm
 * @abstract IKEv2 Integrity Algorithms
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2IntegrityAlgorithm) {
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA96 SHA-1 96 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA96 = 1,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA160 SHA-1 160 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA160 = 2,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA256 SHA-2 256 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA256 = 3,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA384 SHA-2 384 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA384 = 4,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA512 SHA-2 512 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA512 = 5,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @typedef NEVPNIKEv2DeadPeerDetectionRate
 * @abstract IKEv2 Dead Peer Detection Rates
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2DeadPeerDetectionRate) {
	/*! @const NEVPNIKEv2DeadPeerDetectionRateNone Do not perform dead peer detection */
	NEVPNIKEv2DeadPeerDetectionRateNone = 0,
	/*! @const NEVPNIKEv2DeadPeerDetectionRateLow Run dead peer detection once every 60 minutes. If the peer does not respond, retry 5 times at 1 second intervals before declaring the peer dead */
	NEVPNIKEv2DeadPeerDetectionRateLow = 1,
	/*! @const NEVPNIKEv2DeadPeerDetectionRateMedium Run dead peer detection once every 30 minutes. If the peer does not respond, retry 5 times at 1 second intervals before declaring the peer dead */
	NEVPNIKEv2DeadPeerDetectionRateMedium = 2,
	/*! @const NEVPNIKEv2DeadPeerDetectionRateHigh Run dead peer detection once every 10 minute. If the peer does not respond, retry 5 times at 1 second intervals before declaring the peer dead */
	NEVPNIKEv2DeadPeerDetectionRateHigh = 3,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @typedef NEVPNIKEv2DiffieHellmanGroup
 * @abstract IKEv2 Diffie Hellman groups
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2DiffieHellmanGroup) {
	/*! @const NEVPNIKEv2DiffieHellmanGroup0 Diffie Hellman group 0 */
	NEVPNIKEv2DiffieHellmanGroup0 = 0,
	/*! @const NEVPNIKEv2DiffieHellmanGroup1 Diffie Hellman group 1 */
	NEVPNIKEv2DiffieHellmanGroup1 = 1,
	/*! @const NEVPNIKEv2DiffieHellmanGroup2 Diffie Hellman group 2 */
	NEVPNIKEv2DiffieHellmanGroup2 = 2,
	/*! @const NEVPNIKEv2DiffieHellmanGroup5 Diffie Hellman group 5 */
	NEVPNIKEv2DiffieHellmanGroup5 = 5,
	/*! @const NEVPNIKEv2DiffieHellmanGroup14 Diffie Hellman group 14 */
	NEVPNIKEv2DiffieHellmanGroup14 = 14,
	/*! @const NEVPNIKEv2DiffieHellmanGroup15 Diffie Hellman group 15 */
	NEVPNIKEv2DiffieHellmanGroup15 = 15,
	/*! @const NEVPNIKEv2DiffieHellmanGroup16 Diffie Hellman group 16 */
	NEVPNIKEv2DiffieHellmanGroup16 = 16,
	/*! @const NEVPNIKEv2DiffieHellmanGroup17 Diffie Hellman group 17 */
	NEVPNIKEv2DiffieHellmanGroup17 = 17,
	/*! @const NEVPNIKEv2DiffieHellmanGroup18 Diffie Hellman group 18 */
	NEVPNIKEv2DiffieHellmanGroup18 = 18,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @class NEVPNIKEv2SecurityAssociationParameters
 * @discussion The NEVPNIKEv2SecurityAssociationParameters class declares the programmatic interface of an object that manages parameters for an IPSec Security Association
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEVPNIKEv2SecurityAssociationParameters : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property encryptionAlgorithm
 * @discussion The algorithm used by the Security Association to encrypt and decrypt data. Default is NEVPNIKEv2EncryptionAlgorithm3DES.
 */
@property NEVPNIKEv2EncryptionAlgorithm encryptionAlgorithm NS_AVAILABLE(10_10, 8_0);

/*!
 * @property integrityAlgorithm
 * @discussion The algorithm used by the Security Association to verify the integrity of data. Default is NEVPNIKEv2IntegrityAlgorithmSHA96. The IKE psedo-random function algorithm will be inferred based on the integrity algorithm.
 */
@property NEVPNIKEv2IntegrityAlgorithm integrityAlgorithm NS_AVAILABLE(10_10, 8_0);

/*!
 * @property diffieHellmanGroup
 * @discussion The Diffie Hellman group used by the Security Association. Default is NEVPNIKEv2DiffieHellmanGroup2.
 */
@property NEVPNIKEv2DiffieHellmanGroup diffieHellmanGroup NS_AVAILABLE(10_10, 8_0);

/*!
 * @property lifetimeMinutes
 * @discussion The life time of the Security Association, in minutes. Default is 60 for IKE Security Associations, and 30 for Child Security Associations. Before the liftime is reached, IKEv2 will attempt to rekey the Security Association to maintain the connection.
 */
@property int32_t lifetimeMinutes NS_AVAILABLE(10_10, 8_0);

@end

/*!
 * @interface NEVPNProtocolIKEv2
 * @discussion The NEVPNProtocolIKEv2 class declares the programmatic interface of an object that manages the IKEv2-specific portion of a VPN configuration.
 *
 * Instances of this class use IKE version 2 for key negotiation.
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEVPNProtocolIKEv2 : NEVPNProtocolIPSec

/*!
 * @property deadPeerDetectionRate
 * @discussion How frequently the IKEv2 client will run the dead peer detection algorithm.
 */
@property NEVPNIKEv2DeadPeerDetectionRate deadPeerDetectionRate NS_AVAILABLE(10_10, 8_0);

/*!
 * @property serverCertificateIssuerCommonName
 * @discussion A string containing the Subject Common Name field of the Certificate Authority certificate that issued the IKEv2 server's certificate.
 */
@property (copy) NSString *serverCertificateIssuerCommonName NS_AVAILABLE(10_10, 8_0);

/*!
 * @property serverCertificateCommonName
 * @discussion A string containing the value to verify in the IKEv2 server certificate's Subject Common Name field.
 */
@property (copy) NSString *serverCertificateCommonName NS_AVAILABLE(10_10, 8_0);

/*!
 * @property IKESecurityAssociationParameters
 * @discussion Parameters for the IKE SA
 */
@property (readonly) NEVPNIKEv2SecurityAssociationParameters *IKESecurityAssociationParameters NS_AVAILABLE(10_10, 8_0);

/*!
 * @property childSecurityAssociationParameters
 * @discussion Parameters for the child SA
 */
@property (readonly) NEVPNIKEv2SecurityAssociationParameters *childSecurityAssociationParameters NS_AVAILABLE(10_10, 8_0);

@end

