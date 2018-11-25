# ifndef PLUGINSVIEWER_HH_
# define PLUGINSVIEWER_HH_

# include <QComboBox>
# include <QDialog>
# include <QHBoxLayout>
# include <QGridLayout>
# include <QLabel>
# include <QPushButton>
# include <QVBoxLayout>
# include <QTextEdit>
# include <QVector>

# include "../base/plugin.hh"

namespace Gui
{
   class PluginsViewer : public QDialog
   {
      Q_OBJECT

      public:
         explicit PluginsViewer ( void );
         virtual ~PluginsViewer ( void );

         void clearPlugins ( void );
         void setPlugins ( QVector< Base::Plugin* >* plugins_list );

      signals:
         void scanPlugins ( void );

      private:
         void buildGui ( void );
         void buildConnections ( void );

      private slots:
         void pluginChanged ( const int& index );
         void runPlugin ( void );

      private:
         QVBoxLayout* mMainLayout;
         QHBoxLayout* mSearchLayout;
         QPushButton* mSearchButton;
         QHBoxLayout* mPluginsLayout;
         QComboBox* mPluginsCombobox;
         QPushButton* mRunButton;
         QGridLayout* mInfoLayout;
         QLabel* mNameTitle;
         QLabel* mNameValue;
         QLabel* mSourceTitle;
         QLabel* mSourceValue;
         QTextEdit* mConsoleOutput;
         QVector< Base::Plugin* >* mPluginsList;
   };
}

# endif
