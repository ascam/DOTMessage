#ifndef DOT_MESSAGE_IMAGE_OBJECT_HPP
#define DOT_MESSAGE_IMAGE_OBJECT_HPP

#include <string>
#include "alignment.hpp"
#include "object.hpp"

namespace macsa {
	namespace dot {

		enum class NImageBoxAdjustment {
			kNormal,
			kFitToBox,
			kZoom
		};

		static constexpr const char* kImageFitToBox  = "FitToBox";
		static constexpr const char* kImageNormal = "Normal";
		static constexpr const char* kImageZoom = "Zoom";

		class ImageBoxAdjustment final : public utils::SmartEnum<NImageBoxAdjustment>
		{
			public:
				ImageBoxAdjustment (const NImageBoxAdjustment& adjustment = NImageBoxAdjustment::kFitToBox) :
					utils::SmartEnum<NImageBoxAdjustment>(adjustment)
				{}
				ImageBoxAdjustment (const std::string& adjustment) :
					utils::SmartEnum<NImageBoxAdjustment>(NImageBoxAdjustment::kFitToBox)
				{
					fromString(adjustment);
				}

				const ImageBoxAdjustment& operator = (const std::string& adjustment) {
					fromString(adjustment);
					return *this;
				}

				const ImageBoxAdjustment& operator = (NImageBoxAdjustment adjustment) {
					_val = adjustment;
					return *this;
				}

			private:
				const std::vector<std::pair<NImageBoxAdjustment,std::string>>& getData() const override{
					static const std::vector<std::pair<NImageBoxAdjustment,std::string>> kImageBoxAdjustmentData {
						{NImageBoxAdjustment::kNormal,   kImageNormal},
						{NImageBoxAdjustment::kFitToBox, kImageFitToBox},
						{NImageBoxAdjustment::kZoom,     kImageZoom}
					};
					return kImageBoxAdjustmentData;
				}
		};

		class Image : public Object
		{
			public:
				using ByteArray = std::vector<uint8_t>;

				Image(const std::string& id, const Geometry& geometry);
				Image(const Image&) = delete;
				virtual ~Image();

				/**
				 * @brief GetRefreshPolicy. Overrided method of
				 * Object::GetRefreshPolicy
				 * @return The refresh policy of the object.
				 */
				RefreshPolicy GetRefreshPolicy() const override {
					return RefreshPolicy::kNone;
				}
				/**
				 * @brief IsVariable. Overrided method of Object::IsVariable
				 * @return true if the object can change the inner value,
				 * false if the object is static.
				 */
				bool IsVariable() const override {
					return false;
				}

				/**
				 * @brief GetData. Getter method for image file data.
				 * @return The content of the image in a byte array
				 */
				const ByteArray& GetData() const {
					return _data;
				}
				/**
				 * @brief GetData. Setter method for image file data.
				 * @param data: The content of the image in a byte array
				 */
				void SetData(const ByteArray& data);

				/**
				 * @brief GetFilepath. Getter method for image filepath.
				 * @return The filepath of the current image
				 */
				const std::string& GetFilepath() const {
					return _filepath;
				}
				/**
				 * @brief SetFilepath. Setter method for image filepath.
				 * @param filepath: The filepath of the image to render
				 */
				void SetFilepath(const std::string& filepath);

				/**
				 * @brief GetBoxAdjustment. Getter method of the image fitting
				 * in the container box.
				 * @return The current image box fitting.
				 */
				const ImageBoxAdjustment& GetBoxAdjustment() const {
					return _boxAdjustment;
				}
				/**
				 * @brief SetBoxAdjustment. Setter method of the image fitting
				 * in the container box.
				 * @param adjustment: How the image must fit in the container box.
				 */
				void SetBoxAdjustment(const ImageBoxAdjustment& adjustment);
				/**
				 * @brief GetVerticalAlignment. Getter method for image vertical
				 * alignment.
				 * @return How the image is aligned verticaly.
				 */
				const VerticalAlignment& GetVerticalAlignment() const {
					return _verticalAlignment;
				}
				/**
				 * @brief SetVerticalAlignment. Setter method for image vertical
				 * alignment.
				 * @param alignment: How the image is aligned verticaly.
				 * This parameter only has effects in a Normal box adjustment.
				 */
				void SetVerticalAlignment(const VerticalAlignment& alignment);
				/**
				 * @brief GetHorizontalAlignment. Getter method for image horizontal
				 * alignment.
				 * @return How the image is aligned horizontally.
				 */
				const HorizontalAlignment& GetHorizontalAlignment() const {
					return _horizontalAlignment;
				}
				/**
				 * @brief SetHorizontalAlignment. Setter method for image horizontal
				 * alignment.
				 * @param alignment: How the image is aligned horizontally.
				 * This parameter only has effects in a Normal box adjustment.
				 */
				void SetHorizontalAlignment(const HorizontalAlignment& alignment);

				/**
				 * @brief GetAlgorithm. Getter method for the image processing algorithm
				 * @return The name of the current image processing algorithm
				 */
				const std::string& GetAlgorithm() const {
					return _algorithm;
				}
				/**
				 * @brief SetAlgorithm. Setter method for the image processing algorithm
				 * @param algorithm: The name of the image processing algorithm to apply
				 */
				void SetAlgorithm(const std::string& algorithm);

				/**
				 * @brief GetTopThreshold. Getter method for the color's top threshold.
				 * @return The color's top threshold.
				 */
				uint32_t GetTopThreshold() const {
					return _topThreshold;
				}
				/**
				 * @brief SetTopThreshold. Setter method for the color's top threshold.
				 * @param threshold: The color's top threshold.
				 */
				void SetTopThreshold(uint32_t threshold);
				/**
				 * @brief GetDownThreshold. Getter method for the color's down threshold.
				 * @return The color's down threshold.
				 */
				uint32_t GetDownThreshold() const {
					return _downThreshold;
				}
				/**
				 * @brief SetDownThreshold Setter method for the color's down threshold.
				 * @param threshold: The color's down threshold.
				 */
				void SetDownThreshold(uint32_t threshold);

			public:
				Signal<std::string> PathChanged;
				Signal<> ImageDataChanged;
				Signal<> AdjustmentChanged;

			private:
				ByteArray _data;
				std::string _filepath;
				ImageBoxAdjustment _boxAdjustment;
				VerticalAlignment _verticalAlignment;
				HorizontalAlignment _horizontalAlignment;
				std::string _algorithm;
				uint32_t _topThreshold;
				uint32_t _downThreshold;
		};
	}
}

#endif
