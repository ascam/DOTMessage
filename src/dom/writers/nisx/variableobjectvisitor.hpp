#ifndef MACSA_NISX_VARIABLE_OBJECT_VISITOR_HPP
#define MACSA_NISX_VARIABLE_OBJECT_VISITOR_HPP

#include "dom/documentvisitor.hpp"
#include "objectvisitor.hpp"

namespace macsa {
	namespace nisx {
		class VariableObjectVisitor :  public dot::IDocumentVisitor, public ObjectVisitor
		{
			public:
				VariableObjectVisitor(tinyxml2::XMLDocument& xmlDocument, const dot::Document& dom);
				virtual ~VariableObjectVisitor() = default;

				/**
				 * @brief Visit. Visits a counter data source
				 * @param counter: counter data source to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool Visit(const dot::CounterDataSource& counter) override;

				/**
				 * @brief Visit. Visits a database data source
				 * @param database: database data source to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool Visit(const dot::DatabaseDataSource& database) override;

				/**
				 * @brief Visit. Visits a date and time data source
				 * @param datetime: Date and time data source to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool Visit(const dot::DateTimeDataSource& datetime) override;

				/**
				 * @brief Visit. Visits a user input data source
				 * @param userInput: User input data source to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool Visit(const dot::UserInputDataSource& userInput) override;

				/**
				 * @brief Visit. Visits a composite data source
				 * @param composite: Composite data source to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool Visit(const dot::CompositeDataSource& composite) override;

			protected:
				const dot::Document& _dom;
				tinyxml2::XMLDocument& _xmlDocument;
				tinyxml2::XMLElement* _xmlElement;
				tinyxml2::XMLElement* _xmlDataSource;

				bool writeColor(const dot::Color& color, tinyxml2::XMLElement* xmlColor) const;
		};
	}
}

#endif
