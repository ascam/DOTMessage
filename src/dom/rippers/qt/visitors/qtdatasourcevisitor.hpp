#ifndef MACSA_QT_DATASOURCE_VISITOR_HPP
#define MACSA_QT_DATASOURCE_VISITOR_HPP

#include "dom/documentvisitor.hpp"
#include "dom/rippers/context.hpp"
#include "utils/macsalogger.hpp"

using macsa::dot::Document;
using macsa::utils::MacsaLogger;

namespace macsa
{
	namespace dot
	{
		class DataSourceVisitor : public macsa::dot::IDocumentVisitor
		{
			public:
			DataSourceVisitor(Context* context) :
			_context{context}
			{}

			bool Visit(const CounterDataSource& ds)
			{
				_result = ds.GetData(_context);

				return true;
			}

			bool Visit(const DateTimeDataSource& ds)
			{
				_result = ds.GetData(_context);

				return true;
			}

			bool Visit(const UserInputDataSource& ds)
			{
				_result = ds.GetData(_context);

				return true;
			}

			bool Visit(const DatabaseDataSource& ds)
			{
				_result = ds.GetData(_context);

				return true;
			}

			bool Visit(const CompositeDataSource& ds)
			{
				_result = ds.GetData(_context);

				return true;
			}

			std::string getDataSourceResult()
			{
				return _result;
			}

			private:
			Context* _context;
			std::string _result;
		};
	}
}
#endif
