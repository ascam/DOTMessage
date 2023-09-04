#ifndef BARCODE_APPLICATIONS_DOT_MESSAGE
#define BARCODE_APPLICATIONS_DOT_MESSAGE

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
}

#endif
