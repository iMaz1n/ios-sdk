/*	CFDateFormatter.h
	Copyright (c) 2003-2016, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFDATEFORMATTER__)
#define __COREFOUNDATION_CFDATEFORMATTER__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFLocale.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

typedef CFStringRef CFDateFormatterKey CF_STRING_ENUM;

typedef struct CF_BRIDGED_MUTABLE_TYPE(id) __CFDateFormatter *CFDateFormatterRef;

// CFDateFormatters are not thread-safe.  Do not use one from multiple threads!

CF_EXPORT
CFStringRef CFDateFormatterCreateDateFormatFromTemplate(CFAllocatorRef allocator, CFStringRef tmplate, CFOptionFlags options, CFLocaleRef locale) CF_AVAILABLE(10_6, 4_0);
	// no options defined, pass 0 for now

CF_EXPORT
CFTypeID CFDateFormatterGetTypeID(void);

// The exact formatted result for these date and time styles depends on the
// locale, but generally:
//     Short is completely numeric, such as "12/13/52" or "3:30pm"
//     Medium is longer, such as "Jan 12, 1952"
//     Long is longer, such as "January 12, 1952" or "3:30:32pm"
//     Full is pretty complete; e.g. "Tuesday, April 12, 1952 AD" or "3:30:42pm PST"
// The specifications though are left fuzzy, in part simply because a user's
// preference choices may affect the output, and also the results may change
// from one OS release to another.  To produce an exactly formatted date you
// should not rely on styles and localization, but set the format string and
// use nothing but numbers.

typedef CF_ENUM(CFIndex, CFDateFormatterStyle) {	// date and time format styles
    kCFDateFormatterNoStyle = 0,
    kCFDateFormatterShortStyle = 1,
    kCFDateFormatterMediumStyle = 2,
    kCFDateFormatterLongStyle = 3,
    kCFDateFormatterFullStyle = 4
};

typedef CF_OPTIONS(CFOptionFlags, CFISO8601DateFormatOptions) {
    /* The format for year is inferred based on whether or not the week of year option is specified.
     - if week of year is present, "YYYY" is used to display week dates.
     - if week of year is not present, "yyyy" is used by default.
     */
    kCFISO8601DateFormatWithYear API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = (1UL << 0),
    kCFISO8601DateFormatWithMonth API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = (1UL << 1),

    kCFISO8601DateFormatWithWeekOfYear API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = (1UL << 2),  // This includes the "W" prefix (e.g. "W49")

    /* The format for day is inferred based on provided options.
     - if month is not present, day of year ("DDD") is used.
     - if month is present, day of month ("dd") is used.
     - if either weekOfMonth or weekOfYear is present, local day of week ("ee") is used.
     */
    kCFISO8601DateFormatWithDay API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = (1UL << 4),

    kCFISO8601DateFormatWithTime API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = (1UL << 5),  // This uses the format "HH:mm:ss"
    kCFISO8601DateFormatWithTimeZone API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = (1UL << 6),

    kCFISO8601DateFormatWithSpaceBetweenDateAndTime API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = (1UL << 7),  // Use space instead of "T"
    kCFISO8601DateFormatWithDashSeparatorInDate API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = (1UL << 8),  // Add separator for date ("-")
    kCFISO8601DateFormatWithColonSeparatorInTime API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = (1UL << 9),  // Add separator for time (":")
    kCFISO8601DateFormatWithColonSeparatorInTimeZone API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = (1UL << 10),  // Add ":" separator in timezone (eg. +08:00)

    kCFISO8601DateFormatWithFullDate API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithYear | kCFISO8601DateFormatWithMonth | kCFISO8601DateFormatWithDay | kCFISO8601DateFormatWithDashSeparatorInDate,
    kCFISO8601DateFormatWithFullTime API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithTime | kCFISO8601DateFormatWithColonSeparatorInTime | kCFISO8601DateFormatWithTimeZone | kCFISO8601DateFormatWithColonSeparatorInTimeZone,

    kCFISO8601DateFormatWithInternetDateTime API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithFullDate | kCFISO8601DateFormatWithFullTime,  // RFC3339
};

CF_EXPORT
CFDateFormatterRef CFDateFormatterCreateISO8601Formatter(CFAllocatorRef allocator, CFISO8601DateFormatOptions formatOptions) API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

CF_EXPORT
CFDateFormatterRef CFDateFormatterCreate(CFAllocatorRef allocator, CFLocaleRef locale, CFDateFormatterStyle dateStyle, CFDateFormatterStyle timeStyle);
	// Returns a CFDateFormatter, localized to the given locale, which
	// will format dates to the given date and time styles.

CF_EXPORT
CFLocaleRef CFDateFormatterGetLocale(CFDateFormatterRef formatter);

CF_EXPORT
CFDateFormatterStyle CFDateFormatterGetDateStyle(CFDateFormatterRef formatter);

CF_EXPORT
CFDateFormatterStyle CFDateFormatterGetTimeStyle(CFDateFormatterRef formatter);
	// Get the properties with which the date formatter was created.

CF_EXPORT
CFStringRef CFDateFormatterGetFormat(CFDateFormatterRef formatter);

CF_EXPORT
void CFDateFormatterSetFormat(CFDateFormatterRef formatter, CFStringRef formatString);
	// Set the format description string of the date formatter.  This
	// overrides the style settings.  The format of the format string
	// is as defined by the ICU library.  The date formatter starts with a
	// default format string defined by the style arguments with
	// which it was created.


CF_EXPORT
CFStringRef CFDateFormatterCreateStringWithDate(CFAllocatorRef allocator, CFDateFormatterRef formatter, CFDateRef date);

CF_EXPORT
CFStringRef CFDateFormatterCreateStringWithAbsoluteTime(CFAllocatorRef allocator, CFDateFormatterRef formatter, CFAbsoluteTime at);
	// Create a string representation of the given date or CFAbsoluteTime
	// using the current state of the date formatter.


CF_EXPORT
CFDateRef CFDateFormatterCreateDateFromString(CFAllocatorRef allocator, CFDateFormatterRef formatter, CFStringRef string, CFRange *rangep);

CF_EXPORT
Boolean CFDateFormatterGetAbsoluteTimeFromString(CFDateFormatterRef formatter, CFStringRef string, CFRange *rangep, CFAbsoluteTime *atp);
	// Parse a string representation of a date using the current state
	// of the date formatter.  The range parameter specifies the range
	// of the string in which the parsing should occur in input, and on
	// output indicates the extent that was used; this parameter can
	// be NULL, in which case the whole string may be used.  The
	// return value indicates whether some date was computed and
	// (if atp is not NULL) stored at the location specified by atp.


CF_EXPORT
void CFDateFormatterSetProperty(CFDateFormatterRef formatter, CFStringRef key, CFTypeRef value);

CF_EXPORT
CFTypeRef CFDateFormatterCopyProperty(CFDateFormatterRef formatter, CFDateFormatterKey key);
	// Set and get various properties of the date formatter, the set of
	// which may be expanded in the future.

CF_EXPORT const CFDateFormatterKey kCFDateFormatterIsLenient;	// CFBoolean
CF_EXPORT const CFDateFormatterKey kCFDateFormatterTimeZone;		// CFTimeZone
CF_EXPORT const CFDateFormatterKey kCFDateFormatterCalendarName;	// CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterDefaultFormat;	// CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterTwoDigitStartDate; // CFDate
CF_EXPORT const CFDateFormatterKey kCFDateFormatterDefaultDate;	// CFDate
CF_EXPORT const CFDateFormatterKey kCFDateFormatterCalendar;		// CFCalendar
CF_EXPORT const CFDateFormatterKey kCFDateFormatterEraSymbols;	// CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterMonthSymbols;	// CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterShortMonthSymbols; // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterWeekdaySymbols;	// CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterShortWeekdaySymbols; // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterAMSymbol;		// CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterPMSymbol;		// CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterLongEraSymbols CF_AVAILABLE(10_5, 2_0);   // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterVeryShortMonthSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterStandaloneMonthSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterShortStandaloneMonthSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterVeryShortStandaloneMonthSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterVeryShortWeekdaySymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterStandaloneWeekdaySymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterShortStandaloneWeekdaySymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterVeryShortStandaloneWeekdaySymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterQuarterSymbols CF_AVAILABLE(10_5, 2_0); 	// CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterShortQuarterSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterStandaloneQuarterSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterShortStandaloneQuarterSymbols CF_AVAILABLE(10_5, 2_0); // CFArray of CFString
CF_EXPORT const CFDateFormatterKey kCFDateFormatterGregorianStartDate CF_AVAILABLE(10_5, 2_0); // CFDate
CF_EXPORT const CFDateFormatterKey kCFDateFormatterDoesRelativeDateFormattingKey CF_AVAILABLE(10_6, 4_0); // CFBoolean

// See CFLocale.h for these calendar constants:
//	const CFStringRef kCFGregorianCalendar;
//	const CFStringRef kCFBuddhistCalendar;
//	const CFStringRef kCFJapaneseCalendar;
//	const CFStringRef kCFIslamicCalendar;
//	const CFStringRef kCFIslamicCivilCalendar;
//	const CFStringRef kCFHebrewCalendar;
//	const CFStringRef kCFChineseCalendar;
//	const CFStringRef kCFRepublicOfChinaCalendar;
//	const CFStringRef kCFPersianCalendar;
//	const CFStringRef kCFIndianCalendar;
//	const CFStringRef kCFISO8601Calendar;

CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFDATEFORMATTER__ */

