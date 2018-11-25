# ifndef PLUGIN_HH_
# define PLUGIN_HH_

# include <QObject>
# include <QProcess>
# include <QString>
# include <QVector>

namespace Base
{
   class Plugin : public QObject
   {
      Q_OBJECT

      public:
         explicit Plugin ( void );
         virtual ~Plugin ( void );

         QString name ( void ) const;
         QString source ( void ) const;
         bool isRunning ( void ) const;
         QVector< QString >* consoleOutput ( void ) const;
         void start ( void );

         void setPath ( const QString& path );
         bool isValid ( void );

      signals:
         void outputUpdated ( QVector< QString >* output );

      private:
         bool loadInfoFile ( void );
         void parseInfoLine ( const QString& line );

      private slots:
         void fetchOutput ( void );

      private:
         QString mContentFolder;
         QString mScriptFilePath;
         QString mInfoFilePath;
         QString mName;
         QString mSource;
         QProcess mScriptRunner;
         QVector< QString >* mConsoleOutput;
   };
}

# endif
