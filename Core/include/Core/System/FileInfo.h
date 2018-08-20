#pragma once

#include <Core/core_global.h>

#include <QtCore/QString>

#include <Windows.h>

namespace P1 {
  namespace Core {
    namespace System {

      class CORE_EXPORT FileInfo
      {
      public:
        static QString version(const QString& fileName);
        static bool version(const QString& fileName, int& hiVersion, int& loVersion);

      private:
        FileInfo();
        ~FileInfo();

        static wchar_t* QStringToTCharBuffer(const QString& buffer);
      };
    }
  }
}