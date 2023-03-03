#ifndef DOT_MESSAGE_DATABASE_DATASOURCE_HPP
#define DOT_MESSAGE_DATABASE_DATASOURCE_HPP

#include <string>
#include "dom/components/datasources/datasource.hpp"

namespace macsa {
	namespace dot {

		class IDocumentVisitor;

		/**
		 * @brief The DatabaseDataSource class. This class allow the objects
		 * to return variable data from a database.
		 * NOT IMPLEMENTED!
		 */
		class DatabaseDataSource final : public DataSource
		{
			public:
				DatabaseDataSource();
				virtual ~DatabaseDataSource() = default;

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) override;

				/**
				 * @brief GetFieldName. Getter method for database fieldname
				 * data source
				 * @return The selected fieldname.
				 */
				const std::string& GetFieldName() const {
					return _fieldName;
				}

				/**
				 * @brief SetFieldName. Setter method for database fieldname
				 * data source
				 * @param fieldName: The selected fieldname.
				 */
				void SetFieldName(const std::string& fieldName) {
					_fieldName = fieldName;
				}

				/**
				 * @brief GetDefaultValue. Getter method for datasource
				 * default value.
				 * @return The string to return if database is not present.
				 */
				const std::string& GetDefaultValue() const {
					return _defaultValue;
				}

				/**
				 * @brief SetDefaultValue. Setter method for datasource
				 * default value.
				 * @param defaultValue: The string to return if database is
				 * not present.
				 */
				void SetDefaultValue(const std::string& defaultValue) {
					_defaultValue = defaultValue;
				}

				/**
				 * @brief GetValue. Getter method for database record value
				 * @return string with the current value
				 */
				const std::string& GetValue() const {
					return _value;
				}

				/**
				 * @brief SetValue. Setter method for database record value
				 * @param value: string with the value to set
				 */
				void SetValue(const std::string& value) {
					_value = value;
				}

				/**
				 * @brief GetConnectionName. Getter method for database
				 * connection name
				 * @return string with the connection name
				 */
				const std::string& GetConnectionName() const {
					return _connectionName;
				}

				/**
				 * @brief SetConnectionName. Setter method for database
				 * connection name
				 * @param name: Name of the connection to set
				 */
				void SetConnectionName(const std::string& name) {
					_connectionName = name;
				}

				/**
				 * @brief GetTableName. Getter method for the table name.
				 * @return string with the table to use
				 */
				const std::string& GetTableName() const {
					return _tableName;
				}

				/**
				 * @brief SetTableName. Setter method for the table name.
				 * @param name: Name to set the current table to use
				 */
				void SetTableName(const std::string& name) {
					_tableName = name;
				}

			private:
				std::string _fieldName;
				std::string _defaultValue;
				std::string _value;
				std::string _connectionName;
				std::string _tableName;
		};
	}
}

#endif
