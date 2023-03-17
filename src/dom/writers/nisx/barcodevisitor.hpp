#ifndef MACSA_NISX_BARCODE_VISITOR_HPP
#define MACSA_NISX_BARCODE_VISITOR_HPP

#include "variableobjectvisitor.hpp"

namespace macsa {
	namespace nisx {
		class BarcodeVisitor :  public VariableObjectVisitor
		{
			public:
				BarcodeVisitor(tinyxml2::XMLDocument& xmlDocument, tinyxml2::XMLElement* xmlParent, const dot::Document& dom);
				virtual ~BarcodeVisitor() = default;

				/**
				 * @brief VisitEnter. Start the visit in a Barcode object
				 * @param barcode: Barcode object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool VisitEnter(const dot::Barcode& barcode) override;

				/**
				 * @brief VisitExit. Exits the visit in a Barcode Object
				 * @param barcode: Barcode object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool VisitExit(const dot::Barcode& barcode) override;

			private:
				tinyxml2::XMLElement* _xmlParent;
		};
	}
}

#endif
