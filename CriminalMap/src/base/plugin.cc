# include "plugin.hh"

# include <QDebug>
# include <QFile>
# include <QTextStream>

Base::Plugin::Plugin ( void )
   : QObject ()
{
   connect ( &mScriptRunner , SIGNAL ( readyReadStandardOutput () ) ,
             this           , SLOT   ( fetchOutput () ) );
}

Base::Plugin::~Plugin ( void )
{
}

QString Base::Plugin::name ( void ) const
{
   return ( mName );
}

QString Base::Plugin::source ( void ) const
{
   return ( mSource );
}

void Base::Plugin::setPath ( const QString& path )
{
   mContentFolder = path;

   if ( !mContentFolder.endsWith ( "/" ) )
   {
      mContentFolder += "/";
   }

   return;
}

bool Base::Plugin::isValid ( void )
{
   // To be valid, I need to confirm that there is a script file there,
   // and an info file.

   // The file name differs depending on the OS.
# if defined ( Q_OS_WIN )
   mScriptFilePath = mContentFolder + "main.bat";
# else
   mScriptFilePath = mContentFolder + "main.sh";
# endif

   mInfoFilePath = mContentFolder + "info.txt";

   // Exists the script?
   QFile validator;
   validator.setFileName ( mScriptFilePath );

   if ( !validator.exists () )
   {
      qDebug () << "Script file not found: " << mScriptFilePath;

      return ( false );
   }

   // Does the info file exists?
   validator.setFileName ( mInfoFilePath );

   if ( !validator.exists () )
   {
      qDebug () << "Info file not found: " << mInfoFilePath;
      return ( false );
   }

   // Both files exists, try to load the info file.

   return ( loadInfoFile () );
}

bool Base::Plugin::loadInfoFile ( void )
{
   QFile info_file;
   info_file.setFileName ( mInfoFilePath );

   if ( !info_file.open ( QIODevice::ReadOnly ) )
   {
      qDebug () << "Can't open info file: " << mInfoFilePath;

      return ( false );
   }

   QTextStream input_stream ( &info_file );

   while ( !input_stream.atEnd () )
   {
      QString line;
      line = input_stream.readLine ();

      parseInfoLine ( line );
   }

   return ( true );
}

void Base::Plugin::parseInfoLine ( const QString& line )
{
   // Remove whitespaces at the beggining and end
   QString tmp;
   tmp = line.trimmed ();

   if ( tmp.isEmpty () )
   {
      // The line is empty, so, ignore it.

      return;
   }

   // Try to aplit the string using an equal char
   QStringList pieces;
   pieces = tmp.split ( "=" );

   // There must be 2 pieces. If more or less elements, ignore the line.
   if ( pieces.size () != 2 )
   {
      return;
   }

   // First element is a key, the second is the value. Make the first uppercase.
   QString key;
   key = pieces[ 0 ].toUpper ();

   if ( key == "NAME" )
   {
      mName = pieces[ 1 ];
   }
   else if ( key == "SOURCE" )
   {
      mSource = pieces[ 1 ];
   }

   return;
}

bool Base::Plugin::isRunning ( void ) const
{
   return ( mScriptRunner.state () != QProcess::NotRunning );
}

QVector< QString >* Base::Plugin::consoleOutput ( void ) const
{
   return ( mConsoleOutput );
}

void Base::Plugin::start ( void )
{
   // Prepare final run command
# if defined ( Q_OS_WIN )
   QString command;
   QStringList arguments;

   command = "cmd";
   arguments << QString ( "\"%1\"" ).arg ( mScriptFilePath );

   mScriptRunner.startDetached ( command , arguments );
# else
   mScriptRunner.startDetached ( mScriptFilePath );
# endif

   return;
}

void Base::Plugin::fetchOutput ( void )
{


   return;
}
