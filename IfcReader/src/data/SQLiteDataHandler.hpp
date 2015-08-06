#pragma once
#include <string>
#include <iosfwd>
#include <ifcpp/model/shared_ptr.h>
#include "DataHandler.hpp"
namespace SQLite
{
	class Database;
	class Transaction;
}
class IfcMaterialLayerSet;
class IfcMaterialLayer;
class IfcMaterial;
class IfcPropertySet;
class IfcPropertySingleValue;
class IfcRelAssociatesMaterial;

namespace IfcReader
{
	class SQLiteDataHandler : public DataHandler
	{
	public:
		bool closed;
		SQLite::Database *db;
		SQLite::Transaction *transaction;

		SQLiteDataHandler(std::string path);
		~SQLiteDataHandler();
		void initialize();
		void close();
		virtual int handleProduct(shared_ptr<IfcProduct> ifc_product);
		void handleMaterial(int product_id, shared_ptr<IfcMaterialLayerSet> matls, shared_ptr<IfcMaterialLayer> matl, shared_ptr<IfcMaterial> mat);
		int handlePropertySet(int product_id, shared_ptr<IfcPropertySet> prop_set);
		void handleProperty(int property_set_id, shared_ptr<IfcPropertySingleValue> prop_single_value);
	private:
		int getLastInsertedProductId();
		int getLastInsertedPropertySetId();
	};
}