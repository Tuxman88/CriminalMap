# include "pluginsviewer.hh"

# include <QDebug>

Gui::PluginsViewer::PluginsViewer ( void )
   : QDialog () ,
     mMainLayout ( nullptr ) ,
     mSearchLayout ( nullptr ) ,
     mSearchButton ( nullptr ) ,
     mPluginsLayout ( nullptr ) ,
     mPluginsCombobox ( nullptr ) ,
     mRunButton ( nullptr ) ,
     mInfoLayout ( nullptr ) ,
     mNameTitle ( nullptr ) ,
     mNameValue ( nullptr ) ,
     mSourceTitle ( nullptr ) ,
     mSourceValue ( nullptr ) ,
     mConsoleOutput ( nullptr )
{
   buildGui ();
   buildConnections ();
}

Gui::PluginsViewer::~PluginsViewer ( void )
{
}

void Gui::PluginsViewer::buildGui ( void )
{
   /*
    * Basic design:
    *
    * |-----------------------------------------|
    * | [Search Plugins]                        |
    * |                                         |
    * | <Plugin Name> [Run]                     |
    * |                                         |
    * | Name:   *PluginName  *                  |
    * | Source: *PluginSource*                  |
    * |                                         |
    * | |-------------------------------------| |
    * | |                                     | |
    * | |                                     | |
    * | |                                     | |
    * | |                                     | |
    * | |                                     | |
    * | |                                     | |
    * | |                                     | |
    * | |-------------------------------------| |
    * |                                         |
    * |-----------------------------------------|
    */

   // Main layout for the components.
   mMainLayout = new QVBoxLayout ( this );
   setLayout ( mMainLayout );

   // Horizontal layout for the search button
   mSearchLayout = new QHBoxLayout ();
   mMainLayout->addLayout ( mSearchLayout );

   // Actual button, centered horizontally
   mSearchButton = new QPushButton ( "Search plugins" );
   mSearchLayout->addStretch ();
   mSearchLayout->addWidget ( mSearchButton );
   mSearchLayout->addStretch ();

   // Horizontal layout for the plugins list
   mPluginsLayout = new QHBoxLayout ();
   mMainLayout->addLayout ( mPluginsLayout );

   // Combobox and run button
   mPluginsCombobox = new QComboBox ();
   mRunButton = new QPushButton ( "Run" );
   mPluginsLayout->addWidget ( mPluginsCombobox );
   mPluginsLayout->addWidget ( mRunButton );
   mPluginsLayout->addStretch ();

   // Grid layout to add the values of the info
   mInfoLayout = new QGridLayout ();
   mMainLayout->addLayout ( mInfoLayout );

   // Info labels for the plugin
   mNameTitle = new QLabel ( "Name:" );
   mSourceTitle = new QLabel ( "Source:" );
   mNameValue = new QLabel ();
   mSourceValue = new QLabel ();
   mInfoLayout->addWidget ( mNameTitle   , 0 , 0 );
   mInfoLayout->addWidget ( mNameValue   , 0 , 1 );
   mInfoLayout->addWidget ( mSourceTitle , 1 , 0 );
   mInfoLayout->addWidget ( mSourceValue , 1 , 1 );

   // Console output area
   mConsoleOutput = new QTextEdit ();
   mMainLayout->addWidget ( mConsoleOutput );

   // Set myself a title
   setWindowTitle ( "Plugins viewer" );

   clearPlugins ();

   return;
}

void Gui::PluginsViewer::buildConnections ( void )
{
   connect ( mSearchButton , SIGNAL ( clicked () ) ,
             this          , SIGNAL ( scanPlugins () ) );

   connect ( mPluginsCombobox , SIGNAL ( currentIndexChanged ( int ) ) ,
             this             , SLOT   ( pluginChanged ( const int& ) ) );

   connect ( mRunButton , SIGNAL ( clicked () ) ,
             this       , SLOT   ( runPlugin () ) );

   return;
}

void Gui::PluginsViewer::clearPlugins ( void )
{
   mSearchButton->setText ( "Search plugins" );
   mSearchButton->setEnabled ( true );

   mRunButton->setText ( "Run" );
   mRunButton->setEnabled ( false );
   mPluginsCombobox->clear ();
   mPluginsCombobox->setEnabled ( false );

   mConsoleOutput->setText ( "" );

   return;
}

void Gui::PluginsViewer::setPlugins ( QVector< Base::Plugin* >* plugins_list )
{
   mPluginsList = plugins_list;

   // Iterate over the list of plugins and fill the combo with the names
   int size;
   size = mPluginsList->size ();

   for ( int i = 0; i < size; i++ )
   {
      mPluginsCombobox->addItem ( mPluginsList->at ( i )->name () );
   }

   // The list is empty?
   if ( size == 0 )
   {
      // Nothing to do.
      return;
   }

   // Select the first element of the combo
   mPluginsCombobox->setCurrentIndex ( 0 );

   pluginChanged ( 0 );

   return;
}

void Gui::PluginsViewer::pluginChanged ( const int& index )
{
   // Set the info of the element selected
   mNameValue->setText   ( mPluginsList->at ( index )->name () );
   mSourceValue->setText ( mPluginsList->at ( index )->source () );

   mPluginsCombobox->setEnabled ( true );

   // Is the current plugin running?
   if ( mPluginsList->at ( index )->isRunning () )
   {
      mRunButton->setEnabled ( false );
      mRunButton->setText ( "Running..." );
   }
   else
   {
      mRunButton->setEnabled ( true );
      mRunButton->setText ( "Run" );
   }

   return;
}

void Gui::PluginsViewer::runPlugin ( void )
{
   int index;
   index = mPluginsCombobox->currentIndex ();

   mPluginsList->at ( index )->start ();

   // Update UI
   pluginChanged ( index );

   return;
}
