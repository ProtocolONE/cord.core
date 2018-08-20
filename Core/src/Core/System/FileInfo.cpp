#include <Core/System/FileInfo.h>

#include <QtCore/QDebug>

namespace P1 {
  namespace Core {
    namespace System {

    FileInfo::FileInfo()
    {
    }

    FileInfo::~FileInfo()
    {
    }

    wchar_t* FileInfo::QStringToTCharBuffer(const QString& buffer)  
    { 
      wchar_t *toReturn = (wchar_t*)malloc((buffer.size() + 1) * sizeof(wchar_t));   

      if (buffer.length() != buffer.toWCharArray(toReturn)) { 
        delete toReturn; 
        return 0; 
      } 

      toReturn[buffer.length()] = L'\0';
      return toReturn; 
    }

    QString FileInfo::version(const QString& fileName)
    {
      int hiVersion;
      int loVersion;

      if (FileInfo::version(fileName, hiVersion, loVersion)) 
        return QString("%1.%2.%3.%4").arg(
            QString::number(HIWORD(hiVersion)), 
            QString::number(LOWORD(hiVersion)),
            QString::number(HIWORD(loVersion)), 
            QString::number(LOWORD(loVersion)));


      return QString();
    }

    bool FileInfo::version(const QString& fileName, int& hiVersion, int& loVersion)
    {
      DWORD dwSize = 0;
      BYTE* pbVersionInfo = 0;
      VS_FIXEDFILEINFO* pFileInfo = 0;
      UINT puLenFileInfo = 0;

      wchar_t* filePath = QStringToTCharBuffer(fileName);   

      dwSize = GetFileVersionInfoSize(filePath, 0);  
      if (dwSize == 0) {
        DEBUG_LOG << "Error : " << GetLastError();

        free(filePath);
        return false;
      }

      pbVersionInfo = new BYTE[dwSize];

      if (!GetFileVersionInfo(filePath, 0, dwSize, pbVersionInfo)) {
        DEBUG_LOG << "Error : " << GetLastError();
        free(filePath);

        delete[] pbVersionInfo;
        return false;
      }

      if (!VerQueryValue(pbVersionInfo, TEXT("\\"), (LPVOID*)&pFileInfo, &puLenFileInfo)) {
        DEBUG_LOG << "Error : " << GetLastError();
        free(filePath);

        delete[] pbVersionInfo;
        return false;
      }

     hiVersion = pFileInfo->dwFileVersionMS;
     loVersion = pFileInfo->dwFileVersionLS;

     delete[] pbVersionInfo;
     free(filePath);

     return true;
    }

    }
  }
}
