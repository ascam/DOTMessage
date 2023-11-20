#ifndef DOT_MESSAGE_DOCUMENT_BUILDER_HPP
#define DOT_MESSAGE_DOCUMENT_BUILDER_HPP

#include <cstdint>
#include "document.hpp"

namespace macsa
{
	namespace dot
	{
		class IDocumentBuilder
		{
			public:
				virtual ~IDocumentBuilder() = default;

				virtual bool BuildFromFile(const std::string& filepath, Document& document) = 0;
				virtual bool BuildFromData(const char* data, uint32_t length, Document& document) = 0;
		};
	}
}

#endif
