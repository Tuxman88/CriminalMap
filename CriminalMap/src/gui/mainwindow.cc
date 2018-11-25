# include "mainwindow.hh"

# include <QMessageBox>

Gui::MainWindow::MainWindow ( void )
   : QMainWindow () ,
     mPluginsViewer ( nullptr ) ,
     mPluginsManager ( nullptr )
{
   buildComponents ();
   buildGui ();
   buildConnections ();
}

Gui::MainWindow::~MainWindow ( void )
{
}

void Gui::MainWindow::buildComponents ( void )
{
   mPluginsManager = new Core::PluginsManager ();

   return;
}

void Gui::MainWindow::buildGui ( void )
{
   mPluginsViewer = new Gui::PluginsViewer ();

   mPluginsViewer->show ();

   // Set myself a title
   setWindowTitle ( "Criminal Map" );

   return;
}

void Gui::MainWindow::buildConnections ( void )
{
   connect ( mPluginsViewer , SIGNAL ( scanPlugins () ) ,
             this           , SLOT   ( scanPlugins () ) );

   return;
}

void Gui::MainWindow::scanPlugins ( void )
{
   mPluginsViewer->clearPlugins ();

   if ( mPluginsManager->scanPlugins () )
   {
      mPluginsViewer->setPlugins ( mPluginsManager->pluginsList () );

      QMessageBox::information ( this , "Scan process results" , "Plugins found added to list." );
   }
   else
   {
      QMessageBox::warning ( this , "Scan process results" , "None plugin found." );
   }

   return;
}
