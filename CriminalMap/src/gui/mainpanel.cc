# include "mainpanel.hh"

# include <QDebug>
# include <QFileDialog>

# include "../core/core.hh"

Gui::MainPanel::MainPanel ( void )
   : QWidget ()
{
   buildGui ();
   buildConnections ();
}

Gui::MainPanel::~MainPanel ( void )
{
}

void Gui::MainPanel::buildConnections ( void )
{
   connect ( mLoadButton , SIGNAL ( clicked () ) ,
             this        , SLOT   ( selectDBFile () ) );

   return;
}

void Gui::MainPanel::buildGui ( void )
{
   /*
    * The panel is expected to display the whole application window. The base
    * design is as follows:
    *
    * -------------------------------------------------
    * | < Area name > [Load]                          |
    * |                                               |
    * | ############################################# |
    * | ############################################# |
    * | ############################################# |
    * | ############################################# |
    * |                                               |
    * | Problem: < ROBO >                             |
    * -------------------------------------------------
    */

   mMainLayout = new QVBoxLayout ( this );
   setLayout ( mMainLayout );

   mLoadLayout = new QHBoxLayout ();
   mMainLayout->addLayout ( mLoadLayout );

   mAreaCombo = new QComboBox ();
   mAreaCombo->setEnabled ( false );
   mLoadLayout->addWidget ( mAreaCombo );

   mLoadButton = new QPushButton ( "Load DB" );
   mLoadLayout->addWidget ( mLoadButton );
   mLoadLayout->addStretch ();

   mProblemLayout = new QHBoxLayout ();
   mMainLayout->addLayout ( mProblemLayout );

   mCrimeLabel = new QLabel ( "Crime:" );
   mProblemLayout->addWidget ( mCrimeLabel );

   mCrimeCombo = new QComboBox ();
   mCrimeCombo->setEnabled ( false );
   mProblemLayout->addWidget ( mCrimeCombo );
   mProblemLayout->addStretch ();

   return;
}

void Gui::MainPanel::selectDBFile ( void )
{
   QString filename;

   filename = QFileDialog::getOpenFileName ( this ,
                                             "Open DB file" );

   if ( Core::DBParse ( filename , mCrimes ) )
   {
      mFinalCrimes.clear ();
      qDebug () << "DB entries loaded: " << mCrimes.size ();

      // Process the list
      //      STATE           AREA            Date            Crime     Counter
      //QMap< QString , QMap< QString , QMap< QString , QMap< QString , int > > > > mFinalCrimes;
      int size;
      size = mCrimes.size ();

      for ( int i = 0; i < size; i++ )
      {
         QString state;
         QString area;
         QString date;

         state = mCrimes.at ( i ).State;
         area = mCrimes.at ( i ).Area;
         date = mCrimes.at ( i ).Timestamp.left ( 10 ); // 2018-11-09

         int events_size;
         events_size = mCrimes.at ( i ).Cases.size ();

         for ( int j = 0; j < events_size; j++ )
         {
            QString event;
            event = mCrimes.at ( i ).Cases.at ( j );

            if ( !event.isEmpty () )
            {
               // Add or increase
               if ( mFinalCrimes[ state ][ area ][ date ].contains ( event ) )
               {
                  mFinalCrimes[ state ][ area ][ date ][ event ]++;
               }
               else
               {
                  mFinalCrimes[ state ][ area ][ date ][ event ] = 1;
               }
            }
         }
      }

      dumpData ();
   }
   else
   {
      qDebug () << "Can't load DB file.";
   }

   return;
}

void Gui::MainPanel::dumpData ( void )
{
   //      STATE           AREA            Date            Crime     Counter
   //QMap< QString , QMap< QString , QMap< QString , QMap< QString , int > > > > mFinalCrimes;

   QList< QString > states;
   states = mFinalCrimes.keys ();

   foreach ( QString state , states )
   {
      qDebug () << "- " << state;

      QList< QString > areas;
      areas = mFinalCrimes[ state ].keys ();

      foreach ( QString area , areas )
      {
         qDebug () << "\t- " << area;

         QList< QString > dates;
         dates = mFinalCrimes[ state ][ area ].keys ();

         foreach ( QString date , dates )
         {
            qDebug () << "\t\t- " << date;

            QList< QString > crimes;
            crimes = mFinalCrimes[ state ][ area ][ date ].keys ();

            foreach ( QString crime , crimes )
            {
               qDebug () << "\t\t\t- " << crime << ": " << mFinalCrimes[ state ][ area ][ date ][ crime ];
            }
         }
      }
   }

   return;
}
