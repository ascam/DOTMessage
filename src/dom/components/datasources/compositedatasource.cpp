#include "dom/components/datasources/compositedatasource.hpp"
#include "dom/documentvisitor.hpp"
#include "dom/factories/datasourcefactory.hpp"
#include "dom/text.hpp"
#include "dom/barcode.hpp"
#include "utils/stringutils.hpp"
#include "utils/macsalogger.hpp"

using macsa::dot::CompositeDataSource;
using macsa::dot::IDocumentVisitor;
using namespace macsa::utils;

constexpr const char* kFieldItem = "Field";
constexpr const char* kTextItem = "Fixed";
constexpr const char* kCharsToRemove = "\'\"";
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
	std::string returnValue;

	if (!_formula.empty()) {
		auto&& tokens = stringutils::Split(_formula, kDelimiter);
		_visitedFields.insert({GetId(), std::string()});

		returnValue = getCompositeData(context, tokens);
		_visitedFields.clear();
	}

	return returnValue;
}

std::string CompositeDataSource::getCompositeData(Context* context, const std::vector<std::string>& tokens) const
{
	std::string returnValue;
	std::stringstream ss;

	for (auto index = 0UL; index < tokens.size(); ++index) {
		if (tokens.at(index) == kFieldItem) {
			const auto& objectName = tokens.at(index + 1);
			const auto object = context->document->GetObjectById(objectName);
			if (object != nullptr) {
				auto itVisitedFiels = std::find_if(_visitedFields.cbegin(), _visitedFields.cend(),
					[&objectName](const std::pair<std::string, std::string>& visitedField)	{
						return visitedField.first == objectName;
					});

				if (itVisitedFiels == _visitedFields.cend()) {
					_visitedFields.insert({GetId(), std::string()});
					auto&& value = getObjectData(context, object);
					_visitedFields[GetId()] = value;
					ss << std::move(value);
				}
				else	{
					ss << itVisitedFiels->second;
				}
			}
		}
		else if (tokens.at(index) == kTextItem) {
			const auto& textToken = tokens.at(index + 1);
			auto&& text = stringutils::RemoveChars(textToken, kCharsToRemove);
			ss << text;
		}
	}

	returnValue = ss.str();

	return returnValue;
}

std::string CompositeDataSource::getObjectData(Context* context, const Object* object) const
{
	if (object != nullptr) {
		if (object->IsVariable())	{
			auto variableObject = dynamic_cast<const VariableObject*>(object);
			if (variableObject != nullptr)	{
				auto ds = variableObject->GetDatasource();
				if (ds != nullptr)	{
					if (ds->GetType() == NDataSourceType::kComposite)	{
						auto dsComposite = dynamic_cast<const CompositeDataSource*>(ds);
						if (dsComposite != nullptr)	{
							auto&& newTokens = stringutils::Split(dsComposite->GetFormula(), kDelimiter);
							return getCompositeData(context, newTokens);
						}
					}
					else	{
						return ds->GetData(context);
					}
				}
			}
		}
		else	{
			if (object->GetType().toString() == kText)	{
				auto textObject = dynamic_cast<const Text*>(object);
				if (textObject != nullptr)	{
					return textObject->GetText();
				}
			}
			else if (object->GetType().toString() == kBarcode)	{
				auto barcodeObject = dynamic_cast<const Barcode*>(object);
				if (barcodeObject != nullptr)	{
					return barcodeObject->GetCode();
				}
			}
		}
	}

	return {};
}
