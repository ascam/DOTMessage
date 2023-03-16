#ifndef NISX_QT_RIPPER_HPP
#define NISX_QT_RIPPER_HPP

#include "dom/rippers/ripper.hpp"
#include "dom/rippers/context.hpp"
#include "dom/rippers/sdl/sdlgenerator.hpp"

namespace macsa
{
	namespace dot
	{
		class SDLDOTRipper : public DOTRipper
		{
			public:
				SDLDOTRipper() : DOTRipper()	{
					_generator.reset(new SDLGenerator());
				}
				SDLDOTRipper(const SDLDOTRipper& ripper) = delete;
				SDLDOTRipper(SDLDOTRipper&& ripper) = delete;
				SDLDOTRipper& operator=(const SDLDOTRipper& ripper) = delete;
				SDLDOTRipper& operator=(SDLDOTRipper&& ripper) = delete;
				virtual ~SDLDOTRipper();

				void* Draw(Context* context){return _generator->NativeHandler(context);};
		};
	}
}
#endif
