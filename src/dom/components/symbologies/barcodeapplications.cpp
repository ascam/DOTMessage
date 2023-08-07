#include "dom/components/barcodeapplications.hpp"

using macsa::dot::BarcodeApplications;
using macsa::dot::BarcodeApplicationData;

const std::vector<BarcodeApplicationData>& BarcodeApplications::getData()
{
	static const std::vector<BarcodeApplicationData> kBarcodeApplications {
		{NBarcodeApplications::kSerialShippingContainerCode, "00", "Serial Shipping Container Code (SSCC-18)", "18 digits"},
		{NBarcodeApplications::kGTIN14, "01", "GTIN-14", "14 digits"},
		{NBarcodeApplications::kNumberOfContainers, "02", "Number of containers", "14 digits"},
		{NBarcodeApplications::kBatchNumber, "10", "Batch Number", "1-20 alphanumeric"},
		{NBarcodeApplications::kProductionRate, "11", "Production Date", "YYMMDD"},
		{NBarcodeApplications::kPackagingData, "13", "Packaging Data", "YYMMDD"},
		{NBarcodeApplications::kSellByDate, "15", "Sell by Date (Quality Control)", "YYMMDD"},
		{NBarcodeApplications::kExpirationDate, "17", "Expiration Date", "YYMMDD"},
		{NBarcodeApplications::kProductVariant, "20", "Product Variant", "2 digits"},
		{NBarcodeApplications::kSerialNumber, "21", "Serial Number", "1-20 alphanumeric"},
		{NBarcodeApplications::kHIBCC, "22", "HIBCC Quantity, Date, Batch and Link", "1-29 alphanumeric"},
		{NBarcodeApplications::kLotNumber, "23x", "Lot Number", "1-19 alphanumeric"},
		{NBarcodeApplications::kAdditionalProductIdentification, "240", "Additional Product identification", "1-30 alphanumeric"},
		{NBarcodeApplications::kReferenceToSourceEntity, "251", "Reference to source entity", "N3+X..30"},
		{NBarcodeApplications::kQuantityEach, "30", "Quantity Each -", "8 digits"},
		{NBarcodeApplications::kProductNetWeight, "310y", "Product Net Weight in kg", "6 digits"},
		{NBarcodeApplications::kNumberOfUnitsContained, "37", "Number of Units Contained", "1-8 digits"},
		{NBarcodeApplications::kCustomerPurchaseOrderNumber, "400", "Customer Purchase Order Number", "1-29 alphanumeric"},
		{NBarcodeApplications::kShipDeliverToLocationCode, "410", "Ship To/Deliver To Location Code (EAN13 or DUNS code)", "13 digits"},
		{NBarcodeApplications::kPricePerUnitOfMeasure, "8005", "Price per Unit of Measure", "6 digits"},
		{NBarcodeApplications::k91CompanyInternalInformation, "91", "Company Internal Information", "1-30 alphanumeric"},
		{NBarcodeApplications::k92CompanyInternalInformation, "92", "Company Internal Information", "1-30 alphanumeric"},
		{NBarcodeApplications::k93CompanyInternalInformation, "93", "Company Internal Information", "1-30 alphanumeric"}
	};

	return kBarcodeApplications;
}
