#include <Core/System/ProcessTools.h>

#include <QtCore/QDebug>

#include <TlHelp32.h>

namespace P1 {
  namespace Core {
    namespace System {

      void ProcessTools::killProcessTree(DWORD pid, UINT ec)
      {
        PROCESSENTRY32 pe;

        memset(&pe, 0, sizeof(PROCESSENTRY32));
        pe.dwSize = sizeof(PROCESSENTRY32);

        HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (::Process32First(hProcessSnap, &pe)) {
          do // Recursion
          {
            if (pe.th32ParentProcessID == pid)
              killProcessTree(pe.th32ProcessID);
          } while (::Process32Next(hProcessSnap, &pe));
        }

        ::CloseHandle(hProcessSnap);

        // kill the main process
        HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, false, pid);

        if (hProcess && hProcess != INVALID_HANDLE_VALUE) {
          ::TerminateProcess(hProcess, ec);
          ::CloseHandle(hProcess);
        }
      }
    }
  }
}
