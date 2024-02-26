#include "dom/dotmessage.hpp"
#include <sstream>

#ifdef _WINDOWS
#include "builders/nisx/objects/textparser.hpp"
#include "builders/nisx/objects/barcodeparser.hpp"
#include "builders/nisx/objects/diamondparser.hpp"
#include "builders/nisx/objects/ellipseparser.hpp"
#include "builders/nisx/objects/rectangleparser.hpp"
#include "builders/nisx/objects/lineparser.hpp"
#include "builders/nisx/objects/imageparser.hpp"
#include "builders/nisx/objects/datasources/compositeparser.hpp"
#include "builders/nisx/objects/datasources/counterparser.hpp"
#include "builders/nisx/objects/datasources/databaseparser.hpp"
#include "builders/nisx/objects/datasources/datetimeparser.hpp"
#include "builders/nisx/objects/datasources/userinputparser.hpp"
#include "dom/text.hpp"
#include "dom/barcode.hpp"
#include "dom/image.hpp"
#include "dom/primitives.hpp"
#include "dom/components/datasources/compositedatasource.hpp"
#include "dom/components/datasources/counterdatasource.hpp"
#include "dom/components/datasources/databasedatasource.hpp"
#include "dom/components/datasources/datetimedatasource.hpp"
#include "dom/components/datasources/userinputdatasource.hpp"
#include "dom/components/symbologies/symbology.hpp"

const bool macsa::dot::DOTMessage::RegisterFactories()
{
	static bool registered{};

	if (!registered) {
		registered = true;
		registered &= nisx::TextParser::GetRegistered();
		registered &= nisx::BarcodeParser::GetRegistered();
		registered &= nisx::DiamondParser::GetRegistered();
		registered &= nisx::EllipseParser::GetRegistered();
		registered &= nisx::RectangleParser::GetRegistered();
		registered &= nisx::LineParser::GetRegistered();
		registered &= nisx::ImageParser::GetRegistered();
		registered &= nisx::CompositeParser::GetRegistered();
		registered &= nisx::CounterParser::GetRegistered();
		registered &= nisx::DatabaseParser::GetRegistered();
		registered &= nisx::DateTimeParser::GetRegistered();
		registered &= nisx::UserInputParser::GetRegistered();

		registered &= CompositeDataSource::GetRegistered();
		registered &= CounterDataSource::GetRegistered();
		registered &= DatabaseDataSource::GetRegistered();
		registered &= DateTimeDataSource::GetRegistered();
		registered &= UserInputDataSource::GetRegistered();

		registered &= Image::GetRegistered();
		registered &= Text::GetRegistered();
		registered &= Barcode::GetRegistered();
		registered &= Line::GetRegistered();
		registered &= Rectangle::GetRegistered();
		registered &= Ellipse::GetRegistered();

		registered &= Code128::GetRegistered();
		registered &= Code39::GetRegistered();
		registered &= Pharmacode::GetRegistered();
		registered &= UpcA::GetRegistered();
		registered &= UpcE::GetRegistered();
		registered &= Interleaved2of5::GetRegistered();
		registered &= Itf14::GetRegistered();
		registered &= Ean13::GetRegistered();
		registered &= Ean13CCA::GetRegistered();
		registered &= Ean13CCB::GetRegistered();
		registered &= Ean8::GetRegistered();
		registered &= Ean8CCA::GetRegistered();
		registered &= Ean8CCB::GetRegistered();
		registered &= Ean128::GetRegistered();
		registered &= Ean128CCA::GetRegistered();
		registered &= Ean128CCB::GetRegistered();
		registered &= Ean128CCC::GetRegistered();
		registered &= GS1128::GetRegistered();
		registered &= GS1128CCA::GetRegistered();
		registered &= GS1128CCB::GetRegistered();
		registered &= GS1128CCC::GetRegistered();
		registered &= GS1DataBar14::GetRegistered();
		registered &= GS1DataBarExpanded::GetRegistered();
		registered &= GS1DataBarExpandedStacked::GetRegistered();
		registered &= GS1DataBarStacked::GetRegistered();
		registered &= Rss14StackedOmnidirectional::GetRegistered();
		registered &= DotCode::GetRegistered();
		registered &= DataMatrix::GetRegistered();
		registered &= GS1DataMatrix::GetRegistered();
		registered &= Pdf417::GetRegistered();
		registered &= CompactPdf417::GetRegistered();
		registered &= MicroPdf417::GetRegistered();
		registered &= QRCode::GetRegistered();
		registered &= GS1QRCode::GetRegistered();
		registered &= MicroQRCode::GetRegistered();
	}

	return registered;
}
#endif

std::string macsa::dot::DOTMessage::GetLibraryVersion()
{
	std::stringstream version;
	version << DOT_MESSAGE_LIB_VERSION_MAJOR << "."
			<< DOT_MESSAGE_LIB_VERSION_MINOR << "."
			<< DOT_MESSAGE_LIB_VERSION_BUILD;
	return version.str();
}

std::string macsa::dot::DOTMessage::GetLibraryName()
{
	return DOT_MESSAGE_LIB_NAME;
}
