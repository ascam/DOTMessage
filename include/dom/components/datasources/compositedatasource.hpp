#ifndef DOT_MESSAGE_COMPOSITE_DATASOURCE_HPP
#define DOT_MESSAGE_COMPOSITE_DATASOURCE_HPP

#include <string>

#include "signal/signal.hpp"
#include "dom/rippers/context.hpp"
#include "dom/components/datasources/datasource.hpp"

namespace macsa {
	namespace dot {
		class IDocumentVisitor;

		/**
		 * @brief The CompositeDataSource class. This class allow the objects
		 * to return variable data composed from fixed text and the data of other
		 * objects
		 */
		class CompositeDataSource final : public DataSource
		{
			public:
				CompositeDataSource();
				virtual ~CompositeDataSource() = default;

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) override;

				/**
				 * @brief GetFormula. Getter method for the inner composition
				 * formula.
				 * @return The inner composition formula.
				 */
				const std::string GetFormula() const {
					return _formula;
				}

				/**
				 * @brief SetFormula. Setter method of the formula composition.
				 * @param formula: The
				 */
				void SetFormula(const std::string& formula);


				/**
				 * @brief GetData. Get data source updated data result.
				 * @return data source text result data.
				 */
				std::string GetData(Context* context) const override;

			public:
				Signal<> FormulaChanged;

			private:
				std::string _formula;
				static bool _registered;
		};
	}
}

#endif
