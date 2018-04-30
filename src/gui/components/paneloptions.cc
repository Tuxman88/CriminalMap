# include "paneloptions.hh"

Gui::PanelOptions::PanelOptions ( void )
   : QGroupBox ()
{
   buildGui ();
   buildConnections ();
}

Gui::PanelOptions::~PanelOptions ( void )
{
}

void Gui::PanelOptions::buildGui ( void )
{
   setMinimumWidth ( 640 );
   setMaximumHeight ( 100 );
   setTitle ( "Options" );

   mMainLayout = new QVBoxLayout ( this );
   setLayout ( mMainLayout );

   mOptionsLayout = new QHBoxLayout ();
   mMainLayout->addStretch ();
   mMainLayout->addLayout ( mOptionsLayout );
   mMainLayout->addStretch ();

   mScanButton = new QPushButton ( "Scan sites" );
   mOptionsLayout->addStretch ();
   mOptionsLayout->addWidget ( mScanButton );
   mOptionsLayout->addStretch ();

   return;
}

void Gui::PanelOptions::buildConnections ( void )
{
   connect ( mScanButton , SIGNAL ( clicked () ) ,
             this        , SIGNAL ( scanSites () ) );

   return;
}
