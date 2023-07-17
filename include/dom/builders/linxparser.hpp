#ifndef MACSA_LINX_PARSER_HPP
#define MACSA_LINX_PARSER_HPP

#include "dom/idocumentbuilder.hpp"

namespace macsa {
	namespace dot {
		class LinxParser : public IDocumentBuilder
		{
			public:
				LinxParser();
				virtual ~LinxParser();

				static std::string GetSupportedLinxVersion();

				bool BuildFromFile(const std::string& filepath, Document& document) override;
				bool BuildFromData(const char* data, uint length, Document& document) override;

			private:
				bool buildFromData(const char* data, uint length, Document& document);
		};
	}
}

#endif
