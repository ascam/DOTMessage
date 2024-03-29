#ifndef DOT_MESSAGE_DOCUMENT_HPP
#define DOT_MESSAGE_DOCUMENT_HPP

#include <string>
#include <array>
#include <deque>
#include <memory>

#include "objecttype.hpp"
#include "components/geometry.hpp"
#include "components/color.hpp"
#include "signal/signal.hpp"

namespace macsa {
	namespace dot {

		class Object;
		class IDocumentVisitor;

		/**
		 * @brief The Document class.
		 *
		 * This class contains all the objects to create a DOM
		 * for a Macsa DOT printable messages.
		 */
		class Document
		{
				using VersionEncodingArray = std::array<uint8_t, 3>;
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
				 * @brief GetVersion. Getter method for current
				 * document version.
				 * @return The current document version.
				 */
				const VersionEncodingArray& GetVersion() const {
					return _versions;
				}

				/**
				 * @brief SetVersion. Setter method for document version.
				 * @param versions: array with the versions to store.
				 */
				void SetVersion(const VersionEncodingArray& versions);

				/**
				 * @brief GetUnits. Getter method for measurement units.
				 * @return The current measurement units (mm, dots, inches).
				 */
				const std::string& GetUnits() const {
					return _units;
				}

				/**
				 * @brief SetUnits. Setter method for measurement units.
				 * @param units: The measurement units (mm, dots, inches)
				 * to be used.
				 */
				void SetUnits(const std::string& units);

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
				std::deque<Object*> GetObjects() const;

				/**
				 * @brief GetObjectById. Getter method for a DOM object.
				 * @param id: Id of the object to find.
				 * @return a pointer to the object if the object is found,
				 * otherwise return  a nullptr
				 */
				Object* GetObjectById(const std::string& id) const;

				/**
				 * @brief AddObject. Method to add new object to the dom.
				 * @param objectId: Unique string identifier of the object.
				 * @param type: Type of the object to add.
				 * @param geometry: the object geometry
				 * @return If the object was succesfully inserted in the DOM
				 * this method returns a pointer to the object, otherwise
				 * return a nullptr.
				 */
				Object* AddObject(const std::string& objectId, const ObjectType& type, const Geometry& geometry = Geometry());

				/**
				 * @brief RemoveObject. Remove the object of the DOM if the object exist
				 * and free the memory alocated by the object.
				 * @param id: Id of the object to remove.
				 * @return true if the object is found and can be removed, otherwise returns
				 * false.
				 */
				bool RemoveObject(const std::string& id);

				/**
				 * @brief Clear. Remove all objects and document relative data
				 */
				void Clear();

				/**
				 * @brief RenameObject. Renames an object of the DOM if the object exist
				 * and the newid is no used.
				 * @param oldId: Id of the object to rename.
				 * @param newId: New Id to set to the object.
				 * @return true if the object is found and can be renamed, otherwise returns
				 * false.
				 */
				bool RenameObject(const std::string& oldId, const std::string& newId);

				/**
				 * @brief GetColorsPalette. Getter method for document's colors palette.
				 * @return The document's colors palette.
				 */
				const ColorsPalette& GetColorsPalette() const {return _colors;}

				/**
				 * @brief SetColorsPaletter. Setter method for document's colors palette.
				 * @param colors: a new colors palette to set to the document.
				 */
				void SetColorsPalette(const ColorsPalette& colors) {_colors = colors;}

				/**
				 * @brief AddColor. Add a color to the document's colors palette.
				 * @param name: name of the color.
				 * @param color: Color object.
				 */
				void AddColor(const std::string& name, const Color& color);

				/**
				 * @brief DeleteColor. Remove a color from the document's colors palette.
				 * @param name: name of te color to remove.
				 */
				void DeleteColor(const std::string& name);

				/**
				 * @brief GetGrayScaleLevel. Getter method for gray scale level,
				 * this value is the maximum number of gray scale.
				 * @return The current gray scale level.
				 */
				uint32_t GetGrayScaleLevels() const {return _gsLevels;}

				/**
				 * @brief SetGrayScaleLevel
				 * @param gsLevel
				 */
				void SetGrayScaleLevel(uint32_t levels) {_gsLevels = levels;}

				/**
				 * @brief Accept: Accept a hierarchical visit of the nodes in the
				 * dot::Document DOM. Every node in the DOM tree will be conditionally
				 * visited and the host will be called back via the IDocumentVisitor interface.
				 * This is essentially a SAX interface for DOM and document.
				 * @param visitor: Visitor interfaced used to visit the DOM.
				 * @return the result of visitor::visit().
				 */
				bool Accept(IDocumentVisitor* visitor) const;

				/**
				 * @brief GetResolution. Getter method to obtain the document resolution.
				 * @return Document resolution.
				 */
				uint16_t GetResolution() const {return _resolution;}

				/**
				 * @brief SetResolution sets the new message resolution.
				 * @param resolution new resolution
				 */
				void SetResolution(uint16_t resolution) {_resolution = resolution;}

			public:
				Signal<> NameChanged;
				Signal<> UnitsChanged;
				Signal<> VersionEncodingChanged;
				Signal<> ColorsPaletteChanged;
				Signal<> CanvasGeometryChanged;
				Signal<> ViewPortSizeChanged;
				Signal<> GsLevelsChanged;
				Signal<> DomChanged;

			private:
				std::string _name;
				std::string _units;
				VersionEncodingArray _versions;
				ColorsPalette _colors;
				Geometry _canvasGeometry;
				Size _viewport;
				uint32_t _gsLevels;
				DOM _dom;
				uint16_t _resolution;
		};
	}
}

#endif

