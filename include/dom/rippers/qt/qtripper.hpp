#ifndef NISX_QT_RIPPER_HPP
#define NISX_QT_RIPPER_HPP

#include "qtgenerator.hpp"
#include "ripper.hpp"

namespace macsa
{
	namespace dot
	{
		class QtDOTRipper : public DOTRipper
		{
			public:
				QtDOTRipper() : DOTRipper()	{
					_generator.reset(new QtGenerator());
				}
				QtDOTRipper(const QtDOTRipper& ripper) = delete;
				QtDOTRipper(QtDOTRipper&& ripper) = delete;
				QtDOTRipper& operator=(const QtDOTRipper& ripper) = delete;
				QtDOTRipper& operator=(QtDOTRipper&& ripper) = delete;
				~QtDOTRipper() = default;

				QPixmap* Draw(){return static_cast<QPixmap*>(_generator->NativeHandler());};
		};
	}
}
#endif
