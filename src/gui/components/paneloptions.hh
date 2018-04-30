# ifndef PANELOPTIONS_HH
# define PANELOPTIONS_HH

# include <QGroupBox>
# include <QHBoxLayout>
# include <QPushButton>
# include <QVBoxLayout>

namespace Gui
{
   class PanelOptions : public QGroupBox
   {
      Q_OBJECT

      public:
         explicit PanelOptions ( void );
         virtual ~PanelOptions ( void );

      signals:
         void scanSites ( void );

      private:
         void buildGui ( void );
         void buildConnections ( void );

      private:
         QVBoxLayout* mMainLayout;
         QHBoxLayout* mOptionsLayout;
         QPushButton* mScanButton;
   };
}

# endif // PANELOPTIONS_HH
