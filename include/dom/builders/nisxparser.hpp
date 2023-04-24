#ifndef MACSA_NISX_PARSER_HPP
#define MACSA_NISX_PARSER_HPP

#include "../idocumentbuilder.hpp"

namespace macsa {
	namespace dot {

		class NisxParser : public IDocumentBuilder
		{
			public:
				NisxParser() = default;
				virtual ~NisxParser() = default;

				static std::string GetSupportedNisxVersion();

				bool BuildFromFile(const std::string& filepath, dot::Document& document) override;
				bool BuildFromData(const char* data, uint length, dot::Document& document) override;
		};
	}
}

#endif
