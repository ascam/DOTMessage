#include "dom/dotmessage.hpp"
#include <sstream>

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
