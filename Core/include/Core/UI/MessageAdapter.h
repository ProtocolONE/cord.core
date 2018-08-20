#pragma once

#include <Core/core_global.h>

#include <Core/UI/Message.h>
#include <QtCore/QObject>
#include <QtCore/QMap>

/*
by igor bugaev

Адаптер, по методу show должен показать уведомление с соответствующими кнопками, икноками и текстом.
При этом он сразу же должен соединить сигнал нажатия кнопки, с приёмником передающимся как параметр в эту функцию.
После нажатия кнопки, должен быть заполнен контейнер _returnButtons с кодом кнопки.

buttonClicked() возвращает из контейнера код нажатой кнопки, и сразу же производит очистку из контейнера.
*/

namespace P1 {
  namespace Core {
    namespace UI {

      class CORE_EXPORT MessageAdapter : public QObject
      {
        Q_OBJECT
      public:
        MessageAdapter(QObject *parent = 0);
        ~MessageAdapter();

      public slots:
        virtual void show(
          const QString& title, 
          const QString& text, 
          P1::Core::UI::Message::StandardButtons buttons, 
          P1::Core::UI::Message::Icon icon, 
          int messageId, 
          QObject* reciever, 
          const char* member) = 0;

        P1::Core::UI::Message::StandardButton buttonClicked(int messageId);

      protected:
        QMap<int, Message::StandardButton> _returnButtons;
      };
    }
  }
}
