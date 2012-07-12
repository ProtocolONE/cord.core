#ifndef _GGS_CORE_UI_MESSAGEADAPTER_H_
#define _GGS_CORE_UI_MESSAGEADAPTER_H_

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

namespace GGS{
  namespace Core{
    namespace UI{

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
          GGS::Core::UI::Message::StandardButtons buttons, 
          GGS::Core::UI::Message::Icon icon, 
          int messageId, 
          QObject* reciever, 
          const char* member) = 0;

        GGS::Core::UI::Message::StandardButton buttonClicked(int messageId);

      protected:
        QMap<int, Message::StandardButton> _returnButtons;
      };
    }
  }
}

#endif // MESSAGEADAPTER_H
