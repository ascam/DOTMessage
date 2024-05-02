#include "imagevisitor.hpp"
#include "nisxcommonnames.hpp"
#include "xmltools/xmlwriter.hpp"
#include "utils/macsalogger.hpp"
#include "utils/base64.h"
#include "utils/stringutils.hpp"

using macsa::nisx::ImageVisitor;
using macsa::dot::Image;
using macsa::xmltools::XmlWriter;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using namespace macsa::utils::stringutils;

static constexpr const char* kImageField = "IMAGEFIELD";
static constexpr const char* kImage = "IMAGE";
static constexpr const char* kAlignment = "ALIGNMENT";
static constexpr const char* kAlgorithm = "ALGORITHM";
static constexpr const char* kPath = "PATH";
static constexpr const char* kTopThreshold = "TOPTHRESOLD";
static constexpr const char* kDownThreshold = "DOWNTHRESOLD";
static constexpr const char* kMinThreshold = "BINARYTHRESHOLDMIN";
static constexpr const char* kMaxThreshold = "BINARYTHRESHOLDMAX";


ImageVisitor::ImageVisitor(XMLDocument& document, XMLElement* parent) :
	ObjectVisitor(document),
	_xmlParent{parent},
	_xmlElement{}
{}

bool ImageVisitor::Visit(const Image& image)
{
	if (_xmlParent) {
		auto xmlImageResult = XmlWriter::CreateChildNode(_xmlDocument, kImageField, _xmlParent);
		if (xmlImageResult.second){
			_xmlElement = xmlImageResult.first;
			_xmlElement->SetAttribute(kAttrName, image.GetId().c_str());
			if (!visitObject(image, _xmlElement)) {
				return false;
			}
			auto xmlImageAdjustResult = XmlWriter::CreateChildNode(_xmlDocument, kAdjust, _xmlElement);
			if (xmlImageAdjustResult.second) {
				xmlImageAdjustResult.first->SetAttribute(kAttrType, image.GetBoxAdjustment().toString().c_str());
			}
			auto xmlAlignmentResult = XmlWriter::CreateChildNode(_xmlDocument, kAlignment, _xmlElement);
			if (xmlAlignmentResult.second) {
				std::stringstream alignment;
				alignment << image.GetVerticalAlignment().toString() << image.GetHorizontalAlignment().toString();
				xmlAlignmentResult.first->SetAttribute(kAttrValue, alignment.str().c_str());
			}
			auto xmlFilepathResult = XmlWriter::CreateChildNode(_xmlDocument, kPath, _xmlElement);
			if (xmlFilepathResult.second) {
				xmlFilepathResult.first->SetAttribute(kAttrValue, image.GetFilepath().c_str());
			}
			auto xmlAlgorithmResult = XmlWriter::CreateChildNode(_xmlDocument, kAlgorithm, _xmlElement);
			if (xmlAlgorithmResult.second) {
				xmlAlgorithmResult.first->SetAttribute(kAttrValue, image.GetAlgorithm().c_str());
			}
			auto xmlTopThresholdResult = XmlWriter::CreateChildNode(_xmlDocument, kTopThreshold, _xmlElement);
			if (xmlTopThresholdResult.second) {
				xmlTopThresholdResult.first->SetAttribute(kAttrValue, ToString((int)image.GetTopThreshold()).c_str());
			}
			auto xmlDownThresholdResult = XmlWriter::CreateChildNode(_xmlDocument, kDownThreshold, _xmlElement);
			if (xmlDownThresholdResult.second) {
				xmlDownThresholdResult.first->SetAttribute(kAttrValue, ToString((int)image.GetDownThreshold()).c_str());
			}
			auto xmlMinThresholdResult = XmlWriter::CreateChildNode(_xmlDocument, kMinThreshold, _xmlElement);
			if (xmlMinThresholdResult.second) {
				xmlMinThresholdResult.first->SetAttribute(kAttrValue, ToString((int)image.GetBinaryThresholdMin()).c_str());
			}
			auto xmlMaxThresholdResult = XmlWriter::CreateChildNode(_xmlDocument, kMaxThreshold, _xmlElement);
			if (xmlMaxThresholdResult.second) {
				xmlMaxThresholdResult.first->SetAttribute(kAttrValue, ToString((int)image.GetBinaryThresholdMax()).c_str());
			}
			auto xmlImageContentResult = XmlWriter::CreateChildNode(_xmlDocument, kImage, _xmlElement);
			if (xmlImageContentResult.second) {
				xmlImageContentResult.first->SetText(contentToBase64(image.GetData()).c_str());
			}
			return true;
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

std::string ImageVisitor::contentToBase64(const std::vector<uint8_t>& content) const
{
	std::stringstream out;
	const char* plainData = reinterpret_cast<const char*>(&content[0]);

	int len = Base64encode_len(static_cast<int>(content.size()));
	char* encodeData = new char[len + 1];
	if(encodeData) {
		Base64encode(encodeData, plainData, static_cast<int>(content.size()));

		out << encodeData;
		delete[]  encodeData;
	}
	return out.str();
}
