#include "message/variableobject.hpp"
#include "factories/datasourcefactory.hpp"

using macsa::dot::VariableObject;
using macsa::dot::DataSource;
using macsa::dot::ObjectType;
using macsa::dot::Geometry;
using macsa::dot::DataSourceType;
using macsa::dot::RefreshPolicy;

VariableObject::VariableObject(const std::string &id, const ObjectType &type, const Geometry &geometry) :
	Object(id, type, geometry),
	_datasource{}
{}

DataSource* VariableObject::GetDatasource() const
{
	return _datasource.get();
}

DataSource* VariableObject::SetDatasource(const DataSourceType &type)
{
	_datasource.reset(DataSourceFactory::Get(type()));
	return _datasource.get();
}

bool VariableObject::IsVariable() const
{
	return (_datasource.get() != nullptr);
}
