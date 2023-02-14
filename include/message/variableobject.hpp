#ifndef DOT_MESSAGE_VARIABLE_OBJECT_HPP
#define DOT_MESSAGE_VARIABLE_OBJECT_HPP

#include <memory>
#include "object.hpp"
#include "datasources/datasource.hpp"

namespace macsa {
	namespace dot {

		/**
		 * @brief The Variable Object class.
		 * This class contains the abstract variable object definition.
		 */
		class VariableObject : public Object
		{
			public:
				VariableObject(const std::string& id, const ObjectType& type, const Geometry& geometry = Geometry());
				VariableObject(const Object&) = delete;
				virtual ~VariableObject();

				/**
				 * @brief GetData. Getter method to get the current
				 * value of the text resolving the variable fields.
				 * @return The text that must be rendered after resolving
				 * variable fields.
				 */
				virtual std::string GetData() const = 0;

				/**
				 * @brief GetRefreshPolicy. Overrided method of
				 * Object::GetRefreshPolicy
				 * @return The refresh policy of the object.
				 */
				virtual RefreshPolicy GetRefreshPolicy() const override;

				/**
				 * @brief GetDatasource. Getter method for variable data source
				 * @return The raw pointer to a data source if has data source or
				 * nullptr if text hasn't variable data.
				 */
				DataSource* GetDatasource() const;
				/**
				 * @brief SetDatasource. Setter method for variable data source
				 * @param type: type to data source to create and attach.
				 * @return Raw pointer to the created data source.
				 */
				DataSource* SetDatasource(const DataSourceType& type);

				/**
				 * @brief IsVariable. Getter method to get if the object
				 * can change its inner value.
				 * @return true if the object can change the inner value,
				 * false if the object is static.
				 */
				bool IsVariable() const override;

			protected:
				std::unique_ptr<DataSource> _datasource;
		};
	}
}

#endif
