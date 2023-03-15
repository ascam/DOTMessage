#ifndef DOT_MESSAGE_BARCODE_SYMBOLOGIES_HPP
#define DOT_MESSAGE_BARCODE_SYMBOLOGIES_HPP

#include "utils/smartenum.hpp"

namespace macsa {
	namespace dot {

		enum class NBarcodeSymbol {
			kCode128,
			kCode39,
			kCompactPdf417,
			kDataMatrix,
			kGS1DataMatrix,
			kGS1QRCode,
			kMicroPdf417,
			kMicroQRCode,
			kInterleaved2of5,
			kItf14,
			kQRCode,
			kEan13,
			kEan13CCA,
			kEan13CCB,
			kEan8,
			kEan8CCA,
			kEan8CCB,
			kPdf417,
			kPharmacode,
			kEan128,
			kEan128CCA,
			kEan128CCB,
			kEan128CCC,
			kGS1128,
			kGS1128CCA,
			kGS1128CCB,
			kGS1128CCC,
			kUpcA,
			kGS1DataBar14,
			kGS1DataBarExpanded,
			kGS1DataBarExpandedStacked,
			kGS1DataBarStacked,
			kRss14StackedOmnidirectional,
			kDotCode

			/*
			kAustraliaPost,
			kAustraliaPostDomesticEParcelBarcode,
			kAztecCode,
			kCodabar,
			kCode11,
			kCode16k,
			kCode32,
			kCode93,
			kDanishPostal39,
			kDeutschePostIdentcode,
			kDeutschePostLeitcode,
			kEan99,
			kEanUpcAddOn2,
			kEanUpcAddOn5,
			kEanVelocity,
			kFedExGround96,
			kFrenchPostal39AR,
			kGS1DataBar14CCA,
			kGS1DataBar14CCB,
			kGS1DataBar14Stacked,
			kGS1DataBar14StackedCCA,
			kGS1DataBar14StackedCCB,
			kGS1DataBar14StackedOmnidirectional,
			kGS1DataBar14StackedOmnidirectionalCCA,
			kGS1DataBar14StackedOmnidirectionalCCB,
			kGS1DataBar14Truncated,
			kGS1DataBar14TruncatedCCA,
			kGS1DataBar14TruncatedCCB,
			kGS1DataBarExpandedCCA,
			kGS1DataBarExpandedCCB,
			kGS1DataBarExpandedStackedCCA,
			kGS1DataBarExpandedStackedCCB,
			kGS1DataBarLimited,
			kGS1DataBarLimitedCCA,
			kGS1DataBarLimitedCCB,
			kGS1DataBarOmnidirectional,
			kGS1DataBarOmnidirectionalCCA,
			kGS1DataBarOmnidirectionalCCB,
			kGS1DataBarStackedCCA,
			kGS1DataBarStackedCCB,
			kGS1DataBarStackedOmnidirectional,
			kGS1DataBarStackedOmnidirectionalCCA,
			kGS1DataBarStackedOmnidirectionalCCB,
			kGS1DataBarTruncated,
			kGS1DataBarTruncatedCCA,
			kGS1DataBarTruncatedCCB,
			kHibcLic128,
			kHibcLic39,
			kHibcPas128,
			kHibcPas39,
			kIATA2of5,
			kIndustrial2of5,
			kIsbn,
			kIsbt128,
			kIsmn,
			kIssn,
			kItalianPost25,
			kJan13,
			kJan8,
			kKodakPatchCode,
			kMacroPdf417,
			kMatrix2of5,
			kMaxiCode,
			kMICRE13B,
			kMsi,
			kNumlyNumber,
			kOpc,
			kPlanet,
			kPostnet,
			kPzn,
			kRoyalMail,
			kRoyalTpgPostKix,
			kRss14,
			kRss14CCA,
			kRss14CCB,
			kRss14Stacked,
			kRss14StackedCCA,
			kRss14StackedCCB,
			kRss14StackedOmnidirectionalCCA,
			kRss14StackedOmnidirectionalCCB,
			kRss14Truncated,
			kRss14TruncatedCCA,
			kRss14TruncatedCCB,
			kRssExpanded,
			kRssExpandedCCA,
			kRssExpandedCCB,
			kRssExpandedStacked,
			kRssExpandedStackedCCA,
			kRssExpandedStackedCCB,
			kRssLimited,
			kRssLimitedCCA,
			kRssLimitedCCB,
			kScc14,
			kSemacode,
			kSingaporePost,
			kSscc18,
			kSwissPostParcel,
			kTelepen,
			kUccEan128,
			kUccEan128CCA,
			kUccEan128CCB,
			kUccEan128CCC,
			kUpcACCA,
			kUpcACCB,
			kUpcE,
			kUpcECCA,
			kUpcECCB,
			kUspsFim,
			kUspsHorizontalBars,
			kUspsIntelligentMail,
			kUspsIntelligentMailContainerBarcode,
			kUspsOneCode4CB,
			kUspsPicCode128,
			kUspsPicUccEan128,
			kUspsSackLabel,
			kUspsTrayLabel,
			kVicsBol,
			kVicsScacPro
			*/
		};

		class BarcodeSymbol final : public utils::SmartEnum<NBarcodeSymbol>
		{
			public:
				BarcodeSymbol (const NBarcodeSymbol& type = NBarcodeSymbol::kCode128) :
					utils::SmartEnum<NBarcodeSymbol>(type)
				{}
				BarcodeSymbol (const std::string& type) :
					utils::SmartEnum<NBarcodeSymbol>(NBarcodeSymbol::kCode128)
				{
					fromString(type);
				}

				const BarcodeSymbol& operator = (const std::string& val) {
					fromString(val);
					return *this;
				}

				const std::vector<std::pair<NBarcodeSymbol,std::string>>& getData() const override;
		};

		/**
		 * @brief Bearer bar style for Nisx Barcode
		 */
		enum class NBearerBarStyle
		{
			kNone,           // No Frame
			kFrame,          // Frame around the barcode
			kHorizontalRules // Frame lines on top and bottom
		};

		/**
		 * @brief Bearer bar style smart enum
		 */
		class BearerBarStyle final : public utils::SmartEnum<NBearerBarStyle>
		{
			public:
				BearerBarStyle(const NBearerBarStyle& style = NBearerBarStyle::kNone) :
				utils::SmartEnum<NBearerBarStyle>(style)
			{}

			BearerBarStyle(const std::string& style) :
				utils::SmartEnum<NBearerBarStyle>(NBearerBarStyle::kNone)
			{
				fromString(style);
			}

			const BearerBarStyle& operator = (const std::string& style) {
				fromString(style);
				return *this;
			}

		private:
			const std::vector<std::pair<NBearerBarStyle,std::string>>& getData() const override{
				static const std::vector<std::pair<NBearerBarStyle,std::string>> kNBearerBarStyleData {
					{NBearerBarStyle::kNone, "None"},
					{NBearerBarStyle::kFrame, "Frame"},
					{NBearerBarStyle::kHorizontalRules, "HorizontalRuler"}
				};
				return kNBearerBarStyleData;
			}
		};

		/**
		 * @brief QR code error correction capability
		 */
		enum class NQRCorrectionLevel
		{
			kL, // Level L, approx 7%
			kM, // Level M, approx 15%
			kQ, // Level Q, approx 25%
			kH // Level H, approx 30%
		};
		/**
		 * @brief QR correction level smart enum
		 */
		class QRCorrectionLevel final : public utils::SmartEnum<NQRCorrectionLevel>
		{
			public:
				QRCorrectionLevel(const NQRCorrectionLevel& level = NQRCorrectionLevel::kH) :
					utils::SmartEnum<NQRCorrectionLevel>(level)
				{}

				QRCorrectionLevel(const std::string& level) :
					utils::SmartEnum<NQRCorrectionLevel>(NQRCorrectionLevel::kH)
				{
					fromString(level);
				}

				const QRCorrectionLevel& operator = (const std::string& level) {
					fromString(level);
					return *this;
				}

			private:
				const std::vector<std::pair<NQRCorrectionLevel,std::string>>& getData() const override{
					static const std::vector<std::pair<NQRCorrectionLevel,std::string>> kNQRCorrectionLevelData {
						{NQRCorrectionLevel::kL, "L"},
						{NQRCorrectionLevel::kM, "M"},
						{NQRCorrectionLevel::kQ, "Q"},
						{NQRCorrectionLevel::kH, "H"}
					};
					return kNQRCorrectionLevelData;
				}
		};


		/**
		 * @brief GS1 AI separator character
		 */
		enum class NGS1AISeparator
		{
			kFNC1,
			kGS
		};
		/**
		 * @brief GS1 AI separator smart enum
		 */
		class GS1AISeparator final : public utils::SmartEnum<NGS1AISeparator>
		{
			public:
				GS1AISeparator(const NGS1AISeparator& separator = NGS1AISeparator::kFNC1) :
					utils::SmartEnum<NGS1AISeparator>(separator)
				{}

				GS1AISeparator(const std::string& separator) :
					utils::SmartEnum<NGS1AISeparator>(NGS1AISeparator::kFNC1)
				{
					fromString(separator);
				}

				const GS1AISeparator& operator = (const std::string& separator) {
					fromString(separator);
					return *this;
				}

			private:
				const std::vector<std::pair<NGS1AISeparator,std::string>>& getData() const override{
					static const std::vector<std::pair<NGS1AISeparator,std::string>> kNGS1AISeparatorData {
						{NGS1AISeparator::kFNC1, "FNC1"},
						{NGS1AISeparator::kGS,   "GS"},
					};
					return kNGS1AISeparatorData;
				}
		};
	}
}

#endif
