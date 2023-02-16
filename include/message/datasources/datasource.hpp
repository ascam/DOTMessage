#ifndef DOT_MESSAGE_OBJECT_DATASOURCES_HPP
#define DOT_MESSAGE_OBJECT_DATASOURCES_HPP

#include "utils/smartenum.hpp"
#include "message/refreshpolicy.hpp"

namespace macsa {
	namespace dot {
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
					static const std::vector<std::pair<NDataSourceType,std::string>> kNNDataSourceType {
						{NDataSourceType::kCounter,   "Counter"},
						{NDataSourceType::kComposite, "Composite"},
						{NDataSourceType::kDataBase,  "DataBase"},
						{NDataSourceType::kDateTime,  "DateTime"},
						{NDataSourceType::kUserInput, "UserInput"}
					};
					return kNNDataSourceType;
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
				 * @brief GetData. Getter method to get the inner data
				 * of a data source.
				 * @return The text generated with the inner data of a
				 * data source.
				 */
				virtual std::string GetData() = 0;

				/**
				 * @brief GetRefreshPolicy. Getter method to get the refresh
				 * policy of a data source.
				 * @return The refresh policy of the data source.
				 */
				virtual RefreshPolicy GetRefreshPolicy() const = 0;

			private:
				const DataSourceType& _type;
		};
	}
}

#endif
