#ifndef MACSA_NISX_PRIMITIVE_PARSER_HPP
#define MACSA_NISX_PRIMITIVE_PARSER_HPP

#include "dom/primitives.hpp"
#include "objectparser.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class PrimitiveParser : public ObjectParser
		{
			public:
				PrimitiveParser(const std::string& fieldType, dot::Object* primitive);
				virtual ~PrimitiveParser() = default;

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

			private:
				dot::Primitive* _primitive;
		};

		class PenParser : public tinyxml2::XMLVisitor
		{
			public:
				PenParser(dot::Primitive* primitive);
				virtual ~PenParser() = default;

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit(const tinyxml2::XMLElement& element) override;

			private:
				dot::Primitive* _primitive;
				dot::Pen _pen;
		};

		class BrushParser : public tinyxml2::XMLVisitor
		{
			public:
				BrushParser(dot::Primitive* primitive);
				virtual ~BrushParser() = default;

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

			private:
				dot::Primitive* _primitive;
		};
	}
}

#endif
