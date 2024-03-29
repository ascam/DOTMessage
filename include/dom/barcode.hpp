#ifndef DOT_MESSAGE_BARCODE_OBJECTS_HPP
#define DOT_MESSAGE_BARCODE_OBJECTS_HPP

#include <memory>
#include "variableobject.hpp"
#include "components/font.hpp"
#include "components/barcodesymbologies.hpp"

namespace macsa {
	namespace dot {
		class Symbology;
		class IDocumentVisitor;
		class Barcode : public VariableObject
		{
			public:
				Barcode(const std::string& id, const Geometry& geometry);
				Barcode(const Barcode&) = delete;
				virtual ~Barcode();

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) const override;

				/**
				 * @brief GetSymbology. Getter method for the barcode symbology
				 * @return The current barcode symbology
				 */
				const BarcodeSymbol& GetSymbology() const;

				/**
				 * @brief SetSymbology. Setter method for the barcode symbology
				 * @param symbology: The barcode symbology to set
				 */
				void SetSymbology(const BarcodeSymbol& symbology);

				/**
				 * @brief GetCode. Getter method for the code codified in the barcode.
				 * @return The text codified in the barcode.
				 */
				const std::string& GetCode() const;

				/**
				 * @brief SetCode. Setter method for the code codified in the barcode.
				 * @param code: text to codify in the barcode.
				 */
				void SetCode(const std::string& code);

				/**
				 * @brief IsGS1Barcode. Getter method to know if barcode
				 * is part of GS1 standard.
				 * @return true if the barcode is part of the GS1 standard.
				 */
				bool IsGS1Barcode() const;

				/**
				 * @brief GetGS1AISeparator. Getter method to get the GS1 AI separator.
				 * @return The used GS1AISeparator.
				 */
				GS1AISeparator GetGS1AISeparator() const;

				/**
				 * @brief SetGS1AISeparator. Setter method to get the GS1 AI separator.
				 * @param separator: The GS1AISeparator to use.
				 */
				void SetGS1AISeparator(const GS1AISeparator& separator);

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
				int GetSecurityLevel() const;

				/**
				 * @brief HasShavingMode. Getter method to know if barcode
				 * has shaving mode capability.
				 * @return true if the barcode has shaving mode capability,
				 * otherwise returns false.
				 */
				bool HasShavingMode() const;

				/**
				 * @brief IsShavingModeEnabled. Getter method for shaving mode enabled.
				 * @return true if the barcode has shaving mode enbled
				 */
				bool IsShavingModeEnabled() const;

				/**
				 * @brief EnableShavingMode. Setter method for shaving mode enabled.
				 * @param enable: bool to enable/disable shaving mode.
				 */
				void EnableShavingMode(bool enable);

				/**
				 * @brief GetShavingValue. Getter method for shaving value.
				 * @return The shaving value rate in percentage.
				 */
				double GetShavingValue() const;

				/**
				 * @brief SetShavingValue. Setter method for shaving value.
				 * @param shavingValue: The shaving value rate in percentage (0.0 - 100.0).
				 */
				void SetShavingValue(double shavingValue);

				/**
				 * @brief GetRatio. Getter method for barcode ratio. This is the ratio
				 * between the thinner and the heaviest line.
				 * @return the ratio between the thinner and the heaviest line.
				 */
				double GetRatio() const;

				/**
				 * @brief SetRatio. Setter method for barcode ratio. This is the relation
				 * between the thinner and the heaviest line.
				 * @param ratio: the ratio between the thinner and the heaviest line.
				 */
				void SetRatio(double ratio);

				/**
				 * @brief IsKeepAspectRatioSupported. Getter method, informs the hability to change the aspect ratio.
				 * @return true: if the keep aspect ratio is supported.
				 */
				bool IsKeepAspectRatioSupported() const;

				/**
				 * @brief GetKeepAspectRatio. Getter method for keep aspect ratio property.
				 * @return keep aspect ratio value.
				 */
				bool GetKeepAspectRatio() const;

				/**
				 * @brief SetKeepAspectRatio. Setter method for keep aspect ratio property.
				 * @param keepAspectRatio: bool to set if the barcode must be rendered
				 * keeping aspect ratio.
				 */
				void SetKeepAspectRatio(bool keepAspectRatio);

				/**
				 * @brief GetDisplayChecksum. Getter method for display checksum value
				 * in the human readable code.
				 * @return true if the checksum is visible, othrewise return false.
				 */
				bool GetDisplayChecksum() const;

				/**
				 * @brief SetDisplayChecksum. Setter method for display checksum value
				 * in the human readable code.
				 * @param displayChecksum: bool to set checksum visible in the human
				 * readable code
				 */
				void SetDisplayChecksum(bool displayChecksum);

				/**
				 * @brief GetFont. Getter method for text font.
				 * @return The Font struct of the text object.
				 */
				const Font& GetFont() const {return _font;}

				/**
				 * @brief SetFont. Setter method for text font.
				 * @param font: The Font struct to be applied.
				 */
				void SetFont(const Font& font);

				/**
				 * @brief GetForegroundColor. Getter method for the foreground color
				 * to apply to the barcode.
				 * @return The current foreground color.
				 */
				const Color& GetForegroundColor() const {return _foreColor;}

				/**
				 * @brief SetForegroundColor. Setter method for the foreground color
				 * to apply to the barcode.
				 * @param foreColor: The color to apply to the barcode.
				 */
				void SetForegroundColor(const Color& foreColor);

				/**
				 * @brief GetBackgroundColor. Getter method for the background color
				 * to apply to the barcode.
				 * @return The current background color.
				 */
				const Color& GetBackgroundColor() const {return _backgroundColor;}

				/**
				 * @brief SetBackgroundColor. Setter method for the background color
				 * to apply to the barcode.
				 * @param backgroundColor: The color to apply to the barcode background.
				 */
				void SetBackgroundColor(const Color& backgroundColor);

				/**
				 * @brief CanShowHumanReadableCode. Method to check if the code
				 * can be displayed.
				 * @return true if the barcode has de capability of display the
				 * code as human readable.
				 */
				bool CanShowHumanReadableCode() const;

				/**
				 * @brief GetShowHumanReadableCode. Getter method for show human readable code.
				 * If is enabled the code will be displayed under the barcode.
				 * @return if code will be displayed under the barcode.
				 */
				bool GetShowHumanReadableCode() const;

				/**
				 * @brief SetShowHumanReadableCode. Setter method for show human readable code.
				 * @param show: bool to set if code will be displayed under the barcode.
				 */
				void SetShowHumanReadableCode(bool show);

				/**
				 * @brief IsBearerSupported. Getter method to know if bearer is supported.
				 * @return true if this symbology support bearer bars.
				 */
				bool IsBearerBarStyleSupported() const;

				/**
				 * @brief GetBearerBarStyle. Getter method for bearer bars.
				 * @return Type of bearer bars.
				 */
				BearerBarStyle GetBearerBarStyle() const;

				/**
				 * @brief SetBearerBarStyle. Setter method for bearer bars.
				 * @param bearerBarSyle: Type of bearer bars.
				 */
				void SetBearerBarStyle(const BearerBarStyle& bearerBarSyle);

				/**
				 * @brief IsQrCode. Getter method to check if symbol is part of
				 * QrCode family
				 * @return true if the symbology is part of QrCode family, otherwise
				 * returns false.
				 */
				bool IsQrCode() const;

				/**
				 * @brief GetQrVersion. Getter method for Qr version. Only valid for
				 * Qr codes.
				 * @return The version of the Qr code if the symbology is qr, otherwise
				 * return 0.
				 */
				uint8_t GetQrVersion() const;

				/**
				 * @brief SetQrVersion. Setter method for Qr version.
				 * @param qrVersion: Qr version to set. Only valid for Qr codes.
				 */
				void SetQrVersion(uint8_t qrVersion);
				/**
				 * @brief GetQrCorrectionLevel. Getter method for QrCorrectionLevel.
				 * Only valid for Qr codes.
				 * @return The Qr Correction level.
				 */
				QRCorrectionLevel GetQrCorrectionLevel() const;

				/**
				 * @brief SetQrCorrectionLevel. Setter method for QrCorrectionLevel.
				 * @param qrCorrectionLevel: The Qr Correction level.
				 * Only valid for Qr codes.
				 */
				void SetQrCorrectionLevel(const QRCorrectionLevel& qrCorrectionLevel);

			public:
				Signal<> SymbologyChanged;
				Signal<> ShavingValueChanged;
				Signal<> FontChanged;
				Signal<> ForegroundColorChanged;
				Signal<> BackgroundColorChanged;
				Signal<> RatioValueChanged;
				Signal<> KeepAspectRatioChanged;
				Signal<> DisplayChecksumChanged;
				Signal<> ShowHumanReadableCodeChanged;
				Signal<> BearerBarStyleChanged;
				Signal<> QrVersionChanged;
				Signal<> QrCorrectionLevelChanged;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				std::unique_ptr<Symbology> _symbology;
				Font _font;
				Color _foreColor;
				Color _backgroundColor;
				std::string _code;
				static bool _registered;

				void transferSymbologyInnerData(Symbology* source, Symbology* target);
		};
	}
}

#endif

