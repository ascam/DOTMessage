#ifndef MACSA_NISX_COMMON_NAMES_HPP
#define MACSA_NISX_COMMON_NAMES_HPP

namespace macsa {
	namespace nisx {

		static constexpr const char* kTextField = "TEXTFIELD";
		static constexpr const char* kBarcodeField = "BARCODEFIELD";
		static constexpr const char* kImageField = "IMAGEFIELD";
		static constexpr const char* kRectangleField = "RECTANGLEFIELD";
		static constexpr const char* kEllipseField = "ELLIPSEFIELD";
		static constexpr const char* kLineField = "LINEFIELD";
		static constexpr const char* kDiamondField = "DIAMONDFIELD";

		static constexpr const char* kName = "Name";
		static constexpr const char* kAttrValue = "Value";
		static constexpr const char* kSize = "Size";
		static constexpr const char* kType = "Type";

		// Common object tags and attributes
		static constexpr const char* kPosX = "X";
		static constexpr const char* kPosY = "Y";
		static constexpr const char* kWidth = "WIDTH";
		static constexpr const char* kHeight = "HEIGHT";
		static constexpr const char* kAngle = "ANGLE";
		static constexpr const char* kPrintable = "PRINTABLE";
		static constexpr const char* kLinked = "LINKED";
		static constexpr const char* kLinkedObject = "LINKED_OBJECT";
		static constexpr const char* kZOrder = "ZORDER";
		static constexpr const char* kLayer = "LAYOUT";
		static constexpr const char* kGSLevel = "GS_LEVEL"; //Not used
		static constexpr const char* kForeColor = "FORECOLOR";
		static constexpr const char* kBackColor = "BACKCOLOR";
		static constexpr const char* kAdjust = "ADJUST";

		// Fonts related tags
		static constexpr const char* kFont = "FONT";
		static constexpr const char* kBold = "BOLD";
		static constexpr const char* kItalic = "ITALIC";
		static constexpr const char* kUnderline = "UNDERLINE";
		static constexpr const char* kStrikeout = "STRIKEOUT";

		// Text field related tags
		static constexpr const char* kText = "TEXT";
		static constexpr const char* kHorizontal = "HORIZONTAL";
		static constexpr const char* kVertical = "VERTICAL";
		static constexpr const char* kFitToBox = "FITTOBOX";
		static constexpr const char* kParagraph = "PARAGRAPH";
		static constexpr const char* kMaxCharsLine = "MAXCHARSLINE";
		static constexpr const char* kAutoincrement = "AUTOINC";
		static constexpr const char* kInterLine = "INTERLINE";

		// Barcode field related tags
		static constexpr const char* kCode = "CODE";
		static constexpr const char* kSymbology = "SYMBOLOGY";
		static constexpr const char* kRatio = "RATIO";
		static constexpr const char* kDisplayChecksum = "DISPLAYCHECKSUM";
		static constexpr const char* kDisplayCode = "DISPLAYCODE";
		static constexpr const char* kQrVersion = "QRVERSION";
		static constexpr const char* kQrCorrectionLevel ="QRCORRECTIONLEVEL";
		static constexpr const char* kBearerStyle = "BEARERSTYLE";
		static constexpr const char* kShavingMode = "SHAVINGMODE";
		static constexpr const char* kShavingValue = "SHAVINGVALUE";
		static constexpr const char* kNormalized = "NORMALIZED";

		// Image field related tags
		static constexpr const char* kImage = "IMAGE";
		static constexpr const char* kAlignment = "ALIGNMENT";
		static constexpr const char* kAlgorithm = "ALGORITHM";
		static constexpr const char* kPath = "PATH";
		static constexpr const char* kTopThreshold = "TOPTHRESOLD";
		static constexpr const char* kDownThreshold = "DOWNTHRESOLD";

		// Primitives related tags
		static constexpr const char* kPen = "PEN";
		static constexpr const char* kColor = "COLOR";
		static constexpr const char* kBrush = "BRUSH";
		static constexpr const char* kFilled = "FILLED";
		static constexpr const char* kPrintBorder = "PRINTBORDER";
		static constexpr const char* kDashStyle = "DASHSTYLE";
		static constexpr const char* kDashCustom =  "DASHCUSTOM";

		// DataSources
		static constexpr const char* kDataSource = "DATASOURCE";
		static constexpr const char* kFormat = "FORMAT";
		static constexpr const char* kDefaultValue = "DEFAULT_VALUE";
		  // Counter Data Source
		static constexpr const char* kDataSourceCounter = "CibNeoDsCounter";
		  // DateTime Data Source
		static constexpr const char* kDateTime = "DATETIME";
		static constexpr const char* kDataSourceDatetime = "CibNeoDsDateTime";
		static constexpr const char* kOffsetDays = "OFFSETDAYS";
		static constexpr const char* kOffsetMonths = "OFFSETMONTHS";
		static constexpr const char* kOffsetYears = "OFFSETYEARS";
		static constexpr const char* kHourDayStart = "HOURDAYSTART";
		  // Composite Data Source
		static constexpr const char* kComposite = "COMPOSITE";
		static constexpr const char* kDataSourceComposite = "CibNeoDsCompositeField";
		static constexpr const char* kFormula = "FORMULA";
		  // Database Data Source
		static constexpr const char* kDatabase = "DATABASE";
		static constexpr const char* kDataSourceDatabase = "CibNeoDsDatabase";
		static constexpr const char* kFieldName = "FIELDNAME";
		  // User inputs Data Source
		static constexpr const char* kUserInput = "USERINPUT";
		static constexpr const char* kDataSourceUserInput = "CibNeoDsUserInput";
		static constexpr const char* kPrompt = "PROMPT";
		static constexpr const char* kValue = "VALUE";
		static constexpr const char* kUserText = "USER_TEXT";
		static constexpr const char* kUserInfo = "USER_INFO";
		static constexpr const char* kDevice = "DEVICE";
		static constexpr const char* kDate = "DATE";
		static constexpr const char* kPromptValueBehavior = "PROMPT_VALUE_BEHAVIOR";
		static constexpr const char* kRequired = "REQUIRED";
		static constexpr const char* kDataType = "DATATYPE";
		static constexpr const char* kMode = "Mode";
		static constexpr const char* kLength = "LENGTH";
		static constexpr const char* kMin = "MIN";
		static constexpr const char* kMax = "MAX";
		static constexpr const char* kAttrMin = "Min";
		static constexpr const char* kAttrMax = "Max";
		static constexpr const char* kPad = "PAD";
		static constexpr const char* kPaddingChar = "PADDING_CHAR";
		static constexpr const char* kRange = "RANGE";
	}
}

#endif
