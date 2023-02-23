#include "message/datasources/compositedatasource.hpp"
#include "message/documentvisitor.hpp"
#include "factories/datasourcefactory.hpp"
#include "utils/stringutils.hpp"
#include "utils/macsalogger.hpp"

using macsa::dot::CompositeDataSource;
using macsa::dot::RefreshPolicy;
using macsa::dot::IDocumentVisitor;
using namespace macsa::utils;

// TODO(iserra) move to visitors
//constexpr const char* kFieldItem = "Field";
//constexpr const char* kTextItem = "Fixed";
//constexpr const char* kCharsToRemove = "\'\"";
constexpr const char* kDelimiter = "|";

namespace macsa {
	namespace dot {
		namespace  {
			static const bool CompositeFactoryRegistered = ConcreteDataSourceFactory<CompositeDataSource>::Register(NDataSourceType::kComposite);
		}
	}
}

CompositeDataSource::CompositeDataSource() :
	DataSource(NDataSourceType::kComposite),
	_formula{}
{}

bool CompositeDataSource::Accept(IDocumentVisitor* visitor)
{
	if (visitor) {
		return visitor->Visit(*this);
	}
	return false;
}

//RefreshPolicy CompositeDataSource::GetRefreshPolicy() const
//{
//	RefreshPolicy policy = RefreshPolicy::kNone;
//	for (auto& token : _tokens) {
//		if (token.first == kFieldItem) {
//			const auto* object = _document->GetObjectById(token.second);
//			if (object && object->IsVariable())  {
//				auto objPolicy = object->GetRefreshPolicy();
//				if (objPolicy != RefreshPolicy::kNone) {
//					if (policy > objPolicy || policy == RefreshPolicy::kNone) {
//						policy = objPolicy;
//					}
//				}
//			}
//		}
//	}
//	return policy;
//}

void CompositeDataSource::SetFormula(const std::string &formula)
{
	std::vector<std::string> slices =  stringutils::Split(_formula, kDelimiter);
	if (slices.size() % 2 != 0) {
		ELog() << "Invalid formula \"" << formula << "\"";
		return;
	}
	_formula = formula;
//	_tokens.clear();
//	for (uint32_t index = 0; index < slices.size(); index += 2) {
//		_tokens.emplace_back(slices.at(index), slices.at(index + 1));
//	}
}

