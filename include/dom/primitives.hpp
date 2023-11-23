#ifndef DOT_MESSAGE_PRIMITIVES_OBJECTS_HPP
#define DOT_MESSAGE_PRIMITIVES_OBJECTS_HPP

#include "object.hpp"
#include "components/pen.hpp"

namespace macsa {
	namespace dot {
		class IDocumentVisitor;

		class Primitive : public Object
		{
			public:
				Primitive(const std::string& id, const Geometry& geometry, const ObjectType& primitiveType);
				Primitive(const Primitive&) = delete;
				virtual ~Primitive() = default;

				/**
				 * @brief IsVariable. Overrided method of Object::IsVariable
				 * @return false always.
				 */
				bool IsVariable() const override {
					return false;
				}

				/**
				 * @brief GetPen. Getter method for the border pen.
				 * @return The current border pen settings.
				 */
				virtual const Pen& GetPen() const {
					return _pen;
				}

				/**
				 * @brief SetPen. Setter method for the border pen.
				 * @param pen: The border pen settings.
				 */
				virtual void SetPen(const Pen& pen);

				/**
				 * @brief GetBrush. Getter method for the fill color.
				 * @return The color to fill the primitive.
				 */
				virtual const Color& GetBrush() const {
					return _brush;
				}

				/**
				 * @brief SetBrush. Setter method for the fill color.
				 * @param brush: The color to fill the primitive.
				 */
				virtual void SetBrush(const Color& brush);

				/**
				 * @brief IsFilled. Getter method of the filling parameter
				 * @return true if the primitive is print filled with the
				 * brush color or false if the primitive is transparent.
				 */
				virtual bool IsFilled() const {
					return _filled;
				}

				/**
				 * @brief SetFilled. Setter method of the filling parameter
				 * @param fill: bool to force if the primitive will be printed
				 * filled with the brush color or is transparent.
				 */
				virtual void SetFilled(bool fill);

				/**
				 * @brief HasBorder. Getter method of the printing border
				 * parameter.
				 * @return true if the primitive will be printed with a border
				 * or false if the border will not be printed.
				 */
				virtual bool HasBorder() const {
					return _border;
				}

				/**
				 * @brief ShowBorder. Setter method of the printing border
				 * parameter.
				 * @param show: bool to select if the border of the primitive
				 * has to be printed.
				 */
				virtual void ShowBorder(bool show);

			public:
				Signal<> Changed;

			private:
				Pen _pen;
				Color _brush;
				bool _filled;
				bool _border;
		};

		class Rectangle : public Primitive
		{
			public:
				Rectangle(const std::string& id, const Geometry& geometry);
				Rectangle(const Rectangle&) = delete;
				virtual ~Rectangle(){}

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) const override;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Ellipse : public Primitive
		{
			public:
				Ellipse(const std::string& id, const Geometry& geometry);
				Ellipse(const Ellipse&) = delete;
				virtual ~Ellipse(){}

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) const override;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Diamond : public Primitive
		{
			public:
				Diamond(const std::string& id, const Geometry& geometry);
				Diamond(const Diamond&) = delete;
				virtual ~Diamond(){}

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) const override;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};

		class Line : public Primitive
		{
			public:
				Line(const std::string& id, const Geometry& geometry);
				Line(const Line&) = delete;
				virtual ~Line(){}

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) const override;

				bool IsFilled() const override {return false;}
				bool HasBorder() const override {return true;}

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};
	}
}

#endif
