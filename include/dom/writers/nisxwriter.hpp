#ifndef MACSA_NISX_WRITER_HPP
#define MACSA_NISX_WRITER_HPP

#include "dom/document.hpp"

namespace macsa {
	namespace dot {
		class NisxWriter
		{
			public:
				using ByteArray = std::vector<uint8_t>;

			public:
				NisxWriter() = default;
				virtual ~NisxWriter() = default;

				static std::string GetWriterNisxVersion();

				bool Write(const std::string& filepath, dot::Document& document);
				bool Write(ByteArray& data, dot::Document& document);
		};
	}
}

#endif
