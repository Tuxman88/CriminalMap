# ifndef MAINCORE_HH
# define MAINCORE_HH

# include <QObject>

# include "sitesscanner.hh"

namespace Core
{
   class MainCore : public QObject
   {
      Q_OBJECT

      public:
         explicit MainCore ( void );
         virtual ~MainCore ( void );

      public slots:
         void scanSites ( void );

      private:
         Core::SitesScanner* mSitesScanner;
   };
}

# endif // MAINCORE_HH
