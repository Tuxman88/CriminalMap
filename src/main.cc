# include <QApplication>

# include "gui/gui.hh"
# include "core/core.hh"

int main ( int argc , char *argv[] )
{
   QApplication application ( argc , argv );

   Gui::MainWindow main_window;
   main_window.show ();

   Core::MainCore main_core;

   QObject::connect ( &main_window , SIGNAL ( scanSites () ) ,
                      &main_core   , SLOT   ( scanSites () ) );

   return ( application.exec () );
}
