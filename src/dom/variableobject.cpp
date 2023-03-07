#include "dom/variableobject.hpp"
#include "dom/factories/datasourcefactory.hpp"

using macsa::dot::VariableObject;
using macsa::dot::DataSource;
using macsa::dot::ObjectType;
using macsa::dot::Geometry;
using macsa::dot::DataSourceType;

VariableObject::VariableObject(const std::string& id, const ObjectType& type, const Geometry& geometry) :
	Object(id, type, geometry),
	_datasource{}
{}

DataSource* VariableObject::GetDatasource() const
{
	return _datasource.get();
}

DataSource* VariableObject::SetDatasource(const DataSourceType& type)
{
	if (_datasource.get() == nullptr || _datasource->GetType() != type) {
		_datasource.reset(DataSourceFactory::Get(type()));
		DataSourceChanged.Emit();
	}
	return _datasource.get();
}

void VariableObject::ClearDataSource()
{
	if (IsVariable()) {
		_datasource.reset(nullptr);
		DataSourceChanged.Emit();
	}
}

bool VariableObject::IsVariable() const
{
	return (_datasource.get() != nullptr);
}
