#include "dom/variableobject.hpp"

namespace macsa {
	namespace dot {
		class VariableObjectMock : public VariableObject
		{
			public:
				VariableObjectMock(const std::string& id, const ObjectType& type, const Geometry& geometry = Geometry()) :
					VariableObject(id, type, geometry)
				{}
				virtual ~VariableObjectMock() = default;

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				virtual bool Accept(IDocumentVisitor* visitor) const {return true;}
		};
	}
}

