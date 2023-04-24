#ifndef MACSA_NISX_TEXT_VISITOR_HPP
#define MACSA_NISX_TEXT_VISITOR_HPP

#include "variableobjectvisitor.hpp"

namespace macsa {
	namespace nisx {
		class TextVisitor :  public VariableObjectVisitor
		{
			public:
				TextVisitor(tinyxml2::XMLDocument& xmlDocument, tinyxml2::XMLElement* xmlParent, const dot::Document& dom);
				virtual ~TextVisitor() = default;

				/**
				 * @brief VisitEnter. Start the visit in a Text object
				 * @param text: Text object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool VisitEnter(const dot::Text&) override;

				/**
				 * @brief VisitExit. Exits the visit in a Text Object
				 * @param text: Text object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool VisitExit(const dot::Text&) override;

			private:
				tinyxml2::XMLElement* _xmlParent;

				bool visitTextBoxProperties(const dot::TextBoxProperties& textBox);
		};
	}
}

#endif
