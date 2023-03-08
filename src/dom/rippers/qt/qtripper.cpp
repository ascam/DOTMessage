#include "dom/rippers/qt/qtripper.hpp"

#include "dom/rippers/ripper.hpp"
#include "dom/rippers/qt/qtgenerator.hpp"

using macsa::dot::QtDOTRipper;

QtDOTRipper::QtDOTRipper() : DOTRipper()
{
	_generator.reset(new QtGenerator());
}

QPixmap* QtDOTRipper::Draw()
{
	return static_cast<QPixmap*>(_generator->NativeHandler());
}
