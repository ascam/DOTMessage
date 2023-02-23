#include "symbology.hpp"
#include "factories/barcodesymbologyfactory.hpp"

using namespace macsa::dot;

namespace  {
	static const bool Code128FactoryRegistered = ConcreteSymbologyFactory<Code128>::Register(NBarcodeSymbol::kCode128);
	static const bool Code39FactoryRegistered = ConcreteSymbologyFactory<Code39>::Register(NBarcodeSymbol::kCode39);
	static const bool PharmacodeFactoryRegistered = ConcreteSymbologyFactory<Pharmacode>::Register(NBarcodeSymbol::kPharmacode);
	static const bool UpcAFactoryRegistered = ConcreteSymbologyFactory<UpcA>::Register(NBarcodeSymbol::kUpcA);
	static const bool Interleaved2of5FactoryRegistered = ConcreteSymbologyFactory<Interleaved2of5>::Register(NBarcodeSymbol::kInterleaved2of5);
	static const bool Itf14FactoryRegistered = ConcreteSymbologyFactory<Itf14>::Register(NBarcodeSymbol::kItf14);
	static const bool Ean13FactoryRegistered = ConcreteSymbologyFactory<Ean13>::Register(NBarcodeSymbol::kEan13);
	static const bool Ean13CCAFactoryRegistered = ConcreteSymbologyFactory<Ean13CCA>::Register(NBarcodeSymbol::kEan13CCA);
	static const bool Ean13CCBFactoryRegistered = ConcreteSymbologyFactory<Ean13CCB>::Register(NBarcodeSymbol::kEan13CCB);
	static const bool Ean8FactoryRegistered = ConcreteSymbologyFactory<Ean8>::Register(NBarcodeSymbol::kEan8);
	static const bool Ean8CCAFactoryRegistered = ConcreteSymbologyFactory<Ean8CCA>::Register(NBarcodeSymbol::kEan8CCA);
	static const bool Ean8CCBFactoryRegistered = ConcreteSymbologyFactory<Ean8CCB>::Register(NBarcodeSymbol::kEan8CCB);
	static const bool Ean128FactoryRegistered = ConcreteSymbologyFactory<Ean128>::Register(NBarcodeSymbol::kEan128);
	static const bool Ean128CCAFactoryRegistered = ConcreteSymbologyFactory<Ean128CCA>::Register(NBarcodeSymbol::kEan128CCA);
	static const bool Ean128CCBFactoryRegistered = ConcreteSymbologyFactory<Ean128CCB>::Register(NBarcodeSymbol::kEan128CCB);
	static const bool Ean128CCCFactoryRegistered = ConcreteSymbologyFactory<Ean128CCC>::Register(NBarcodeSymbol::kEan128CCC);
	static const bool GS1128FactoryRegistered = ConcreteSymbologyFactory<GS1128>::Register(NBarcodeSymbol::kGS1128);
	static const bool GS1128CCAFactoryRegistered = ConcreteSymbologyFactory<GS1128CCA>::Register(NBarcodeSymbol::kGS1128CCA);
	static const bool GS1128CCBFactoryRegistered = ConcreteSymbologyFactory<GS1128CCB>::Register(NBarcodeSymbol::kGS1128CCB);
	static const bool GS1128CCCFactoryRegistered = ConcreteSymbologyFactory<GS1128CCC>::Register(NBarcodeSymbol::kGS1128CCC);
	static const bool GS1DataBar14FactoryRegistered = ConcreteSymbologyFactory<GS1DataBar14>::Register(NBarcodeSymbol::kGS1DataBar14);
	static const bool GS1DataBarExpandedFactoryRegistered = ConcreteSymbologyFactory<GS1DataBarExpanded>::Register(NBarcodeSymbol::kGS1DataBarExpanded);
	static const bool GS1DataBarExpandedStackedFactoryRegistered = ConcreteSymbologyFactory<GS1DataBarExpandedStacked>::Register(NBarcodeSymbol::kGS1DataBarExpandedStacked);
	static const bool GS1DataBarStackedFactoryRegistered = ConcreteSymbologyFactory<GS1DataBarStacked>::Register(NBarcodeSymbol::kGS1DataBarStacked);
	static const bool Rss14StackedOmnidirectionalFactoryRegistered = ConcreteSymbologyFactory<Rss14StackedOmnidirectional>::Register(NBarcodeSymbol::kRss14StackedOmnidirectional);
	static const bool DotCodeFactoryRegistered = ConcreteSymbologyFactory<DotCode>::Register(NBarcodeSymbol::kDotCode);
	static const bool DataMatrixFactoryRegistered = ConcreteSymbologyFactory<DataMatrix>::Register(NBarcodeSymbol::kDataMatrix);
	static const bool GS1DataMatrixFactoryRegistered = ConcreteSymbologyFactory<GS1DataMatrix>::Register(NBarcodeSymbol::kGS1DataMatrix);
	static const bool Pdf417FactoryRegistered = ConcreteSymbologyFactory<Pdf417>::Register(NBarcodeSymbol::kPdf417);
	static const bool CompactPdf417FactoryRegistered = ConcreteSymbologyFactory<CompactPdf417>::Register(NBarcodeSymbol::kCompactPdf417);
	static const bool MicroPdf417FactoryRegistered = ConcreteSymbologyFactory<MicroPdf417>::Register(NBarcodeSymbol::kMicroPdf417);
	static const bool QRCodeFactoryRegistered = ConcreteSymbologyFactory<QRCode>::Register(NBarcodeSymbol::kQRCode);
	static const bool GS1QRCodeFactoryRegistered = ConcreteSymbologyFactory<GS1QRCode>::Register(NBarcodeSymbol::kGS1QRCode);
	static const bool MicroQRCodeFactoryRegistered = ConcreteSymbologyFactory<MicroQRCode>::Register(NBarcodeSymbol::kMicroQRCode);
}

Symbology::Symbology(const BarcodeSymbol& symbol) :
	_symbology{symbol}
{}

OneDimensionBarcode::OneDimensionBarcode(const BarcodeSymbol& symbol) :
	Symbology(symbol),
	_ratio{1.0},
	_keepAspectRatio{true},
	_displayChecksum{true},
	_showHRT{false},
	_bearer{NBearerBarStyle::kNone}
{}

TwoDimensionsBarcode::TwoDimensionsBarcode(const BarcodeSymbol& symbol) :
	Symbology(symbol),
	_shavingEnabled{false},
	_shavingValue{0}
{}

TwoDimensionsGS1Barcode::TwoDimensionsGS1Barcode(const BarcodeSymbol& symbol) :
	TwoDimensionsBarcode(symbol),
	_separator{NGS1AISeparator::kFNC1}
{}
