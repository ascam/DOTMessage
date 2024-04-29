#ifndef DOT_MESSAGE_ROUNDING_DATE_POLICY_HPP
#define DOT_MESSAGE_ROUNDING_DATE_POLICY_HPP

#include "utils/smartenum.hpp"

namespace macsa::dot {
	enum class NRoundingPolicy {
		kNoRound,
		kRoundFDM, // First day of the month.
		kRoundLDM, // Last day of the month.
		kRoundDoM, // Concrete day of the month.
		kRoundDoW  // Concrete day of the week.
	};

	class RoundingPolicy final : public utils::SmartEnum<NRoundingPolicy>
	{
		public:
			RoundingPolicy(NRoundingPolicy type = NRoundingPolicy::kNoRound) :
				utils::SmartEnum<NRoundingPolicy>(type)
			{}
			RoundingPolicy(const std::string& type) :
				utils::SmartEnum<NRoundingPolicy>(NRoundingPolicy::kNoRound)
			{
				fromString(type);
			}

			const RoundingPolicy& operator = (const std::string& val) {
				fromString(val);
				return *this;
			}

		private:
			const std::vector<std::pair<NRoundingPolicy,std::string>>& getData() const override{
				static const std::vector<std::pair<NRoundingPolicy,std::string>> data {
					{NRoundingPolicy::kNoRound , "NoRound"},
					{NRoundingPolicy::kRoundFDM, "RoundFDM"},
					{NRoundingPolicy::kRoundLDM, "RoundLDM"},
					{NRoundingPolicy::kRoundDoM, "RoundDoM"},
					{NRoundingPolicy::kRoundDoW, "RoundDoW"}
				};
				return data;
			}
	};
}

#endif
