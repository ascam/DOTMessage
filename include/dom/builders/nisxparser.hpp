#ifndef MACSA_NISX_PARSER_HPP
#define MACSA_NISX_PARSER_HPP

#include "dom/documentparser.hpp"
namespace macsa {
	namespace dot {

		class NisxParser : public IDocumentParser
		{
			public:
				NisxParser() = default;
				virtual ~NisxParser() = default;

				static std::string GetSupportedNisxVersion();

				bool Parse(const std::string& filepath, dot::Document& document) override;
				bool Parse(const char* data, uint length, dot::Document& document) override;
		};
	}
}

#endif
