#ifndef DOT_MESSAGE_OBJECT_TYPE_HPP
#define DOT_MESSAGE_OBJECT_TYPE_HPP

#include <string>
#include "utils/smartenum.hpp"

namespace macsa {
	namespace dot {
		enum class NObjectType {
			kText,
			kBarcode,
			kImage,
			kRectangle,
			kDiamond,
			kEllipse,
			kLine
		};

		static constexpr const char* kText      = "TextField";
		static constexpr const char* kBarcode   = "BarcodeField";
		static constexpr const char* kImage     = "ImageField";
		static constexpr const char* kRectangle = "RectangleField";
		static constexpr const char* kDiamond   = "DiamondField";
		static constexpr const char* kEllipse   = "EllipseField";
		static constexpr const char* kLine      = "LineField";

		class ObjectType final : public utils::SmartEnum<NObjectType>
		{
			public:
				ObjectType (const NObjectType& type = NObjectType::kText) :
					utils::SmartEnum<NObjectType>(type)
				{}
				ObjectType (const std::string& type) :
					utils::SmartEnum<NObjectType>(NObjectType::kText)
				{
					fromString(type);
				}

				const ObjectType& operator = (const std::string& val) {
					fromString(val);
					return *this;
				}

			private:
				const std::vector<std::pair<NObjectType,std::string>>& getData() const override{
					static const std::vector<std::pair<NObjectType,std::string>> kNObjectTypeData {
						{NObjectType::kText,      kText},
						{NObjectType::kBarcode,	  kBarcode},
						{NObjectType::kImage,	  kImage},
						{NObjectType::kRectangle, kRectangle},
						{NObjectType::kDiamond,	  kDiamond},
						{NObjectType::kEllipse,	  kEllipse},
						{NObjectType::kLine,	  kLine}
					};
					return kNObjectTypeData;
				}
		};
	}
}

#endif
