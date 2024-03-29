#ifndef DOT_MESSAGE_DATASOURCE_FACTORY_HPP
#define DOT_MESSAGE_DATASOURCE_FACTORY_HPP

#include <utility>
#include <unordered_map>
#include "dom/object.hpp"
#include "dom/components/datasources/datasource.hpp"
#include "utils/macsalogger.hpp"

namespace macsa {
	namespace dot {
		class IConcreteDataSourceFactory
		{
			public :
				virtual DataSource* MakeDataSource(const dot::Object& obj) = 0;
		};
		using tDataSourceFactories = std::unordered_map<NDataSourceType, std::unique_ptr<IConcreteDataSourceFactory>>;

		class DataSourceFactory
		{
			public:
				static DataSource* Get(NDataSourceType dataSource, const dot::Object& obj)
				{
					const auto& dataSourceFactories = getFactories();
					auto foundIt = dataSourceFactories.find(dataSource);
					if (foundIt != dataSourceFactories.end()) {
						return foundIt->second->MakeDataSource(obj);
					}
					else {
						utils::ELog() << DataSourceType(dataSource).toString() << " dataSource factory not found.";
						return nullptr;
					}
				}

				static bool Register(NDataSourceType type, IConcreteDataSourceFactory* concreteDataSourceFactory) {
					auto& DataSourceFactories = getFactories();
					if (DataSourceFactories.find(type) == DataSourceFactories.end()) {
#if defined(ARM) // Required by linaro toolchains
						auto result = DataSourceFactories.emplace(type.toString(), std::unique_ptr<IConcreteDataSourceFactory>(concreteDataSourceFactory));
#else
						auto result = DataSourceFactories.emplace(type, concreteDataSourceFactory);
#endif
						return result.second;
					}
					else {
						utils::WLog() << "Unable to register " << DataSourceType(type).toString()
									  << " dataSource factory: Duplicated key.";
						return false;
					}
				}
			private:
				static tDataSourceFactories& getFactories() {
					static tDataSourceFactories dataSourceFactories{};
					return dataSourceFactories;
				}
		};

		template<class tDataSource>
		class ConcreteDataSourceFactory : public IConcreteDataSourceFactory
		{
			public:
				static bool Register(const NDataSourceType& type) {
					return DataSourceFactory::Register(type, new ConcreteDataSourceFactory<tDataSource>());
				};

				DataSource* MakeDataSource(const dot::Object& obj) {
					return new tDataSource(obj);
				}
		};
	}
}

#endif
