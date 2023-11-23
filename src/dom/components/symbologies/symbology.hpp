#ifndef DOT_MESSAGE_SYMBOLOGY_HPP
#define DOT_MESSAGE_SYMBOLOGY_HPP

#include "dom/components/barcodesymbologies.hpp"

namespace macsa {
	namespace  dot {
		class Symbology
		{
			public:
				Symbology(const BarcodeSymbol& symbol);
				Symbology(const Symbology&) = delete;
				virtual ~Symbology() = default;

				/**
				 * @brief GetSymbology. Getter method for barcode symbology enum
				 * @return The barcode symbology
				 */
				const BarcodeSymbol& GetSymbology() const {
					return _symbology;
				}

				/**
				 * @brief IsGS1Barcode. Getter method to know if barcode
				 * is part of GS1 standard.
				 * @return true if the barcode is part of the GS1 standard.
				 */
				virtual bool IsGS1Barcode() const = 0;

				/**
				 * @brief GetGS1AISeparator. Getter method to get the GS1 AI separator.
				 * @return The used GS1AISeparator.
				 */
				virtual GS1AISeparator GetGS1AISeparator() const = 0;

				/**
				 * @brief SetGS1AISeparator. Setter method to get the GS1 AI separator.
				 * @param separator: The GS1AISeparator to use.
				 */
				virtual void SetGS1AISeparator(const GS1AISeparator& separator) = 0;

				/**
				 * @brief GetSecurityLevel. Return CCX security level in int value
				 * @verbatim
				 * CCA = 1
				 * CCB = 2
				 * CCC = 3
				 * None CCX = -1
				 * @endverbatim
				 * @return a positive integer for CCX barcodes otherwise returns -1.
				 */
				virtual int GetSecurityLevel() const  = 0;

				/**
				 * @brief HasShavingMode. Getter method to know if barcode
				 * has shaving mode capability.
				 * @return true if the barcode has shaving mode capability,
				 * otherwise returns false.
				 */
				virtual bool HasShavingMode() const = 0;

				/**
				 * @brief IsShavingModeEnabled. Getter method for shaving mode enabled.
				 * @return true if the barcode has shaving mode enbled
				 */
				virtual bool IsShavingModeEnabled() const = 0;

				/**
				 * @brief EnableShavingMode. Setter method for shaving mode enabled.
				 * @param enable: bool to enable/disable shaving mode.
				 */
				virtual void EnableShavingMode(bool enable) = 0;

				/**
				 * @brief GetShavingValue. Getter method for shaving value.
				 * @return The shaving value rate in percentage.
				 */
				virtual double GetShavingValue() const = 0;

				/**
				 * @brief SetShavingValue. Setter method for shaving value.
				 * @param shavingValue: The shaving value rate in percentage (0.0 - 100.0).
				 */
				virtual void SetShavingValue(double shavingValue) = 0;

				/**
				 * @brief GetRatio. Getter method for barcode ratio. This is the ratio
				 * between the thinner and the heaviest line.
				 * @return the ratio between the thinner and the heaviest line.
				 */
				virtual double GetRatio() const = 0;

				/**
				 * @brief SetRatio. Setter method for barcode ratio. This is the relation
				 * between the thinner and the heaviest line.
				 * @param ratio: the ratio between the thinner and the heaviest line.
				 */
				virtual void SetRatio(double ratio) = 0;

				/**
				 * @brief IsKeepAspectRatioSupported. Getter method, informs the hability to change the aspect ratio.
				 * @return true: if the keep aspect ratio is supported.
				 */
				virtual bool IsKeepAspectRatioSupported() const = 0;

				/**
				 * @brief GetKeepAspectRatio. Getter method for keep aspect ratio property.
				 * @return keep aspect ratio value.
				 */
				virtual bool GetKeepAspectRatio() const = 0;

				/**
				 * @brief SetKeepAspectRatio. Setter method for keep aspect ratio property.
				 * @param keepAspectRatio: bool to set if the barcode must be rendered
				 * keeping aspect ratio.
				 */
				virtual void SetKeepAspectRatio(bool keepAspectRatio) = 0;

				/**
				 * @brief GetDisplayChecksum. Getter method for display checksum value
				 * in the human readable code.
				 * @return true if the checksum is visible, othrewise return false.
				 */
				virtual bool GetDisplayChecksum() const = 0;

				/**
				 * @brief SetDisplayChecksum. Setter method for display checksum value
				 * in the human readable code.
				 * @param displayChecksum: bool to set checksum visible in the human
				 * readable code
				 */
				virtual void SetDisplayChecksum(bool displayChecksum) = 0;

				/**
				 * @brief CanShowHumanReadableCode. Method to check if the code
				 * can be displayed.
				 * @return true if the barcode has de capability of display the
				 * code as human readable.
				 */
				virtual bool CanShowHumanReadableCode() const = 0;

				/**
				 * @brief GetShowHumanReadableCode. Getter method for show human readable code.
				 * If is enabled the code will be displayed under the barcode.
				 * @return if code will be displayed under the barcode.
				 */
				virtual bool GetShowHumanReadableCode() const = 0;

				/**
				 * @brief SetShowHumanReadableCode. Setter method for show human readable code.
				 * @param show: bool to set if code will be displayed under the barcode.
				 */
				virtual void SetShowHumanReadableCode(bool show) = 0;

				/**
				 * @brief IsBearerBarStyleSupported. Getter method to know if barcode
				 * has bearer capability.
				 * @return true if the barcode has bearer
				 * otherwise returns false.
				 */
				virtual bool IsBearerBarStyleSupported() const = 0;

				/**
				 * @brief GetBearerBarStyle. Getter method for bearer bars.
				 * @return Type of bearer bars.
				 */
				virtual BearerBarStyle GetBearerBarStyle() const = 0;

				/**
				 * @brief SetBearerBarStyle. Setter method for bearer bars.
				 * @param bearerBarSyle: Type of bearer bars.
				 */
				virtual void SetBearerBarStyle(const BearerBarStyle& bearerBarSyle) = 0;

				/**
				 * @brief IsQrCode. Getter method to check if symbol is part of
				 * QrCode family
				 * @return true if the symbology is part of QrCode family, otherwise
				 * returns false.
				 */
				virtual bool IsQrCode() const = 0;

				/**
				 * @brief GetQrVersion. Getter method for Qr version. Only valid for
				 * Qr codes.
				 * @return The version of the Qr code if the symbology is qr, otherwise
				 * return 0.
				 */
				virtual uint8_t GetQrVersion() const = 0;

				/**
				 * @brief SetQrVersion. Setter method for Qr version.
				 * @param qrVersion: Qr version to set. Only valid for Qr codes.
				 */
				virtual void SetQrVersion(uint8_t qrVersion) = 0;

				/**
				 * @brief GetQrCorrectionLevel. Getter method for QrCorrectionLevel.
				 * Only valid for Qr codes.
				 * @return The Qr Correction level.
				 */
				virtual QRCorrectionLevel GetQrCorrectionLevel() const = 0;

				/**
				 * @brief SetQrCorrectionLevel. Setter method for QrCorrectionLevel.
				 * @param qrCorrectionLevel: The Qr Correction level.
				 * Only valid for Qr codes.
				 */
				virtual void SetQrCorrectionLevel(const QRCorrectionLevel& qrCorrectionLevel) = 0;

			private:
				BarcodeSymbol _symbology;
		};

		class OneDimensionBarcode : public Symbology
		{
			public:
				OneDimensionBarcode(const BarcodeSymbol& symbol);
				virtual ~OneDimensionBarcode() = default;

				// Immutable methods
				bool HasShavingMode() const override {return false;}
				bool IsShavingModeEnabled() const override {return false;}
				void EnableShavingMode(bool enable) override {}
				double GetShavingValue() const override {return 0;}
				void SetShavingValue(double shavingValue) override {}
				// Qr related methods
				bool IsQrCode() const override {return false;}
				uint8_t GetQrVersion() const override {return 0;}
				void SetQrVersion(uint8_t qrVersion) override {}
				QRCorrectionLevel GetQrCorrectionLevel() const override {return NQRCorrectionLevel::kH;}
				void SetQrCorrectionLevel(const QRCorrectionLevel& qrCorrectionLevel) override {}
				// GS1 methods
				bool IsGS1Barcode() const override {return false;}
				GS1AISeparator GetGS1AISeparator() const override{
					return NGS1AISeparator::kFNC1;
				}
				void SetGS1AISeparator(const GS1AISeparator& separator) override{}
				//Security level
				int GetSecurityLevel() const override {return -1;}
				// 1D barcode methods
				double GetRatio() const override {
					return _ratio;
				}
				void SetRatio(double ratio) override {
					_ratio = ratio;
				}

				bool IsKeepAspectRatioSupported() const override {
					return true;
				}
				bool GetKeepAspectRatio() const override {
					return _keepAspectRatio;
				}
				void SetKeepAspectRatio(bool keepAspectRatio) override {
					_keepAspectRatio = keepAspectRatio;
				}
				bool GetDisplayChecksum() const override {
					return _displayChecksum;
				}
				void SetDisplayChecksum(bool displayChecksum) override {
					_displayChecksum = displayChecksum;
				}
				bool CanShowHumanReadableCode() const override {return true;}
				bool GetShowHumanReadableCode() const override {
					return _showHRT;
				}
				void SetShowHumanReadableCode(bool show) override {
					_showHRT = show;
				}

				bool IsBearerBarStyleSupported() const override
				{
					return true;
				}

				BearerBarStyle GetBearerBarStyle() const override {
					return _bearer;
				}
				void SetBearerBarStyle(const BearerBarStyle& bearerBarSyle) override {
					_bearer = bearerBarSyle;
				}

			private:
				double _ratio;
				bool _keepAspectRatio;
				bool _displayChecksum;
				bool _showHRT;
				BearerBarStyle _bearer;

		};

		class OneDimensionGS1Barcode : public OneDimensionBarcode
		{
			public:
				OneDimensionGS1Barcode(const BarcodeSymbol& symbol) :
					OneDimensionBarcode(symbol)
				{}
				virtual ~OneDimensionGS1Barcode() = default;

				bool IsGS1Barcode() const override {return true;}
				GS1AISeparator GetGS1AISeparator() const override{
					return _separator;
				}
				void SetGS1AISeparator(const GS1AISeparator& separator) override{
					_separator = separator;
				}

			private:
				GS1AISeparator _separator;
		};

		class Code128 final : public OneDimensionBarcode
		{
			public:
				Code128() :
					OneDimensionBarcode(NBarcodeSymbol::kCode128)
				{}
				virtual ~Code128() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Code39 final : public OneDimensionBarcode
		{
			public:
				Code39() :
					OneDimensionBarcode(NBarcodeSymbol::kCode39)
				{}
				virtual ~Code39() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Pharmacode final : public OneDimensionBarcode
		{
			public:
				Pharmacode() :
					OneDimensionBarcode(NBarcodeSymbol::kPharmacode)
				{}
				virtual ~Pharmacode() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class UpcA final : public OneDimensionBarcode
		{
			public:
				UpcA() :
					OneDimensionBarcode(NBarcodeSymbol::kUpcA)
				{}
				virtual ~UpcA() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class UpcE final : public OneDimensionBarcode
		{
			public:
				UpcE() :
					OneDimensionBarcode(NBarcodeSymbol::kUpcE)
				{}
				virtual ~UpcE() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Interleaved2of5 final : public OneDimensionBarcode
		{
			public:
				Interleaved2of5() :
					OneDimensionBarcode(NBarcodeSymbol::kInterleaved2of5)
				{}
				virtual ~Interleaved2of5() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Itf14 final : public OneDimensionBarcode
		{
			public:
				Itf14() :
					OneDimensionBarcode(NBarcodeSymbol::kItf14)
				{}
				virtual ~Itf14() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Ean13 final : public OneDimensionBarcode
		{
			public:
				Ean13() :
					OneDimensionBarcode(NBarcodeSymbol::kEan13)
				{}
				virtual ~Ean13() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Ean13CCA final : public OneDimensionBarcode
		{
			public:
				Ean13CCA() :
					OneDimensionBarcode(NBarcodeSymbol::kEan13CCA)
				{}
				virtual ~Ean13CCA() = default;
				//Security level
				int GetSecurityLevel() const override {return 1;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Ean13CCB final : public OneDimensionBarcode
		{
			public:
				Ean13CCB() :
					OneDimensionBarcode(NBarcodeSymbol::kEan13CCB)
				{}
				virtual ~Ean13CCB() = default;
				//Security level
				int GetSecurityLevel() const override {return 2;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Ean8 final : public OneDimensionBarcode
		{
			public:
				Ean8() :
					OneDimensionBarcode(NBarcodeSymbol::kEan8)
				{}
				virtual ~Ean8() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Ean8CCA final : public OneDimensionBarcode
		{
			public:
				Ean8CCA() :
					OneDimensionBarcode(NBarcodeSymbol::kEan8CCA)
				{}
				virtual ~Ean8CCA() = default;
				//Security level
				int GetSecurityLevel() const override {return 1;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Ean8CCB final : public OneDimensionBarcode
		{
			public:
				Ean8CCB() :
					OneDimensionBarcode(NBarcodeSymbol::kEan8CCB)
				{}
				virtual ~Ean8CCB() = default;
				//Security level
				int GetSecurityLevel() const override {return 2;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Ean128 final : public OneDimensionBarcode
		{
			public:
				Ean128() :
					OneDimensionBarcode(NBarcodeSymbol::kEan128)
				{}
				virtual ~Ean128() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Ean128CCA final : public OneDimensionBarcode
		{
			public:
				Ean128CCA() :
					OneDimensionBarcode(NBarcodeSymbol::kEan128CCA)
				{}
				virtual ~Ean128CCA() = default;
				//Security level
				int GetSecurityLevel() const override {return 1;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Ean128CCB final : public OneDimensionBarcode
		{
			public:
				Ean128CCB() :
					OneDimensionBarcode(NBarcodeSymbol::kEan128CCB)
				{}
				virtual ~Ean128CCB() = default;
				//Security level
				int GetSecurityLevel() const override {return 2;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Ean128CCC final : public OneDimensionBarcode
		{
			public:
				Ean128CCC() :
					OneDimensionBarcode(NBarcodeSymbol::kEan128CCC)
				{}
				virtual ~Ean128CCC() = default;
				//Security level
				int GetSecurityLevel() const override {return 3;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class GS1128 final : public OneDimensionGS1Barcode
		{
			public:
				GS1128() :
					OneDimensionGS1Barcode(NBarcodeSymbol::kGS1128)
				{}
				virtual ~GS1128() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class GS1128CCA final : public OneDimensionGS1Barcode
		{
			public:
				GS1128CCA() :
					OneDimensionGS1Barcode(NBarcodeSymbol::kGS1128CCA)
				{}
				virtual ~GS1128CCA() = default;
				//Security level
				int GetSecurityLevel() const override {return 1;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class GS1128CCB final : public OneDimensionGS1Barcode
		{
			public:
				GS1128CCB() :
					OneDimensionGS1Barcode(NBarcodeSymbol::kGS1128CCB)
				{}
				virtual ~GS1128CCB() = default;
				//Security level
				int GetSecurityLevel() const override {return 2;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class GS1128CCC final : public OneDimensionGS1Barcode
		{
			public:
				GS1128CCC() :
					OneDimensionGS1Barcode(NBarcodeSymbol::kGS1128CCC)
				{}
				virtual ~GS1128CCC() = default;
				//Security level
				int GetSecurityLevel() const override {return 3;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};


		class GS1DataBar14 final : public OneDimensionBarcode // it has AI but only "(01)" and zint library puts the AI automatically
		{
			public:
				GS1DataBar14() :
					OneDimensionBarcode(NBarcodeSymbol::kGS1DataBar14)
				{}
				virtual ~GS1DataBar14() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class GS1DataBarExpanded final : public OneDimensionGS1Barcode
		{
			public:
				GS1DataBarExpanded() :
					OneDimensionGS1Barcode(NBarcodeSymbol::kGS1DataBarExpanded)
				{}
				virtual ~GS1DataBarExpanded() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class GS1DataBarExpandedStacked final : public OneDimensionGS1Barcode
		{
			public:
				GS1DataBarExpandedStacked() :
					OneDimensionGS1Barcode(NBarcodeSymbol::kGS1DataBarExpandedStacked)
				{}
				virtual ~GS1DataBarExpandedStacked() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class GS1DataBarStacked final : public OneDimensionGS1Barcode
		{
			public:
				GS1DataBarStacked() :
					OneDimensionGS1Barcode(NBarcodeSymbol::kGS1DataBarStacked)
				{}
				virtual ~GS1DataBarStacked() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Rss14StackedOmnidirectional final : public OneDimensionGS1Barcode
		{
			public:
				Rss14StackedOmnidirectional() :
					OneDimensionGS1Barcode(NBarcodeSymbol::kRss14StackedOmnidirectional)
				{}
				virtual ~Rss14StackedOmnidirectional() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class TwoDimensionsBarcode : public Symbology
		{
			public:
				TwoDimensionsBarcode(const BarcodeSymbol& symbol);
				virtual ~TwoDimensionsBarcode() = default;

				// Immutable methods
				double GetRatio() const override {return 1.0;}
				void SetRatio(double ratio) override {}
				bool GetKeepAspectRatio() const override { return true; }
				void SetKeepAspectRatio(bool keepAspectRatio) override {}
				bool IsKeepAspectRatioSupported() const override {
					return false;
				}
				bool GetDisplayChecksum() const override { return false; }
				void SetDisplayChecksum(bool displayChecksum) override {}
				bool CanShowHumanReadableCode() const override { return false; }
				bool GetShowHumanReadableCode() const override { return false; }
				void SetShowHumanReadableCode(bool show) override {}
				BearerBarStyle GetBearerBarStyle() const override {return NBearerBarStyle::kNone;}
				void SetBearerBarStyle(const BearerBarStyle& bearerBarSyle) override {}
				bool IsBearerBarStyleSupported() const override
				{
					return false;
				}

				// GS1 methods
				bool IsGS1Barcode() const override {return false;}
				GS1AISeparator GetGS1AISeparator() const override{
					return NGS1AISeparator::kFNC1;
				}
				void SetGS1AISeparator(const GS1AISeparator& separator) override{}
				//Security level
				int GetSecurityLevel() const override {return -1;}
				// 2D barcodes methods
				virtual bool HasShavingMode() const override {return true;}
				virtual bool IsShavingModeEnabled() const override {
					return _shavingEnabled;
				}
				virtual void EnableShavingMode(bool enable) override {
					_shavingEnabled = enable;
				}
				virtual double GetShavingValue() const override {
					return _shavingValue;
				}
				virtual void SetShavingValue(double shavingValue) override {
					_shavingValue = shavingValue;
				}
				// Qr related methods
				virtual bool IsQrCode() const override {return false;}
				virtual uint8_t GetQrVersion() const override {return 0;}
				virtual void SetQrVersion(uint8_t qrVersion) override {}
				virtual QRCorrectionLevel GetQrCorrectionLevel() const override {return NQRCorrectionLevel::kH;}
				virtual void SetQrCorrectionLevel(const QRCorrectionLevel& qrCorrectionLevel) override {}

			private:
				bool _shavingEnabled;
				double _shavingValue;

		};

		class TwoDimensionsGS1Barcode : public TwoDimensionsBarcode
		{
			public:
				TwoDimensionsGS1Barcode(const BarcodeSymbol& symbol);
				virtual ~TwoDimensionsGS1Barcode() = default;

				bool IsGS1Barcode() const override {return true;}
				GS1AISeparator GetGS1AISeparator() const override{
					return _separator;
				}
				void SetGS1AISeparator(const GS1AISeparator& separator) override{
					_separator = separator;
				}

			private:
				GS1AISeparator _separator;
		};

		class DotCode final : public TwoDimensionsBarcode
		{
			public:
				DotCode():
					TwoDimensionsBarcode(NBarcodeSymbol::kDotCode)
				{}
				virtual ~DotCode() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class DataMatrix final : public TwoDimensionsBarcode
		{
			public:
				DataMatrix():
					TwoDimensionsBarcode(NBarcodeSymbol::kDataMatrix)
				{}
				virtual ~DataMatrix() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class GS1DataMatrix final : public TwoDimensionsGS1Barcode
		{
			public:
				GS1DataMatrix():
					TwoDimensionsGS1Barcode(NBarcodeSymbol::kGS1DataMatrix)
				{}
				virtual ~GS1DataMatrix() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class PdfBarcode : public TwoDimensionsBarcode
		{
			public:
				PdfBarcode(const BarcodeSymbol& symbol) :
					TwoDimensionsBarcode(symbol){}
				virtual ~PdfBarcode() = default;

				bool HasShavingMode() const override {return false;}
				bool IsShavingModeEnabled() const override {return false;}
				void EnableShavingMode(bool enable) override {}
				double GetShavingValue() const override {return 0.0;}
				virtual void SetShavingValue(double shavingValue) override {}
		};

		class Pdf417 final : public PdfBarcode
		{
			public:
				Pdf417() :
					PdfBarcode(NBarcodeSymbol::kPdf417)
				{}
				virtual ~Pdf417() = default;
				bool IsGS1Barcode() const override {return false;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class CompactPdf417 final : public PdfBarcode
		{
			public:
				CompactPdf417() :
					PdfBarcode(NBarcodeSymbol::kCompactPdf417)
				{}
				virtual ~CompactPdf417() = default;
				bool IsGS1Barcode() const override {return false;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class MicroPdf417 final : public PdfBarcode
		{
			public:
				MicroPdf417() :
					PdfBarcode(NBarcodeSymbol::kMicroPdf417)
				{}
				virtual ~MicroPdf417() = default;
				bool IsGS1Barcode() const override {return false;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class QrTypeBarcode : public TwoDimensionsBarcode
		{
			public:
				QrTypeBarcode(const BarcodeSymbol& symbol) :
					TwoDimensionsBarcode(symbol){}
				virtual ~QrTypeBarcode() = default;
				// Qr related methods
				bool IsQrCode() const override {return true;}
				uint8_t GetQrVersion() const override {
					return _version;
				}
				void SetQrVersion(uint8_t qrVersion) override {
					_version = qrVersion;
				}
				QRCorrectionLevel GetQrCorrectionLevel() const override {
					return _level;
				}
				void SetQrCorrectionLevel(const QRCorrectionLevel& qrCorrectionLevel) override {
					_level = qrCorrectionLevel;
				}

			private:
				QRCorrectionLevel _level;
				uint8_t _version;

		};

		class QRCode : public QrTypeBarcode
		{
			public:
				QRCode() :
					QrTypeBarcode(NBarcodeSymbol::kQRCode)
				{}
				virtual ~QRCode() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class GS1QRCode : public QrTypeBarcode
		{
			public:
				GS1QRCode() :
					QrTypeBarcode(NBarcodeSymbol::kGS1QRCode)
				{}
				virtual ~GS1QRCode() = default;
				bool IsGS1Barcode() const override {return true;}
				GS1AISeparator GetGS1AISeparator() const override{
					return _separator;
				}
				void SetGS1AISeparator(const GS1AISeparator& separator) override{
					_separator = separator;
				}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				GS1AISeparator _separator;
				static bool _registered;
		};

		class MicroQRCode : public QrTypeBarcode
		{
			public:
				MicroQRCode() :
					QrTypeBarcode(NBarcodeSymbol::kMicroQRCode)
				{}
				virtual ~MicroQRCode() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};
	}
}
#endif
