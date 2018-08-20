#include <Core/Service.h>
#include <Core/Service.h>
#include <Core/UI/Message.h>
#include <Core/Marketing.h>

#include <Windows.h>
#include <QtCore/QMetaType>

namespace P1 {
  namespace Core {

    void registerTypes()
    {
      qRegisterMetaType<P1::Core::Service>("P1::Core::Service");
      qRegisterMetaType<P1::Core::UI::Message::StandardButtons>("P1::Core::UI::Message::StandardButtons");
      qRegisterMetaType<P1::Core::UI::Message::Icon>("P1::Core::UI::Message::Icon");
      qRegisterMetaType<P1::Core::Marketing::MarketingTargets>("P1::Core::Marketing::MarketingTargets");
    }
  }
}

