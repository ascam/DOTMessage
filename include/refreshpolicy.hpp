#ifndef DOT_MESSAGE_OBJECT_REFRESH_POLICY_HPP
#define DOT_MESSAGE_OBJECT_REFRESH_POLICY_HPP

#include <type_traits>

namespace macsa {
	namespace dot {
		/**
		 * @brief Enumeration for DateTime precision
		 */
		enum class RefreshPolicy
		{
			// No update
			kNone = 0,
			// Update frequency when counter change
			kCounter = 0x1,
			// Update frequency every second
			kSeconds = 0x2,
			// Update frequency every minute
			kMinutes = 0x4,
			// Update frequency every hour
			kHours = 0x8,
			// Update frequency every 12 hours
			kPeriod = 0x10,
			// Update frequency every day
			kDays = 0x20,
			// Update frequency every week
			kWeeks = 0x40,
			// Update frequency every month
			kMonths = 0x80,
			// Update frequency every year
			kYears = 0x100,
		};

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
