# include "pluginsmanager.hh"

# include <QCoreApplication>
# include <QDebug>
# include <QDir>
# include <QFileInfoList>
# include <QString>

Core::PluginsManager::PluginsManager ( void )
   : QObject () ,
     mPluginsList ( nullptr )
{
   mPluginsList = new QVector< Base::Plugin* > ();
}

Core::PluginsManager::~PluginsManager ( void )
{
   int size;
   size = mPluginsList->size ();

   for ( int i = 0; i < size; i++ )
   {
      delete mPluginsList->operator[] ( i );
      mPluginsList->operator[] ( i ) = nullptr;
   }

   mPluginsList->clear ();
   delete mPluginsList;
}

bool Core::PluginsManager::scanPlugins ( void )
{
   // Clean the current plugins.
   int size;
   size = mPluginsList->size ();

   for ( int i = 0; i < size; i++ )
   {
      delete mPluginsList->operator[] ( i );
      mPluginsList->operator[] ( i ) = nullptr;
   }

   mPluginsList->clear ();

   // Get my current path
   QString current_folder;
   current_folder = QCoreApplication::applicationDirPath ();

   if ( !current_folder.endsWith ( "/" ) )
   {
      current_folder += "/";
   }

   // Check if the "plugins" folder exists.
   QDir plugins_folder;
   plugins_folder.setPath ( current_folder + "plugins/" );

   if ( !plugins_folder.exists () )
   {
      qDebug () << "No plugins folder found.";

      return ( false );
   }

   // Ok, the folder exists. Iterate over its internal contents and get
   // the list of all its folder. Each one should be a plugin. However,
   // each plugin is in charge of validating itself.

   QFileInfoList plugins_folder_contents;
   plugins_folder_contents = plugins_folder.entryInfoList ( QDir::AllDirs | QDir::NoDotAndDotDot );

   // Iterate over the folder list, if any.
   foreach ( QFileInfo folder_info , plugins_folder_contents )
   {
      // Just to make sure that this think is a folder.
      if ( folder_info.isDir () )
      {
         Base::Plugin* plugin;
         plugin = new Base::Plugin ();

         plugin->setPath ( folder_info.absoluteFilePath () );

         // Is the plugin folder valid?
         if ( plugin->isValid () )
         {
            // Store it
            mPluginsList->append ( plugin );
         }
      }
   }

   return ( true );
}

QVector< Base::Plugin* >* Core::PluginsManager::pluginsList ( void )
{
   return ( mPluginsList );
}
