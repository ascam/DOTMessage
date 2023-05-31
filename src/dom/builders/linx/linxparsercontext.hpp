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

				///
				/// \brief GetDocument
				/// \return
				///
				dot::Document& GetDocument() const;
				///
				/// \brief SetUnits of the document, normally mm or dots
				/// \param units
				///
				void SetUnits(const std::string& units);
				///
				/// \brief SetUnitsRatio, dots x mm
				/// \param ratio
				///
				void SetUnitsRatio(double ratio);
				///
				/// \brief Converts units to mm
				/// \param units
				/// \return
				///
				double ConvertUnits(double units);
				///
				/// \brief ConvertGeometry to mm and rotates if it's need it
				/// \param geometry
				/// \return
				///
				dot::Geometry ConvertGeometry(dot::Geometry geometry);
				///
				/// \brief GetOffsetDateMap
				/// \return
				///
				OffsetDateMap& GetOffsetDateMap();
				///
				/// \brief AddOffsetDate, adds an offsetDate to offsetDateMap
				/// \param name
				/// \param offset
				///
				void AddOffsetDate(std::string& name, OffsetDate& offset);
				///
				/// \brief GetColorsPalette
				/// \return
				///
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
