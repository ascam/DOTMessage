#ifndef DOT_MESSAGE_OBJECT_DATASOURCES_HPP
#define DOT_MESSAGE_OBJECT_DATASOURCES_HPP

#include "utils/smartenum.hpp"
#include "dom/refreshpolicy.hpp"

namespace macsa {
	namespace dot {
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
						{NDataSourceType::kCounter,   "Counter"},
						{NDataSourceType::kComposite, "Composite"},
						{NDataSourceType::kDataBase,  "DataBase"},
						{NDataSourceType::kDateTime,  "DateTime"},
						{NDataSourceType::kUserInput, "UserInput"}
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

			private:
				DataSourceType _type;
		};
	}
}

#endif
