#include "dom/components/barcodeapplications.hpp"

namespace macsa::dot {

const std::vector<std::pair<NBarcodeApplications, std::string>>& BarcodeApplications::getData() const
{
	static const std::vector<std::pair<NBarcodeApplications, std::string>> kBarcodeApplications {
		{NBarcodeApplications::kSerialShippingContainerCode, "00 - Serial Shipping Container Code (SSCC-18)"},
		{NBarcodeApplications::kGTIN14, "01 - GTIN-14"},
		{NBarcodeApplications::kNumberOfContainers, "02 - Number of containers"},
		{NBarcodeApplications::kBatchNumber, "10 - Batch Number"},
		{NBarcodeApplications::kProductionRate, "11 - Production Date"},
		{NBarcodeApplications::kPackagingData, "13 - Packaging Data"},
		{NBarcodeApplications::kSellByDate, "15 - Sell by Date (Quality Control)"},
		{NBarcodeApplications::kExpirationDate, "17 - Expiration Date"},
		{NBarcodeApplications::kProductVariant, "20 - Product Variant"},
		{NBarcodeApplications::kSerialNumber, "21 - Serial Number"},
		{NBarcodeApplications::kHIBCC, "22 - HIBCC Quantity, Date, Batch and Link"},
		{NBarcodeApplications::kLotNumber, "23x - Lot Number"},
		{NBarcodeApplications::kAdditionalProductIdentification, "240 - Additional Product identification"},
		{NBarcodeApplications::kReferenceToSourceEntity, "251 - Reference to source entity"},
		{NBarcodeApplications::kQuantityEach, "30 - Quantity Each - "},
		{NBarcodeApplications::kProductNetWeight, "310y - Product Net Weight in kg"},
		{NBarcodeApplications::kNumberOfUnitsContained, "37 - Number of Units Contained"},
		{NBarcodeApplications::kCustomerPurchaseOrderNumber, "400 - Customer Purchase Order Number"},
		{NBarcodeApplications::kShipDeliverToLocationCode, "410 - Ship To/Deliver To Location Code (EAN13 or DUNS code)"},
		{NBarcodeApplications::kPricePerUnitOfMeasure, "8005 - Price per Unit of Measure"},
		{NBarcodeApplications::k91CompanyInternalInformation, "91 - Company Internal Information"},
		{NBarcodeApplications::k92CompanyInternalInformation, "92 - Company Internal Information"},
		{NBarcodeApplications::k93CompanyInternalInformation, "93 - Company Internal Information"}
	};

	return kBarcodeApplications;
}

}

