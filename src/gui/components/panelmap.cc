# include "panelmap.hh"

Gui::PanelMap::PanelMap ( void )
   : QGroupBox ()
{
   buildGui ();
}

Gui::PanelMap::~PanelMap ( void )
{
}

void Gui::PanelMap::buildGui ( void )
{
   setMinimumSize ( 640 , 480 );

   setTitle ( "Map" );

   return;
}
