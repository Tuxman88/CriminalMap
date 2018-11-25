# include <QApplication>

# include "src/gui/mainwindow.hh"

int main ( int argc , char* argv[] )
{
   QApplication a(argc, argv);

   Gui::MainWindow main_window;
   main_window.show ();

   return a.exec();
}
