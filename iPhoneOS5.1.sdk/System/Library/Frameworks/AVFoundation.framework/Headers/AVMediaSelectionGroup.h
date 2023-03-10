/*
	File:  AVMediaSelectionGroup.h

	Framework:  AVFoundation
 
	Copyright 2011-2012 Apple Inc. All rights reserved.

*/

/*!
 @class			AVMediaSelectionGroup

 @abstract		AVMediaSelectionGroup provides a collection of mutually exclusive options for the presentation of media within an asset.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

@class AVMediaSelectionOption;
@class AVMediaSelectionGroupInternal;

NS_CLASS_AVAILABLE(TBD, 5_0)
@interface AVMediaSelectionGroup : NSObject <NSCopying> {
	AVMediaSelectionGroupInternal	*_mediaSelectionGroup;
}

/*!
 @property		options
 @abstract		A collection of mutually exclusive media selection options.
 @discussion	An NSArray of AVMediaSelectionOption*.
*/
@property (nonatomic, readonly) NSArray *options;

/*!
 @property		allowsEmptySelection
 @abstract		Indicates whether it's possible to present none of the options in the group when an associated AVPlayerItem is played.
 @discussion
	If allowsEmptySelection is YES, all of the available media options in the group can be deselected by passing nil
	as the specified AVMediaSelectionOption to -[AVPlayerItem selectMediaOption:inMediaSelectionGroup:].
*/
@property (nonatomic, readonly) BOOL allowsEmptySelection;

/*!
  @method		mediaSelectionOptionWithPropertyList:
  @abstract		Returns the instance of AVMediaSelectionOption with properties that match the specified property list.
  @param		plist
  				A property list previously obtained from an option in the group via -[AVMediaSelectionOption propertyList].
  @result		If the specified properties match those of an option in the group, an instance of AVMediaSelectionOption. Otherwise nil.
*/
- (AVMediaSelectionOption *)mediaSelectionOptionWithPropertyList:(id)plist;

@end


/*!
  @category		AVMediaSelectionOptionFiltering
  @abstract		Filtering of media selection options.
  @discussion
	The AVMediaSelectionOptionFiltering category is provided for convenience in filtering the media selection options in a group
	according to playability, locale, and media characteristics.
	Note that it's possible to implement additional filtering behaviors by using -[NSArray indexesOfObjectsPassingTest:].
*/
@interface AVMediaSelectionGroup (AVMediaSelectionOptionFiltering)

/*!
  @method		playableMediaSelectionOptionsFromArray:
  @abstract		Filters an array of AVMediaSelectionOptions according to whether they are playable.
  @param		array
  				An array of AVMediaSelectionOption to be filtered according to whether they are playable.
  @result		An instance of NSArray containing the media selection options of the specified NSArray that are playable.
*/
+ (NSArray *)playableMediaSelectionOptionsFromArray:(NSArray *)array;

/*!
  @method		mediaSelectionOptionsFromArray:withLocale:
  @abstract		Filters an array of AVMediaSelectionOptions according to locale.
  @param		array
				An array of AVMediaSelectionOption to be filtered by locale.
  @param		locale
  				The NSLocale that must be matched for a media selection option to be copied to the output array.
  @result		An instance of NSArray containing the media selection options of the specified NSArray that match the specified locale.
*/
+ (NSArray *)mediaSelectionOptionsFromArray:(NSArray *)array withLocale:(NSLocale *)locale;

/*!
  @method		mediaSelectionOptionsFromArray:withMediaCharacteristics:
  @abstract		Filters an array of AVMediaSelectionOptions according to one or more media characteristics.
  @param		array
  				An array of AVMediaSelectionOptions to be filtered by media characteristic.
  @param		mediaCharacteristics
  				The media characteristics that must be matched for a media selection option to be copied to the output array.
  @result		An instance of NSArray containing the media selection options of the specified NSArray that match the specified
				media characteristics.
*/
+ (NSArray *)mediaSelectionOptionsFromArray:(NSArray *)array withMediaCharacteristics:(NSArray *)mediaCharacteristics;

/*!
  @method		mediaSelectionOptionsFromArray:withoutMediaCharacteristics:
  @abstract		Filters an array of AVMediaSelectionOptions according to whether they lack one or more media characteristics.
  @param		array
  				An array of AVMediaSelectionOptions to be filtered by media characteristic.
  @param		mediaCharacteristics
  				The media characteristics that must not be present for a media selection option to be copied to the output array.
  @result		An instance of NSArray containing the media selection options of the specified NSArray that lack the specified
				media characteristics.
*/
+ (NSArray *)mediaSelectionOptionsFromArray:(NSArray *)array withoutMediaCharacteristics:(NSArray *)mediaCharacteristics;

@end


/*!
 @class			AVMediaSelectionOption

 @abstract		AVMediaSelectionOption represents a specific option for the presentation of media within a group of options.

*/

@class AVMediaSelectionOptionInternal;

NS_CLASS_AVAILABLE(TBD, 5_0)
@interface AVMediaSelectionOption : NSObject <NSCopying> {
	AVMediaSelectionOptionInternal	*_mediaSelectionOption;
}

/*!
 @property		mediaType
 @abstract		The media type of the media data, e.g. AVMediaTypeAudio, AVMediaTypeSubtitle, etc.
*/
@property (nonatomic, readonly) NSString *mediaType;

/*!
 @property		mediaSubTypes
 @abstract		The mediaSubTypes of the media data associated with the option. 
 @discussion
	An NSArray of NSNumbers carrying four character codes (of type FourCharCode) as defined in CoreAudioTypes.h for audio media and in CMFormatDescription.h for video media.
	Also see CMFormatDescriptionGetMediaSubType in CMFormatDescription.h for more information about media subtypes.
	
	Note that if no information is available about the encoding of the media presented when a media option is selected, the value of mediaSubTypes will be an empty array. This can occur, for example, with streaming media. In these cases the value of mediaSubTypes should simply not be used as a criteria for selection.
*/
@property (nonatomic, readonly) NSArray *mediaSubTypes;

/*!
  @method		hasMediaCharacteristic:
  @abstract		Reports whether the media selection option includes media with the specified media characteristic.
  @param		mediaCharacteristic
  				The media characteristic of interest, e.g. AVMediaCharacteristicVisual, AVMediaCharacteristicAudible, AVMediaCharacteristicLegible, etc.
  @result		YES if the media selection option includes media with the specified characteristic, otherwise NO.
*/
- (BOOL)hasMediaCharacteristic:(NSString *)mediaCharacteristic;

/*!
 @property		playable
 @abstract		Indicates whether a media selection option is playable.
 @discussion	If the media data associated with the option cannot be decoded or otherwise rendered, playable is NO.
*/
@property (nonatomic, readonly, getter=isPlayable) BOOL playable;

/*!
 @property		locale
 @abstract		Indicates the locale for which the media option was authored.
 @discussion
 	Use -[NSLocale objectForKey:NSLocaleLanguageCode] to obtain the language code of the locale. See NSLocale.h for additional information.
*/
@property (nonatomic, readonly) NSLocale *locale;

/*!
 @property		commonMetadata
 @abstract		Provides an array of AVMetadataItems for each common metadata key for which a value is available.
 @discussion
   The array of AVMetadataItems can be filtered according to locale via +[AVMetadataItem metadataItemsFromArray:withLocale:]
   or according to key via +[AVMetadataItem metadataItemsFromArray:withKey:keySpace:].
   Example: to obtain the name (or title) of a media selection option in the current locale.

	NSArray *titles = [AVMetadataItem metadataItemsFromArray:[mediaSelectionOption commonMetadata] withKey:AVMetadataCommonKeyTitle keySpace:AVMetadataKeySpaceCommon];
	if ([titles count] > 0)
	{
		// Try to get a title that matches one of the user's preferred languages.
		NSArray *preferredLanguages = [NSLocale preferredLanguages];
		
		for (NSString *thisLanguage in preferredLanguages)
		{
			NSLocale *locale = [[NSLocale alloc] initWithLocaleIdentifier:thisLanguage];
			NSArray *titlesForLocale = [AVMetadataItem metadataItemsFromArray:titles withLocale:locale];
			[locale release];
			if ([titlesForLocale count] > 0)
			{
				title = [[titlesForLocale objectAtIndex:0] stringValue];
				break;
			}
	
		}
		
		// No matches in any of the preferred languages. Just use the primary title metadata we find.
		if (title == nil)
		{
			title = [[titles objectAtIndex:0] stringValue];
		}
	}

*/
@property (nonatomic, readonly) NSArray *commonMetadata;

/*!
 @property		availableMetadataFormats
 @abstract		Provides an NSArray of NSStrings, each representing a metadata format that contains metadata associated with the option (e.g. ID3, iTunes metadata, etc.).
 @discussion
   Metadata formats are defined in AVMetadataFormat.h.
*/
@property (nonatomic, readonly) NSArray *availableMetadataFormats;

/*!
  @method		metadataForFormat:
  @abstract		Provides an NSArray of AVMetadataItems, one for each metadata item in the container of the specified format.
  @param		format
  				The metadata format for which items are requested.
  @result		An NSArray containing AVMetadataItems; may be nil if there is no metadata of the specified format.
*/
- (NSArray *)metadataForFormat:(NSString *)format;

/*!
  @method		associatedMediaSelectionOptionInMediaSelectionGroup
  @abstract		If a media selection option in another group is associated with the specified option, returns a reference to the associated option.
  @param		mediaSelectionGroup
  				A media selection group in which an associated option is to be sought.
  @result		An instance of AVMediaSelectionOption.
 @discussion
   Audible media selection options often have associated legible media selection options; in particular, audible options are typically associated with forced-only subtitle options with the same locale. See AVMediaCharacteristicContainsOnlyForcedSubtitles in AVMediaFormat.h for a discussion of forced-only subtitles.
*/
- (AVMediaSelectionOption *)associatedMediaSelectionOptionInMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup;

/*!
  @method		propertyList
  @abstract		Returns a serializable property list that can be used to obtain an instance of AVMediaSelectionOption representing the same option as the receiver via -[AVMediaSelectionGroup mediaSelectionOptionWithPropertyList:].
  @result		A serializable property list that's sufficient to identify the option within its group. For serialization utilities, see NSPropertyList.h.
*/
- (id)propertyList;

@end
