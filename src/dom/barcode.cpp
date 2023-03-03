#include "dom/barcode.hpp"
#include <exception>
#include <sstream>

#include "dom/documentvisitor.hpp"
#include "components/symbologies/symbology.hpp"
#include "dom/factories/abstractobjectfactory.hpp"
#include "dom/factories/barcodesymbologyfactory.hpp"
#include "utils/macsalogger.hpp"

using macsa::dot::Barcode;
using macsa::dot::BarcodeSymbol;
using macsa::utils::MacsaLogger;
using macsa::dot::IDocumentVisitor;
using namespace std::placeholders;

namespace  {
	static const bool FactoryRegistered = macsa::dot::ConcreteObjectsFactory<Barcode>::Register(macsa::dot::NObjectType::kBarcode);
}

Barcode::Barcode(const std::string& id, const macsa::dot::Geometry& geometry) :
	VariableObject(id, NObjectType::kBarcode, geometry),
	_symbology{SymbologyFactory::Get(NBarcodeSymbol::kCode128)}
{}

bool Barcode::Accept(IDocumentVisitor* visitor) const
{
	if (visitor) {
		if (visitor->VisitEnter(*this)) {
			if (IsVariable()) {
				_datasource->Accept(visitor);
			}
		}
		return visitor->VisitExit(*this);
	}
	return false;
}


const BarcodeSymbol& Barcode::GetSymbology() const
{
	if (_symbology.get()) {
		return _symbology->GetSymbology();
	}
	else {
		throw (std::invalid_argument("Unable to get symbology. Missing symbology pointer"));
	}
}

void Barcode::SetSymbology(const macsa::dot::BarcodeSymbol& symbology)
{
	if (_symbology.get() == nullptr || _symbology->GetSymbology() != symbology) {

		Symbology* oldSymbology = _symbology.release();
		_symbology.reset(SymbologyFactory::Get(symbology()));

		if (oldSymbology != nullptr) {
			// Transfer the values between symbologies
			transferSymbologyInnerData(oldSymbology, _symbology.get());
			delete oldSymbology;
		}

		SymbologyChanged.Emit();
	}
}

const std::string& Barcode::GetCode() const
{
	return _code;
}

void Barcode::SetCode(const std::string& code)
{
	_code = code;
}

bool Barcode::IsGS1Barcode() const
{
	if (_symbology) {
		return _symbology->IsGS1Barcode();
	}
	return false;
}

macsa::dot::GS1AISeparator Barcode::GetGS1AISeparator() const
{
	if (_symbology) {
		return _symbology->GetGS1AISeparator();
	}
	return NGS1AISeparator::kFNC1;
}

void Barcode::SetGS1AISeparator(const macsa::dot::GS1AISeparator& separator)
{
	if (_symbology && _symbology->GetGS1AISeparator() != separator) {
		_symbology->SetGS1AISeparator(separator);
	}
}

int Barcode::GetSecurityLevel() const
{
	if (_symbology) {
		return _symbology->GetSecurityLevel();
	}
	return -1;
}

bool Barcode::HasShavingMode() const
{
	if (_symbology) {
		return _symbology->HasShavingMode();
	}
	return false;
}

bool Barcode::IsShavingModeEnabled() const
{
	if (_symbology && _symbology->HasShavingMode()) {
		return _symbology->IsShavingModeEnabled();
	}
	return false;
}

void Barcode::EnableShavingMode(bool enable)
{
	if (_symbology && _symbology->HasShavingMode()) {
		if (_symbology->IsShavingModeEnabled() != enable) {
			_symbology->EnableShavingMode(enable);
			ShavingValueChanged.Emit();
		}
	}
}

double Barcode::GetShavingValue() const
{
	double shavingValue = 0.0;
	if (_symbology && _symbology->HasShavingMode()) {
		shavingValue = _symbology->GetShavingValue();
	}
	return shavingValue;
}

void Barcode::SetShavingValue(double shavingValue)
{
	if (_symbology && _symbology->HasShavingMode()) {
		if (_symbology->GetShavingValue() != shavingValue){
			_symbology->SetShavingValue(shavingValue);
			if (_symbology->IsShavingModeEnabled()) {
				ShavingValueChanged.Emit();
			}
		}
	}
}

double Barcode::GetRatio() const
{
	double ratio = 0.0;
	if (_symbology) {
		 ratio =_symbology->GetRatio();
	}
	return ratio;
}

void Barcode::SetRatio(double ratio)
{
	if (_symbology && _symbology->GetRatio() != ratio) {
		_symbology->SetRatio(ratio);
		RatioValueChanged.Emit();
	}
}

bool Barcode::GetKeepAspectRatio() const
{
	bool enabled = true;
	if (_symbology) {
		 enabled =_symbology->GetKeepAspectRatio();
	}
	return enabled;
}

void Barcode::SetKeepAspectRatio(bool keepAspectRatio)
{
	if (_symbology && _symbology->GetKeepAspectRatio() != keepAspectRatio) {
		_symbology->SetKeepAspectRatio(keepAspectRatio);
		KeepAspectRatioChanged.Emit();
	}
}

bool Barcode::GetDisplayChecksum() const
{
	bool display = false;
	if (_symbology) {
		 display =_symbology->GetDisplayChecksum();
	}
	return display;
}

void Barcode::SetDisplayChecksum(bool displayChecksum)
{
	if (_symbology && _symbology->GetDisplayChecksum() != displayChecksum) {
		_symbology->SetDisplayChecksum(displayChecksum);
		DisplayChecksumChanged.Emit();
	}
}

void Barcode::SetFont(const macsa::dot::Font& font)
{
	if (_font != font) {
		_font = font;
		if (GetShowHumanReadableCode()) {
			FontChanged.Emit();
		}
	}
}

void Barcode::SetForegroundColor(const Color& foreColor)
{
	if (_foreColor != foreColor){
		_foreColor = foreColor;
		ForegroundColorChanged.Emit();
	}
}

void Barcode::SetBackgroundColor(const Color& backgroundColor)
{
	if (_backgroundColor != backgroundColor) {
		_backgroundColor = backgroundColor;
		BackgroundColorChanged.Emit();
	}
}

bool Barcode::CanShowHumanReadableCode() const
{
	bool hrt = false;
	if (_symbology) {
		 hrt =_symbology->CanShowHumanReadableCode();
	}
	return hrt;
}

bool Barcode::GetShowHumanReadableCode() const
{
	bool hrt = false;
	if (_symbology && _symbology->CanShowHumanReadableCode()) {
		hrt =_symbology->GetShowHumanReadableCode();
	}
	return hrt;
}

void Barcode::SetShowHumanReadableCode(bool show)
{
	if (_symbology && _symbology->CanShowHumanReadableCode()) {
		if (_symbology->GetShowHumanReadableCode() != show){
			_symbology->SetShowHumanReadableCode(show);
			ShowHumanReadableCodeChanged.Emit();
		}
	}
}

macsa::dot::BearerBarStyle Barcode::GetBearerBarStyle() const
{
	BearerBarStyle bearer{NBearerBarStyle::kNone};
	if (_symbology) {
		bearer =_symbology->GetBearerBarStyle();
	}
	return bearer;
}

void Barcode::SetBearerBarStyle(const macsa::dot::BearerBarStyle& bearerBarSyle)
{
	if (_symbology && _symbology->GetBearerBarStyle() != bearerBarSyle) {
		_symbology->SetBearerBarStyle(bearerBarSyle);
		BearerBarStyleChanged.Emit();
	}
}

bool Barcode::IsQrCode() const
{
	bool isQr{};
	if (_symbology) {
		isQr =_symbology->IsQrCode();
	}
	return isQr;
}

uint8_t Barcode::GetQrVersion() const
{
	uint8_t qrVersion{};
	if (_symbology) {
		qrVersion =_symbology->GetQrVersion();
	}
	return qrVersion;
}

void Barcode::SetQrVersion(uint8_t qrVersion)
{
	if (_symbology && _symbology->GetQrVersion() != qrVersion) {
		_symbology->SetQrVersion(qrVersion);
		QrVersionChanged.Emit();
	}
}

macsa::dot::QRCorrectionLevel Barcode::GetQrCorrectionLevel() const
{
	QRCorrectionLevel qrCorrectionLevel{};
	if (_symbology) {
		qrCorrectionLevel =_symbology->GetQrCorrectionLevel();
	}
	return qrCorrectionLevel;
}

void Barcode::SetQrCorrectionLevel(const macsa::dot::QRCorrectionLevel& qrCorrectionLevel)
{
	if (_symbology && _symbology->GetQrCorrectionLevel() != qrCorrectionLevel) {
		_symbology->SetQrCorrectionLevel(qrCorrectionLevel);
		QrCorrectionLevelChanged.Emit();
	}
}

void Barcode::transferSymbologyInnerData(macsa::dot::Symbology* source, macsa::dot::Symbology* target)
{
	if (source && target) {
		// Human readable text capability
		if (source->CanShowHumanReadableCode() && target->CanShowHumanReadableCode()) {
			target->SetShowHumanReadableCode(source->GetShowHumanReadableCode());
			target->SetDisplayChecksum(source->GetDisplayChecksum());
		}
		// Shaving mode capability
		if (source->HasShavingMode() && target->HasShavingMode()) {
			target->EnableShavingMode(source->IsShavingModeEnabled());
			target->SetShavingValue(source->GetShavingValue());
		}
		// Qr Codes
		if (source->IsQrCode() && target->IsQrCode()) {
			target->SetQrCorrectionLevel(source->GetQrCorrectionLevel());
			target->SetQrVersion(source->GetQrVersion());
		}
		// GS1 barcodes
		if (source->IsGS1Barcode() && target->IsGS1Barcode()) {
			target->SetGS1AISeparator(source->GetGS1AISeparator());
		}
		// Bearer bar and other stuff
		target->SetBearerBarStyle(source->GetBearerBarStyle());
		target->SetRatio(source->GetRatio());
		target->SetKeepAspectRatio(source->GetKeepAspectRatio());
	}
}
