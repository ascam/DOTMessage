#ifndef MACSA_REFRESH_POLICY_VISITOR_HPP
#define MACSA_REFRESH_POLICY_VISITOR_HPP

#include <bitset>

#include "dom/documentvisitor.hpp"
#include "dom/rippers/context.hpp"
#include "dom/visitors/refreshpolicy/refreshpolicydatasourcevisitor.hpp"

namespace macsa {
	namespace dot {
		class RefreshPolicyObjectVisitor : public dot::IDocumentVisitor
		{
			public:
				RefreshPolicyObjectVisitor(dot::Document* doc, Context* context);
				virtual ~RefreshPolicyObjectVisitor() = default;

				/**
				 * @brief VisitEnter. Start the visit in a Text object
				 * @param text: Text object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool VisitEnter(const dot::Text&) override;

				/**
				 * @brief VisitEnter. Start the visit in a Barcode object
				 * @param barcode: Barcode object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool VisitEnter(const dot::Barcode& barcode) override;

				/**
				 * @brief getResult. Return the list of active refresh
				 * policies on the label.
				 * @return bitset : list of the active refresh policies.
				 */
				LabelRefreshPolicies getResult()
				{
					return _result;
				}

			private:
				const dot::Document* _doc;
				Context* _context;
				LabelRefreshPolicies _result;
		};
	}
}

#endif
