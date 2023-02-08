#ifndef DOT_MESSAGE_OBJECTSFACTORY_HPP
#define DOT_MESSAGE_OBJECTSFACTORY_HPP

#include <utility>
#include <unordered_map>
#include "message/object.hpp"
#include "message/objecttype.hpp"
#include "utils/macsalogger.hpp"

namespace macsa {
	namespace dot {

		class IConcreteObjectsFactory
		{
			public :
				virtual Object* MakeObject(const std::string& id) = 0;
		};

		using tObjectsFactories = std::unordered_map<std::string, std::unique_ptr<IConcreteObjectsFactory>>;

		class ObjectsFactory
		{
			public:
				static Object* Get(const std::string& id, const ObjectType& type)
				{
					const auto& commandFactories = getFactories();
					auto foundIt = commandFactories.find(type.toString());
					if (foundIt != commandFactories.end()) {
						return foundIt->second->MakeObject(id);
					}
					else {
						utils::ELog() << type.toString() << " objects factory not found.";
						return nullptr;
					}
				}

				static bool Register(const ObjectType& type, IConcreteObjectsFactory* concreteObjectsFactory) {
					auto& objectsFactories = getFactories();
					if (objectsFactories.find(type.toString()) == objectsFactories.end()) {
#if defined(ARM) // Required by linaro toolchains
						auto result = objectsFactories.emplace(type.toString(), std::unique_ptr<IConcreteObjectsFactory>(concreteObjectsFactory));
#else
						auto result = objectsFactories.emplace(type.toString(), concreteObjectsFactory);
#endif
						return result.second;
					}
					else {
						utils::WLog() << "Unable to register " << type.toString() << " objects factory: Duplicated key.";
						return false;
					}
				}
			private:
				static tObjectsFactories& getFactories() {
					static tObjectsFactories objectsFactories{};
					return objectsFactories;
				}
		};

		template<class tObject>
		class ConcreteObjectsFactory : public IConcreteObjectsFactory
		{
			public:
				static bool Register(const ObjectType& type) {
					return ObjectsFactory::Register(type, new ConcreteObjectsFactory<tObject>());
				};

				Object* MakeObject(const std::string& id) override {
					return new tObject(id);
				}
		};

	}
}

#endif
