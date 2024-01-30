#ifndef DOT_BITMAP_GENERATOR_HPP
#define DOT_BITMAP_GENERATOR_HPP

#include <memory>
#include <vector>
#include <array>
#include <cstdint>

#include "dom/document.hpp"
#include "dom/rippers/context.hpp"

using bitmap = std::vector<uint8_t>;

namespace macsa
{
	namespace dot
	{
		class BitmapGenerator
		{
			public:
				BitmapGenerator() :
					_hres(300),
					_vres(300),
					_rotation(),
					_hflip(),
					_vflip(),
					_printHiddenItems()
				{}
				virtual ~BitmapGenerator() = default;

				virtual void* NativeHandler() const =0;
				virtual uint32_t GetWidth() const = 0;
				virtual uint32_t GetHeight() const = 0;
				virtual int GetRawData(bitmap& buff) const = 0;

				/**
				 * @brief GetBitmapMono Get image in bitmap form (1 bit per pixel) // TODO(iserra): Allow variants
				 * Invert Byte changes the swaps the bytes internally like endianess. // TODO(iserra): review
				 * @param buff
				 * @param invertByte
				 */
				virtual void GetBitmapMono(bitmap& buff, bool invertByte) const = 0;
				virtual void GetDoubleColBitmapMono(bitmap& buff1, bitmap& buff2,
													uint32_t colOffset, bool invertByte) const = 0;

				/**
				 * @brief SaveToBmpFile Stores the current image as a bmp file in the given filename (relative/full path)
				 */
				virtual void SaveToBmpFile(const std::string& filename) = 0;

				virtual void Update(dot::Document* doc, Context* context, bool editorMode = false) = 0;
				virtual void UpdateVariableFields(dot::Document* doc, Context* context) = 0;
				virtual void Clear() = 0;

				virtual void AddFontsDirectory(const std::string& fullpath) = 0;
				virtual void AddFontFamily(const std::string& fullpath) = 0;

				virtual void SetBackgroundColorFromRGBA(const std::string& rgba) = 0;
				virtual void SetBackgroundColorFromRGBA(uint32_t rgba) = 0;

				void SetVerticalResolution(uint32_t vres) {_vres = vres; }
				uint32_t GetVerticalResolution() const { return _vres; }

				void SetHorizontalResolution(uint32_t hres) {_hres = hres; }
				uint32_t GetHorizontalResolution() const { return _hres; }

				void SetFlipHorizontal(bool flip) {_hflip = flip;}
				bool GetFlipHorizontal() const {return _hflip;}

				void SetFlipVertical(bool flip) {_vflip = flip;}
				bool GetFlipVertical() const {return _vflip;}

				uint16_t GetRotation() const {return _rotation;}
				void SetRotation(uint16_t rotation) {_rotation = rotation;}

				/**
				 * @brief setPrintHiddenItems allow hidden items to be printed
				 * @param printHiddenItems true to print hidden items.
				 */
				void setPrintHiddenItems(bool printHiddenItems)	{
					_printHiddenItems = printHiddenItems;
				}

				/**
				 * @brief GetPrintHiddenItems return configured value to print hidden items
				 * @return true if hidden items are printed.
				 */
				bool getPrintHiddenItems() const	{
					return _printHiddenItems;
				}

				virtual Point getCanvasOffset() const = 0;

			protected:
				uint32_t _hres;
				uint32_t _vres;
				uint16_t _rotation;
				bool _hflip;
				bool _vflip;
				bool _printHiddenItems;
		};
	}
}
#endif
