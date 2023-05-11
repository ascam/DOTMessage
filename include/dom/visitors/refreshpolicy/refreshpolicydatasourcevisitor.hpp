#ifndef MACSA_REFRESH_POLICY_DATA_SOURCE_VISITOR_HPP
#define MACSA_REFRESH_POLICY_DATA_SOURCE_VISITOR_HPP

#include <bitset>

#include "dom/documentvisitor.hpp"
#include "dom/rippers/context.hpp"
#include "dom/refreshpolicy.hpp"

using macsa::dot::Document;

static const int TotalRefreshPolicyEnumerationElements = 10;

namespace macsa
{
	namespace dot
	{
		using LabelRefreshPolicies = std::bitset<TotalRefreshPolicyEnumerationElements>;

		class RefreshPolicyDataSourceVisitor : public macsa::dot::IDocumentVisitor
		{
			public:

			RefreshPolicyDataSourceVisitor(Context* context) :
			_context{context}
			{}

			bool Visit(const CounterDataSource& ds)
			{
				_result |= static_cast <unsigned int>(RefreshPolicy::kCounter);

				return true;
			}

			bool Visit(const DateTimeDataSource& ds)
			{
				//TODO : @jsubi, parse formula to obtain refresh policy
				_result |= static_cast <unsigned int>(RefreshPolicy::kSeconds);

				return true;
			}

			/**
			* @brief getDataSourceResult. Return the list of active refresh
			* policies on the label.
			* @return bitset : list of the active refresh policies.
			*/
			LabelRefreshPolicies getDataSourceResult()
			{
				return _result;
			}

			private:
			Context* _context;
			LabelRefreshPolicies _result;
		};
	}
}
#endif
