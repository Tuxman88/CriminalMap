# ifndef PANELMAIN_HH_
# define PANELMAIN_HH_

# include <QWidget>
# include <QVBoxLayout>

# include "panelmap.hh"
# include "paneloptions.hh"

namespace Gui
{
   class PanelMain : public QWidget
   {
      Q_OBJECT

      public:
         explicit PanelMain ( void );
         virtual ~PanelMain ( void );

      signals:
         void scanSites ( void );

      private:
         void buildGui ( void );
         void buildConnections ( void );

      private:
         QVBoxLayout* mMainLayout;
         Gui::PanelMap* mPanelMap;
         Gui::PanelOptions* mPanelOptions;
   };
}

# endif
