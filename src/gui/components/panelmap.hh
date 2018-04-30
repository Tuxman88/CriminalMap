# ifndef PANELMAP_HH_
# define PANELMAP_HH_

# include <QGroupBox>

namespace Gui
{
   class PanelMap : public QGroupBox
   {
      Q_OBJECT

      public:
         explicit PanelMap ( void );
         virtual ~PanelMap ( void );

      private:
         void buildGui ( void );
   };
}

# endif // PANELMAP_HH
