#ifndef DOT_MESSAGE_RIPPER_HPP
#define DOT_MESSAGE_RIPPER_HPP

#include <memory>
#include <vector>
#include <cstdint>
#include <mutex>
#include <map>
#include <string>

#include "dom/document.hpp"
#include "dom/rippers/context.hpp"

using bitmap = std::vector<uint8_t>;

namespace macsa
{
	namespace dot
	{
		class BitmapGenerator;

		class DOTRipper
		{
			public:
				DOTRipper(const DOTRipper& ripper) = delete;
				DOTRipper(DOTRipper&& ripper) = delete;
				DOTRipper& operator=(const DOTRipper& ripper) = delete;
				DOTRipper& operator=(DOTRipper&& ripper) = delete;
				virtual ~DOTRipper();

				uint32_t GetWidth();
				uint32_t GetHeight();
				bool GetRawData(bitmap& bitmap) const;
				bool GetDataMono(bitmap& bitmap, bool invertBytes);
				bool GetDoubleColDataMono(bitmap& bitmap1, bitmap& bitmap2, uint32_t colOffset, bool invertBytes);
				void SaveToBmpFile(const std::string& filepath);

				void Update(Context* context, bool editorMode = false);
				void UpdateVariableFields(Context* context);
				void Clear();

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

				bool GetFlipHorizontal() const;
				void SetFlipHorizontal(bool flip);

				void SetFlipVertical(bool flip);
				bool GetFlipVertical() const;

				uint16_t GetRotation() const;
				void SetRotation(uint16_t rotation);

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


				dot::Document* GetDocument() {return _doc;}
				void SetDocument(dot::Document* document);

				/**
				 * @brief setPrintHiddenItems allow hidden items to be printed
				 * @param printHiddenItems true to print hidden items.
				 */
				void setPrintHiddenItems(bool printHiddenItems);

				/**
				 * @brief GetPrintHiddenItems return configured value to print hidden items
				 * @return true if hidden items are printed.
				 */
				bool getPrintHiddenItems() const;

				static std::string GetVersion();
				static uint8_t GetMajorVersion();
				static uint8_t GetMinorVersion();
				static uint8_t GetPatchVersion();

				Size getCanvasOffset();

			protected:
				std::mutex _mutex;
				std::unique_ptr<BitmapGenerator> _generator;
				Document* _doc;

				DOTRipper() = default;
		};
	}
}
#endif
