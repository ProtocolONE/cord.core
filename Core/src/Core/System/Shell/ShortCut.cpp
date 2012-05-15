#include <Core/System/Shell/ShortCut.h>

#include <QtCore/QScopedPointer>
#include <QtCore/QDebug>

#include <windows.h>
#include <string>

#include <atlbase.h> 
#include <objidl.h>  //For IPersistFile
#include <shlobj.h>  //For IShellLink 

#define CHECK_HRESULT(f) { HRESULT res = f; if (res != S_OK) { qWarning() << __LINE__ << __FILE__ << "HRESULT: " << res; return false; } }

namespace GGS{
  namespace Core {
    namespace System {
      namespace Shell {
        ShortCut::ShortCut()
        {
        }

        ShortCut::~ShortCut()
        {
        }

        void ShortCut::setPath(const QString &path)
        {
          this->_path = path;
        }

        const QString & ShortCut::path() const
        {
          return this->_path;
        }

        void ShortCut::setWorkingDirectory(const QString &workingDir)
        {
          this->_workingDir = workingDir;
        }

        const QString & ShortCut::workingDirectory() const
        {
          return this->_workingDir;
        }

        void ShortCut::setArguments(const QString &args)
        {
          this->_args = args;
        }

        const QString & ShortCut::arguments() const
        {
          return this->_args;
        }

        void ShortCut::setDescription(const QString &description)
        {
          this->_description = description;
        }

        const QString & ShortCut::description() const
        {
          return this->_description;
        }

        void ShortCut::setShowCmd(ShowWindowCommand cmd)
        {
          this->_cmd = cmd;
        }

        GGS::Core::System::Shell::ShortCut::ShowWindowCommand ShortCut::showCmd() const
        {
          return this->_cmd;
        }

        void ShortCut::setIconLocation(const QString &iconLocation)
        {
          this->_iconLocation = iconLocation;
        }

        const QString & ShortCut::iconLocation() const
        {
          return this->_iconLocation;
        }

        void ShortCut::setIconIndex(int iconIndex)
        {
          this->_iconIndex = iconIndex;
        }

        int ShortCut::iconIndex() const
        {
          return this->_iconIndex;
        }

        bool ShortCut::save(const QString &pathToLnkFile)
        {
          //http://msdn.microsoft.com/en-us/library/windows/desktop/bb774955(v=vs.85).aspx
          if (this->_description.length() > INFOTIPSIZE) {
            qWarning()  << __LINE__ << __FILE__ << "Description to length";
            return false;
          }

          if (this->_path.length() > MAX_PATH) {
            qWarning()  << __LINE__ << __FILE__ << "Path to length";
            return false;
          }

          if (this->_iconIndex < 0) {
            qWarning()  << __LINE__ << __FILE__ << "Wrong icon index";
            return false;
          }

          if (FAILED(CoInitialize(NULL))) {
            qWarning()  << __LINE__ << __FILE__ << "Trying without CoInitialize";
            return this->internalSave(pathToLnkFile);
          }

          bool res = this->internalSave(pathToLnkFile);
          CoUninitialize();

          return res;
        }

        bool ShortCut::internalSave(const QString &pathToLnkFile)
        {
          CComPtr<IShellLink> pShellLink;    
          CHECK_HRESULT(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*) &pShellLink))
          CHECK_HRESULT(pShellLink->SetPath(reinterpret_cast<const wchar_t *>(this->_path.utf16()))) 
          CHECK_HRESULT(pShellLink->SetWorkingDirectory(reinterpret_cast<const wchar_t *>(this->_workingDir.utf16())))
          CHECK_HRESULT(pShellLink->SetArguments(reinterpret_cast<const wchar_t *>(this->_args.utf16())))
          CHECK_HRESULT(pShellLink->SetDescription(reinterpret_cast<const wchar_t *>(this->_description.utf16())))
          CHECK_HRESULT(pShellLink->SetShowCmd(static_cast<int>(this->_cmd)))

          LPCWSTR iconLocation = reinterpret_cast<const wchar_t *>(this->_iconLocation.utf16());
          CHECK_HRESULT(pShellLink->SetIconLocation(iconLocation, this->_iconIndex))

          CComPtr<IPersistFile> pPersistFile;          
          CHECK_HRESULT(pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*) &pPersistFile)) 
          
          //http://msdn.microsoft.com/en-us/library/windows/desktop/ms693701(v=vs.85).aspx
          CHECK_HRESULT(pPersistFile->Save(reinterpret_cast<const wchar_t *>(pathToLnkFile.utf16()), TRUE))
          return true;
        }

        bool ShortCut::load(const QString &pathToLnkFile)
        {
          if (FAILED(CoInitialize(NULL))) {
            qWarning()  << __LINE__ << __FILE__ << "Trying without CoInitialize";
            return this->internalLoad(pathToLnkFile);
          }

          bool res = this->internalLoad(pathToLnkFile);
          CoUninitialize();

          return res;
        }

        bool ShortCut::internalLoad(const QString &pathToLnkFile)
        {
          CComPtr<IShellLink> pShellLink;    
          CHECK_HRESULT(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*) &pShellLink))

          CComPtr<IPersistFile> pPersistFile;          
          CHECK_HRESULT(pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*) &pPersistFile)) 
          CHECK_HRESULT(pPersistFile->Load(reinterpret_cast<const wchar_t *>(pathToLnkFile.utf16()),STGM_READ))

          //»спользуем INFOTIPSIZE вместо MAX_PATH т.к. это максимально возможна€ строка при работе с €рлыком
          QScopedPointer<wchar_t> buffer(new wchar_t[INFOTIPSIZE]);

          CHECK_HRESULT(pShellLink->GetPath(static_cast<LPWSTR>(buffer.data()), INFOTIPSIZE, NULL, SLGP_RAWPATH))
          this->_path = QString::fromWCharArray(buffer.data());
                             
          CHECK_HRESULT(pShellLink->GetWorkingDirectory(static_cast<LPWSTR>(buffer.data()), INFOTIPSIZE))
          this->_workingDir = QString::fromWCharArray(buffer.data());
            
          CHECK_HRESULT(pShellLink->GetArguments(static_cast<LPWSTR>(buffer.data()), INFOTIPSIZE))
          this->_args = QString::fromWCharArray(buffer.data());

          CHECK_HRESULT(pShellLink->GetDescription(static_cast<LPWSTR>(buffer.data()), INFOTIPSIZE))
          this->_description = QString::fromWCharArray(buffer.data());

          int value = 0;  
          CHECK_HRESULT(pShellLink->GetShowCmd(&value))
          switch(value) {
            case 1: this->_cmd = Normal; break;
            case 3: this->_cmd = Maximized; break;
            case 7: this->_cmd = MinNoActive; break;
            default: 
              qWarning()  << __LINE__ << __FILE__ << value << "Wrong ShowCmd";
              return false;
          }
          
          CHECK_HRESULT(pShellLink->GetIconLocation(static_cast<LPWSTR>(buffer.data()), INFOTIPSIZE, &this->_iconIndex))
          this->_iconLocation = QString::fromWCharArray(buffer.data());

          return true;
        }
      }
    }
  }
}