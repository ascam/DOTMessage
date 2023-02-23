#ifndef DOT_MESSAGE_COMPOSITE_DATASOURCE_HPP
#define DOT_MESSAGE_COMPOSITE_DATASOURCE_HPP

#include <string>

#include "signal/signal.hpp"
#include "message/datasources/datasource.hpp"

namespace macsa {
	namespace dot {

		class Document;
		class Object;

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

				void SetContext(const Document* document, const Object* parent) {
					_document = document;
					_parent = parent;
				}

				/**
				 * @brief GetData. Getter method to get the inner data
				 * of a data source.
				 * @return The text generated with the inner data of a
				 * data source.
				 */
				std::string GetData() override;

				/**
				 * @brief GetRefreshPolicy. Getter method to get the refresh
				 * policy of a data source.
				 * @return The refresh policy of the data source.
				 */
				RefreshPolicy GetRefreshPolicy() const override;

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

			public:
				Signal<> FormulaChanged;

			private:
				using Token = std::pair<std::string,std::string>;
				std::string _formula;
				const Document* _document;
				const Object* _parent;
				std::vector<Token> _tokens;
		};
	}
}

#endif
