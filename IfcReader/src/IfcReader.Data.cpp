/*
* This file contains the function `handleData` which handles everything related to the persistance of useful information for later LCA computing.
* It is expected this is the module that is going to change the most often.
*/
#include "IfcReader.hpp"

#include <iostream>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>
#include <ifcpp/model/IfcPPModel.h>
#include <ifcpp/IFC4/include/IfcProduct.h>
#include <ifcpp/IFC4/include/IfcGloballyUniqueId.h>
#include <ifcpp/IFC4/include/IfcLabel.h>
#include <ifcpp/IFC4/include/IfcPlaneAngleMeasure.h>
#include <ifcpp/IFC4/include/IfcIdentifier.h>
#include <ifcpp/IFC4/include/IfcValue.h>
#include <ifcpp/IFC4/include/IfcUnit.h>
#include <ifcpp/IFC4/include/IfcBoolean.h>
#include <ifcpp/IFC4/include/IfcInteger.h>
#include <ifcpp/IFC4/include/IfcReal.h>
#include <ifcpp/IFC4/include/IfcLengthMeasure.h>
#include <ifcpp/IFC4/include/IfcAreaMeasure.h>
#include <ifcpp/IFC4/include/IfcComplexNumber.h>
#include <ifcpp/IFC4/include/IfcContextDependentMeasure.h>
#include <ifcpp/IFC4/include/IfcCountMeasure.h>
#include <ifcpp/IFC4/include/IfcDescriptiveMeasure.h>
#include <ifcpp/IFC4/include/IfcElectricCurrentMeasure.h>
#include <ifcpp/IFC4/include/IfcLengthMeasure.h>
#include <ifcpp/IFC4/include/IfcLuminousIntensityMeasure.h>
#include <ifcpp/IFC4/include/IfcMassMeasure.h>
#include <ifcpp/IFC4/include/IfcAmountOfSubstanceMeasure.h>
#include <ifcpp/IFC4/include/IfcNonNegativeLengthMeasure.h>
#include <ifcpp/IFC4/include/IfcNormalisedRatioMeasure.h>
#include <ifcpp/IFC4/include/IfcNumericMeasure.h>
#include <ifcpp/IFC4/include/IfcParameterValue.h>
#include <ifcpp/IFC4/include/IfcPlaneAngleMeasure.h>
#include <ifcpp/IFC4/include/IfcPositiveLengthMeasure.h>
#include <ifcpp/IFC4/include/IfcPositivePlaneAngleMeasure.h>
#include <ifcpp/IFC4/include/IfcPositiveRatioMeasure.h>
#include <ifcpp/IFC4/include/IfcRatioMeasure.h>
#include <ifcpp/IFC4/include/IfcSolidAngleMeasure.h>
#include <ifcpp/IFC4/include/IfcThermodynamicTemperatureMeasure.h>
#include <ifcpp/IFC4/include/IfcTimeMeasure.h>
#include <ifcpp/IFC4/include/IfcVolumeMeasure.h>
#include <ifcpp/IFC4/include/IfcText.h>
#include <ifcpp/IFC4/include/IfcRelAssociates.h>
#include <ifcpp/IFC4/include/IfcRelAssociatesMaterial.h>
#include <ifcpp/IFC4/include/IfcRelDefinesByProperties.h>
#include <ifcpp/IFC4/include/IfcPropertySet.h>
#include <ifcpp/IFC4/include/IfcProperty.h>
#include <ifcpp/IFC4/include/IfcPropertySingleValue.h>
#include <ifcpp/IFC4/include/IfcMaterialSelect.h>
#include <ifcpp/IFC4/include/IfcMaterial.h>
#include <ifcpp/IFC4/include/IfcMaterialLayerSetUsage.h>
#include <ifcpp/IFC4/include/IfcMaterialLayerSet.h>
#include <ifcpp/IFC4/include/IfcMaterialLayer.h>
#include <ifcpp/IFC4/include/IfcNonNegativeLengthMeasure.h>

namespace 
{ //Anonymous namespace. Thread safe.
	class DatabaseConfig {
	public:
		IfcReader::IfcReader* ifc_reader;
		SQLite::Database *db;
		DatabaseConfig(IfcReader::IfcReader* ifc_reader, SQLite::Database *db)
		{
			this->ifc_reader = ifc_reader;
			this->db = db;
		};
	};

	void HandleAssociationsInverse(DatabaseConfig dbc, shared_ptr<IfcProduct> ifc_product, int product_id);
	void HandleDefinesInverse(DatabaseConfig dbc, shared_ptr<IfcProduct> ifc_product, int product_id);
	int InsertPropertySet(DatabaseConfig dbc, int product_id, std::string name);
	void InsertProperty(DatabaseConfig dbc, int property_set_id, std::string name, std::string value);
	void InsertMaterial(DatabaseConfig dbc, int product_id, std::string name, double thickness, std::string layer_name);
	int GetLastInsertedProductId(DatabaseConfig dbc);
	int GetLastInsertedPropertySetId(DatabaseConfig dbc);

	void HandleProduct(DatabaseConfig dbc, shared_ptr<IfcProduct> ifc_product){
		std::wstring wguid = ifc_product->m_GlobalId->m_value;
		std::wstring wname = ifc_product->m_Name->m_value;
		std::wstring wdescription;
		if (ifc_product->m_Description)
			wdescription = ifc_product->m_Description->m_value;
		std::string	guid(wguid.begin(), wguid.end());
		std::string	name(wname.begin(), wname.end());
		std::string	description(wdescription.begin(), wdescription.end());

		SQLite::Statement query(*dbc.db, "INSERT INTO products VALUES(NULL, ?, ?, ?, ?, ?)");
		query.bind(1, dbc.ifc_reader->project_id);
		query.bind(2, guid);
		query.bind(3, name);
		query.bind(4, description);
		query.bind(5, ifc_product->className());

		int nb = query.exec();
		if (nb != 1) //If this did not insert 1 row, something went wrong..!
			std::cout << "ERROR ([IfcReader.Data.cpp]::HandleProduct): " << query.getQuery() << " returned " << nb << "(" << query.errmsg() << ")" << std::endl;

		int product_id = GetLastInsertedProductId(dbc);

		if (product_id != 0)
		{
			HandleAssociationsInverse(dbc, ifc_product, product_id);
			HandleDefinesInverse(dbc, ifc_product, product_id);
		}

		/*// also inverse attributes can be accessed:
		std::vector<weak_ptr<IfcRelAssigns> >& vec_has_assignments = ifc_product->m_HasAssignments_inverse;
		std::vector<weak_ptr<IfcRelNests> >& vec_nests = ifc_product->m_Nests_inverse;
		std::vector<weak_ptr<IfcRelNests> >& vec_is_nested_by = ifc_product->m_IsNestedBy_inverse;
		std::vector<weak_ptr<IfcRelDeclares> >& vec_has_context = ifc_product->m_HasContext_inverse;
		std::vector<weak_ptr<IfcRelAggregates> >& vec_is_decomposed = ifc_product->m_IsDecomposedBy_inverse;
		std::vector<weak_ptr<IfcRelAggregates> >& vec_decomposes = ifc_product->m_Decomposes_inverse;
		std::vector<weak_ptr<IfcRelAssociates> >& vec_has_associations = ifc_product->m_HasAssociations_inverse;
		//*/
	}

	/* Example of an IFC material association:
	#606= IFCMATERIAL('Leichtbeton');
	#756= IFCMATERIALLAYER(#606,0.3,.U.);
	#758= IFCMATERIALLAYERSET((#756),'Leichtbeton 300');
	#9791= IFCMATERIALLAYERSETUSAGE(#758,.AXIS2.,.NEGATIVE.,0.);
	#9880= IFCRELASSOCIATESMATERIAL('0SGYIDeQf6d84TJ9vXtUZL',#13,$,$,(#9806),#9791);
	#9806= IFCWALLSTANDARDCASE('16DNNqzfP2thtfaOflvsKA',#13,'Wand-Ext-ERDG-4',$,$,#9803,#9876,'A6C3DE63-3731-4F6A-94-7E-DE8A8295779F');
	*/
	void HandleMaterialAssociation(DatabaseConfig dbc, shared_ptr<IfcRelAssociatesMaterial> rel_mat, int product_id){
		if (rel_mat->m_RelatingMaterial->className() == "IfcMaterial")
		{
			shared_ptr<IfcMaterial> mat = dynamic_pointer_cast<IfcMaterial>(rel_mat->m_RelatingMaterial);
			std::string name = mat->m_Name ? IfcReader::w2str(mat->m_Name->m_value) : "";
			InsertMaterial(dbc, product_id, name, 0, "");
		}
		else if (rel_mat->m_RelatingMaterial->className() == "IfcMaterialLayerSetUsage")
		{
			shared_ptr<IfcMaterialLayerSetUsage> matlsu = dynamic_pointer_cast<IfcMaterialLayerSetUsage>(rel_mat->m_RelatingMaterial);
			shared_ptr<IfcMaterialLayerSet> matls = dynamic_pointer_cast<IfcMaterialLayerSet>(matlsu->m_ForLayerSet);
			std::string layer_name = matls->m_LayerSetName ? IfcReader::w2str(matls->m_LayerSetName->m_value) : "";
			std::vector<shared_ptr<IfcMaterialLayer> >::iterator it_mat;
			for (it_mat = matls->m_MaterialLayers.begin(); it_mat != matls->m_MaterialLayers.end(); ++it_mat)
			{
				shared_ptr<IfcMaterialLayer> mat(*it_mat);
				std::string name = mat->m_Material && mat->m_Material->m_Name ? IfcReader::w2str(mat->m_Material->m_Name->m_value) : "";
				double thickness = mat->m_LayerThickness ? mat->m_LayerThickness->m_value : 0;
				InsertMaterial(dbc, product_id, name, thickness, layer_name);
			}
		}
	}


	#define SEQ_FOR_EACH(D, ...)                                        \
		if(bool c = false) ; else                                       \
			for(boost::remove_reference<boost::function_traits<void(D)> \
					::arg1_type>::type _t[] = __VA_ARGS__;              \
				!c; c = true)                                           \
				BOOST_FOREACH(D, _t)

	std::wstring GetIfcValueAsWstr(shared_ptr<IfcValue> ifc_value){
		std::wstring val = L"";

		if (shared_ptr<IfcLabel> v = dynamic_pointer_cast<IfcLabel>(ifc_value))
			val = v->m_value;
#define CheckTypeWithCast(n) else if (shared_ptr<n> v = dynamic_pointer_cast<n>(ifc_value)) val = std::to_wstring(v->m_value);
#define CheckTypeWithoutCast(n) else if (shared_ptr<n> v = dynamic_pointer_cast<n>(ifc_value)) val = (v->m_value);
		CheckTypeWithCast(IfcReal)
		CheckTypeWithCast(IfcInteger)
		CheckTypeWithCast(IfcBoolean)
		CheckTypeWithCast(IfcAmountOfSubstanceMeasure)
		CheckTypeWithCast(IfcAreaMeasure)
		CheckTypeWithoutCast(IfcIdentifier)
		// CheckType(IfcComplexNumber) //TO-DO: Special case, how to serialize it in the Database ?
		CheckTypeWithCast(IfcContextDependentMeasure)
		CheckTypeWithCast(IfcCountMeasure)
		CheckTypeWithoutCast(IfcDescriptiveMeasure)
		CheckTypeWithCast(IfcElectricCurrentMeasure)
		CheckTypeWithCast(IfcLengthMeasure)
		CheckTypeWithCast(IfcLuminousIntensityMeasure)
		CheckTypeWithCast(IfcMassMeasure)
		CheckTypeWithCast(IfcNonNegativeLengthMeasure)
		CheckTypeWithCast(IfcNormalisedRatioMeasure)
		CheckTypeWithCast(IfcNumericMeasure)
		CheckTypeWithCast(IfcParameterValue)
		CheckTypeWithCast(IfcPlaneAngleMeasure)
		CheckTypeWithCast(IfcPositiveLengthMeasure)
		CheckTypeWithCast(IfcPositivePlaneAngleMeasure)
		CheckTypeWithCast(IfcPositiveRatioMeasure)
		CheckTypeWithCast(IfcRatioMeasure)
		CheckTypeWithCast(IfcSolidAngleMeasure)
		CheckTypeWithCast(IfcThermodynamicTemperatureMeasure)
		CheckTypeWithCast(IfcTimeMeasure)
		CheckTypeWithCast(IfcVolumeMeasure)
		else
			std::cout << "ERROR ([IfcReader.Data.cpp]::GetIfcValueAsWstr): Cannot find suitable conversion for " << ifc_value->className() << std::endl;
		return val;
	}

	/* Example of an IFC property set association:
	#57936= IFCPROPERTYSINGLEVALUE('Size',$,IFCLABEL('450x200'),$);
	#57943= IFCPROPERTYSET('1SzJxSRej5LuG_nXi1Xjz5',#52,'Dimensions',$,(#57936));
	#57945= IFCRELDEFINESBYPROPERTIES('0Hj$dmqfP5uQGhnaXCcumD',#52,$,$,(#57935),#57943);
	#57935= IFCFLOWTERMINAL('2g3pwqJVH2Q89NwiSLsb6V',#52,'M_Supply Diffuser - Sidewall:450 x 200:450 x 200:386293',$,'450 x 200',#57934,#57929,'386293');
	*/
	void HandlePropertySet(DatabaseConfig dbc, shared_ptr<IfcPropertySet> prop_set, int product_id){
		std::vector<shared_ptr<IfcProperty> >::iterator it;
		int prop_set_id = InsertPropertySet(dbc, product_id, IfcReader::w2str(prop_set->m_Name->m_value));
		for (it = prop_set->m_HasProperties.begin(); it != prop_set->m_HasProperties.end(); ++it)
		{
			shared_ptr<IfcProperty> prop(*it);
			if (shared_ptr<IfcPropertySingleValue> prop_single_value = dynamic_pointer_cast<IfcPropertySingleValue>(prop)) {
				std::wstring val = GetIfcValueAsWstr(prop_single_value->m_NominalValue);
				InsertProperty(dbc, prop_set_id, IfcReader::w2str(prop_single_value->m_Name->m_value), IfcReader::w2str(val));
			}
		}
	}

	void HandleAssociationsInverse(DatabaseConfig dbc, shared_ptr<IfcProduct> ifc_product, int product_id){
		std::vector<weak_ptr<IfcRelAssociates> >& vec_has_associations = ifc_product->m_HasAssociations_inverse;
		if (vec_has_associations.size() > 0){
			std::vector<weak_ptr<IfcRelAssociates> >::iterator it;
			for (it = vec_has_associations.begin(); it != vec_has_associations.end(); ++it)
			{
				shared_ptr<IfcRelAssociates> rel(*it);
				if (shared_ptr<IfcRelAssociatesMaterial> rel_mat = dynamic_pointer_cast<IfcRelAssociatesMaterial>(rel)) {
					HandleMaterialAssociation(dbc, rel_mat, product_id);
				}
			}
		}
	}

	void HandleDefinesInverse(DatabaseConfig dbc, shared_ptr<IfcProduct> ifc_product, int product_id){
		std::vector<weak_ptr<IfcRelDefinesByProperties> >& vec_defines = ifc_product->m_IsDefinedBy_inverse;
		if (vec_defines.size() > 0){
			std::vector<weak_ptr<IfcRelDefinesByProperties> >::iterator it;
			for (it = vec_defines.begin(); it != vec_defines.end(); ++it)
			{
				shared_ptr<IfcRelDefinesByProperties> rel_prop(*it);
				shared_ptr<IfcPropertySet> prop_set = dynamic_pointer_cast<IfcPropertySet>(rel_prop->m_RelatingPropertyDefinition);
				if (prop_set)
					HandlePropertySet(dbc, prop_set, product_id);
			}
		}
	}

	void InsertMaterial(DatabaseConfig dbc, int product_id, std::string name, double thickness, std::string layer_name){
		SQLite::Statement query(*dbc.db, "INSERT INTO materials VALUES(NULL, ?, ?, ?, ?)");
		query.bind(1, product_id);
		query.bind(2, name);
		query.bind(3, thickness);
		query.bind(4, layer_name);

		int nb = query.exec();
		if (nb != 1) //If this did not insert 1 row, something went wrong..!
			std::cout << "ERROR ([IfcReader.Data.cpp]::InsertMaterial): " << query.getQuery() << " returned " << nb << "(" << query.errmsg() << ")" << std::endl;
	}

	int InsertPropertySet(DatabaseConfig dbc, int product_id, std::string name){
		SQLite::Statement query(*dbc.db, "INSERT INTO property_set VALUES(NULL, ?, ?)");
		query.bind(1, product_id);
		query.bind(2, name);

		int nb = query.exec();
		if (nb != 1) //If this did not insert 1 row, something went wrong..!
			std::cout << "ERROR ([IfcReader.Data.cpp]::InsertPropertySet): " << query.getQuery() << " returned " << nb << "(" << query.errmsg() << ")" << std::endl;

		return GetLastInsertedPropertySetId(dbc);
	}

	void InsertProperty(DatabaseConfig dbc, int property_set_id, std::string name, std::string value){
		SQLite::Statement query(*dbc.db, "INSERT INTO property VALUES(NULL, ?, ?, ?)");
		query.bind(1, property_set_id);
		query.bind(2, name);
		query.bind(3, value);

		int nb = query.exec();
		if (nb != 1) //If this did not insert 1 row, something went wrong..!
			std::cout << "ERROR ([IfcReader.Data.cpp]::InsertProperty): " << query.getQuery() << " returned " << nb << "(" << query.errmsg() << ")" << std::endl;
	}

	int GetLastInsertedProductId(DatabaseConfig dbc){
		int product_id = 0;
		SQLite::Statement query(*dbc.db, "SELECT id FROM products ORDER BY id DESC LIMIT 1");
		if (query.executeStep())
			product_id = query.getColumn(0);
		return product_id;
	}

	int GetLastInsertedPropertySetId(DatabaseConfig dbc){
		int id = 0;
		SQLite::Statement query(*dbc.db, "SELECT id FROM property_set ORDER BY id DESC LIMIT 1");
		if (query.executeStep())
			id = query.getColumn(0);
		return id;
	}
}

namespace IfcReader
{
	void IfcReader::handleData(shared_ptr<IfcPPModel> ifc_model, std::string sqlite_db_path){
		const boost::unordered_map<int, shared_ptr<IfcPPEntity> >& map_ifc_entities = ifc_model->getMapIfcEntities();
		try
		{
			SQLite::Database db(sqlite_db_path, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
			SQLite::Transaction transaction(db);

			db.exec("CREATE TABLE IF NOT EXISTS products(id INTEGER PRIMARY KEY, project_id INTEGER, GUID TEXT, name TEXT, description TEXT, class_name TEXT)");
			db.exec("CREATE TABLE IF NOT EXISTS materials(id INTEGER PRIMARY KEY, product_id INTEGER, name TEXT, thickness REAL, layer_name TEXT)");
			db.exec("CREATE TABLE IF NOT EXISTS property_set(id INTEGER PRIMARY KEY, product_id INTEGER, name TEXT)");
			db.exec("CREATE TABLE IF NOT EXISTS property(id INTEGER PRIMARY KEY, property_set_id INTEGER, name TEXT, value TEXT)");

			DatabaseConfig dbc(this, &db);
			for (auto it = map_ifc_entities.begin(); it != map_ifc_entities.end(); ++it)
			{
				int entity_id = it->first;
				const shared_ptr<IfcPPEntity>& ifcpp_entity = it->second;
				shared_ptr<IfcProduct> ifc_product = dynamic_pointer_cast<IfcProduct>(ifcpp_entity);
				if (ifc_product)
				{
					if (ifc_product->m_GlobalId && ifc_product->m_Name)
					{
						HandleProduct(dbc, ifc_product);
					}
				}
			}

			transaction.commit(); // Don't forget to commit !
		}
		catch (std::exception& e)
		{
			std::wcout << "ERROR (IfcReader::handleData): " << e.what() << std::endl;
		}

	};
};