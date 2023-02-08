#ifndef DOT_MESSAGE_DOCUMENT_HPP
#define DOT_MESSAGE_DOCUMENT_HPP

#include <string>
#include <array>
#include <deque>
#include <memory>

#include "geometry.hpp"
#include "objecttype.hpp"

// TODO(iserra): Add DateCodes support

namespace macsa {
	namespace dot {
		class Object;
		/**
		 * @brief The Document class.
		 *
		 * This class contains all the objects to create a DOM
		 * for a Macsa DOT printable messages.
		 */
		class Document
		{
			public:
				using DOM = std::deque<std::unique_ptr<Object>>;

			public:
				Document(const std::string& name = "");
				~Document();

				/**
				 * @brief GetName. Getter for document name.
				 * @return document name
				 */
				const std::string& GetName() const {return _name;}
				/**
				 * @brief SetName. Setter for document name.
				 * @param name: document name
				 */
				void SetName(const std::string& name);

				/**
				 * @brief GetCanvasXOffset. Getter for the canvas geometry x position
				 * @return the relative x position between the canvas and the viewport.
				 */
				float GetCanvasXOffset() const {return _canvasGeometry.position.x;}
				/**
				 * @brief SetCanvasXOffset. Setter for the canvas geometry x position
				 * @param x: the relative x position between the canvas and the viewport.
				 */
				void SetCanvasXOffset(float x);
				/**
				 * @brief GetCanvasYOffset. Getter for the canvas geometry y position
				 * @return the relative y position between the canvas and the viewport.
				 */
				float GetCanvasYOffset() const {return _canvasGeometry.position.y;}
				/**
				 * @brief SetCanvasYOffset. Setter for the canvas geometry y position
				 * @param y: the relative y position between the canvas and the viewport.
				 */
				void SetCanvasYOffset(float y);
				/**
				 * @brief GetCanvasOffset. Getter for the canvas geometry position
				 * @return the relative position between the canvas and the viewport.
				 */
				const Point& GetCanvasOffset() const {return _canvasGeometry.position;}
				/**
				 * @brief SetCanvasOffset. Setter for the canvas geometry position
				 * @param pos: the relative position between the canvas and the viewport.
				 */
				void SetCanvasOffset(const Point& pos);

				/**
				 * @brief GetCanvasWidth. Getter for the canvas geometry width
				 * @return the canvas with.
				 */
				float GetCanvasWidth() const {return _canvasGeometry.size.width;}
				/**
				 * @brief SetCanvasWidth. Setter for the canvas geometry width
				 * @param width: with of the canvas.
				 */
				void SetCanvasWidth(float width);
				/**
				 * @brief GetCanvasHeight. Getter for the canvas geometry height
				 * @return the canvas height.
				 */
				float GetCanvasHeight() const {return _canvasGeometry.size.height;}
				/**
				 * @brief SetCanvasHeight. Setter for the canvas geometry height
				 * @param height: with of the canvas.
				 */
				void SetCanvasHeight(float height);
				/**
				 * @brief GetCanvasSize. Getter for the canvas geometry size
				 * @return The canvas size.
				 */
				const Size& GetCanvasSize() const {return _canvasGeometry.size;}
				/**
				 * @brief SetCanvasSize. Setter for the canvas geometry size
				 * @param size: The canvas size
				 */
				void SetCanvasSize(const Size& size);

				/**
				 * @brief GetCanvasRotation. Getter for the canvas rotation in CW degrees
				 * @return The canvas rotation angle.
				 */
				int GetCanvasRotation() const {return _canvasGeometry.rotation;}
				/**
				 * @brief SetCanvasRotation. Setter for the canvas rotation in CW degrees
				 * @param rotation: canvas rotation in CW degrees
				 */
				void SetCanvasRotation(int rotation);

				/**
				 * @brief GetViewportWidth. Getter for the viewport geometry width
				 * @return the viewport with.
				 */
				float GetViewportWidth() const {return _viewport.width;}
				/**
				 * @brief SetViewportWidth. Setter for the viewport geometry width
				 * @param width: with of the viewport.
				 */
				void SetViewportWidth(float width);
				/**
				 * @brief GetViewportHeight. Getter for the viewport geometry height
				 * @return the viewport with.
				 */
				float GetViewportHeight() const {return _viewport.height;}
				/**
				 * @brief SetViewportHeight. Setter for the viewport geometry height
				 * @param height: with of the viewport.
				 */
				void SetViewportHeight(float height);
				/**
				 * @brief GetViewportSize. Getter for the viewport geometry size
				 * @return The viewport size.
				 */
				const Size& GetViewportSize() const {return _viewport;}
				/**
				 * @brief SetViewportSize. Setter for the viewport geometry size
				 * @param size: The viewport size
				 */
				void SetViewportSize(const Size& size);

				/**
				 * @brief GetObjects. Getter for document objects list.
				 * @return reference to internal dom.
				 */
				const DOM& GetObjects() const {return _dom;}

				/**
				 * @brief AddObject. Metho to add new object to the dom.
				 * @param objectId: Unique string identifier of the object.
				 * @param type: Type of the object to add.
				 * @return If the object was succesfully inserted in the DOM
				 * this method returns a pointer to the object, otherwise
				 * return a nullptr.
				 */
				Object const * AddObject(const std::string& objectId, const ObjectType& type);

			private:
				std::string _name;
				std::array<uint8_t, 3> _versions;
				Geometry _canvasGeometry;
				Size _viewport;
				DOM _dom;
		};
	}
}

#endif

