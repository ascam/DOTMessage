#ifndef DOT_MESSAGE_OBJECT_ALIGNMENT_HPP
#define DOT_MESSAGE_OBJECT_ALIGNMENT_HPP

#include <string>
#include "utils/smartenum.hpp"

namespace macsa
{
	namespace dot
	{
		/**
		 * @brief The VerticalAlignment smart enum.
		 */
		enum class NVerticalAlignment {
			kTop,
			kMiddle,
			kBottom
		};

		static constexpr const char* kTop    = "Top";
		static constexpr const char* kMiddle = "Middle";
		static constexpr const char* kBottom = "Bottom";

		class VerticalAlignment final : public utils::SmartEnum<NVerticalAlignment>
		{
			public:
				VerticalAlignment (const NVerticalAlignment& alignment = NVerticalAlignment::kTop) :
					utils::SmartEnum<NVerticalAlignment>(alignment)
				{}
				VerticalAlignment (const std::string& alignment) :
					utils::SmartEnum<NVerticalAlignment>(NVerticalAlignment::kTop)
				{
					fromString(alignment);
				}

				const VerticalAlignment& operator = (const std::string& alignment) {
					fromString(alignment);
					return *this;
				}
				const VerticalAlignment& operator = (NVerticalAlignment alignment) {
					_val = alignment;
					return *this;
				}

			private:
				const std::vector<std::pair<NVerticalAlignment,std::string>>& getData() const override{
					static const std::vector<std::pair<NVerticalAlignment,std::string>> kNVerticalAlignmentData {
						{NVerticalAlignment::kTop,    kTop},
						{NVerticalAlignment::kMiddle, kMiddle},
						{NVerticalAlignment::kBottom, kBottom}
					};
					return kNVerticalAlignmentData;
				}
		};

		enum class NHorizontalAlignment {
			kLeft,
			kCenter,
			kRight
		};

		static constexpr const char* kLeft    = "Left";
		static constexpr const char* kCenter = "Center";
		static constexpr const char* kRight = "Right";

		class HorizontalAlignment final : public utils::SmartEnum<NHorizontalAlignment>
		{
			public:
				HorizontalAlignment (const NHorizontalAlignment& alignment = NHorizontalAlignment::kLeft) :
					utils::SmartEnum<NHorizontalAlignment>(alignment)
				{}
				HorizontalAlignment (const std::string& alignment) :
					utils::SmartEnum<NHorizontalAlignment>(NHorizontalAlignment::kLeft)
				{
					fromString(alignment);
				}

				const HorizontalAlignment& operator = (const std::string& alignment) {
					fromString(alignment);
					return *this;
				}

				const HorizontalAlignment& operator = (NHorizontalAlignment alignment) {
					_val = alignment;
					return *this;
				}

			private:
				const std::vector<std::pair<NHorizontalAlignment,std::string>>& getData() const override{
					static const std::vector<std::pair<NHorizontalAlignment,std::string>> kNHorizontalAlignmentData {
						{NHorizontalAlignment::kLeft,   kLeft},
						{NHorizontalAlignment::kCenter, kCenter},
						{NHorizontalAlignment::kRight,  kRight}
					};
					return kNHorizontalAlignmentData;
				}
		};
	}
}
#endif
