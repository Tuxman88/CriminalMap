# ifndef MAINPANEL_HH
# define MAINPANEL_HH

# include <QComboBox>
# include <QHBoxLayout>
# include <QLabel>
# include <QMap>
# include <QPushButton>
# include <QVBoxLayout>
# include <QVector>
# include <QWidget>

# include "../base/base.hh"

namespace Gui
{
   class MainPanel : public QWidget
   {
      Q_OBJECT

      public:
         explicit MainPanel ( void );
         virtual ~MainPanel ( void );

      private:
         void buildConnections ( void );
         void buildGui ( void );

      private slots:
         void dumpData ( void );
         void selectDBFile ( void );

      private:
         QVBoxLayout* mMainLayout;

         QHBoxLayout* mLoadLayout;
         QComboBox* mAreaCombo;
         QPushButton* mLoadButton;

         QHBoxLayout* mProblemLayout;
         QLabel* mCrimeLabel;
         QComboBox* mCrimeCombo;

         QVector< Base::Crime > mCrimes;
         // STATE
         //    - AREA
         //       - Date
         //          - Crime
         //             - Counter
         //
         //    STATE           AREA            Date            Crime     Counter
         QMap< QString , QMap< QString , QMap< QString , QMap< QString , int > > > > mFinalCrimes;
   };
}

# endif // MAINPANEL_HH
