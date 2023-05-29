#ifndef MACSA_LINX_PARSER_CONTEXT_HPP
#define MACSA_LINX_PARSER_CONTEXT_HPP

#include "dom/document.hpp"
#include <string>
#include <map>

namespace macsa {
	namespace linx {

		static constexpr const char* kBlack = "Black";
		static constexpr const char* kWhite = "White";
		static constexpr const char* kTransparent = "Transparent";

		struct OffsetDate
		{
				int day;
				int month;
				int year;
				std::string prompt;

				OffsetDate() :
					day{},
					month{},
					year{},
					prompt{}
				{}
		};
		using OffsetDateMap = std::map<std::string, OffsetDate>;

		class LinxParserContext
		{
			public:
				LinxParserContext(dot::Document& doc);
				~LinxParserContext() = default;

				dot::Document& GetDocument() const;

				void SetUnits(const std::string& units);
				void SetUnitsRatio(double ratio);
				double ConvertUnits(double units);
				dot::Geometry CheckGeometry(dot::Geometry geometry);
				OffsetDateMap& GetOffsetDateMap();
				void AddOffsetDate(std::string& name, OffsetDate& offset);
				dot::ColorsPalette& GetColorsPalette();

			private:
				dot::Document& _doc;
				std::string _units;
				double _unitsRatio;
				OffsetDateMap _offsetDateMap;
				dot::ColorsPalette _colorsPalette;
		};
	}
}

#endif
