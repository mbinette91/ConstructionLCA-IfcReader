#pragma once
#include <string>
#include <iosfwd>
#include <ifcpp/model/shared_ptr.h>
class IfcMaterialLayerSet;
class IfcMaterialLayer;
class IfcMaterial;
class IfcPropertySet;
class IfcPropertySingleValue;
class IfcRelAssociatesMaterial;

namespace IfcReader
{
	class DataHandler
	{
	public:
		virtual ~DataHandler() {};
		void setProjectId(int project_id);
		virtual void initialize() = 0;
		virtual void close() = 0;
		void DataHandler::handleModel(shared_ptr<IfcPPModel> ifc_model);
	protected:
		int project_id = 0;

		virtual int handleProduct(shared_ptr<IfcProduct> ifc_product) = 0; // Returns product id
		virtual void handleMaterial(int product_id, shared_ptr<IfcMaterialLayerSet> matls, shared_ptr<IfcMaterialLayer> matl, shared_ptr<IfcMaterial> mat) = 0;
		virtual int handlePropertySet(int product_id, shared_ptr<IfcPropertySet> prop_set) = 0; // Returns property set id
		virtual void handleProperty(int property_set_id, shared_ptr<IfcPropertySingleValue> prop_single_value) = 0;
	private:
		void handleAssociationsInverse(int product_id, shared_ptr<IfcProduct> ifc_product);
		void handleDefinesInverse(int product_id, shared_ptr<IfcProduct> ifc_product);
		void handleMaterialAssociation(int product_id, shared_ptr<IfcRelAssociatesMaterial> rel_mat);
		void handlePropertySetRel(int product_id, shared_ptr<IfcPropertySet> prop_set);
	};
}