/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#pragma once
#include <Core/core_global>

#include <QtCore/QString>

#include <windows.h>

namespace GGS {
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