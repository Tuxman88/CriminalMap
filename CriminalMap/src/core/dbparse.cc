# include "dbparse.hh"

# include <QDebug>
# include <QFile>
# include <QTextStream>

bool Core::DBParse ( const QString& filename ,
                     QVector< Base::Crime >& crimes )
{
   crimes.clear ();

   QFile file;
   file.setFileName ( filename );

   if ( !file.exists () )
   {
      qDebug () << "File doesn't exist: " << filename;

      return ( false );
   }

   // Ok, open the file in read mode
   if ( !file.open ( QIODevice::ReadOnly ) )
   {
      qDebug () << "Can't open input file: " << filename;
      qDebug () << "Error: " << file.errorString ();

      return ( false );
   }

   // Set the file as input device for the strea, for reading line by line
   QTextStream input_stream ( &file );

   // Ok. The format I'm expecting to read is a file that contains a lot of lines.
   // Each line has this format:
   //
   // STATE,AREA,TIMESTAMP,ID,CASES,URL
   //
   // So, I'll load each line and create a map of maps, containing crime cases.

   while ( !input_stream.atEnd () )
   {
      QString line;
      line = input_stream.readLine ();

      // Trim the line and see if it is not empty. If empty, ignore the line
      line = line.trimmed ();

      if ( !line.isEmpty () )
      {
         QStringList pieces;
         pieces = line.split ( "," );

         // Are there 6 components?
         if ( pieces.size () == 6 )
         {
            Base::Crime crime;
            crime.State = pieces[ 0 ];
            crime.Area = pieces[ 1 ];
            crime.Timestamp = pieces[ 2 ];
            crime.ID = pieces[ 3 ].toInt ();
            crime.Cases = pieces[ 4 ].split ( ":" );
            crime.URL = pieces[ 5 ];

            crimes.append ( crime );
         }
      }
   }

   return ( true );
}
