#include "symbology.hpp"
#include "dom/factories/barcodesymbologyfactory.hpp"

using namespace macsa::dot;

bool Code128::_registered = ConcreteSymbologyFactory<Code128>::Register(NBarcodeSymbol::kCode128);
bool Code39::_registered = ConcreteSymbologyFactory<Code39>::Register(NBarcodeSymbol::kCode39);
bool Pharmacode::_registered = ConcreteSymbologyFactory<Pharmacode>::Register(NBarcodeSymbol::kPharmacode);
bool UpcA::_registered = ConcreteSymbologyFactory<UpcA>::Register(NBarcodeSymbol::kUpcA);
bool Interleaved2of5::_registered = ConcreteSymbologyFactory<Interleaved2of5>::Register(NBarcodeSymbol::kInterleaved2of5);
bool Itf14::_registered = ConcreteSymbologyFactory<Itf14>::Register(NBarcodeSymbol::kItf14);
bool Ean13::_registered = ConcreteSymbologyFactory<Ean13>::Register(NBarcodeSymbol::kEan13);
bool Ean13CCA::_registered = ConcreteSymbologyFactory<Ean13CCA>::Register(NBarcodeSymbol::kEan13CCA);
bool Ean13CCB::_registered = ConcreteSymbologyFactory<Ean13CCB>::Register(NBarcodeSymbol::kEan13CCB);
bool Ean8::_registered = ConcreteSymbologyFactory<Ean8>::Register(NBarcodeSymbol::kEan8);
bool Ean8CCA::_registered = ConcreteSymbologyFactory<Ean8CCA>::Register(NBarcodeSymbol::kEan8CCA);
bool Ean8CCB::_registered = ConcreteSymbologyFactory<Ean8CCB>::Register(NBarcodeSymbol::kEan8CCB);
bool Ean128::_registered = ConcreteSymbologyFactory<Ean128>::Register(NBarcodeSymbol::kEan128);
bool Ean128CCA::_registered = ConcreteSymbologyFactory<Ean128CCA>::Register(NBarcodeSymbol::kEan128CCA);
bool Ean128CCB::_registered = ConcreteSymbologyFactory<Ean128CCB>::Register(NBarcodeSymbol::kEan128CCB);
bool Ean128CCC::_registered = ConcreteSymbologyFactory<Ean128CCC>::Register(NBarcodeSymbol::kEan128CCC);
bool GS1128::_registered = ConcreteSymbologyFactory<GS1128>::Register(NBarcodeSymbol::kGS1128);
bool GS1128CCA::_registered = ConcreteSymbologyFactory<GS1128CCA>::Register(NBarcodeSymbol::kGS1128CCA);
bool GS1128CCB::_registered = ConcreteSymbologyFactory<GS1128CCB>::Register(NBarcodeSymbol::kGS1128CCB);
bool GS1128CCC::_registered = ConcreteSymbologyFactory<GS1128CCC>::Register(NBarcodeSymbol::kGS1128CCC);
bool GS1DataBar14::_registered = ConcreteSymbologyFactory<GS1DataBar14>::Register(NBarcodeSymbol::kGS1DataBar14);
bool GS1DataBarExpanded::_registered = ConcreteSymbologyFactory<GS1DataBarExpanded>::Register(NBarcodeSymbol::kGS1DataBarExpanded);
bool GS1DataBarExpandedStacked::_registered = ConcreteSymbologyFactory<GS1DataBarExpandedStacked>::Register(NBarcodeSymbol::kGS1DataBarExpandedStacked);
bool GS1DataBarStacked::_registered = ConcreteSymbologyFactory<GS1DataBarStacked>::Register(NBarcodeSymbol::kGS1DataBarStacked);
bool Rss14StackedOmnidirectional::_registered = ConcreteSymbologyFactory<Rss14StackedOmnidirectional>::Register(NBarcodeSymbol::kRss14StackedOmnidirectional);
bool DotCode::_registered = ConcreteSymbologyFactory<DotCode>::Register(NBarcodeSymbol::kDotCode);
bool DataMatrix::_registered = ConcreteSymbologyFactory<DataMatrix>::Register(NBarcodeSymbol::kDataMatrix);
bool GS1DataMatrix::_registered = ConcreteSymbologyFactory<GS1DataMatrix>::Register(NBarcodeSymbol::kGS1DataMatrix);
bool Pdf417::_registered = ConcreteSymbologyFactory<Pdf417>::Register(NBarcodeSymbol::kPdf417);
bool CompactPdf417::_registered = ConcreteSymbologyFactory<CompactPdf417>::Register(NBarcodeSymbol::kCompactPdf417);
bool MicroPdf417::_registered = ConcreteSymbologyFactory<MicroPdf417>::Register(NBarcodeSymbol::kMicroPdf417);
bool QRCode::_registered = ConcreteSymbologyFactory<QRCode>::Register(NBarcodeSymbol::kQRCode);
bool GS1QRCode::_registered = ConcreteSymbologyFactory<GS1QRCode>::Register(NBarcodeSymbol::kGS1QRCode);
bool MicroQRCode::_registered = ConcreteSymbologyFactory<MicroQRCode>::Register(NBarcodeSymbol::kMicroQRCode);

static constexpr double kDefaultRatio = 2.0;

Symbology::Symbology(const BarcodeSymbol& symbol) :
	_symbology{symbol}
{}

OneDimensionBarcode::OneDimensionBarcode(const BarcodeSymbol& symbol) :
	Symbology(symbol),
	_ratio{kDefaultRatio},
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
