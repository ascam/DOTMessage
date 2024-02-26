#include "barcodevisitor.hpp"
#include "xmltools/xmlwriter.hpp"
#include "nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::BarcodeVisitor;
using macsa::dot::Barcode;
using macsa::xmltools::XmlWriter;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kBarcodeField = "BARCODEFIELD";
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


BarcodeVisitor::BarcodeVisitor(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLElement *xmlParent, const dot::Document& dom) :
	VariableObjectVisitor(xmlDocument, dom),
	_xmlParent{xmlParent}
{}

bool BarcodeVisitor::VisitEnter(const Barcode& barcode)
{
	if (_xmlParent) {
		auto xmlElementResult = XmlWriter::CreateChildNode(_xmlDocument, kBarcodeField, _xmlParent);
		if (xmlElementResult.second){
			_xmlElement = xmlElementResult.first;
			_xmlElement->SetAttribute(kAttrName, barcode.GetId().c_str());
			return visitObject(barcode, _xmlElement);
		}
		else {
			ELog() << "Unable to create new TEXFIELD component";
		}
	}
	else {
		ELog() << "Unable to create new TEXFIELD component: Missing xml parent element";
	}

	return false;
}

bool BarcodeVisitor::VisitExit(const Barcode& barcode)
{
	DLog() << barcode.GetId();
	if (_xmlParent) {
		if (_xmlDataSource != nullptr) {
			_xmlElement->InsertEndChild(_xmlDataSource);
		}

		XmlWriter::CreateTextChildNode(_xmlDocument, kSymbology, barcode.GetSymbology().toString(), _xmlElement);
		XmlWriter::CreateTextChildNode(_xmlDocument, kCode, barcode.GetCode(), _xmlElement);
		XmlWriter::CreateTextChildNode(_xmlDocument, kRatio, ToString(barcode.GetRatio()), _xmlElement);
		XmlWriter::CreateTextChildNode(_xmlDocument, kNormalized, ToString(barcode.GetKeepAspectRatio()), _xmlElement);
		if (barcode.HasShavingMode()) {
			XmlWriter::CreateTextChildNode(_xmlDocument, kShavingMode, ToString(barcode.IsShavingModeEnabled()), _xmlElement);
			XmlWriter::CreateTextChildNode(_xmlDocument, kShavingValue, ToString(barcode.GetShavingValue()), _xmlElement);
		}
		if (barcode.CanShowHumanReadableCode()) {
			XmlWriter::CreateTextChildNode(_xmlDocument, kDisplayChecksum, ToString(barcode.GetDisplayChecksum()), _xmlElement);
			XmlWriter::CreateTextChildNode(_xmlDocument, kDisplayCode, ToString(barcode.GetShowHumanReadableCode()), _xmlElement);
		}
		if (!visitFont(barcode.GetFont(), _xmlElement)) {
			return false;
		}
		writeColor(barcode.GetForegroundColor(), XmlWriter::CreateChildNode(_xmlDocument, kForeColor, _xmlElement).first);
		writeColor(barcode.GetBackgroundColor(), XmlWriter::CreateChildNode(_xmlDocument, kBackColor, _xmlElement).first);
		XmlWriter::CreateTextChildNode(_xmlDocument, kBearerStyle, barcode.GetBearerBarStyle().toString(), _xmlElement);
		if (barcode.IsQrCode()) {
			XmlWriter::CreateTextChildNode(_xmlDocument, kQrVersion, ToString((uint32_t)barcode.GetQrVersion()), _xmlElement);
			XmlWriter::CreateTextChildNode(_xmlDocument, kQrCorrectionLevel, barcode.GetQrCorrectionLevel().toString(), _xmlElement);
		}
		return true;
	}
	return false;
}
