#ifndef DOT_MESSAGE_OBJECT_HPP
#define DOT_MESSAGE_OBJECT_HPP

#include <string>
#include <array>
#include <queue>
#include <memory>

#include "geometry.hpp"
#include "objecttype.hpp"
#include "refreshpolicy.hpp"
#include "signal/signal.hpp"

#include "document.hpp"

namespace macsa {
	namespace dot {

		struct LinkedObject {
			bool enabled;
			std::string objectId;
		};

		/**
		 * @brief The Object class.
		 *
		 * This class contains the abstract object definition.
		 */
		class Object
		{
			public:
				Object(const std::string& id, const ObjectType& type, const Geometry& geometry = Geometry());
				Object(const Object&) = delete;
				virtual ~Object();

				friend class Document;

				/**
				 * @brief GetId. Getter method for object string identifier
				 * @return the object string identifier.
				 */
				const std::string& GetId() const {return _id;}

				/**
				 * @brief GetType. Getter method for object type identifier
				 * @return the enum value of the object type.
				 */
				const ObjectType& GetType() const {return _type;}

				/**
				 * @brief GetGeometry. Getter method for object geometry
				 * @return The current object geometry in canvas relative
				 * coords.
				 */
				const Geometry& GetGeometry() const {return _geometry;}

				/**
				 * @brief SetGeometry. Setter method for object geometry
				 * @param geometry: The object geometry to be set.
				 */
				void SetGeometry(const Geometry& geometry);

				/**
				 * @brief GetPosition. Getter method for object position
				 * @return The current object top left point in canvas relative
				 * coords.
				 */
				const Point& GetPosition() const {return _geometry.position;}

				/**
				 * @brief SetPosition. Setter method for object position
				 * @param position: the object top left point.
				 */
				void SetPosition(const Point& position);

				/**
				 * @brief GetXPosition. Getter method for object x coord position
				 * @return The current object left side x position in canvas relative
				 * coords.
				 */
				float GetXPosition() const {return _geometry.position.x;}

				/**
				 * @brief SetXPosition. Setter method for object x coord position
				 * @param x: The object left side x position to be set.
				 */
				void SetXPosition(float x);

				/**
				 * @brief GetYPosition. Getter method for object y coord position
				 * @return The current object top y position in canvas relative
				 * coords.
				 */
				float GetYPosition() const {return _geometry.position.y;}

				/**
				 * @brief SetYPosition. Setter method for object y coord position
				 * @param x: The object top y position to be set.
				 */
				void SetYPosition(float y);

				/**
				 * @brief GetSize. Getter method for object size
				 * @return The current object size.
				 */
				const Size& GetSize() const {return _geometry.size;}

				/**
				 * @brief SetSize. Setter method for object size
				 * @param size: The object size to be set.
				 */
				void SetSize(const Size& size);

				/**
				 * @brief GetWidth. Getter method for object width.
				 * @return The current object width.
				 */
				float GetWidth() const {return _geometry.size.width;}

				/**
				 * @brief SetWidth. Setter method for object width.
				 * @param width: The object width to be set.
				 */
				void SetWidth(float width);

				/**
				 * @brief GetHeight. Getter method for object height
				 * @return The current object height.
				 */
				float GetHeight() const {return _geometry.size.height;}

				/**
				 * @brief SetHeight. Setter method for object height.
				 * @param height:  The object height to be set.
				 */
				void SetHeight(float height);

				/**
				 * @brief GetRotation. Getter method for object rotation
				 * @return The current object rotation in canvas relative
				 * coords.
				 */
				int GetRotation() const {return _geometry.rotation;}

				/**
				 * @brief SetRotation. Setter method for object rotation
				 * @param rotation: The object rotation to be set.
				 */
				void SetRotation(int rotation);

				/**
				 * @brief Collides. Method to detect collision between 2
				 * objects.
				 * @param other. The other object to check collisions
				 * @return true if booth objects collides, otherwise returns
				 * false
				 */
				bool Collides(const Object& other) const;

				/**
				 * @brief Collides. Overloaded Method to detect collision. This
				 * method detects collisions between this object and a geometry.
				 * @param geometry. A geometry struct to detect collisions.
				 * @return true if this objects collides with the given geometry,
				 * otherwise returns false.
				 */
				bool Collides(const Geometry& geometry) const;

				/**
				 * @brief Collides. Overloaded Method to detect collision. This
				 * method detects collisions between this object and a point.
				 * @param point:  A point struct to detect collisions.
				 * @return true if the point is inside this objects, otherwise
				 * returns false.
				 */
				bool Collides(const Point& point) const;

				/**
				 * @brief GetSelected. Getter method for check if object is
				 * selected
				 * @return true if selected is active, otherwise return false
				 */
				bool GetSelected() const {return _selected;}

				/**
				 * @brief SetSelected. Setter method to mark the object as
				 * selected or not
				 * @param select: bool to mark objected selected or unselected.
				 */
				void SetSelected(bool select);

				/**
				 * @brief GetPrintable. Getter method for printable property
				 * @return true if the object is printable or false if
				 * the object is hidden.
				 */
				bool GetPrintable() const {return _printable;}

				/**
				 * @brief SetPrintable. Setter method for printable property
				 * @param printable: boolean to set if the object is visible
				 * or is hidden.
				 */
				void SetPrintable(bool printable);

				/**
				 * @brief GetLinked. Getter method for linked objects enable status.
				 * @return true if this object is linked to another object, otherwise
				 * returns false.
				 */
				bool GetLinked() const {return _linked.enabled;}

				/**
				 * @brief SetLinked. Setter method for linked objects enable status.
				 * @param linked: bool to mark this object is linked to another object
				 */
				void SetLinked(bool linked);

				/**
				 * @brief GetLinkedObject. Getter method for linked objects.
				 * @return string with the linked object id.
				 */
				const std::string& GetLinkedObject() const {return _linked.objectId;}

				/**
				 * @brief SetLinkedObject. Setter method for linked objects.
				 * @param objectId: string with the linked object id.
				 */
				void SetLinkedObject(const std::string& objectId);

				/**
				 * @brief GetLayer. Getter method for object layer.
				 * @return The number of the layer where the object resides.
				 */
				uint32_t GetLayer() const {return _layer;}

				/**
				 * @brief SetLayer. Setter method for object layer.
				 * @param layer: The number of the layer where the object
				 * will be moved.
				 */
				void SetLayer(uint32_t layer);

				/**
				 * @brief GetZOrder. Getter method for object Z order.
				 * z Order is the position in z coord for an specific layer
				 * @return the z coord postion.
				 */
				int32_t GetZOrder() const {return _zOrder;}

				/**
				 * @brief SetZOrder. Setter method for object Z order.
				 * @param zOrder: Number of z coord position.
				 */
				void SetZOrder(int32_t zOrder);

				/**
				 * @brief operator >. Helper function for sorting by z coords.
				 * @param other: object to compare
				 * @return true if this object is upper in a z order than
				 * the other object, otherwise returns false.
				 */
				bool operator > (const Object& other) const  {
					if (_layer < other._layer) {
						return false;
					}
					return _layer > other._layer || _zOrder < other._zOrder;
				}

				/**
				 * @brief operator <. Helper function for sorting by z coords.
				 * @param other: object to compare
				 * @return false if this object is upper in a z order than
				 * the other object, otherwise returns true.
				 */
				bool operator < (const Object& other) const {
					if (_layer > other._layer) {
						return false;
					}
					return _layer < other._layer || _zOrder > other._zOrder;
				}

				/**
				 * @brief GetRefreshPolicy. Getter method to get the refresh
				 * policy of a variable object
				 * @return The refresh policy of the object.
				 */
				virtual RefreshPolicy GetRefreshPolicy() const = 0;

				/**
				 * @brief IsVariable. Getter method to get if the object
				 * can change its inner value.
				 * @return true if the object can change the inner value,
				 * false if the object is static.
				 */
				virtual bool IsVariable() const = 0;

			public:
				Signal<> GeometryChanged;
				Signal<> SelectedChanged;
				Signal<> PrintableChanged;
				Signal<> LinkedChanged;
				Signal<> ZOrderChanged;
				Signal<> IdChanged;

			private:
				std::string _id;
				const ObjectType _type;
				Geometry _geometry;
				uint32_t _layer;
				int32_t _zOrder;
				LinkedObject _linked;
				bool _selected;
				bool _printable;

				/**
				 * @brief setId. Setter method for object string identifier
				 * @param id: the object string identifier to be set.
				 */
				void setId(const std::string& id);
		};
	}
}

#endif
