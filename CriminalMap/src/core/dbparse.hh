# ifndef DBPARSE_HH
# define DBPARSE_HH

# include <QString>
# include <QVector>

# include "../base/base.hh"

namespace Core
{
   bool DBParse ( const QString& filename ,
                  QVector< Base::Crime >& crimes );
}

# endif // DBPARSE_HH
