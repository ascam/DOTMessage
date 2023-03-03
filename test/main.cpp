#include <iostream>
#include <iomanip>
#include <memory>
#include <cmath>

#include "cmrc/cmrc.hpp" //Compiled resources
#include "dom/builders/nisxparser.hpp"
#include "dom/visitors/nisx/nisxwriter.hpp"
// DOM Objects
#include "dom/object.hpp"
#include "dom/text.hpp"
#include "dom/barcode.hpp"
#include "dom/image.hpp"
#include "dom/primitives.hpp"
// Data sources
#include "dom/datasources/counterdatasource.hpp"
#include "dom/datasources/compositedatasource.hpp"
#include "dom/datasources/datetimedatasource.hpp"
#include "dom/datasources/databasedatasource.hpp"
#include "dom/datasources/userinputdatasource.hpp"
// Utils
#include "utils/macsalogger.hpp"
#include "utils/chronometer.hpp"

CMRC_DECLARE(dot);

using namespace macsa::dot;
using macsa::utils::MacsaLogger;
using macsa::utils::Chronometer;

//constexpr const int kCurrentMessage = 1;
const std::vector<std::string>kTestFiles {
	"messages/CQ.nisx",
	"messages/MENSAJE3.NISX",
	"messages/MENSAJE5.NISX",
	"messages/TEST_BARCODES.nisx",
	"messages/TEST_III.nisx",
	"messages/TEST_II.nisx",
	"messages/TEST_I.nisx",
	"messages/TEST_IV.nisx",
	"messages/TEST.nisx",
	"messages/TEST_VI.nisx",
	"messages/TEST_V.nisx",
	"messages/testParserNisx.nisx",
	"messages/GALLO.nisx"
};


struct Benchmark {
	double parseTime;
	double writeTime;
	Benchmark(double parse = 0, double write = 0) :
		parseTime{parse},
		writeTime{write}
	{}
};

int main(int argc, char *argv[])
{
	macsa::utils::ThreadsMap::instance().AddThread(std::this_thread::get_id(), "Main");
	MLog() << "Macsa Dot Message tester v" << DOM_TESTER_VERSION;
	MacsaLogger::SetCurrentLevel(macsa::utils::NLogLevel::kInfo);

	Document doc;
	NisxParser parser;

	std::map<std::string,Benchmark> times;
	unsigned long maxLength{};
	auto fs = cmrc::dot::get_filesystem();

	for (const auto& filepath : kTestFiles) {
		auto file = fs.open(filepath);
		std::cout << std::endl;
		MLog() << "Parsin " << filepath << " file";
		size_t slash = filepath.find_last_of("/");
		std::string result = "./results/";
		std::string filename {(slash != std::string::npos) ? filepath.substr(slash + 1): filepath};
		result.append(filename);
		maxLength = std::max(maxLength, filename.size());
		{
			Chronometer chrono;
			if (!parser.BuildFromData(file.begin(), file.size(), doc)) {
				ELog() << "Parser return failure when parsing nisx file";
			}
			else {
				times.insert({filename, {chrono.get() / 1000, 0}});
				macsa::dot::NisxWriter writer;
				chrono.reset();
				writer.Write(result, doc);
				times[filename].writeTime = chrono.get() / 1000;
			}
		}
	}

	std::stringstream header;
	header << std::setw(maxLength) << std::setfill(' ') << "Files" << " | " << "Parse time " << " | " << "Write time ";
	auto header_str = header.str();
	std::cout << std::endl << header_str << std::endl;
	std::cout << std::setw(maxLength) << std::setfill('-') << "-" << "-|-------------|-------------" << std::endl;
	for (const auto& samples : times ) {
		std::cout << std::setw(maxLength) << std::setfill(' ') << samples.first << " | "
				  << std::setw(8) << std::setfill(' ') << samples.second.parseTime << " ms" << " | "
				  << std::setw(8) << std::setfill(' ') << samples.second.writeTime << " ms" << std::endl;
	}

	return 0;
}
