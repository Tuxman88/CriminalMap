# ifndef CRIME_HH
# define CRIME_HH

# include <QString>
# include <QStringList>

namespace Base
{
   struct t_Crime
   {
      // The fields are based on the information of each line of a DB file:
      //
      // STATE,AREA,TIMESTAMP,ID,CASES,URL

      int ID;
      QString State;
      QString Area;
      QString Timestamp;
      QString URL;
      QStringList Cases;
   };
   typedef struct t_Crime Crime;
}

# endif // CRIME_HH
