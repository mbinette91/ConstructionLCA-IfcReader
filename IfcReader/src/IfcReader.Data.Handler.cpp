/*
* This file contains the function `handleData` which handles everything related to the persistance of useful information for later LCA computing.
* It is expected this is the module that is going to change the most often.
*/
#include "IfcReader.hpp"
#include "IfcReader.Data.Handler.hpp"

#include <ifcpp/model/IfcPPModel.h>
#include <ifcpp/IFC4/include/IfcProduct.h>
#include <ifcpp/IFC4/include/IfcPropertySet.h>
#include <ifcpp/IFC4/include/IfcRelDefinesByProperties.h>
#include <ifcpp/IFC4/include/IfcRelAssociatesMaterial.h>
#include <ifcpp/IFC4/include/IfcMaterialLayerSetUsage.h>
#include <ifcpp/IFC4/include/IfcMaterialLayerSet.h>
#include <ifcpp/IFC4/include/IfcMaterialLayer.h>
#include <ifcpp/IFC4/include/IfcMaterial.h>
#include <ifcpp/IFC4/include/IfcPropertySingleValue.h>

namespace IfcReader
{
	void DataHandler::setProjectId(int project_id) {
		this->project_id = project_id;
	}

	void DataHandler::handleModel(shared_ptr<IfcPPModel> ifc_model){
		const boost::unordered_map<int, shared_ptr<IfcPPEntity> >& map_ifc_entities = ifc_model->getMapIfcEntities();
		for (auto it = map_ifc_entities.begin(); it != map_ifc_entities.end(); ++it)
		{
			int entity_id = it->first;
			const shared_ptr<IfcPPEntity>& ifcpp_entity = it->second;
			shared_ptr<IfcProduct> ifc_product = dynamic_pointer_cast<IfcProduct>(ifcpp_entity);
			if (ifc_product)
			{
				if (ifc_product->m_GlobalId && ifc_product->m_Name)
				{
					int product_id = handleProduct(ifc_product);

					if (product_id != 0)
					{
						handleAssociationsInverse(product_id, ifc_product);
						handleDefinesInverse(product_id, ifc_product);
					}
				}
			}
		}
	}

	void DataHandler::handleAssociationsInverse(int product_id, shared_ptr<IfcProduct> ifc_product){
		std::vector<weak_ptr<IfcRelAssociates> >& vec_has_associations = ifc_product->m_HasAssociations_inverse;
		if (vec_has_associations.size() > 0){
			std::vector<weak_ptr<IfcRelAssociates> >::iterator it;
			for (it = vec_has_associations.begin(); it != vec_has_associations.end(); ++it)
			{
				shared_ptr<IfcRelAssociates> rel(*it);
				if (shared_ptr<IfcRelAssociatesMaterial> rel_mat = dynamic_pointer_cast<IfcRelAssociatesMaterial>(rel)) {
					handleMaterialAssociation(product_id, rel_mat);
				}
			}
		}
	}

	void DataHandler::handleDefinesInverse(int product_id, shared_ptr<IfcProduct> ifc_product){
		std::vector<weak_ptr<IfcRelDefinesByProperties> >& vec_defines = ifc_product->m_IsDefinedBy_inverse;
		if (vec_defines.size() > 0){
			std::vector<weak_ptr<IfcRelDefinesByProperties> >::iterator it;
			for (it = vec_defines.begin(); it != vec_defines.end(); ++it)
			{
				shared_ptr<IfcRelDefinesByProperties> rel_prop(*it);
				shared_ptr<IfcPropertySet> prop_set = dynamic_pointer_cast<IfcPropertySet>(rel_prop->m_RelatingPropertyDefinition);
				if (prop_set)
					handlePropertySetRel(product_id, prop_set);
			}
		}
	}

	/* Example of an IFC material association:
	#606= IFCMATERIAL('Leichtbeton');
	#756= IFCMATERIALLAYER(#606,0.3,.U.);
	#758= IFCMATERIALLAYERSET((#756),'Leichtbeton 300');
	#9791= IFCMATERIALLAYERSETUSAGE(#758,.AXIS2.,.NEGATIVE.,0.);
	#9880= IFCRELASSOCIATESMATERIAL('0SGYIDeQf6d84TJ9vXtUZL',#13,$,$,(#9806),#9791);
	#9806= IFCWALLSTANDARDCASE('16DNNqzfP2thtfaOflvsKA',#13,'Wand-Ext-ERDG-4',$,$,#9803,#9876,'A6C3DE63-3731-4F6A-94-7E-DE8A8295779F');
	*/
	void DataHandler::handleMaterialAssociation(int product_id, shared_ptr<IfcRelAssociatesMaterial> rel_mat){
		if (rel_mat->m_RelatingMaterial->className() == "IfcMaterial")
		{
			shared_ptr<IfcMaterial> mat = dynamic_pointer_cast<IfcMaterial>(rel_mat->m_RelatingMaterial);
			handleMaterial(product_id, NULL, NULL, mat);
		}
		else if (rel_mat->m_RelatingMaterial->className() == "IfcMaterialLayerSetUsage")
		{
			shared_ptr<IfcMaterialLayerSetUsage> matlsu = dynamic_pointer_cast<IfcMaterialLayerSetUsage>(rel_mat->m_RelatingMaterial);
			shared_ptr<IfcMaterialLayerSet> matls = dynamic_pointer_cast<IfcMaterialLayerSet>(matlsu->m_ForLayerSet);
			std::vector<shared_ptr<IfcMaterialLayer> >::iterator it_mat;
			for (it_mat = matls->m_MaterialLayers.begin(); it_mat != matls->m_MaterialLayers.end(); ++it_mat)
			{
				shared_ptr<IfcMaterialLayer> matl(*it_mat);
				handleMaterial(product_id, matls, matl, matl->m_Material);
			}
		}
	}

	/* Example of an IFC property set association:
	#57936= IFCPROPERTYSINGLEVALUE('Size',$,IFCLABEL('450x200'),$);
	#57943= IFCPROPERTYSET('1SzJxSRej5LuG_nXi1Xjz5',#52,'Dimensions',$,(#57936));
	#57945= IFCRELDEFINESBYPROPERTIES('0Hj$dmqfP5uQGhnaXCcumD',#52,$,$,(#57935),#57943);
	#57935= IFCFLOWTERMINAL('2g3pwqJVH2Q89NwiSLsb6V',#52,'M_Supply Diffuser - Sidewall:450 x 200:450 x 200:386293',$,'450 x 200',#57934,#57929,'386293');
	*/
	void DataHandler::handlePropertySetRel(int product_id, shared_ptr<IfcPropertySet> prop_set){
		std::vector<shared_ptr<IfcProperty> >::iterator it;
		int prop_set_id = handlePropertySet(product_id, prop_set);
		for (it = prop_set->m_HasProperties.begin(); it != prop_set->m_HasProperties.end(); ++it)
		{
			shared_ptr<IfcProperty> prop(*it);
			if (shared_ptr<IfcPropertySingleValue> prop_single_value = dynamic_pointer_cast<IfcPropertySingleValue>(prop)) {
				handleProperty(prop_set_id, prop_single_value);
			}
		}
	}
}