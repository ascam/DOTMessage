#ifndef DOT_MESSAGE_OBJECT_DATASOURCES_HPP
#define DOT_MESSAGE_OBJECT_DATASOURCES_HPP

#include "utils/smartenum.hpp"

namespace macsa {
	namespace dot {
		class Context;
		class IDocumentVisitor;
		/**
		 * @brief DataSource types
		 */
		enum class NDataSourceType
		{
			kCounter,
			kDataBase,
			kDateTime,
			kComposite,
			kUserInput
		};

		static constexpr const char* kDataSourceTypeCounter = "Counter";
		static constexpr const char* kDataSourceTypeDataBase = "DataBase";
		static constexpr const char* kDataSourceTypeDateTime = "DateTime";
		static constexpr const char* kDataSourceTypeComposite = "Composite";
		static constexpr const char* kDataSourceTypeUserInput = "UserInput";

		/**
		 * @brief DataSource types smart enum
		 */
		class DataSourceType final : public utils::SmartEnum<NDataSourceType>
		{
			public:
				DataSourceType(const NDataSourceType& dataSource = NDataSourceType::kCounter) :
					utils::SmartEnum<NDataSourceType>(dataSource)
				{}

				DataSourceType(const std::string& dataSource) :
					utils::SmartEnum<NDataSourceType>(NDataSourceType::kCounter)
				{
					fromString(dataSource);
				}

				const DataSourceType& operator = (const std::string& val) {
					fromString(val);
					return *this;
				}

			private:
				const std::vector<std::pair<NDataSourceType,std::string>>& getData() const override{
					static const std::vector<std::pair<NDataSourceType,std::string>> kDataSourceType {
						{NDataSourceType::kCounter, kDataSourceTypeCounter},
						{NDataSourceType::kComposite, kDataSourceTypeComposite},
						{NDataSourceType::kDataBase, kDataSourceTypeDataBase},
						{NDataSourceType::kDateTime, kDataSourceTypeDateTime},
						{NDataSourceType::kUserInput, kDataSourceTypeUserInput}
					};
					return kDataSourceType;
				}
		};

		/**
		 * @brief The DataSource class: This class allow the objects to return variable data
		 */
		class DataSource
		{
			public:
				DataSource(const DataSourceType& type) :
					_type{type}
				{}
				virtual ~DataSource() = default;

				const DataSourceType& GetType() const {
					return _type;
				}

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				virtual bool Accept(IDocumentVisitor* visitor) = 0;

				/**
				 * @brief GetData. Get data source updated data result.
				 * @return data source text result data.
				 */
				virtual std::string GetData(Context* context) const = 0;

			private:
				DataSourceType _type;
		};
	}
}

#endif
