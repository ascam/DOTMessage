#ifndef BARCODE_APPLICATIONS_DOT_MESSAGE
#define BARCODE_APPLICATIONS_DOT_MESSAGE

#include <string>
#include <vector>

namespace macsa::dot
{
	enum class NBarcodeApplications {
		kSerialShippingContainerCode,
		kGTIN14,
		kNumberOfContainers,
		kBatchNumber,
		kProductionRate,
		kPackagingData,
		kSellByDate,
		kExpirationDate,
		kProductVariant,
		kSerialNumber,
		kHIBCC,
		kLotNumber,
		kAdditionalProductIdentification,
		kReferenceToSourceEntity,
		kQuantityEach,
		kProductNetWeight,
		kNumberOfUnitsContained,
		kCustomerPurchaseOrderNumber,
		kShipDeliverToLocationCode,
		kPricePerUnitOfMeasure,
		k91CompanyInternalInformation,
		k92CompanyInternalInformation,
		k93CompanyInternalInformation
	};

	struct BarcodeApplicationData
	{
		NBarcodeApplications type;
		std::string code;
		std::string description;
		std::string format;
	};

	class BarcodeApplications
	{
		public:
			const static std::vector<BarcodeApplicationData>& getData();
	};
}

#endif
