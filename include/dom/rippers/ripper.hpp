#ifndef NISX_RIPPER_HPP
#define NISX_RIPPER_HPP

#include <memory>
#include <vector>
#include <cstdint>
#include <mutex>
#include <map>
#include <string>

#include "document.hpp"
#include "bitmapgenerator.hpp"
#include "refreshpolicy.hpp"

using bitmap = std::vector<uint8_t>;

namespace macsa
{
	namespace dot
	{
		class DOTRipper
		{
			public:
				enum class Backend
				{
					kBackendInvalid = 0x00,
					kBackendQt      = 0x01,
					kBackendSdl     = 0x02
				};

				static std::string GetVersion();
				static uint8_t GetMajorVersion();
				static uint8_t GetMinorVersion();
				static uint8_t GetPatchVersion();

			public:
				DOTRipper(Backend backend = Backend::kBackendInvalid);

				DOTRipper(const DOTRipper& ripper) = delete;
				DOTRipper(DOTRipper&& ripper) = delete;
				DOTRipper& operator=(const DOTRipper& ripper) = delete;
				DOTRipper& operator=(DOTRipper&& ripper) = delete;
				~DOTRipper();

				void SetCurrentBackend(const Backend &currentBackend);

				void* Draw();
				void* NativeHandler() {return _generator->NativeHandler();}
				uint32_t GetWidth() {return  _generator->GetWidth();}
				uint32_t GetHeight() {return _generator->GetHeight();}
				bool GetRawData(bitmap& bitmap) const;
				bool GetDataMono(bitmap& bitmap, bool invertBytes);
				bool GetDoubleColDataMono(bitmap& bitmap1, bitmap& bitmap2,
										  uint32_t colOffset, bool invertBytes);
				void SaveToBmpFile(const std::string& filepath);

				void Update();
				void UpdateVariableFields();

				RefreshPolicy GetUpdateFrequency() const;

				void Clear();

				/**
				 * @brief GetCurrentFile Gets the current parsed document path
				 */
				const std::string& GetCurrentFile() const {return _currentDoc;}

				float GetDocumentWidth() const;
				float GetDocumentHeight() const;

				void SetUserFieldsValues(const std::map<std::string, std::string>& ufValues);
				void SetUserFieldsValue(const std::string& id, const std::string& value);
				std::map<std::string, std::string> GetUserFieldsValues() const;
				std::string GetUserFieldsValue(const std::string& id) const;

				void SetVerticalResolution(uint32_t vres);
				uint32_t GetVerticalResolution() const;
				void SetHorizontalResolution(uint32_t hres);
				uint32_t GetHorizontalResolution() const;

				void AddFontsDirectory(const std::string& fullpath);
				void AddFontFamily(const std::string& fullpath);

				/**
				 * @brief SetBackgroundColorFromRGBA. Set the label background color
				 * to the specified rgba color.
				 * @param rgba: Color to set the background, this argument can be
				 * passed as a string "#RRGGBBAA" in hexa or as an unsigned 32 bits
				 * integer.
				 */
				void SetBackgroundColorFromRGBA(const std::string& rgba);
				void SetBackgroundColorFromRGBA(uint32_t rgba);

				/**
				 * @brief SetRotated Rotated property (true by default) build the bitmap rotated 90º CW
				 */
				void SetRotated(bool rotated);
				bool GetRotated() const;

				dot::Document* GetDocument() {return _doc.get();}
				void SetDocument(dot::Document* document);

				/**
				 * @brief setPrintHiddenItems allow hidden items to be printed
				 * @param printHiddenItems true to print hidden items.
				 */
				void setPrintHiddenItems(bool printHiddenItems)	{
					_generator->setPrintHiddenItems(printHiddenItems);
				}

				/**
				 * @brief GetPrintHiddenItems return configured value to print hidden items
				 * @return true if hidden items are printed.
				 */
				bool getPrintHiddenItems() const	{
					return _generator->getPrintHiddenItems();
				}

			private:
				std::mutex _mutex;
				std::unique_ptr<BitmapGenerator> _generator;
				std::unique_ptr<Document> _doc;
				std::string _currentDoc;
				Backend _currentBackend;

				std::string getFilename(const std::string& filepath) const;
		};
	}
}
#endif
