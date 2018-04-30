# include "mainwindow.hh"

# include <QDebug>

Gui::MainWindow::MainWindow ( void )
   : QMainWindow () ,
     mScanningDialog ( nullptr )
{
   buildGui ();
   buildConnections ();
}

Gui::MainWindow::~MainWindow ( void )
{
}

void Gui::MainWindow::buildGui ( void )
{
   mPanelMain = new Gui::PanelMain ();
   setCentralWidget ( mPanelMain );

   return;
}

void Gui::MainWindow::buildConnections ( void )
{
   connect ( mPanelMain , SIGNAL ( scanSites () ) ,
             this       , SIGNAL ( scanSites () ) );

   connect ( mPanelMain , SIGNAL ( scanSites () ) ,
             this       , SLOT   ( notifyScanning () ) );

   return;
}

void Gui::MainWindow::notifyScanning ( void )
{
   if ( !mScanningDialog )
   {
      mScanningDialog = new QMessageBox ();
   }

   mScanningDialog->setWindowTitle ( "Scanning sites" );
   mScanningDialog->setText ( "Scanning sites. Please wait..." );
   mScanningDialog->show ();

   qDebug () << "Scanning sites";

   return;
}
