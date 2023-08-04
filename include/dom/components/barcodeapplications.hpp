#ifndef BARCODE_APPLICATIONS_DOT_MESSAGE
#define BARCODE_APPLICATIONS_DOT_MESSAGE

#include "utils/smartenum.hpp"

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

	class BarcodeApplications final : public utils::SmartEnum<NBarcodeApplications>
	{
		public:
			BarcodeApplications (const NBarcodeApplications& type = NBarcodeApplications::kSerialShippingContainerCode) :
				utils::SmartEnum<NBarcodeApplications>(type)
			{}
			BarcodeApplications (const std::string& type) :
				utils::SmartEnum<NBarcodeApplications>(NBarcodeApplications::kSerialShippingContainerCode)
			{
				fromString(type);
			}

			const BarcodeApplications& operator = (const std::string& val) {
				fromString(val);
				return *this;
			}

			const std::vector<std::pair<NBarcodeApplications, std::string>>& getData() const override;
	};
}

#endif
