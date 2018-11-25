# ifndef PLUGINSMANAGER_HH_
# define PLUGINSMANAGER_HH_

# include <QObject>
# include <QVector>

# include "../base/plugin.hh"

namespace Core
{
   class PluginsManager : public QObject
   {
      Q_OBJECT

      public:
         explicit PluginsManager ( void );
         virtual ~PluginsManager ( void );

         QVector< Base::Plugin* >* pluginsList ( void );
         bool scanPlugins ( void );

      private:
         QVector< Base::Plugin* >* mPluginsList;
   };
}

# endif
