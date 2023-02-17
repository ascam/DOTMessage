#include "message/barcode.hpp"
#include <exception>
#include <sstream>

#include "symbologies/symbology.hpp"
#include "factories/abstractobjectfactory.hpp"
#include "factories/barcodesymbologyfactory.hpp"
#include "utils/macsalogger.hpp"

using macsa::dot::Barcode;
using macsa::dot::BarcodeSymbol;
using macsa::utils::MacsaLogger;
using namespace std::placeholders;

namespace macsa {
	namespace dot {
		namespace  {
			static const bool FactoryRegistered = ConcreteObjectsFactory<Barcode>::Register(NObjectType::kBarcode);
		}
	}
}

Barcode::Barcode(const std::string &id, const macsa::dot::Geometry &geometry) :
	VariableObject(id, NObjectType::kBarcode, geometry),
	_symbology{SymbologyFactory::Get(NBarcodeSymbol::kCode128)}
{}

std::string Barcode::GetData() const
{
	if (IsVariable()) {
		return _datasource->GetData();
	}
	if (_symbology.get() != nullptr ) {
		return _symbology->GetCode();
	}
	return "";
}

const BarcodeSymbol& Barcode::GetSymbology() const
{
	if (_symbology.get()) {
		return _symbology->GetSymbology();
	}
	else {
		std::string message {"Unable to get symbology. Missing symbology pointer"};
		throw (std::invalid_argument(message));
	}
}

void Barcode::SetSymbology(const macsa::dot::BarcodeSymbol &symbology)
{
	if (_symbology.get() == nullptr || _symbology->GetSymbology() != symbology) {
		_symbology.reset(SymbologyFactory::Get(symbology()));
		SymbologyChanged.Emit();
	}
}

std::string Barcode::GetCode() const
{
	if (_symbology.get() != nullptr ) {
		_symbology->GetCode();
	}
	else {
		WLog() << "Invalid barcode symbology";
	}
	return "";
}

void Barcode::SetCode(const std::string &code)
{
	if (_symbology.get() != nullptr ) {
		_symbology->SetCode(code);
	}
	else {
		WLog() << "Invalid barcode symbology";
	}
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

void Barcode::SetGS1AISeparator(const macsa::dot::GS1AISeparator &separator)
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
			ShavingValueChanged.Emit(_symbology->IsShavingModeEnabled(), _symbology->GetShavingValue());
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
				ShavingValueChanged.Emit(_symbology->IsShavingModeEnabled(), _symbology->GetShavingValue());
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
		// TODO(iserra): Emit signal?
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
		_symbology->SetRatio(keepAspectRatio);
		// TODO(iserra): Emit signal?
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
		// TODO(iserra): Emit signal?
	}
}

void Barcode::SetFont(const macsa::dot::Font &font)
{
	if (_font != font) {
		_font = font;
		if (GetShowHumanReadableCode()) {
			FontChanged.Emit(std::forward<Font>(_font));
		}
	}
}

void Barcode::SetForegroundColor(const std::string &foreColor)
{
	if (_foreColor != foreColor){
		_foreColor = foreColor;
		ForegroundColorChanged.Emit(std::forward<std::string>(_foreColor));
	}
}

void Barcode::SetBackgroundColor(const std::string &backgroundColor)
{
	if (_backgroundColor != backgroundColor) {
		_backgroundColor = backgroundColor;
		BackgroundColorChanged.Emit(std::forward<std::string>(_backgroundColor));
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

void Barcode::SetBearerBarStyle(const macsa::dot::BearerBarStyle &bearerBarSyle)
{
	if (_symbology && _symbology->GetBearerBarStyle() != bearerBarSyle) {
		_symbology->SetBearerBarStyle(bearerBarSyle);
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

void Barcode::SetQrCorrectionLevel(const macsa::dot::QRCorrectionLevel &qrCorrectionLevel)
{
	if (_symbology && _symbology->GetQrCorrectionLevel() != qrCorrectionLevel) {
		_symbology->SetQrCorrectionLevel(qrCorrectionLevel);
	}
}
