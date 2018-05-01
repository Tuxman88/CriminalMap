# include "maincore.hh"

# include <QDebug>

Core::MainCore::MainCore ( void )
   : QObject ()
{
   mSitesScanner = new Core::SitesScanner ();
}

Core::MainCore::~MainCore ( void )
{
   delete mSitesScanner;
}

void Core::MainCore::scanSites ( void )
{
   qDebug () << "Requested to scan sites.";

   mSitesScanner->scanSites ();

   return;
}
