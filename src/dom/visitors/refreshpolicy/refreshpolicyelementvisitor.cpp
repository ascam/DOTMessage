#include "dom/visitors/refreshpolicy/refreshpolicyelementvisitor.hpp"

#include "dom/text.hpp"
#include "dom/barcode.hpp"
#include "dom/visitors/refreshpolicy/refreshpolicydatasourcevisitor.hpp"

using macsa::dot::Document;
using macsa::dot::RefreshPolicyVisitor;

RefreshPolicyVisitor::RefreshPolicyVisitor(dot::Document* doc, Context* context) :
	dot::IDocumentVisitor(),
	_doc(doc),
	_context{context}
{}

bool RefreshPolicyVisitor::VisitEnter(const dot::Text& text)
{
	if (text.IsVariable())	{
		RefreshPolicyDataSourceVisitor dsv(_context);
		text.GetDatasource()->Accept(&dsv);
		_result |= dsv.getDataSourceResult();
	}

	return false;
}

bool RefreshPolicyVisitor::VisitEnter(const dot::Barcode& barcode)
{
	if (barcode.IsVariable())	{
		RefreshPolicyDataSourceVisitor dsv(_context);
		barcode.GetDatasource()->Accept(&dsv);
		_result |= dsv.getDataSourceResult();
	}

	return false;
}
