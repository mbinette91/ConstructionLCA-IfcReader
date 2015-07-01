/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com  - Copyright (C) 2011 Fabian Gerold
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/

#pragma once

#define _USE_MATH_DEFINES 
#include <math.h>
#include <ifcpp/model/IfcPPOpenMP.h>

#define GEOM_TOLERANCE  0.0000001
#ifdef _DEBUG
	#define HALF_SPACE_BOX_SIZE 100
#else
	#define HALF_SPACE_BOX_SIZE 100
#endif

//#define ROUND_IFC_COORDINATES
#ifdef ROUND_IFC_COORDINATES
	#define ROUND_IFC_COORDINATES_UP 100000.0
	#define ROUND_IFC_COORDINATES_DOWN 0.00001
#endif

//\brief Central class to hold settings that influence geometry processing.

class GeometrySettings
{
public:
	GeometrySettings()
	{
		m_num_vertices_per_circle_default = 14;
		m_num_vertices_per_circle = m_num_vertices_per_circle_default;
		m_min_num_vertices_per_arc = 6;
		m_show_text_literals = false;
		m_ignore_profile_radius = false;
		m_min_crease_angle = M_PI*0.05;

		//m_min_colinearity = 0.1;
		//m_min_delta_v = 1.0;
		//m_min_normal_angle = M_PI / 180.0;
		//m_min_length = 0.0002;
		//m_min_face_area = 1e-8;
	}

	// Number of discretization points per circle
	int getNumVerticesPerCircle() { return m_num_vertices_per_circle; }
	void setNumVerticesPerCircle( int num )
	{
#ifdef IFCPP_OPENMP
		ScopedLock lock( m_mutex_geom_settings );
#endif
		m_num_vertices_per_circle = num;
	}
	void resetNumVerticesPerCircle()
	{
#ifdef IFCPP_OPENMP
		ScopedLock lock( m_mutex_geom_settings );
#endif
		m_num_vertices_per_circle = m_num_vertices_per_circle_default;
	}

	// Minimum number of discretization points per arc
	int getMinNumVerticesPerArc() { return m_min_num_vertices_per_arc; }
	void resetMinNumVerticesPerArc()
	{
#ifdef IFCPP_OPENMP
		ScopedLock lock( m_mutex_geom_settings );
#endif
		m_min_num_vertices_per_arc = 6;
	}

	void setMinNumVerticesPerArc( int num )
	{
#ifdef IFCPP_OPENMP
		ScopedLock lock( m_mutex_geom_settings );
#endif
		m_min_num_vertices_per_arc = num;
	}

	bool isShowTextLiterals() { return m_show_text_literals; }
	bool isIgnoreProfileRadius() { return m_ignore_profile_radius; }
	void setIgnoreProfileRadius( bool ignore_radius )
	{
#ifdef IFCPP_OPENMP
		ScopedLock lock( m_mutex_geom_settings );
#endif
		m_ignore_profile_radius = ignore_radius;
	}

	double getMinCreaseAngle() { return m_min_crease_angle; }
	void setMinCreaseAngle( double min_crease )
	{
#ifdef IFCPP_OPENMP
		ScopedLock lock( m_mutex_geom_settings );
#endif
		m_min_crease_angle = min_crease;
	}

protected:
	int	m_num_vertices_per_circle;
	int m_num_vertices_per_circle_default;
	int m_min_num_vertices_per_arc;
	bool m_show_text_literals;
	bool m_ignore_profile_radius;
	
	/** if angle between two faces is smaller than m_min_crease_angle, the normals will be added and normalized.
	set to negative value to deactivate intermediate normals */
	double m_min_crease_angle;

	//double m_min_colinearity;
	//double m_min_delta_v;
	//double m_min_normal_angle;
	//double m_min_length;
	//double m_min_face_area;

#ifdef IFCPP_OPENMP
	Mutex m_mutex_geom_settings;
#endif
};
