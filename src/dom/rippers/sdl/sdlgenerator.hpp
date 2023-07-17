#ifndef DOTMESSAGE_SDL_GENERATOR_HPP
#define DOTMESSAGE_SDL_GENERATOR_HPP

#include "dom/document.hpp"
#include "dom/rippers/context.hpp"
#include "dom/rippers/bitmapgenerator.hpp"

namespace macsa {
	namespace dot {
		class SDLGenerator : public BitmapGenerator
		{
			public:
				SDLGenerator();
				virtual ~SDLGenerator() = default;

				virtual bitmap GetBitmap() const;
				virtual void Update(Document* doc, Context* context);
				virtual void UpdateVariableFields(Document* doc, Context* context);

		};
	}
}
#endif
