#ifndef NISX_QT_RIPPER_HPP
#define NISX_QT_RIPPER_HPP

#include "dom/rippers/ripper.hpp"
#include "qpixmap.h"

namespace macsa
{
	namespace dot
	{
		class QtDOTRipper : public DOTRipper
		{
			public:
				QtDOTRipper();
				QtDOTRipper(const QtDOTRipper& ripper) = delete;
				QtDOTRipper(QtDOTRipper&& ripper) = delete;
				QtDOTRipper& operator=(const QtDOTRipper& ripper) = delete;
				QtDOTRipper& operator=(QtDOTRipper&& ripper) = delete;
				virtual ~QtDOTRipper() = default;
				QPixmap* Draw();
		};
	}
}
#endif
