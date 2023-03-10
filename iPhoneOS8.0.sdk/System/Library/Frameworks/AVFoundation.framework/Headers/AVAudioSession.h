/*
	File:  AVAudioSession.h
	
	Framework:  AVFoundation
	
	Copyright 2009-2012 Apple Inc. All rights reserved.
	
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>	/* for NSTimeInterval */
#import <AvailabilityMacros.h>
#import <CoreAudio/CoreAudioTypes.h>

/* This protocol is available with iPhone 3.0 or later */
@protocol AVAudioSessionDelegate;
@class NSError, NSString, NSArray, NSNumber;
@class AVAudioSessionChannelDescription, AVAudioSessionPortDescription, AVAudioSessionRouteDescription, AVAudioSessionDataSourceDescription;

/*
 Notes on terminology used in this API.
 Some of the property names and class names in AVAudioSession differ from
 the names used in the 'C' language Audio Session API.  In this API, an audio 
 "route" is made up of zero or more input "ports" and zero or more ouput "ports". 
 If the current audio category does not support inputs, the route will consist purely of 
 outputs.  Conversely, if the category does not support output, the route will
 consist purely of inputs.  Categories that support simultaneous input and output
 will have both inputs and outputs in the route.  
 
 A "port" refers to a single input or output within an audio route.  Examples of 
 ports include built-in speaker, wired microphone, or Bluetooth A2DP output.
*/


#pragma mark -- enumerations --

/* For use with AVAudioSessionInterruptionNotification */
typedef NS_OPTIONS(NSUInteger, AVAudioSessionInterruptionOptions)
{
	AVAudioSessionInterruptionOptionShouldResume = 1
} NS_AVAILABLE_IOS(6_0);

/*  options for use when calling setActive:withOptions:error: 
AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation -- 
Notify an interrupted app that the interruption has ended and it may resume playback. Only valid on 
session deactivation. */
typedef NS_OPTIONS(NSUInteger, AVAudioSessionSetActiveOptions)
{
	AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation = 1
} NS_AVAILABLE_IOS(6_0);

/* values to use for setting overrideOutputAudioPort property
AVAudioSessionPortOverrideNone -- 
No override.  Return audio routing to the default state for the current audio category.
AVAudioSessionPortOverrideSpeaker -- 
Route audio output to speaker.  Use this override with AVAudioSessionCategoryPlayAndRecord, which by 
default routes the output to the receiver. */
typedef NS_ENUM(NSUInteger, AVAudioSessionPortOverride)
{
	AVAudioSessionPortOverrideNone    = 0,
	AVAudioSessionPortOverrideSpeaker = 'spkr'
} NS_AVAILABLE_IOS(6_0);

/* values for AVAudioSessionRouteChangeReasonKey in AVAudioSessionRouteChangeNotification userInfo dictionary
 AVAudioSessionRouteChangeReasonUnknown
	The reason is unknown.
 AVAudioSessionRouteChangeReasonNewDeviceAvailable
	A new device became available (e.g. headphones have been plugged in).
 AVAudioSessionRouteChangeReasonOldDeviceUnavailable
	The old device became unavailable (e.g. headphones have been unplugged).
 AVAudioSessionRouteChangeReasonCategoryChange
	The audio category has changed (e.g. AVAudioSessionCategoryPlayback has been changed to AVAudioSessionCategoryPlayAndRecord).
 AVAudioSessionRouteChangeReasonOverride
	The route has been overridden (e.g. category is AVAudioSessionCategoryPlayAndRecord and the output 
	has been changed from the receiver, which is the default, to the speaker).
 AVAudioSessionRouteChangeReasonWakeFromSleep
	The device woke from sleep.
 AVAudioSessionRouteChangeReasonNoSuitableRouteForCategory
	Returned when there is no route for the current category (for instance, the category is AVAudioSessionCategoryRecord
	but no input device is available).
 AVAudioSessionRouteChangeReasonRouteConfigurationChange
	Indicates that the set of input and/our output ports has not changed, but some aspect of their
	configuration has changed.  For example, a port's selected data source has changed.
*/
typedef NS_ENUM(NSUInteger, AVAudioSessionRouteChangeReason)
{
	AVAudioSessionRouteChangeReasonUnknown = 0,
	AVAudioSessionRouteChangeReasonNewDeviceAvailable = 1,
	AVAudioSessionRouteChangeReasonOldDeviceUnavailable = 2,
	AVAudioSessionRouteChangeReasonCategoryChange = 3,
	AVAudioSessionRouteChangeReasonOverride = 4,
	AVAudioSessionRouteChangeReasonWakeFromSleep = 6,
	AVAudioSessionRouteChangeReasonNoSuitableRouteForCategory = 7,
	AVAudioSessionRouteChangeReasonRouteConfigurationChange NS_ENUM_AVAILABLE_IOS(7_0) = 8
} NS_AVAILABLE_IOS(6_0);

/* values for setCategory:withOptions:error:
AVAudioSessionCategoryOptionMixWithOthers -- 
	This allows an application to change the default behavior of some audio session categories with regards
	to whether other applications can play while your session is active. The typical cases are:
	 (1) AVAudioSessionCategoryPlayAndRecord or AVAudioSessionCategoryMultiRoute
		 this will default to false, but can be set to true. This would allow other applications to play in the background
		 while an app had both audio input and output enabled
	 (2) AVAudioSessionCategoryPlayback
		 this will default to false, but can be set to true. This would allow other applications to play in the background,
		 but an app will still be able to play regardless of the setting of the ringer switch
	 (3) Other categories
		 this defaults to false and cannot be changed (that is, the mix with others setting of these categories
		 cannot be overridden. An application must be prepared for setting this property to fail as behaviour 
		 may change in future releases. If an application changes their category, they should reassert the 
		 option (it is not sticky across category changes).
 
AVAudioSessionCategoryOptionDuckOthers -- 
	If the current session category of an application allows mixing (Music playback in the background for 
	example), then that other audio will be ducked when the current application makes any sound. An example
	of this is the Nike app that does this as it provides periodic updates to its user (it ducks any music
	currently being played while it provides its status). This defaults to off. Note that the other audio 
	will be ducked for as long as the current session is active. You will need to deactivate your audio
	session when you want full volume playback of the other audio. 
    If your category is AVAudioSessionCategoryPlayback, AVAudioSessionCategoryPlayAndRecord, or 
	AVAudioSessionCategoryMultiRoute, by default the audio session will be non-mixable and non-ducking. 
	Setting this option will also make your category mixable with others (AVAudioSessionCategoryOptionMixWithOthers
	will be set).
 
AVAudioSessionCategoryOptionAllowBluetooth --
	This allows an application to change the default behaviour of some audio session categories with regards to showing
	bluetooth devices as available routes. The current category behavior is:
	 (1) AVAudioSessionCategoryPlayAndRecord
		 this will default to false, but can be set to true. This will allow a paired bluetooth device to show up as
		 an available route for input, while playing through the category-appropriate output
	 (2) AVAudioSessionCategoryRecord
		 this will default to false, but can be set to true. This will allow a paired bluetooth device to show up
		 as an available route for input
	 (3) Other categories
		 this defaults to false and cannot be changed (that is, enabling bluetooth for input in these categories is
		 not allowed)
		 An application must be prepared for setting this option to fail as behaviour may change in future releases.
		 If an application changes their category or mode, they should reassert the override (it is not sticky
		 across category and mode changes).
 
AVAudioSessionCategoryOptionDefaultToSpeaker --
	This allows an application to change the default behaviour of some audio session categories with regards to
	the audio route. The current category behavior is:
	 (1) AVAudioSessionCategoryPlayAndRecord category
		 this will default to false, but can be set to true. this will route to Speaker (instead of Receiver)
		 when no other audio route is connected.
	 (2) Other categories
		 this defaults to false and cannot be changed (that is, the default to speaker setting of these
		 categories cannot be overridden
		 An application must be prepared for setting this property to fail as behaviour may change in future releases.
		 If an application changes their category, they should reassert the override (it is not sticky across
		 category and mode changes). */
typedef NS_OPTIONS(NSUInteger, AVAudioSessionCategoryOptions)
{
	/* MixWithOthers is only valid with AVAudioSessionCategoryPlayAndRecord, AVAudioSessionCategoryPlayback, and  AVAudioSessionCategoryMultiRoute */
	AVAudioSessionCategoryOptionMixWithOthers		= 1,
	/* DuckOthers is only valid with AVAudioSessionCategoryPlayAndRecord, AVAudioSessionCategoryPlayback, and AVAudioSessionCategoryMultiRoute */
	AVAudioSessionCategoryOptionDuckOthers			= 2,
	/* AllowBluetooth is only valid with AVAudioSessionCategoryRecord and AVAudioSessionCategoryPlayAndRecord */
	AVAudioSessionCategoryOptionAllowBluetooth		= 4,
	/* DefaultToSpeaker is only valid with AVAudioSessionCategoryPlayAndRecord */
	AVAudioSessionCategoryOptionDefaultToSpeaker	= 8
} NS_AVAILABLE_IOS(6_0);

typedef NS_ENUM(NSUInteger, AVAudioSessionInterruptionType)
{
	AVAudioSessionInterruptionTypeBegan = 1,  /* the system has interrupted your audio session */
	AVAudioSessionInterruptionTypeEnded = 0,  /* the interruption has ended */
} NS_AVAILABLE_IOS(6_0);

/* Used in AVAudioSessionSilenceSecondaryAudioHintNotification to indicate whether optional secondary audio muting should begin or end */
typedef NS_ENUM(NSUInteger, AVAudioSessionSilenceSecondaryAudioHintType)
{
	AVAudioSessionSilenceSecondaryAudioHintTypeBegin = 1,  /* the system is indicating that another application's primary audio has started */
	AVAudioSessionSilenceSecondaryAudioHintTypeEnd = 0,    /* the system is indicating that another application's primary audio has stopped */
} NS_AVAILABLE_IOS(8_0);

/*!
	@enum AVAudioSessionRecordPermission values
	@abstract   These are the values returned by recordPermission.
	@constant   AVAudioSessionRecordPermissionUndetermined
		The user has not yet been asked for permission.
	@constant   AVAudioSessionRecordPermissionDenied
 		The user has been asked and has denied permission.
	@constant   AVAudioSessionRecordPermissionGranted
 		The user has been asked and has granted permission.
*/

typedef NS_OPTIONS(NSUInteger, AVAudioSessionRecordPermission)
{
	AVAudioSessionRecordPermissionUndetermined		= 'undt',
	AVAudioSessionRecordPermissionDenied			= 'deny',
	AVAudioSessionRecordPermissionGranted			= 'grnt'
} NS_AVAILABLE_IOS(8_0);

/*!
	@enum AVAudioSession error codes
	@abstract   These are the error codes returned from the AVAudioSession API.
	@constant   AVAudioSessionErrorCodeNone
		Operation succeeded.
	@constant   AVAudioSessionErrorCodeMediaServicesFailed
		The app attempted to use the audio session during or after a Media Services failure.  App should
 		wait for a AVAudioSessionMediaServicesWereResetNotification and then rebuild all its state.
	@constant	AVAudioSessionErrorCodeIsBusy
 		The app attempted to set its audio session inactive, but it is still actively playing and/or recording.
 	@constant	AVAudioSessionErrorCodeIncompatibleCategory
 		The app tried to perform an operation on a session but its category does not support it.
 		For instance, if the app calls setPreferredInputNumberOfChannels: while in a playback-only category.
	@constant	AVAudioSessionErrorCodeCannotInterruptOthers
		The app's audio session is non-mixable and trying to go active while in the background.
 		This is allowed only when the app is the NowPlaying app.
	@constant	AVAudioSessionErrorCodeMissingEntitlement
		The app does not have the required entitlements to perform an operation.
	@constant	AVAudioSessionErrorCodeSiriIsRecording
 		The app tried to do something with the audio session that is not allowed while Siri is recording.
 	@constant	AVAudioSessionErrorCodeCannotStartPlaying
		The app is not allowed to start recording and/or playing, usually because of a lack of audio key in
 		its Info.plist.  This could also happen if the app has this key but uses a category that can't record 
 		and/or play in the background (AVAudioSessionCategoryAmbient, AVAudioSessionCategorySoloAmbient, etc.).
	@constant	AVAudioSessionErrorCodeCannotStartRecording
		The app is not allowed to start recording, usually because it is starting a mixable recording from the
 		background and is not an Inter-App Audio app.
	@constant	AVAudioSessionErrorCodeBadParam
 		An illegal value was used for a property.
	@constant	AVAudioSessionErrorInsufficientPriority
 		The app was not allowed to set the audio category because another app (Phone, etc.) is controlling it.
	@constant	AVAudioSessionErrorCodeUnspecified
 		An unspecified error has occurred.
*/

typedef NS_ENUM(NSInteger, AVAudioSessionErrorCode)
{
	AVAudioSessionErrorCodeNone							=  0,
	AVAudioSessionErrorCodeMediaServicesFailed			= 'msrv',			/* 0x6D737276, 1836282486	*/
	AVAudioSessionErrorCodeIsBusy						= '!act',			/* 0x21616374, 560030580	*/
	AVAudioSessionErrorCodeIncompatibleCategory			= '!cat',			/* 0x21636174, 560161140	*/
	AVAudioSessionErrorCodeCannotInterruptOthers		= '!int',			/* 0x21696E74, 560557684	*/
	AVAudioSessionErrorCodeMissingEntitlement			= 'ent?',			/* 0x656E743F, 1701737535	*/
	AVAudioSessionErrorCodeSiriIsRecording				= 'siri',			/* 0x73697269, 1936290409	*/
	AVAudioSessionErrorCodeCannotStartPlaying			= '!pla',			/* 0x21706C61, 561015905	*/
	AVAudioSessionErrorCodeCannotStartRecording			= '!rec',			/* 0x21726563, 561145187	*/
	AVAudioSessionErrorCodeBadParam						= -50,
	AVAudioSessionErrorInsufficientPriority				= '!pri',			/* 0x21707269, 561017449	*/
	AVAudioSessionErrorCodeUnspecified					= 'what'			/* 0x77686174, 2003329396	*/
} NS_AVAILABLE_IOS(7_0);

#pragma mark -- AVAudioSession interface --
NS_CLASS_AVAILABLE(NA, 3_0)
@interface AVAudioSession : NSObject {
@private
    void * _impl;
}

 /* returns singleton instance */
+ (AVAudioSession*)sharedInstance;

/* Set the session active or inactive. Note that activating an audio session is a synchronous (blocking) operation.
 Therefore, we recommend that applications not activate their session from a thread where a long blocking operation will be problematic.
 Note that this method will throw an exception in apps linked on or after iOS 8 if the session is set inactive while it has running or 
 paused I/O (e.g. audio queues, players, recorders, converters, remote I/Os, etc.).
*/
- (BOOL)setActive:(BOOL)active error:(NSError **)outError;
- (BOOL)setActive:(BOOL)active withOptions:(AVAudioSessionSetActiveOptions)options error:(NSError **)outError NS_AVAILABLE_IOS(6_0);

/* set session category */
- (BOOL)setCategory:(NSString *)category error:(NSError **)outError;
/* set session category with options */
- (BOOL)setCategory:(NSString *)category withOptions: (AVAudioSessionCategoryOptions)options error:(NSError **)outError NS_AVAILABLE_IOS(6_0);

/* Returns an enum indicating whether the user has granted or denied permission to record, or has not been asked */
- (AVAudioSessionRecordPermission) recordPermission;

/* Checks to see if calling process has permission to record audio.  The 'response' block will be called
 immediately if permission has already been granted or denied.  Otherwise, it presents a dialog to notify
 the user and allow them to choose, and calls the block once the UI has been dismissed.  'granted'
 indicates whether permission has been granted.
 */
typedef void (^PermissionBlock)(BOOL granted);

- (void)requestRecordPermission:(PermissionBlock)response NS_AVAILABLE_IOS(7_0);

/* get session category. Examples: AVAudioSessionCategoryRecord, AVAudioSessionCategoryPlayAndRecord, etc. */
@property(readonly) NSString * category;

/* get the current set of AVAudioSessionCategoryOptions */
@property(readonly) AVAudioSessionCategoryOptions categoryOptions NS_AVAILABLE_IOS(6_0);

/* Modes modify the audio category in order to introduce behavior that is tailored to the specific
use of audio within an application. Examples:  AVAudioSessionModeVideoRecording, AVAudioSessionModeVoiceChat, AVAudioSessionModeMeasurement, etc. */
- (BOOL)setMode:(NSString *)mode error:(NSError **)outError NS_AVAILABLE_IOS(5_0); /* set session mode */
@property(readonly) NSString * mode NS_AVAILABLE_IOS(5_0); /* get session mode */

- (BOOL)overrideOutputAudioPort:(AVAudioSessionPortOverride)portOverride  error:(NSError **)outError NS_AVAILABLE_IOS(6_0);

/* Will be true when another application is playing audio.
Note: As of iOS 8.0, Apple recommends that most applications use secondaryAudioShouldBeSilencedHint instead of this property.
The otherAudioPlaying property will be true if any other audio (including audio from an app using AVAudioSessionCategoryAmbient)
is playing, whereas the secondaryAudioShouldBeSilencedHint property is more restrictive in its consideration of whether 
primary audio from another application is playing.  
*/
@property(readonly, getter=isOtherAudioPlaying) BOOL otherAudioPlaying  NS_AVAILABLE_IOS(6_0);

/* Will be true when another application with a non-mixable audio session is playing audio.  Applications may use
this property as a hint to silence audio that is secondary to the functionality of the application. For example, a game app
using AVAudioSessionCategoryAmbient may use this property to decide to mute its soundtrack while leaving its sound effects unmuted.
Note: This property is closely related to AVAudioSessionSilenceSecondaryAudioHintNotification.
*/
@property(readonly) BOOL secondaryAudioShouldBeSilencedHint  NS_AVAILABLE_IOS(8_0);

/* A description of the current route, consisting of zero or more input ports and zero or more output ports */
@property(readonly) AVAudioSessionRouteDescription * currentRoute NS_AVAILABLE_IOS(6_0);


/* Select a preferred input port for audio routing. If the input port is already part of the current audio route, this will have no effect.
   Otherwise, selecting an input port for routing will initiate a route change to use the preferred input port, provided that the application's
   session controls audio routing. */
- (BOOL) setPreferredInput:(AVAudioSessionPortDescription*)inPort error:(NSError **)outError NS_AVAILABLE_IOS(7_0);
@property(readonly) AVAudioSessionPortDescription * preferredInput NS_AVAILABLE_IOS(7_0); /* Get the preferred input port.  Will be nil if no preference has been set */

/* Get the set of input ports that are available for routing. Note that this property only applies to the session's current category and mode.
   For example, if the session's current category is AVAudioSessionCategoryPlayback, there will be no available inputs.  */
@property(readonly) NSArray * availableInputs NS_AVAILABLE_IOS(7_0); /* NSArray of AVAudioSessionPortDescription objects. */

@end


/* AVAudioSessionHardwareConfiguration manages the set of properties that reflect the current state of
 audio hardware in the current route.  Applications whose functionality depends on these properties should
 reevaluate them any time the route changes. */
@interface AVAudioSession (AVAudioSessionHardwareConfiguration)

/* Get and set preferred values for hardware properties.  Note: that there are corresponding read-only
 properties that describe the actual values for sample rate, I/O buffer duration, etc. */

	/* The preferred hardware sample rate for the session. The actual sample rate may be different. */
- (BOOL)setPreferredSampleRate:(double)sampleRate  error:(NSError **)outError NS_AVAILABLE_IOS(6_0);
@property(readonly) double preferredSampleRate NS_AVAILABLE_IOS(6_0);

	/* The preferred hardware IO buffer duration in seconds. The actual IO buffer duration may be different.  */
- (BOOL)setPreferredIOBufferDuration:(NSTimeInterval)duration error:(NSError **)outError;
@property(readonly) NSTimeInterval preferredIOBufferDuration;

	/* Sets the number of input channels that the app would prefer for the current route */
- (BOOL)setPreferredInputNumberOfChannels:(NSInteger)count error:(NSError **)outError NS_AVAILABLE_IOS(7_0);
@property(readonly) NSInteger preferredInputNumberOfChannels NS_AVAILABLE_IOS(7_0);

	/* Sets the number of output channels that the app would prefer for the current route */
- (BOOL)setPreferredOutputNumberOfChannels:(NSInteger)count error:(NSError **)outError NS_AVAILABLE_IOS(7_0);
@property(readonly) NSInteger preferredOutputNumberOfChannels NS_AVAILABLE_IOS(7_0);


/* Returns the largest number of audio input channels available for the current route */
@property (readonly) NSInteger	maximumInputNumberOfChannels NS_AVAILABLE_IOS(7_0);

/* Returns the largest number of audio output channels available for the current route */
@property (readonly) NSInteger	maximumOutputNumberOfChannels NS_AVAILABLE_IOS(7_0);

/* A value defined over the range [0.0, 1.0], with 0.0 corresponding to the lowest analog
gain setting and 1.0 corresponding to the highest analog gain setting.  Attempting to set values
outside of the defined range will result in the value being "clamped" to a valid input.  This is
a global input gain setting that applies to the current input source for the entire system.
When no applications are using the input gain control, the system will restore the default input
gain setting for the input source.  Note that some audio accessories, such as USB devices, may
not have a default value.  This property is only valid if inputGainSettable
is true.  Note: inputGain is key-value observable */
- (BOOL)setInputGain:(float)gain  error:(NSError **)outError NS_AVAILABLE_IOS(6_0);
@property(readonly) float inputGain NS_AVAILABLE_IOS(6_0); /* value in range [0.0, 1.0] */

/* True when audio input gain is available.  Some input ports may not provide the ability to set the
input gain, so check this value before attempting to set input gain. */
@property(readonly, getter=isInputGainSettable) BOOL inputGainSettable  NS_AVAILABLE_IOS(6_0);

/* True if input hardware is available. */
@property(readonly, getter=isInputAvailable) BOOL inputAvailable  NS_AVAILABLE_IOS(6_0);

/* DataSource methods are for use with routes that support input or output data source selection.
If the attached accessory supports data source selection, the data source properties/methods provide for discovery and 
selection of input and/or output data sources. Note that the properties and methods for data source selection below are
equivalent to the properties and methods on AVAudioSessionPortDescription. The methods below only apply to the currently 
routed ports. */

	/* NSArray of AVAudioSessionDataSourceDescriptions.  Key-value observable. */
@property(readonly) NSArray * inputDataSources NS_AVAILABLE_IOS(6_0);

	/* Get and set the currently selected data source.  Will be nil if no data sources are available. */
@property(readonly) AVAudioSessionDataSourceDescription * inputDataSource NS_AVAILABLE_IOS(6_0);
- (BOOL)setInputDataSource:(AVAudioSessionDataSourceDescription *)dataSource error:(NSError **)outError NS_AVAILABLE_IOS(6_0); 

	/* NSArray of AVAudioSessionDataSourceDescriptions.  Key-value observable. */
@property(readonly) NSArray * outputDataSources NS_AVAILABLE_IOS(6_0);

	/* Get and set currently selected data source.  Will be nil if no data sources are available. */
@property(readonly) AVAudioSessionDataSourceDescription * outputDataSource NS_AVAILABLE_IOS(6_0);
- (BOOL)setOutputDataSource:(AVAudioSessionDataSourceDescription *)dataSource error:(NSError **)outError NS_AVAILABLE_IOS(6_0); 


/* Current values for hardware properties.  Note that most of these properties have corresponding methods 
for getting and setting preferred values.  Input- and output-specific properties will generate an error if they are 
queried if the audio session category does not support them.  Each of these will return 0 (or 0.0) if there is an error.  */

	/* The current hardware sample rate */
@property(readonly) double sampleRate NS_AVAILABLE_IOS(6_0);

	/* The current number of hardware input channels. Is key-value observable */
@property(readonly) NSInteger inputNumberOfChannels NS_AVAILABLE_IOS(6_0);

	/* The current number of hardware output channels. Is key-value observable */
@property(readonly) NSInteger outputNumberOfChannels NS_AVAILABLE_IOS(6_0);

	/* The current output volume. Is key-value observable */
@property(readonly) float outputVolume  NS_AVAILABLE_IOS(6_0); /* value in range [0.0, 1.0] */

	/* The current hardware input latency in seconds. */
@property(readonly) NSTimeInterval inputLatency  NS_AVAILABLE_IOS(6_0);

	/* The current hardware output latency in seconds. */
@property(readonly) NSTimeInterval outputLatency  NS_AVAILABLE_IOS(6_0);

	/* The current hardware IO buffer duration in seconds. */
@property(readonly) NSTimeInterval IOBufferDuration  NS_AVAILABLE_IOS(6_0);

@end

@interface AVAudioSession (AVAudioSessionDeprecated)

/* The delegate property is deprecated. Instead, you should register for the NSNotifications named below. */
/* For example: 
 [[NSNotificationCenter defaultCenter] addObserver: myObject 
 selector:    @selector(handleInterruption:) 
 name:        AVAudioSessionInterruptionNotification 
 object:      [AVAudioSession sharedInstance]]; 
 */
@property(assign) id<AVAudioSessionDelegate> delegate NS_DEPRECATED_IOS(4_0, 6_0);


- (BOOL)setActive:(BOOL)active withFlags:(NSInteger)flags error:(NSError **)outError NS_DEPRECATED_IOS(4_0, 6_0);

@property(readonly) BOOL inputIsAvailable NS_DEPRECATED_IOS(3_0, 6_0); /* is input hardware available or not? */

/* deprecated.  Use the corresponding properties without "Hardware" in their names. */
@property(readonly) double currentHardwareSampleRate NS_DEPRECATED_IOS(3_0, 6_0);
@property(readonly) NSInteger currentHardwareInputNumberOfChannels NS_DEPRECATED_IOS(3_0, 6_0);
@property(readonly) NSInteger currentHardwareOutputNumberOfChannels NS_DEPRECATED_IOS(3_0, 6_0);
- (BOOL)setPreferredHardwareSampleRate:(double)sampleRate error:(NSError **)outError NS_DEPRECATED_IOS(3_0, 6_0);
@property(readonly) double preferredHardwareSampleRate NS_DEPRECATED_IOS(3_0, 6_0);

@end

#pragma mark -- Names for NSNotifications --

/* Registered listeners will be notified when the system has interrupted the audio session and when
 the interruption has ended.  Check the notification's userInfo dictionary for the interruption type -- either begin or end.
 In the case of an end interruption notification, check the userInfo dictionary for AVAudioSessionInterruptionOptions that
 indicate whether audio playback should resume.
 */
AVF_EXPORT NSString *const AVAudioSessionInterruptionNotification NS_AVAILABLE_IOS(6_0);

/* Registered listeners will be notified when a route change has occurred.  Check the notification's userInfo dictionary for the
 route change reason and for a description of the previous audio route.
 */
AVF_EXPORT NSString *const AVAudioSessionRouteChangeNotification NS_AVAILABLE_IOS(6_0);

/* Registered listeners will be notified if the media server is killed.  In the event that the server is killed,
 take appropriate steps to handle requests that come in before the server resets.  See Technical Q&A QA1749.
 */
AVF_EXPORT NSString *const AVAudioSessionMediaServicesWereLostNotification NS_AVAILABLE_IOS(7_0);

/* Registered listeners will be notified when the media server restarts.  In the event that the server restarts,
 take appropriate steps to re-initialize any audio objects used by your application.  See Technical Q&A QA1749.
 */
AVF_EXPORT NSString *const AVAudioSessionMediaServicesWereResetNotification NS_AVAILABLE_IOS(6_0);

/* Registered listeners that are currently in the foreground and have active audio sessions will be notified 
 when primary audio from other applications starts and stops.  Check the notification's userInfo dictionary 
 for the notification type -- either begin or end.
 Foreground applications may use this notification as a hint to enable or disable audio that is secondary
 to the functionality of the application. For more information, see the related property secondaryAudioShouldBeSilencedHint.
*/
AVF_EXPORT NSString *const AVAudioSessionSilenceSecondaryAudioHintNotification NS_AVAILABLE_IOS(8_0);

#pragma mark -- Keys for NSNotification userInfo dictionaries --

/* keys for AVAudioSessionInterruptionNotification */
	/* value is an NSNumber representing an AVAudioSessionInterruptionType */
AVF_EXPORT NSString *const AVAudioSessionInterruptionTypeKey NS_AVAILABLE_IOS(6_0);
	/* Only present for end interruption events.  Value is of type AVAudioSessionInterruptionOptions.*/
AVF_EXPORT NSString *const AVAudioSessionInterruptionOptionKey NS_AVAILABLE_IOS(6_0);
	
/* keys for AVAudioSessionRouteChangeNotification */
	/* value is an NSNumber representing an AVAudioSessionRouteChangeReason */
AVF_EXPORT NSString *const AVAudioSessionRouteChangeReasonKey NS_AVAILABLE_IOS(6_0);
	/* value is AVAudioSessionRouteDescription * */
AVF_EXPORT NSString *const AVAudioSessionRouteChangePreviousRouteKey NS_AVAILABLE_IOS(6_0);

/* keys for AVAudioSessionSilenceSecondaryAudioHintNotification */
/* value is an NSNumber representing an AVAudioSessionSilenceSecondaryAudioHintType */
AVF_EXPORT NSString *const AVAudioSessionSilenceSecondaryAudioHintTypeKey NS_AVAILABLE_IOS(8_0);

#pragma mark -- Values for the category property --

/*  Use this category for background sounds such as rain, car engine noise, etc.  
 Mixes with other music. */
AVF_EXPORT NSString *const AVAudioSessionCategoryAmbient;
	
/*  Use this category for background sounds.  Other music will stop playing. */
AVF_EXPORT NSString *const AVAudioSessionCategorySoloAmbient;

/* Use this category for music tracks.*/
AVF_EXPORT NSString *const AVAudioSessionCategoryPlayback;

/*  Use this category when recording audio. */
AVF_EXPORT NSString *const AVAudioSessionCategoryRecord;

/*  Use this category when recording and playing back audio. */
AVF_EXPORT NSString *const AVAudioSessionCategoryPlayAndRecord;

/*  Use this category when using a hardware codec or signal processor while
 not playing or recording audio. */
AVF_EXPORT NSString *const AVAudioSessionCategoryAudioProcessing;

/*  Use this category to customize the usage of available audio accessories and built-in audio hardware.
 For example, this category provides an application with the ability to use an available USB output 
 and headphone output simultaneously for separate, distinct streams of audio data. Use of 
 this category by an application requires a more detailed knowledge of, and interaction with, 
 the capabilities of the available audio routes.  May be used for input, output, or both.
 Note that not all output types and output combinations are eligible for multi-route.  Input is limited
 to the last-in input port. Eligible inputs consist of the following:
	AVAudioSessionPortUSBAudio, AVAudioSessionPortHeadsetMic, and AVAudioSessionPortBuiltInMic.  
 Eligible outputs consist of the following: 
	AVAudioSessionPortUSBAudio, AVAudioSessionPortLineOut, AVAudioSessionPortHeadphones, AVAudioSessionPortHDMI, 
	and AVAudioSessionPortBuiltInSpeaker.  
 Note that AVAudioSessionPortBuiltInSpeaker is only allowed to be used when there are no other eligible 
 outputs connected.  */
AVF_EXPORT NSString *const AVAudioSessionCategoryMultiRoute NS_AVAILABLE_IOS(6_0);

#pragma mark -- Values for the mode property --

/*!
@abstract      Modes modify the audio category in order to introduce behavior that is tailored to the specific
use of audio within an application.  Available in iOS 5.0 and greater.
 */

/* The default mode */
AVF_EXPORT NSString *const AVAudioSessionModeDefault NS_AVAILABLE_IOS(5_0);

/* Only valid with AVAudioSessionCategoryPlayAndRecord.  Appropriate for Voice over IP
(VoIP) applications.  Reduces the number of allowable audio routes to be only those
that are appropriate for VoIP applications and may engage appropriate system-supplied
signal processing.  Has the side effect of setting AVAudioSessionCategoryOptionAllowBluetooth */
AVF_EXPORT NSString *const AVAudioSessionModeVoiceChat NS_AVAILABLE_IOS(5_0);

/* Set by Game Kit on behalf of an application that uses a GKVoiceChat object; valid
 only with the AVAudioSessionCategoryPlayAndRecord category.
 Do not set this mode directly. If you need similar behavior and are not using
 a GKVoiceChat object, use AVAudioSessionModeVoiceChat instead. */
AVF_EXPORT NSString *const AVAudioSessionModeGameChat NS_AVAILABLE_IOS(5_0);

/* Only valid with AVAudioSessionCategoryPlayAndRecord or AVAudioSessionCategoryRecord.
 Modifies the audio routing options and may engage appropriate system-supplied signal processing. */
AVF_EXPORT NSString *const AVAudioSessionModeVideoRecording NS_AVAILABLE_IOS(5_0);

/* Appropriate for applications that wish to minimize the effect of system-supplied signal
processing for input and/or output audio signals. */
AVF_EXPORT NSString *const AVAudioSessionModeMeasurement NS_AVAILABLE_IOS(5_0);

/* Engages appropriate output signal processing for movie playback scenarios.  Currently
only applied during playback over built-in speaker. */
AVF_EXPORT NSString *const AVAudioSessionModeMoviePlayback NS_AVAILABLE_IOS(6_0);

/* Only valid with kAudioSessionCategory_PlayAndRecord. Reduces the number of allowable audio
routes to be only those that are appropriate for video chat applications. May engage appropriate
system-supplied signal processing.  Has the side effect of setting
AVAudioSessionCategoryOptionAllowBluetooth and AVAudioSessionCategoryOptionDefaultToSpeaker. */
AVF_EXPORT NSString *const AVAudioSessionModeVideoChat NS_AVAILABLE_IOS(7_0);

#pragma mark -- constants for port types --

/* input port types */
AVF_EXPORT NSString *const AVAudioSessionPortLineIn       NS_AVAILABLE_IOS(6_0); /* Line level input on a dock connector */
AVF_EXPORT NSString *const AVAudioSessionPortBuiltInMic   NS_AVAILABLE_IOS(6_0); /* Built-in microphone on an iOS device */
AVF_EXPORT NSString *const AVAudioSessionPortHeadsetMic   NS_AVAILABLE_IOS(6_0); /* Microphone on a wired headset.  Headset refers to an
																				   accessory that has headphone outputs paired with a
																				   microphone. */

/* output port types */
AVF_EXPORT NSString *const AVAudioSessionPortLineOut          NS_AVAILABLE_IOS(6_0); /* Line level output on a dock connector */
AVF_EXPORT NSString *const AVAudioSessionPortHeadphones       NS_AVAILABLE_IOS(6_0); /* Headphone or headset output */
AVF_EXPORT NSString *const AVAudioSessionPortBluetoothA2DP    NS_AVAILABLE_IOS(6_0); /* Output on a Bluetooth A2DP device */
AVF_EXPORT NSString *const AVAudioSessionPortBuiltInReceiver  NS_AVAILABLE_IOS(6_0); /* The speaker you hold to your ear when on a phone call */
AVF_EXPORT NSString *const AVAudioSessionPortBuiltInSpeaker   NS_AVAILABLE_IOS(6_0); /* Built-in speaker on an iOS device */
AVF_EXPORT NSString *const AVAudioSessionPortHDMI             NS_AVAILABLE_IOS(6_0); /* Output via High-Definition Multimedia Interface */
AVF_EXPORT NSString *const AVAudioSessionPortAirPlay          NS_AVAILABLE_IOS(6_0); /* Output on a remote Air Play device */
AVF_EXPORT NSString *const AVAudioSessionPortBluetoothLE	  NS_AVAILABLE_IOS(7_0); /* Output on a Bluetooth Low Energy device */

/* port types that refer to either input or output */
AVF_EXPORT NSString *const AVAudioSessionPortBluetoothHFP NS_AVAILABLE_IOS(6_0); /* Input or output on a Bluetooth Hands-Free Profile device */
AVF_EXPORT NSString *const AVAudioSessionPortUSBAudio     NS_AVAILABLE_IOS(6_0); /* Input or output on a Universal Serial Bus device */
AVF_EXPORT NSString *const AVAudioSessionPortCarAudio     NS_AVAILABLE_IOS(7_0); /* Input or output via Car Audio */

#pragma mark -- constants for data source locations, orientations, polar patterns, and channel roles --

/* The following represent the location of a data source on an iOS device. */
AVF_EXPORT NSString *const AVAudioSessionLocationUpper					NS_AVAILABLE_IOS(7_0);
AVF_EXPORT NSString *const AVAudioSessionLocationLower					NS_AVAILABLE_IOS(7_0);

/* The following represent the orientation or directionality of a data source on an iOS device. */
AVF_EXPORT NSString *const AVAudioSessionOrientationTop					NS_AVAILABLE_IOS(7_0);
AVF_EXPORT NSString *const AVAudioSessionOrientationBottom				NS_AVAILABLE_IOS(7_0);
AVF_EXPORT NSString *const AVAudioSessionOrientationFront				NS_AVAILABLE_IOS(7_0);
AVF_EXPORT NSString *const AVAudioSessionOrientationBack				NS_AVAILABLE_IOS(7_0);

/* The following represent the possible polar patterns for a data source on an iOS device. */
AVF_EXPORT NSString *const AVAudioSessionPolarPatternOmnidirectional	NS_AVAILABLE_IOS(7_0);
AVF_EXPORT NSString *const AVAudioSessionPolarPatternCardioid			NS_AVAILABLE_IOS(7_0);
AVF_EXPORT NSString *const AVAudioSessionPolarPatternSubcardioid		NS_AVAILABLE_IOS(7_0);

#pragma mark -- helper class interfaces --

/* 
 AVAudioSessionChannelDescription objects provide information about a port's audio channels.
 AudioQueues, AURemoteIO and AUVoiceIO instances can be assigned to communicate with specific 
 hardware channels by setting an array of <port UID, channel index> pairs.
 */
NS_CLASS_AVAILABLE(NA, 6_0)
@interface AVAudioSessionChannelDescription : NSObject {
@private
    void *_impl;
}

@property(readonly) NSString *			channelName;
@property(readonly) NSString *			owningPortUID;  /* the unique identifier (UID) for the channel's owning port */
@property(readonly) NSUInteger			channelNumber;  /* the index of this channel in its owning port's array of channels */
@property(readonly) AudioChannelLabel	channelLabel;	/* description of the physical location of this channel.   */

@end

NS_CLASS_AVAILABLE(NA, 6_0)
@interface AVAudioSessionPortDescription : NSObject {
@private
    void * _impl;
}

/* Value is one of the AVAudioSessionPort constants declared above. */
@property(readonly) NSString *	portType;

/* A descriptive name for the port */
@property(readonly) NSString *	portName;

/* A system-assigned unique identifier for the port */
@property(readonly) NSString *	UID;

/* Array of AVAudioSessionChannelDescription objects */
@property(readonly) NSArray *	channels;

/* Array of AVAudioSessionDataSourceDescription objects.  Will be nil if there are no selectable data sources. */
@property(readonly) NSArray *	dataSources NS_AVAILABLE_IOS(7_0);

/* Will be nil if there are no selectable data sources. In all other cases, this
 property reflects the currently selected data source.*/
@property(readonly) AVAudioSessionDataSourceDescription * selectedDataSource NS_AVAILABLE_IOS(7_0);

/* This property reflects the application's preferred data source for the Port.
 Will be nil if there are no selectable data sources or if no preference has been set.*/
@property(readonly) AVAudioSessionDataSourceDescription * preferredDataSource NS_AVAILABLE_IOS(7_0);

/* Select the preferred data source for this port. The input dataSource parameter must be one of the dataSources exposed by the dataSources property.
Note: if the port is part of the active audio route, changing the data source will likely
result in a route reconfiguration.  If the port is not part of the active route, selecting a new data source will
not result in an immediate route reconfiguration.  Use AVAudioSession's setPreferredInput:error: method to activate the port. */
- (BOOL) setPreferredDataSource:(AVAudioSessionDataSourceDescription *)dataSource error:(NSError **)outError NS_AVAILABLE_IOS(7_0);

@end

NS_CLASS_AVAILABLE(NA, 6_0)
@interface AVAudioSessionRouteDescription : NSObject {
@private
    void * _impl;
}

/* Array of AVAudioSessionPortDescription objects */
@property(readonly) NSArray * inputs;

/* Array of AVAudioSessionPortDescription objects */
@property(readonly) NSArray * outputs;
@end

NS_CLASS_AVAILABLE(NA, 6_0)
@interface AVAudioSessionDataSourceDescription : NSObject {
@private
    void * _impl;
}

/* system-assigned ID for the data source */
@property(readonly) NSNumber * dataSourceID;

/* human-readable name for the data source */
@property(readonly) NSString * dataSourceName;

/* Location and orientation can be used to distinguish between multiple data sources belonging to a single port.  For example, in the case of a port of type AVAudioSessionPortBuiltInMic, one can
   use these properties to differentiate between an upper/front-facing microphone and a lower/bottom-facing microphone. */

/* Describes the general location of a data source. Will be nil for data sources for which the location is not known. */
@property(readonly) NSString *	location NS_AVAILABLE_IOS(7_0);

/* Describes the orientation of a data source.  Will be nil for data sources for which the orientation is not known. */
@property(readonly) NSString *	orientation NS_AVAILABLE_IOS(7_0);

/* Array of one or more NSStrings describing the supported polar patterns for a data source.  Will be nil for data sources that have no selectable patterns. */
@property(readonly) NSArray *	supportedPolarPatterns NS_AVAILABLE_IOS(7_0);

/* Describes the currently selected polar pattern.  Will be nil for data sources that have no selectable patterns. */
@property(readonly) NSString *	selectedPolarPattern NS_AVAILABLE_IOS(7_0);

/* Describes the preferred polar pattern.  Will be nil for data sources that have no selectable patterns or if no preference has been set. */
@property(readonly) NSString *	preferredPolarPattern NS_AVAILABLE_IOS(7_0);

/* Select the desired polar pattern from the set of available patterns. Note: if the owning port and data source are part of the active audio route, 
   changing the polar pattern will likely result in a route reconfiguration. If the owning port and data source are not part of the active route,
   selecting a polar pattern will not result in an immediate route reconfiguration.  Use AVAudioSession's setPreferredInput:error: method
   to activate the port. Use setPreferredDataSource:error: to active the data source on the port. */
- (BOOL)setPreferredPolarPattern:(NSString *)pattern error:(NSError **)outError NS_AVAILABLE_IOS(7_0);

@end


#pragma mark -- AVAudioSessionDelegate protocol --
/* The AVAudioSessionDelegate protocol is deprecated. Instead you should register for notifications. */
@protocol AVAudioSessionDelegate <NSObject>
@optional 

- (void)beginInterruption; /* something has caused your audio session to be interrupted */

/* the interruption is over */
- (void)endInterruptionWithFlags:(NSUInteger)flags NS_AVAILABLE_IOS(4_0); /* Currently the only flag is AVAudioSessionInterruptionFlags_ShouldResume. */
		
- (void)endInterruption; /* endInterruptionWithFlags: will be called instead if implemented. */

/* notification for input become available or unavailable */
- (void)inputIsAvailableChanged:(BOOL)isInputAvailable;

@end


#pragma mark -- Deprecated enumerations --

/* Deprecated in iOS 6.0.  Use AVAudioSessionInterruptionOptions instead.
 Flags passed to you when endInterruptionWithFlags: is called on the delegate */
enum {
	AVAudioSessionInterruptionFlags_ShouldResume = 1
} NS_DEPRECATED_IOS(4_0, 6_0);

/* Deprecated in iOS 6.0.  Use AVAudioSessionSetActiveOptions instead.
 flags for use when calling setActive:withFlags:error: */
enum {	
	AVAudioSessionSetActiveFlags_NotifyOthersOnDeactivation = 1
} NS_DEPRECATED_IOS(4_0, 6_0);

