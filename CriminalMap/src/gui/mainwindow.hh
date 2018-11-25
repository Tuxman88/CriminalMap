# ifndef MAINWINDOW_HH_
# define MAINWINDOW_HH_

# include <QMainWindow>

# include "pluginsviewer.hh"
# include "../core/pluginsmanager.hh"

namespace Gui
{
   class MainWindow : public QMainWindow
   {
      Q_OBJECT

      public:
         explicit MainWindow ( void );
         virtual ~MainWindow ( void );

      private slots:
         void scanPlugins ( void );

      private:
         void buildComponents ( void );
         void buildGui ( void );
         void buildConnections ( void );

      private:
         Gui::PluginsViewer* mPluginsViewer;
         Core::PluginsManager* mPluginsManager;
   };
}

# endif
