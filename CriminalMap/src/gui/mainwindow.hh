# ifndef MAINWINDOW_HH
# define MAINWINDOW_HH

# include <QMainWindow>

# include "mainpanel.hh"

namespace Gui
{
   class MainWindow : public QMainWindow
   {
      Q_OBJECT

      public:
         explicit MainWindow ( void );
         virtual ~MainWindow ( void );

      private:
         void buildConnections ( void );
         void buildGui ( void );

      private:
         Gui::MainPanel* mMainPanel;
   };
}

# endif // MAINWINDOW_HH
