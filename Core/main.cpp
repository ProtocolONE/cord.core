#include <Core/Service>
#include <Core/UI/Message>

#include <Windows.h>
#include <QtCore/QMetaType>

void registerTypes()
{
  qRegisterMetaType<GGS::Core::Service>("GGS::Core::Service");
  qRegisterMetaType<GGS::Core::UI::Message::StandardButtons>("GGS::Core::UI::Message::StandardButtons");
  qRegisterMetaType<GGS::Core::UI::Message::Icon>("GGS::Core::UI::Message::Icon");
}

BOOL WINAPI DllMain(
  HINSTANCE hinstDLL,  // handle to DLL module
  DWORD fdwReason,     // reason for calling function
  LPVOID lpReserved )  // reserved
{
  // Perform actions based on the reason for calling.
  switch( fdwReason ) 
  { 
  case DLL_PROCESS_ATTACH:
    // Initialize once for each new process.
    // Return FALSE to fail DLL load.
    registerTypes();
    break;

  case DLL_THREAD_ATTACH:
    // Do thread-specific initialization.
    break;

  case DLL_THREAD_DETACH:
    // Do thread-specific cleanup.
    break;

  case DLL_PROCESS_DETACH:
    // Perform any necessary cleanup.
    break;
  }
  return TRUE;  // Successful DLL_PROCESS_ATTACH.
}