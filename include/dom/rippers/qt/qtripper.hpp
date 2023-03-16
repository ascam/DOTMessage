#ifndef DOTMESSAGE_QT_RIPPER_HPP
#define DOTMESSAGE_QT_RIPPER_HPP

#include "dom/rippers/ripper.hpp"
#include "dom/rippers/context.hpp"
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
				QPixmap* Draw(Context* context);
		};
	}
}
#endif
