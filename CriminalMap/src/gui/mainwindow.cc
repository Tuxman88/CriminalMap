# include "mainwindow.hh"

Gui::MainWindow::MainWindow ( void )
   : QMainWindow ()
{
   buildGui ();
   buildConnections ();
}

Gui::MainWindow::~MainWindow ( void )
{
}

void Gui::MainWindow::buildConnections ( void )
{
   return;
}

void Gui::MainWindow::buildGui ( void )
{
   mMainPanel = new Gui::MainPanel ();
   setCentralWidget ( mMainPanel );

   return;
}
