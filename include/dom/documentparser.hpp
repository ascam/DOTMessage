#ifndef DOT_MESSAGE_DOCUMENT_PARSER_HPP
#define DOT_MESSAGE_DOCUMENT_PARSER_HPP

#include <cstdint>
#include "document.hpp"

namespace macsa
{
	namespace dot
	{
		class IDocumentParser
		{
			public:
				virtual ~IDocumentParser() = default;

				virtual bool Parse(const std::string& filepath, Document& document) = 0;
				virtual bool Parse(const char* data, uint length, Document& document) = 0;
		};
	}
}

#endif
