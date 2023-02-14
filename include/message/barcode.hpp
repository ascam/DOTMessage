#ifndef DOT_MESSAGE_BARCODE_OBJECTS_HPP
#define DOT_MESSAGE_BARCODE_OBJECTS_HPP

#include <memory>
#include "message/variableobject.hpp"
#include "message/font.hpp"
#include "message/barcodesymbologies.hpp"

namespace macsa {
	namespace dot {
		class Symbology;
		class Barcode : public VariableObject
		{
			public:
				Barcode(const std::string& id, const Geometry& geometry);
				Barcode(const Barcode&) = delete;
				virtual ~Barcode();

				/**
				 * @brief GetData. Getter method to get the current
				 * value of the code resolving the variable fields.
				 * @return The code that must be rendered after resolving
				 * variable fields.
				 */
				std::string GetData() const override;

				/**
				 * @brief IsVariable. Overrided method of Object::IsVariable
				 * @return true if the object can change the inner value,
				 * false if the object is static.
				 */
				bool IsVariable() const override;

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
				Signal<bool,float> ShavingValueChanged;
				Signal<Font> FontChanged;

			private:
				std::unique_ptr<Symbology> _symbology;
				Font _font;
		};
	}
}

#endif

