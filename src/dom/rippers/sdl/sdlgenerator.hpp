#ifndef DOTMESSAGE_SDL_GENERATOR_HPP
#define DOTMESSAGE_SDL_GENERATOR_HPP

#include "bitmapgenerator.hpp"
#include "document.hpp"

namespace macsa {
	namespace dot {
		class SDLGenerator : public BitmapGenerator
		{
			public:
				SDLGenerator();
				virtual ~SDLGenerator() = default;

				virtual bitmap GetBitmap() const;
				virtual void Update(Document* doc);
				virtual void UpdateVariableFields(Document* doc);

		};
	}
}
#endif
