#ifndef MACSA_NISX_OBJECTPARSERSFACTORY_HPP
#define MACSA_NISX_OBJECTPARSERSFACTORY_HPP

#include <utility>
#include <unordered_map>
#include "objectparser.hpp"
#include "utils/macsalogger.hpp"

namespace macsa {
	namespace nisx {

		class IConcreteObjectParserFactory
		{
			public :
				virtual ObjectParser* MakeParser(dot::Object* object) = 0;
		};

		using tObjectParsersFactories = std::unordered_map<std::string, std::unique_ptr<IConcreteObjectParserFactory>>;

		class ObjectParsersFactory
		{
			public:
				static ObjectParser* Get(const std::string& type, dot::Object* object)
				{
					const auto& objectFactories = getFactories();
					auto foundIt = objectFactories.find(type);
					if (foundIt != objectFactories.end()) {
						return foundIt->second->MakeParser(object);
					}
					else {
						utils::ELog() << type << " object parsers factory not found.";
						return nullptr;
					}
				}

				static bool Register(const std::string& type, IConcreteObjectParserFactory* concreteParsersFactory) {
					auto& objectsFactories = getFactories();
					if (objectsFactories.find(type) == objectsFactories.end()) {
#if defined(ARM) // Required by linaro toolchains
						auto result = objectsFactories.emplace(type, std::unique_ptr<IConcreteObjectParserFactory>(concreteParsersFactory));
#else
						auto result = objectsFactories.emplace(type, concreteParsersFactory);
#endif
						return result.second;
					}
					else {
						utils::WLog() << "Unable to register " << type << " objects parser factory: Duplicated key.";
						return false;
					}
				}
			private:
				static tObjectParsersFactories& getFactories() {
					static tObjectParsersFactories objectsFactories{};
					return objectsFactories;
				}
		};

		template<class tObjectParser>
		class ConcreteObjectParserFactory : public IConcreteObjectParserFactory
		{
			public:
				static bool Register(const std::string& type) {
					return ObjectParsersFactory::Register(type, new ConcreteObjectParserFactory<tObjectParser>());
				};

				ObjectParser* MakeParser(dot::Object* object) {
					return new tObjectParser(object);
				}
		};
	}
}

#endif
