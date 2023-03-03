#ifndef DOT_MESSAGE_BRACODE_SYMBOLOGY_FACTORY_HPP
#define DOT_MESSAGE_BRACODE_SYMBOLOGY_FACTORY_HPP

#include <utility>
#include <unordered_map>
#include "dom/components/barcodesymbologies.hpp"
#include "utils/macsalogger.hpp"

namespace macsa {
	namespace dot {
		class Symbology;
		class IConcreteSymbologyFactory
		{
			public :
				virtual Symbology* MakeBarcode() = 0;
		};
		using tSymbologyFactories = std::unordered_map<NBarcodeSymbol, std::unique_ptr<IConcreteSymbologyFactory>>;

		class SymbologyFactory
		{
			public:
				static Symbology* Get(NBarcodeSymbol symbology)
				{
					const auto& symbologyFactories = getFactories();
					auto foundIt = symbologyFactories.find(symbology);
					if (foundIt != symbologyFactories.end()) {
						return foundIt->second->MakeBarcode();
					}
					else {
						BarcodeSymbol symbol(symbology);
						utils::ELog() << symbol.toString() << " Symbology factory not found.";
						return nullptr;
					}
				}

				static bool Register(NBarcodeSymbol symbol, IConcreteSymbologyFactory* concreteSymbologyFactory) {
					auto& SymbologyFactories = getFactories();
					if (SymbologyFactories.find(symbol) == SymbologyFactories.end()) {
#if defined(ARM) // Required by linaro toolchains
						auto result = SymbologyFactories.emplace(type.toString(), std::unique_ptr<IConcreteSymbologyFactory>(concreteSymbologyFactory));
#else
						auto result = SymbologyFactories.emplace(symbol, concreteSymbologyFactory);
#endif
						return result.second;
					}
					else {
						utils::WLog() << "Unable to register " << BarcodeSymbol(symbol).toString()
									  << " symbology factory: Duplicated key.";
						return false;
					}
				}
			private:
				static tSymbologyFactories& getFactories() {
					static tSymbologyFactories SymbologyFactories{};
					return SymbologyFactories;
				}
		};

		template<class tSymbology>
		class ConcreteSymbologyFactory : public IConcreteSymbologyFactory
		{
			public:
				static bool Register(const NBarcodeSymbol& symbol) {
					return SymbologyFactory::Register(symbol, new ConcreteSymbologyFactory<tSymbology>());
				};

				Symbology* MakeBarcode() {
					return new tSymbology();
				}
		};
	}
}

#endif
