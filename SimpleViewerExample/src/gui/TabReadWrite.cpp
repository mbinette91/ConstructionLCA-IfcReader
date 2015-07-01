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

#pragma warning( disable: 4996 )
#include <qevent.h>
#include <QSettings>
#include <QFileDialog>
#include <QFile>

#include <ifcpp/model/shared_ptr.h>
#include <ifcpp/model/IfcPPModel.h>
#include <ifcpp/model/IfcPPException.h>
#include <ifcpp/model/IfcPPGuid.h>
#include <ifcpp/model/StatusCallback.h>
#include <ifcpp/reader/IfcPPReaderSTEP.h>
#include <ifcpp/writer/IfcPPWriterSTEP.h>
#include <ifcppgeometry/GeometryConverter.h>
#include <ifcppgeometry/GeomUtils.h>

#include "IfcPlusPlusSystem.h"
#include "ViewController.h"
#include "viewer/ViewerWidget.h"
#include "viewer/OrbitCameraManipulator.h"
#include "cmd/LoadIfcFileCommand.h"
#include "cmd/CmdWriteIfcFile.h"
#include "cmd/CommandManager.h"
#include "TabReadWrite.h"


TabReadWrite::TabReadWrite( IfcPlusPlusSystem* sys, ViewerWidget* viewer, QWidget* parent ) : m_system(sys), m_viewer(viewer), QWidget( parent )
{
	QSettings settings(QSettings::UserScope, QLatin1String("IfcPlusPlus"));
	QStringList keys = settings.allKeys();
	
	if( keys.contains( "recentFiles" ) )
	{
		m_recent_files = settings.value("recentFiles").toStringList();
	}
	
	m_combo_recent_files = new QComboBox();
	m_combo_recent_files->setMaxVisibleItems( 40 );
	connect( m_combo_recent_files, SIGNAL(currentIndexChanged(int)),	this,	SLOT( slotRecentFilesIndexChanged(int) ) );

	m_btn_load = new QPushButton( "Load" );
	m_btn_load->setStyleSheet( "min-width: 30px;" );
	connect( m_btn_load, SIGNAL(clicked()),	this,	SLOT( slotLoadRecentIfcFileClicked() ) );
	
	updateRecentFilesCombo();


	QPushButton* btn_add_file = new QPushButton( "Choose file" );
	connect( btn_add_file, SIGNAL( clicked() ), this, SLOT( slotAddOtherIfcFileClicked() ) );

	// write
	m_le_path_write = new QLineEdit( "IfcPlusPlus-out.ifc" );
	QPushButton* btn_set_out_path = new QPushButton( "..." );
	connect( btn_set_out_path, SIGNAL( clicked() ), this, SLOT( slotSetWritePathClicked() ) );
	

	QString path_out;
	if( settings.contains( "pathIfcFileOut" ) )
	{
		path_out = settings.value("pathIfcFileOut").toString();
	}
	m_le_path_write->setText( path_out );
	QPushButton* btn_write_file = new QPushButton( "Write ifc file" );
	connect( btn_write_file, SIGNAL( clicked() ), this, SLOT( slotWriteFileClicked() ) );

	m_txt_out = new QTextEdit();

#ifdef _DEBUG
	std::stringstream uuid_strs;
	//for( int i=0; i<10; ++i )
	uuid_strs << createGUID32().c_str() << std::endl;
	uuid_strs << CreateCompressedGuidString22().c_str() << std::endl;

	m_txt_out->setText( uuid_strs.str().c_str() );
#endif

	m_progress_bar = new QProgressBar();
	m_progress_bar->setRange( 0, 1000 );

	// layout
	QHBoxLayout* combo_hbox = new QHBoxLayout();
	combo_hbox->addWidget( m_combo_recent_files, 1 );
	combo_hbox->addWidget( btn_add_file );
	combo_hbox->addWidget( m_btn_load, 0 );

	m_io_widget = new QWidget(this);
	QVBoxLayout* io_vbox = new QVBoxLayout(m_io_widget);
	io_vbox->setContentsMargins( 0, 0, 0, 0 );
	io_vbox->addWidget( new QLabel( "Read IFC file" ), 0 );
	io_vbox->addLayout( combo_hbox, 1 );
	io_vbox->addSpacing( 10 );
	io_vbox->addStretch( 1 );
	io_vbox->addWidget( m_progress_bar,	0 );

	m_io_splitter = new QSplitter( Qt::Horizontal );
	m_io_splitter->addWidget( m_io_widget );
	m_io_splitter->addWidget( m_txt_out );

	QHBoxLayout* hbox = new QHBoxLayout();
	hbox->addWidget( m_io_splitter );
	setLayout( hbox );

	if( keys.contains( "IOsplitterSizes" ) )
	{
		m_io_splitter->restoreState(settings.value("IOsplitterSizes").toByteArray());
	}
}

TabReadWrite::~TabReadWrite()
{
}

void TabReadWrite::closeEvent( QCloseEvent* )
{
	QSettings settings(QSettings::UserScope, QLatin1String("IfcPlusPlus"));
	settings.setValue("IOsplitterSizes", m_io_splitter->saveState());
}

void TabReadWrite::slotMessageWrapper( void* ptr, shared_ptr<StatusCallback::Message> m )
{
	TabReadWrite* myself = (TabReadWrite*)ptr;
	if( myself )
	{
#ifdef IFCPP_OPENMP
		ScopedLock lock( myself->m_mutex_messages );
#endif
		std::string reporting_function_str( m->m_reporting_function );
		std::wstringstream strs_report;
		if( reporting_function_str.size() > 0 )
		{
			strs_report << m->m_reporting_function << ", ";
		}
		strs_report << m->m_message_text.c_str();

		if( m->m_entity )
		{
			strs_report << ", IFC entity: #" << m->m_entity->m_id << "=" << m->m_entity->className();
		}
		std::wstring message_str = strs_report.str().c_str();

		if( m->m_message_type == StatusCallback::MESSAGE_TYPE_GENERAL_MESSAGE )
		{
			QString qt_str = QString::fromStdWString( message_str );
			myself->slotTxtOut( qt_str );
		}
		else if( m->m_message_type == StatusCallback::MESSAGE_TYPE_WARNING )
		{
			QString qt_str = QString::fromStdWString( message_str );
			myself->slotTxtOutWarning( qt_str );
		}
		else if( m->m_message_type == StatusCallback::MESSAGE_TYPE_ERROR )
		{
			QString qt_str = QString::fromStdWString( message_str );
			myself->slotTxtOutError( qt_str );
		}
		else if( m->m_message_type == StatusCallback::MESSAGE_TYPE_PROGRESS_VALUE )
		{
			myself->slotProgressValue( m->m_progress_value, m->m_progress_type );
		}
	}
}

void TabReadWrite::keyPressEvent( QKeyEvent* e )
{
	if( e->text() == "c" )
	{
		m_recent_files.clear();
		QSettings settings(QSettings::UserScope, QLatin1String("IfcPlusPlus"));
		settings.setValue("recentFiles",m_recent_files );
		updateRecentFilesCombo();
	}
}

void TabReadWrite::updateRecentFilesCombo()
{
	m_combo_recent_files->blockSignals( true );
	m_combo_recent_files->clear();
	foreach( QString path_recent_file, m_recent_files )
	{
		QFileInfo fi( path_recent_file );
		QString file_name = fi.fileName();
		m_combo_recent_files->addItem( file_name );
	}
	m_combo_recent_files->blockSignals( false );
}

void TabReadWrite::slotRecentFilesIndexChanged(int)
{
	slotProgressValue( 0, "" );
	m_btn_load->setFocus();
}

void TabReadWrite::slotLoadIfcFile( QString& path_in )
{
	// redirect message callbacks
	m_system->getGeometryConverter()->setMessageCallBack( this, &TabReadWrite::slotMessageWrapper );
	m_system->getIfcPPReader()->setMessageCallBack( this, &TabReadWrite::slotMessageWrapper );
	m_system->getIfcPPWriter()->setMessageCallBack( this, &TabReadWrite::slotMessageWrapper );
	

	slotTxtOut( QString( "loading file: " ) + path_in );
	QApplication::processEvents();
	clock_t millisecs = clock();
	m_system->notifyModelCleared();
	m_txt_out->clear();
	QSettings settings(QSettings::UserScope, QLatin1String("IfcPlusPlus"));

	if( !QFile::exists(path_in) )
	{
		slotTxtOutError( QString("file ") + path_in + QString(" does not exist\n") );

		// remove all non-existing files from recent files combo
		for( int i=0; i<m_recent_files.size(); )
		{
			QString recent_file = m_recent_files[i];
			if( !QFile::exists(recent_file) )
			{
				m_recent_files.takeAt( i );
			}
			else
			{
				++i;
			}
		}
		settings.setValue("recentFiles",m_recent_files );
		updateRecentFilesCombo();
		return;
	}
	else
	{
		// move to top of recent files list
		int i = m_recent_files.indexOf( path_in );
		if( i > 0 )
		{
			QString current_path = m_recent_files.takeAt( i );
			m_recent_files.insert( 0, current_path );
			m_recent_files.removeDuplicates();
			settings.setValue("recentFiles",m_recent_files );
			updateRecentFilesCombo();
		}
		else
		{
			m_recent_files.insert( 0, path_in );
			m_recent_files.removeDuplicates();
			settings.setValue("recentFiles",m_recent_files );
			updateRecentFilesCombo();
		}
	}

	try
	{
		shared_ptr<LoadIfcFileCommand> cmd_load( new LoadIfcFileCommand( m_system ) );
		std::wstring path_str = path_in.toStdWString();
		cmd_load->setFilePath( path_str );
		cmd_load->doCmd();
	}
	catch( IfcPPOutOfMemoryException& e)
	{
		slotTxtOutError( e.what() );
	}
	catch( IfcPPException& e )
	{
		slotTxtOutError( e.what() );
	}
	catch(std::exception& e)
	{
		slotTxtOutError( e.what() );
	}

	m_viewer->update();
	
	osgViewer::View* main_view = m_viewer->getMainView();
	if( main_view )
	{
		osgGA::CameraManipulator* camera_manip = main_view->getCameraManipulator();
		OrbitCameraManipulator* orbit_manip = dynamic_cast<OrbitCameraManipulator*>( camera_manip );
		if( orbit_manip )
		{
			osg::BoundingSphere bs = m_system->getViewController()->m_sw_model->computeBound();
			orbit_manip->zoomToBoundingSphere( bs );
		}
	}

	clock_t time_diff = clock() - millisecs;
	int num_entities = m_system->getGeometryConverter()->getIfcPPModel()->getMapIfcEntities().size();
	slotTxtOut( tr("File loaded: ") + QString::number(num_entities) + " entities in " + QString::number( round(time_diff*0.1)*0.01 ) + " sec."  );

	m_system->notifyModelLoadingDone();
	slotProgressValue( 1.0, "" );
}

void TabReadWrite::slotTxtOut( QString txt )
{
	m_txt_out->append( "<div style=\"color:black;\">" + txt.replace( "\n", "<br/>" ) + "</div><br/>" );
}

void TabReadWrite::slotTxtOutWarning( QString txt )
{
	m_txt_out->append( "<div style=\"color:#dca103;\">Warning: " + txt.replace( "\n", "<br/>" ) + "</div><br/>" );
}

void TabReadWrite::slotTxtOutError( QString txt )
{
	m_txt_out->append( "<div style=\"color:red;\">Error: " + txt.replace( "\n", "<br/>" ) + "</div><br/>" );
}

void TabReadWrite::slotProgressValue( double progress_value, const std::string& progress_type )
{
	if( progress_value >= 0.0 )
	{
		if( progress_type.compare( "parse" ) == 0 )
		{
			progress_value = progress_value*0.5;
		}
		else if( progress_type.compare( "geometry" ) == 0 )
		{
			progress_value = 0.5 + progress_value*0.5;
		}

		m_progress_bar->setValue( (int)( progress_value * 1000 ) );
		QApplication::processEvents();
	}
}

void TabReadWrite::slotLoadRecentIfcFileClicked()
{
	QPushButton* btn_load = (QPushButton*)sender();
	if( !btn_load )
	{
		return;
	}
	
	int row = m_combo_recent_files->currentIndex();
	if( row < 0 || row >= m_combo_recent_files->count() )
	{
		return;
	}
	
	m_io_widget->setDisabled( true );
	if( row < m_recent_files.size() )
	{
		QString file_name = m_recent_files.at( row );
		slotLoadIfcFile( file_name );
	}
	m_io_widget->setDisabled(false);
}

void TabReadWrite::slotClearRecentIfcFiles()
{
	m_recent_files.clear();
	QSettings settings(QSettings::UserScope, QLatin1String("IfcPlusPlus"));
	settings.setValue("recentFiles",m_recent_files );
	updateRecentFilesCombo();
}

void TabReadWrite::slotAddOtherIfcFileClicked()
{
	QSettings settings(QSettings::UserScope, QLatin1String("IfcPlusPlus"));
	QStringList keys = settings.allKeys();
	QString default_dir = "";
	if( keys.contains( "recentFiles" ) )
	{
		default_dir = settings.value( "defaultDir" ).toString();
	}
	QString selected_file = QFileDialog::getOpenFileName(this, "Choose IFC file", default_dir );
	
	if( !selected_file.isEmpty() )
	{
		QDir current_dir;
		settings.setValue( "defaultDir", current_dir.absoluteFilePath(selected_file) );
		slotLoadIfcFile( selected_file );
	}
}

void TabReadWrite::slotSetWritePathClicked()
{
	QString selectedFilter;
	QString fileName = QFileDialog::getSaveFileName(this, "IfcPlusPlus - choose path to write ifc file", m_le_path_write->text(), "All Files (*);;Text Files (*.ifc)", &selectedFilter);
	if( !fileName.isEmpty() )
	{
		m_le_path_write->setText(fileName);
	}
}

void TabReadWrite::slotWriteFileClicked()
{
	QString path = m_le_path_write->text();
	QSettings settings(QSettings::UserScope, QLatin1String("IfcPlusPlus"));
	settings.setValue("pathIfcFileOut", path );

	slotTxtOut( "writing file: " + path );
	int millisecs = clock();

	std::string path_std = path.toStdString();
	try
	{
		shared_ptr<CmdWriteIfcFile> cmd_write( new CmdWriteIfcFile( m_system ) );
		cmd_write->setFilePath( path_std );
		m_system->getCommandManager()->executeCommand( cmd_write );
		//m_system->writeIfcFile( path_std );
	}
	catch( std::exception& e )
	{
		slotTxtOutWarning( "couldn't write file " + path + e.what() );
	}
	
	int time_diff = clock() - millisecs;
	slotTxtOut( "file written (" + QString::number( time_diff*0.001 ) + " sec)" );
	slotProgressValue( 1.0, "" );
}
