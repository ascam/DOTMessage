#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>
#include <cmath>
#include <codecvt>
#include <locale>
#include <vector>

#include "cmrc/cmrc.hpp" //Compiled resources
#include "dom/builders/nisxparser.hpp"
#include "dom/builders/linxparser.hpp"
#include "dom/writers/nisxwriter.hpp"
//// DOM Objects
//#include "dom/object.hpp"
//#include "dom/text.hpp"
//#include "dom/barcode.hpp"
//#include "dom/image.hpp"
//#include "dom/primitives.hpp"
//// Data sources
//#include "dom/components/datasources/counterdatasource.hpp"
//#include "dom/components/datasources/compositedatasource.hpp"
//#include "dom/components/datasources/datetimedatasource.hpp"
//#include "dom/components/datasources/databasedatasource.hpp"
//#include "dom/components/datasources/userinputdatasource.hpp"
// Utils
#include "utils/macsalogger.hpp"
#include "utils/chronometer.hpp"


CMRC_DECLARE(dot);

#define TEST_FORMAT "LINX"

using namespace macsa::dot;
using macsa::utils::MacsaLogger;
using macsa::utils::Chronometer;

//constexpr const int kCurrentMessage = 1;
const std::vector<std::string> kNisxTestFiles {
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

const std::vector<std::string> kLinxTestFiles {
	"messages/linx/linxformatted.ciff",
	"messages/linx/textofijo.ciff",
	"messages/linx/EFAPEL.ciff",
	"messages/linx/frankfurt.ciff",
	"messages/linx/utf16/frankfurt.ciff",
	"messages/linx/NORTE_EUROCAO.ciff",
	"messages/linx/Pan_molde.ciff",
	"messages/linx/Pan_molde_4_dias.ciff",
	"messages/linx/tt3fira.ciff",
	"messages/linx/tt5nou.ciff",
	"messages/linx/tt10_HSPCK2015.ciff",
	"messages/linx/VARIABLE.ciff",
	"messages/linx/VARIABLE2.ciff",
	"messages/linx/Yogur_35_dias.ciff",
	"messages/linx/msj_01_tto_formatted.ciff",
	"messages/linx/msj_jovi.ciff",
	"messages/linx/Full_barcodes.ciff",
	"messages/linx/pedro.ciff",
	"messages/linx/barcodes_full.ciff",
	"messages/linx/datas_full.ciff"
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
	std::setlocale(LC_ALL, "en_US.UTF-8");
	macsa::utils::ThreadsMap::instance().AddThread(std::this_thread::get_id(), "Main");
	MLog() << "Macsa Dot Message tester v" << DOM_TESTER_VERSION;
	MacsaLogger::SetCurrentLevel(macsa::utils::NLogLevel::kInfo);

	Document doc;
	std::unique_ptr<IDocumentBuilder> builder{};
	const std::vector<std::string>* files{};
	if (strcmp(TEST_FORMAT,"LINX") == 0) {
		builder = std::unique_ptr<IDocumentBuilder>(new LinxParser());
		files = &kLinxTestFiles;
	}
	else {
		builder = std::unique_ptr<IDocumentBuilder>(new NisxParser());
		files = &kNisxTestFiles;
	}

	std::map<std::string,Benchmark> times;
	unsigned long maxLength{};
	auto fs = cmrc::dot::get_filesystem();

	for (const auto& filepath : *files) {
		auto file = fs.open(filepath);

		ILog() << "Parsing " << filepath << " file";
		size_t slash = filepath.find_last_of("/");
		std::string result = "./results/";
		std::string filename {(slash != std::string::npos) ? filepath.substr(slash + 1): filepath};
		size_t dot = filename.find_last_of(".");
		filename = {(dot != std::string::npos) ? filename.substr(0, dot): filename};
		filename.append(".nisx");
		result.append(filename);

		maxLength = std::max(maxLength, filename.size());
		{
			Chronometer chrono;
			if (!builder->BuildFromData(file.begin(), file.size(), doc)) {
				ELog() << "Parser return failure when parsing message file";
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
