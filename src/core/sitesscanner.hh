# ifndef SITESSCANNER_HH
# define SITESSCANNER_HH

# include <QObject>
# include <QProcess>

namespace Core
{
   class SitesScanner : public QObject
   {
      Q_OBJECT

      public:
         explicit SitesScanner ( void );
         virtual ~SitesScanner ( void );

         void scanSites ( void );

      private slots:
         void standardOutputReady ( void );
         void errorOutputReady ( void );

      private:
         QProcess* mProcess;
   };
}

# endif // SITESSCANNER_HH
