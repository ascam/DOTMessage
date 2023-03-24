#ifndef RIPPER_BACKEND_QTBARCODE_HPP
#define RIPPER_BACKEND_QTBARCODE_HPP

#include <QPainter>
#include <QMap>
#include <QString>
#include <QColor>

#include "qtobject.hpp"
#include "dom/barcode.hpp"

namespace macsa {
	namespace dot {
		class QtBarcode : public QtObject
		{
			public:
				QtBarcode(const Barcode* barcode, QPainter& painter,
						  int vres, int hres, const ColorsPalette& palette);

				void Render() override;
				void Render(const std::string& dataSourceResult);

			private:
				const Barcode* _barcode;

				int getZintSymbology(const BarcodeSymbol& symbology) const;
				int getZintSymbologyMode(const BarcodeSymbol& symbology) const;

				bool isBarcodeWithTextOutside(const BarcodeSymbol& symbology) const;
				bool isBarcodeWithoutText(const BarcodeSymbol& symbology) const;
		};
	}
}
#endif
