#ifndef DOT_MESSAGE_OBJECT_REFRESH_POLICY_HPP
#define DOT_MESSAGE_OBJECT_REFRESH_POLICY_HPP

#include <type_traits>

namespace macsa {
	namespace dot {
		/**
		 * @brief Enumeration for datasource refresh policy
		 */
		enum class RefreshPolicy : uint32_t
		{
			kNone = 0,         // No update
			kCounter = 0x1,   // Update frequency when counter changes
			kSeconds = 0x2,   // Update frequency every second
			kMinutes = 0x4,   // Update frequency every minute
			kHours   = 0x8,   // Update frequency every hour
			kPeriod  = 0x10,  // Update frequency every 12 hours
			kDays    = 0x20,  // Update frequency every day
			kWeeks   = 0x40,  // Update frequency every week
			kMonths  = 0x80,  // Update frequency every month
			kYears   = 0x100, // Update frequency every year
		};
		using RefreshPolicy_t = std::underlying_type_t<RefreshPolicy>;

		inline RefreshPolicy operator|(const RefreshPolicy& lhs, const RefreshPolicy& rhs)
		{
			return static_cast<RefreshPolicy> (
						static_cast<std::underlying_type<RefreshPolicy>::type>(lhs) |
						static_cast<std::underlying_type<RefreshPolicy>::type>(rhs));
		}

		inline RefreshPolicy operator&(const RefreshPolicy& lhs, const RefreshPolicy& rhs)
		{
			return static_cast<RefreshPolicy> (
						static_cast<std::underlying_type<RefreshPolicy>::type>(lhs) &
						static_cast<std::underlying_type<RefreshPolicy>::type>(rhs));
		}

		inline RefreshPolicy operator^(const RefreshPolicy& lhs, const RefreshPolicy& rhs)
		{
			return static_cast<RefreshPolicy> (
						static_cast<std::underlying_type<RefreshPolicy>::type>(lhs) ^
						static_cast<std::underlying_type<RefreshPolicy>::type>(rhs));
		}

		inline RefreshPolicy operator~(const RefreshPolicy& rhs)
		{
			return static_cast<RefreshPolicy> (
						~static_cast<std::underlying_type<RefreshPolicy>::type>(rhs));
		}

		inline void operator|=(RefreshPolicy& lhs, const RefreshPolicy& rhs)
		{
			lhs = static_cast<RefreshPolicy> (
					  static_cast<std::underlying_type<RefreshPolicy>::type>(lhs) |
					  static_cast<std::underlying_type<RefreshPolicy>::type>(rhs));
		}

		inline void operator&=(RefreshPolicy& lhs, const RefreshPolicy& rhs)
		{
			lhs = static_cast<RefreshPolicy> (
					  static_cast<std::underlying_type<RefreshPolicy>::type>(lhs) &
					  static_cast<std::underlying_type<RefreshPolicy>::type>(rhs));
		}

		inline void operator^=(RefreshPolicy& lhs, const RefreshPolicy& rhs)
		{
			lhs = static_cast<RefreshPolicy> (
					  static_cast<std::underlying_type<RefreshPolicy>::type>(lhs) ^
					  static_cast<std::underlying_type<RefreshPolicy>::type>(rhs));
		}
	}
}

#endif
