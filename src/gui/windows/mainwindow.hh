# ifndef MAINWINDOW_HH_
# define MAINWINDOW_HH_

# include <QMessageBox>
# include <QMainWindow>

# include "../components/panelmain.hh"

namespace Gui
{
   class MainWindow : public QMainWindow
   {
      Q_OBJECT

      public:
         explicit MainWindow ( void );
         virtual ~MainWindow ( void );

      signals:
         void scanSites ( void );

      private:
         void buildGui ( void );
         void buildConnections ( void );

      private slots:
         void notifyScanning ( void );

      private:
         Gui::PanelMain* mPanelMain;
         QMessageBox* mScanningDialog;
   };
}

# endif
