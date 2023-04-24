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
	//"messages/linx/linxformatted.ciff",
	//"messages/linx/textofijo.ciff",
	//"messages/linx/EFAPEL.ciff",
	"messages/linx/frankfurt.ciff",
	"messages/linx/frankfurtUTF16.ciff"
	//"messages/linx/NORTE_EUROCAO.ciff",
	//"messages/linx/Pan_molde.ciff",
	//"messages/linx/Pan_molde_4_dias.ciff",
	//"messages/linx/tt3fira.ciff",
	//"messages/linx/tt5nou.ciff",
	//"messages/linx/tt10_HSPCK2015.ciff",
	//"messages/linx/VARIABLE.ciff",
	//"messages/linx/VARIABLE2.ciff",
	//"messages/linx/Yogur_35_dias.ciff",
	//"messages/linx/msj_01_tto_formatted.ciff",
	//"messages/linx/msj_jovi.ciff"
};

struct Benchmark {
	double parseTime;
	double writeTime;
	Benchmark(double parse = 0, double write = 0) :
		parseTime{parse},
		writeTime{write}
	{}
};

//static bool isUTF16LE(const std::string& filepath) {
//	std::wifstream file(filepath, std::ios::in | std::ios::binary);
//	if (!file) {
//		ELog() << "Error al abrir el archivo " << filepath << std::endl;
//		return false;
//	}

//	file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));

//	wchar_t bom;
//	file.read(&bom, 1);
//	if (file.fail()) {
//		ELog() << "Error al leer los primeros 2 bytes del archivo " << filepath;
//		return false;
//	}

//	return bom == 0xFEFF;
//}

static bool isUTF16LE(const char* buffer, size_t size) {
	/*
	if (size < 2) {
		return false;
	}

	const uint16_t bom = *((const uint16_t*)buffer);
	return (bom == 0xFEFF);
	*/
	if (size < 2) {
		return false;
	}
	const unsigned char* bytes = reinterpret_cast<const unsigned char*>(buffer);
	if (bytes[0] == 0x00 && bytes[1] == 0x00) {
		// UTF-16 sin BOM
		return true;
	}
	if (bytes[0] == 0xFF && bytes[1] == 0xFE) {
		// UTF-16 LE con BOM
		return true;
	}
	return false;
}

//bool isUTF16LE(const std::string& filepath) {
//	std::wifstream file(filepath);
//	if (!file) {
//		ELog() << "is utf 16 - Error al abrir el archivo " << filepath << std::endl;
//		return false;
//	}
//	file.imbue(std::locale(file.getloc(),
//		new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
//	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
//	std::string contents = converter.to_bytes(std::wstring(
//		std::istreambuf_iterator<wchar_t>(file),
//		std::istreambuf_iterator<wchar_t>()));
//	return contents.substr(0, 2) == "\xff\xfe";
//}

std::string convertir_utf16_a_utf8(const std::wstring& wstr) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(wstr);
}

//std::string convertir_utf16_a_utf8(const std::string& ruta_entrada) {
//	// Abrir el archivo en modo lectura en formato binario
//	std::wifstream archivo(ruta_entrada, std::ios::binary);
//	if (!archivo) {
//		ELog() <<  "convertir utf16 - Error al abrir el archivo " << ruta_entrada;
//		return "";
//	}
//
//	// Configurar la codificación de caracteres de entrada
//	archivo.imbue(std::locale(std::locale(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
//
//	// Leer todo el archivo en un string de wstring
//	std::wstring wstr((std::istreambuf_iterator<wchar_t>(archivo)), std::istreambuf_iterator<wchar_t>());
//
//	// Convertir el string de wstring a un string de utf8
//	std::wstring_convert<std::codecvt_utf8<wchar_t>> convertidor;
//	return convertidor.to_bytes(wstr);
//}

int main(int argc, char *argv[])
{
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

		std::string data;
		if (isUTF16LE(file.begin(), file.size())){
			std::wstring utf16Buffer = (wchar_t*)file.begin();
			data = convertir_utf16_a_utf8(utf16Buffer);
		}
		else{
			data = file.begin();
		}
//		auto file = fs.open(filepath);

		std::cout << std::endl;
		MLog() << "Parsing " << filepath << " file";
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
			if (!builder->BuildFromData(data.c_str(), data.size(), doc)) {
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
