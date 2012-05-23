#ifndef _GGS_CORE_SYSTEM_SHELL_SHORTCUT_H
#define _GGS_CORE_SYSTEM_SHELL_SHORTCUT_H

#include <Core/core_global.h>
#include <QtCore/QString>

namespace GGS{
  namespace Core {
    namespace System {
      namespace Shell {

        /*!
          \class ShortCut
        
          \brief ѕозвол€ет создавать и читать €рлыки.

          \code
              GGS::Core::System::Shell::ShortCut object;
              object.setDescription("The description");
              object.setPath("cmd.exe");
              object.save("c:\\cmd.lnk");
          \endcode 
        */
        class CORE_EXPORT ShortCut
        {
        public:

          /*!
            \enum ShowWindowCommand
          
            \sa http://msdn.microsoft.com/en-us/library/windows/desktop/bb761056(v=vs.85).aspx
          */
          enum ShowWindowCommand {
            Normal      = 1,
            Maximized   = 3,
            MinNoActive = 7
          };

          ShortCut();
          ~ShortCut();

          /*!
            \fn void ShortCut::setPath(const QString &path);
          
            \brief ”станавливает путь внутри €рлыка.
          
            \param path UTF16 строка с полным путЄм к файлу. 
          */
          void setPath(const QString &path);
          const QString &path() const;

          void setWorkingDirectory(const QString &workingDir);
          const QString &workingDirectory() const;

          void setArguments(const QString &args);
          const QString &arguments() const;

          void setDescription(const QString &description);
          const QString &description() const;

          void setShowCmd(ShowWindowCommand cmd);
          ShowWindowCommand showCmd() const; 

          void setIconLocation(const QString &iconLocation);
          const QString &iconLocation() const;

          void setIconIndex(int iconIndex);
          int iconIndex() const;

          bool save(const QString &pathToLnkFile);
          bool load(const QString &pathToLnkFile);

        private:
          bool internalSave(const QString &pathToLnkFile);
          bool internalLoad(const QString &pathToLnkFile);
          QString _path;
          QString _workingDir;
          QString _args;
          QString _description;
          ShowWindowCommand _cmd;
          QString _iconLocation;
          int _iconIndex;
        };
      }
    }
  }
}

#endif //_GGS_CORE_SYSTEM_SHELL_SHORTCUT_H