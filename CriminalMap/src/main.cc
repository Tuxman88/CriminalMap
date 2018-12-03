# include <QApplication>

# include "gui/gui.hh"

int main ( int argc , char** argv )
{
   QApplication application ( argc , argv );

   Gui::MainWindow main_window;
   main_window.show ();

   return ( application.exec () );
}
