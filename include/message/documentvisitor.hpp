#ifndef DOT_MESSAGE_DOCUMENT_VISITOR_HPP
#define DOT_MESSAGE_DOCUMENT_VISITOR_HPP

#include "document.hpp"
#include "text.hpp"
#include "barcode.hpp"
#include "image.hpp"
#include "primitives.hpp"
#include "datasources/counterdatasource.hpp"
#include "datasources/databasedatasource.hpp"
#include "datasources/userinputdatasource.hpp"
#include "datasources/datetimedatasource.hpp"
#include "datasources/compositedatasource.hpp"

namespace macsa
{
	namespace dot
	{
		/**
		 * @brief The IDocumentVisitor class. This class defines the interface for
		 * visiting the DOM document, the internal objects and the possible data
		 * source of variable objects (see the Accept() method.).
		 *
		 * If you call the Accept() method, it requires being passed a IDocumentVisitor
		 * class to handle callbacks. For nodes that contain other nodes (Document, Object)
		 * you will get called with a VisitEnter/VisitExit pair.
		 * Nodes that are always leafs are simply called with Visit().
		 *
		 * If you return 'true' from a Visit method, recursive parsing will continue.
		 * If you return false, <b>no children of this node or its siblings</b> will be visited.
		 *
		 * @sa Document::Accept()
		 */
		class IDocumentVisitor
		{
			public:
				IDocumentVisitor() = default;
				virtual ~IDocumentVisitor() = default;
				/**
				 * @brief VisitEnter. Start the visit in the DOM document
				 * @param document: DOM document to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool VisitEnter(const Document&) {
					return true;
				}

				/**
				 * @brief VisitExit. Exits the visit in the DOM document
				 * @param document: DOM document to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool VisitExit(const Document&) {
					return true;
				}

				/**
				 * @brief VisitEnter. Start the visit in a Text object
				 * @param text: Text object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool VisitEnter(const Text&) {
					return true;
				}

				/**
				 * @brief VisitExit. Exits the visit in a Text Object
				 * @param text: Text object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool VisitExit(const Text&) {
					return true;
				}

				/**
				 * @brief VisitEnter. Start the visit in a Barcode object
				 * @param barcode: Barcode object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool VisitEnter(const Barcode& barcode) {
					return true;
				}

				/**
				 * @brief VisitExit. Exits the visit in a Barcode Object
				 * @param barcode: Barcode object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool VisitExit(const Barcode& barcode) {
					return true;
				}

				/**
				 * @brief Visit. Visits a Image object
				 * @param image: Image object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool Visit(const Image& image) {
					return true;
				}

				/**
				 * @brief Visit. Visits a rectangle object
				 * @param rectangle: Rectangle object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool Visit(const Rectangle& rectangle) {
					return true;
				}

				/**
				 * @brief Visit. Visits an ellipse object
				 * @param ellipse: Ellipse object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool Visit(const Ellipse& ellipse) {
					return true;
				}

				/**
				 * @brief Visit. Visits a diamond object
				 * @param diamond: Diamond object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool Visit(const Diamond& diamond) {
					return true;
				}

				/**
				 * @brief Visit. Visits a line object
				 * @param line: line object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool Visit(const Line& line) {
					return true;
				}

				/**
				 * @brief Visit. Visits a counter data source
				 * @param counter: counter data source to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool Visit(const CounterDataSource& counter) {
					return true;
				}

				/**
				 * @brief Visit. Visits a database data source
				 * @param database: database data source to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool Visit(const DatabaseDataSource& database) {
					return true;
				}

				/**
				 * @brief Visit. Visits a date and time data source
				 * @param datetime: Date and time data source to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool Visit(const DateTimeDataSource& datetime) {
					return true;
				}

				/**
				 * @brief Visit. Visits a user input data source
				 * @param userInput: User input data source to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool Visit(const UserInputDataSource& userInput) {
					return true;
				}

				/**
				 * @brief Visit. Visits a composite data source
				 * @param composite: Composite data source to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool Visit(const CompositeDataSource& composite) {
					return true;
				}
		};
	}
}

#endif
