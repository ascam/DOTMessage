#include "dom/rippers/ripper.hpp"

#include "dom/document.hpp"
#include "dom/object.hpp"
#include "dom/text.hpp"
#include "utils/macsalogger.hpp"
#include "dom/components/datasources/userinputdatasource.hpp"
#include "dom/rippers/bitmapgenerator.hpp"

using macsa::dot::DOTRipper;
using macsa::dot::Document;

using namespace macsa::utils;

std::string DOTRipper::GetVersion()  { return DOT_MESSAGE_LIB_VERSION;}
uint8_t DOTRipper::GetMajorVersion() { return DOT_MESSAGE_LIB_VERSION_MAJOR;}
uint8_t DOTRipper::GetMinorVersion() { return DOT_MESSAGE_LIB_VERSION_MINOR;}
uint8_t DOTRipper::GetPatchVersion() { return DOT_MESSAGE_LIB_VERSION_BUILD;}

DOTRipper::~DOTRipper()
{
	_generator.reset();
}

uint32_t DOTRipper::GetWidth()
{
	return  _generator->GetWidth();
}

uint32_t DOTRipper::GetHeight()
{
	return _generator->GetHeight();
}

void DOTRipper::setPrintHiddenItems(bool printHiddenItems)	{
	_generator->setPrintHiddenItems(printHiddenItems);
}

bool DOTRipper::getPrintHiddenItems() const	{
	return _generator->getPrintHiddenItems();
}

bool DOTRipper::GetRawData(bitmap& bitmap) const
{
	if (!_doc) {
		ELog() << "Invalid nisx document";
		return false;
	}

	_generator->GetRawData(bitmap);
	return true;
}

bool DOTRipper::GetDataMono(bitmap& bitmap, bool invertBytes)
{
	if (!_doc) {
		ELog() << "Invalid nisx document";
		return false;
	}

	{
		std::unique_lock<std::mutex>lck(_mutex);
		_generator->GetBitmapMono(bitmap, invertBytes);
	}

	return true;
}

bool DOTRipper::GetDoubleColDataMono(bitmap& bitmap1, bitmap& bitmap2,
									  uint32_t colOffset, bool invertBytes)
{
	if (!_doc) {
		ELog() << "Invalid nisx document";
		return false;
	}

	{
		std::unique_lock<std::mutex>lck(_mutex);
		_generator->GetDoubleColBitmapMono(bitmap1, bitmap2, colOffset, invertBytes);
	}

	return true;
}

void DOTRipper::SaveToBmpFile(const std::string &filepath)
{
	if (_generator) {
		_generator->SaveToBmpFile(filepath);
	}
	else {
		ELog() << "Unable to save bmp image. No generator provided";
	}
}

void DOTRipper::Update(Context* context)
{
	if (!_doc) {
		ELog() << "Invalid nisx document";
		return;
	}

	{
		ILog() << "Updating full pixmap";
		std::unique_lock<std::mutex>lck(_mutex);
		_generator->Update(_doc, context);
	}
}

void DOTRipper::UpdateVariableFields(Context* context)
{
	if (!_doc) {
		ELog() << "Invalid nisx document";
		return;
	}

	{
		DLog() << "Updating variable pixmap";
		std::unique_lock<std::mutex>lck(_mutex);
		_generator->UpdateVariableFields(_doc, context);
	}
}

macsa::dot::RefreshPolicy DOTRipper::GetUpdateFrequency() const
{
	if (_doc){
		// @jsubi, per tractar!
		//return _doc->GetUpdateRatio();
		return RefreshPolicy::kNone;
	}
	else {
		return RefreshPolicy::kNone;
	}
}

void DOTRipper::Clear()
{
	std::unique_lock<std::mutex>lck(_mutex);
	_doc = nullptr;
	if (_generator) {
		_generator->Clear();
	}
}

float DOTRipper::GetDocumentWidth() const
{
	float width = 0;
	if(_doc) {
		width = _doc->GetCanvasWidth();
	}
	return width;
}

float DOTRipper::GetDocumentHeight() const
{
	float height = 0;
	if(_doc) {
		height = _doc->GetCanvasHeight();
	}
	return height;
}

void DOTRipper::SetUserFieldsValues(const std::map<std::string, std::string>& ufValues)
{
	auto&& objects = _doc->GetObjects();
	for (auto& obj : objects) {
		if (obj->IsVariable()) {
			Text* text = dynamic_cast<Text*>(obj);
			if (text->GetDatasource()->GetType() == NDataSourceType::kUserInput) {
				UserInputDataSource* ui = dynamic_cast<UserInputDataSource*>(text->GetDatasource());
				if (ui != nullptr && ufValues.find(text->GetId()) != ufValues.end()) {
					ui->SetValue(ufValues.at(text->GetId()));
				}
			}
		}
	}
}

void DOTRipper::SetUserFieldsValue(const std::string& id, const std::string& value)
{
	auto obj = dynamic_cast<Text*>(_doc->GetObjectById(id));
	if (obj != nullptr && obj->IsVariable() && obj->GetDatasource()->GetType() == NDataSourceType::kUserInput) {
		auto ui = dynamic_cast<UserInputDataSource*>(obj->GetDatasource());
		if (ui != nullptr){
			ui->SetValue(value);
		}
	}
}

std::map<std::string, std::string> DOTRipper::GetUserFieldsValues() const
{
	std::map<std::string, std::string> uf;
	if (_doc != nullptr) {
		auto&& objects = _doc->GetObjects();
		if (objects.size() > 0ul) {
			for (auto& obj : objects) {
				if (obj->IsVariable()) {
					auto text = dynamic_cast<Text*>(obj);
					if (text->GetDatasource()->GetType() == NDataSourceType::kUserInput) {
						auto ui = dynamic_cast<UserInputDataSource*>(text->GetDatasource());
						uf.insert(std::make_pair(text->GetId(), ui->GetValue()));
					}
				}
			}
		}
	}
	return uf;
}

std::string DOTRipper::GetUserFieldsValue(const std::string& id) const
{
	std::string uf;
	auto obj = dynamic_cast<Text*>(_doc->GetObjectById(id));
	if (obj != nullptr && obj->IsVariable() && obj->GetDatasource()) {
		auto ui = dynamic_cast<UserInputDataSource*>(obj->GetDatasource());
		if (ui != nullptr) {
			uf = ui->GetValue();
		}
	}
	return uf;
}

void DOTRipper::SetVerticalResolution(uint32_t vres)
{
	if (_generator) {
		_generator->SetVerticalResolution(vres);
	}
	else {
		WLog() << "Invalid generator";
	}
}
uint32_t DOTRipper::GetVerticalResolution() const
{
	if (_generator) {
		return _generator->GetVerticalResolution();
	}
	else {
		WLog() << "Invalid generator";
	}
	return 0;
}

void DOTRipper::SetHorizontalResolution(uint32_t hres)
{
	if (_generator) {
		_generator->SetHorizontalResolution(hres);
	}
	else {
		ELog() << "Invalid generator";
	}
}

uint32_t DOTRipper::GetHorizontalResolution() const
{
	if (_generator) {
		return _generator->GetHorizontalResolution();
	}
	else {
		ELog() << "Invalid generator";
	}
	return 0;
}

void DOTRipper::AddFontsDirectory(const std::string &fullpath)
{
	if (_generator) {
		_generator->AddFontsDirectory(fullpath);
	}
}

void DOTRipper::AddFontFamily(const std::string &fullpath)
{
	if (_generator) {
		_generator->AddFontFamily(fullpath);
	}
}

void DOTRipper::SetBackgroundColorFromRGBA(const std::string &rgba)
{
	if (_generator) {
		_generator->SetBackgroundColorFromRGBA(rgba);
	}
}

void DOTRipper::SetBackgroundColorFromRGBA(uint32_t rgba)
{
	if (_generator) {
		_generator->SetBackgroundColorFromRGBA(rgba);
	}
}

int DOTRipper::GetRotation() const
{
	if (_doc) {
		return _doc->GetCanvasRotation();
	}

	return 0;
}

void DOTRipper::SetDocument(Document* document)
{
	_doc = document;
}
