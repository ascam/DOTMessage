#ifndef DOT_MESSAGE_DATETIME_FORMATS_HPP
#define DOT_MESSAGE_DATETIME_FORMATS_HPP

// Fixed text specifiers
static constexpr const char* kFormatSlash ="/";
static constexpr const char* kFormatColon =":";
static constexpr const char* kFormatEscapeChar ="\\";
static constexpr const char* kFormatString ="\"";
static constexpr const char* kFormatCharString ="\'";
static constexpr const char* kFormatPercentage ="%'";
// Day specifiers
static constexpr const char* kFormatdddd ="dddd";
static constexpr const char* kFormatddd ="ddd";
static constexpr const char* kFormatdd ="dd";
static constexpr const char* kFormatd ="d";
static constexpr const char* kFormatBracketsddd ="[ddd]";
static constexpr const char* kFormatBracketsdddd ="[dddd]";
// Year specifiers
static constexpr const char* kFormatyyyy ="yyyy";
static constexpr const char* kFormatyyy ="yyy";
static constexpr const char* kFormatyy ="yy";
static constexpr const char* kFormaty ="y";
// Hour specifiers
static constexpr const char* kFormathh ="hh";
static constexpr const char* kFormath ="h";
static constexpr const char* kFormatHH ="HH";
static constexpr const char* kFormatH ="H";
// Minute specifiers
static constexpr const char* kFormatmm ="mm";
static constexpr const char* kFormatm ="m";
// Month specifiers
static constexpr const char* kFormatMMMM ="MMMM";
static constexpr const char* kFormatMMM ="MMM";
static constexpr const char* kFormatMM ="MM";
static constexpr const char* kFormatM ="M";
static constexpr const char* kFormatBracketsMMM ="[MMM]";
static constexpr const char* kFormatBracketsMMMM ="[MMMM]";
// Julina date specifiers
static constexpr const char* kFormatJJJ ="JJJ";
static constexpr const char* kFormatJ ="J";
static constexpr const char* kFormatBracketsJ ="[J]";      // deprecated in current nisx version
static constexpr const char* kFormatBracketsJJJ ="[JJJ]";  // deprecated in current nisx version
// Second specifiers
static constexpr const char* kFormatss ="ss";
static constexpr const char* kFormats ="s";
// Period specifiers
static constexpr const char* kFormattt ="tt";
static constexpr const char* kFormatt ="t";
// Week specifiers
static constexpr const char* kFormatww ="ww";
static constexpr const char* kFormatw ="w";

#endif
