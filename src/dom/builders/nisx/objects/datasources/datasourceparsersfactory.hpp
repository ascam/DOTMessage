#ifndef MACSA_NISX_OBJECT_DATASOURCE_PARSERSFACTORY_HPP
#define MACSA_NISX_OBJECT_DATASOURCE_PARSERSFACTORY_HPP

#include <utility>
#include <string>
#include <unordered_map>
#include "datasourceparser.hpp"
#include "utils/macsalogger.hpp"

namespace macsa {
	namespace nisx {

		class IConcreteDataSourceParserFactory
		{
			public :
				virtual DataSourceParser* MakeParser(dot::VariableObject* object) = 0;
		};

		using tDataSourceParsersFactories = std::unordered_map<std::string, std::unique_ptr<IConcreteDataSourceParserFactory>>;

		class DataSourceParsersFactory
		{
			public:
				static DataSourceParser* Get(const std::string& type, dot::VariableObject* object)
				{
					const auto& parsersFactories = getFactories();
					auto foundIt = parsersFactories.find(type);
					if (foundIt != parsersFactories.end()) {
						return foundIt->second->MakeParser(object);
					}
					else {
						utils::ELog() << type << " object parsers factory not found.";
						return nullptr;
					}
				}

				static bool Register(const std::string& type, IConcreteDataSourceParserFactory* concreteParsersFactory) {
					auto& parsersFactories = getFactories();
					if (parsersFactories.find(type) == parsersFactories.end()) {
#if defined(ARM) // Required by linaro toolchains
						auto result = parsersFactories.emplace(type, std::unique_ptr<IConcreteDataSourceParserFactory>(concreteParsersFactory));
#else
						auto result = parsersFactories.emplace(type, concreteParsersFactory);
#endif
						return result.second;
					}
					else {
						utils::WLog() << "Unable to register " << type << " datasource parser factory: Duplicated key.";
						return false;
					}
				}
			private:
				static tDataSourceParsersFactories& getFactories() {
					static tDataSourceParsersFactories objectsFactories{};
					return objectsFactories;
				}
		};

		template<class tDataSourceParser>
		class ConcreteDataSourceParserFactory : public IConcreteDataSourceParserFactory
		{
			public:
				static bool Register(const std::string& type) {
					return DataSourceParsersFactory::Register(type, new ConcreteDataSourceParserFactory<tDataSourceParser>());
				};

				DataSourceParser* MakeParser(dot::VariableObject* object) {
					return new tDataSourceParser(object);
				}
		};
	}
}

#endif
