#ifndef NISX_QT_RIPPER_HPP
#define NISX_QT_RIPPER_HPP

#include "sdlgenerator.hpp"
#include "ripper.hpp"

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
				~SDLDOTRipper();

				void* Draw(){return _generator->NativeHandler();};
		};
	}
}
#endif
