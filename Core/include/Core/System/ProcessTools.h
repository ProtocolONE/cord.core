#pragma once

#include <Core/core_global.h>

#include <QtCore/QString>

#include <windows.h>

namespace P1 {
  namespace Core {
    namespace System {

      class CORE_EXPORT ProcessTools
      {
      private:
        ProcessTools() = default;
        ~ProcessTools() = default;

      public:
        static void killProcessTree(DWORD pid, UINT ec = 0);
      };
    }
  }
}