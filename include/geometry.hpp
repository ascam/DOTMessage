#ifndef DOT_MESSAGE_GEOMETRY_HPP
#define DOT_MESSAGE_GEOMETRY_HPP

#include <utility>

namespace macsa
{
	namespace dot
	{
		struct Point
		{
			float x = 0;
			float y= 0;

			bool operator == (const Point& other) const {
				return x == other.x && y == other.y;
			}
			bool operator != (const Point& other) const {
				return x != other.x || y != other.y;
			}
		};

		struct Size
		{
			float width = 0;
			float height = 0;

			bool operator == (const Size& other) const {
				return width == other.width && height == other.height;
			}
			bool operator != (const Size& other) const {
				return width != other.width || height != other.height;
			}
		};

		struct Geometry
		{
			Point position;
			Size size;
			int rotation = 0;

			bool operator == (const Geometry& other) const {
				return position == other.position &&
					   size == other.size &&
					   rotation == other.rotation;
			}
			bool operator != (const Geometry& other) const {
				return position != other.position ||
					   size != other.size ||
					   rotation != other.rotation;
			}
		};

	}
}
#endif
