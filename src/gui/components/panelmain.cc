# include "panelmain.hh"

Gui::PanelMain::PanelMain ( void )
   : QWidget ()
{
   buildGui ();
   buildConnections ();
}

Gui::PanelMain::~PanelMain ( void )
{
}

void Gui::PanelMain::buildGui ( void )
{
   mMainLayout = new QVBoxLayout ( this );
   setLayout ( mMainLayout );

   mPanelMap = new Gui::PanelMap ();
   mMainLayout->addWidget ( mPanelMap );

   mPanelOptions = new Gui::PanelOptions ();
   mMainLayout->addWidget ( mPanelOptions );

   return;
}

void Gui::PanelMain::buildConnections ( void )
{
   connect ( mPanelOptions , SIGNAL ( scanSites () ) ,
             this          , SIGNAL ( scanSites () ) );

   return;
}
