# include "sitesscanner.hh"

# include <QDebug>
# include <QDir>
# include <QFileInfoList>
# include <QFileInfo>
# include <QProcess>

Core::SitesScanner::SitesScanner ( void )
   : QObject ()
{
   mProcess = new QProcess ();

   connect ( mProcess , SIGNAL ( readyReadStandardOutput () ) ,
             this     , SLOT   ( standardOutputReady     () ) );

   connect ( mProcess , SIGNAL ( readyReadStandardError () ) ,
             this     , SLOT   ( errorOutputReady       () ) );
}

Core::SitesScanner::~SitesScanner ( void )
{
}

void Core::SitesScanner::scanSites ( void )
{
   qDebug () << "Scanning plugins.";

   QDir plugins_folder;
   plugins_folder.setPath ( "plugins/" );

   if ( !plugins_folder.exists () )
   {
      qDebug () << "Plugins folder not found.";

      return;
   }

   QFileInfoList entries;
   entries = plugins_folder.entryInfoList ();

   foreach ( QFileInfo entry , entries )
   {
      if ( entry.isDir () && !entry.baseName ().isEmpty () )
      {
         qDebug () << "Running plugin: " << entry.baseName ();

         mProcess->setWorkingDirectory ( QDir::currentPath () + "plugins/" + entry.baseName () );

         qDebug () << "Current path: " << mProcess->workingDirectory ();

         mProcess->start ( "bash" , QStringList () << "\"main.sh\"" );

         mProcess->waitForFinished ();
      }
   }

   return;
}

void Core::SitesScanner::standardOutputReady ( void )
{
   return;
}

void Core::SitesScanner::errorOutputReady ( void )
{
   return;
}
