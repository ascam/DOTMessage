#include "dom/components/datasources/compositedatasource.hpp"
#include "dom/documentvisitor.hpp"
#include "dom/factories/datasourcefactory.hpp"
#include "utils/stringutils.hpp"
#include "utils/macsalogger.hpp"

using macsa::dot::CompositeDataSource;
using macsa::dot::IDocumentVisitor;
using namespace macsa::utils;

// TODO(iserra) move to visitors
//constexpr const char* kFieldItem = "Field";
//constexpr const char* kTextItem = "Fixed";
//constexpr const char* kCharsToRemove = "\'\"";
constexpr const char* kDelimiter = "|";

bool CompositeDataSource::_registered = macsa::dot::ConcreteDataSourceFactory<CompositeDataSource>::Register(macsa::dot::NDataSourceType::kComposite);

CompositeDataSource::CompositeDataSource(const dot::Object& obj) :
	DataSource(NDataSourceType::kComposite, obj),
	_formula{}
{}

bool CompositeDataSource::Accept(IDocumentVisitor* visitor)
{
	if (visitor) {
		return visitor->Visit(*this);
	}
	return false;
}

void CompositeDataSource::SetFormula(const std::string& formula)
{
	auto&& slices = stringutils::Split(_formula, kDelimiter);
	if (slices.size() % 2) {
		ELog() << "Invalid formula \"" << formula << "\"";
		return;
	}

	if (_formula != formula) {
		_formula = formula;

		FormulaChanged.Emit();
	}
}

std::string CompositeDataSource::GetData(Context* context) const
{
	if (_formula.empty()) {
		return {};
	}

	//auto&& tokens = stringutils::Split(_formula, kDelimiter);
	//std::vector<std::string> visitedFields;
	//visitedFields.emplace_back(getParentName());

	//return getCompositeData(tokens, visitedFields);
	return {};
}
