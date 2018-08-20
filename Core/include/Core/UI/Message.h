#pragma once

#include <Core/core_global.h>

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QPointer>

namespace P1 {
  namespace Core {
    namespace UI {

      /*
      05.06.2012 igor bugaev
      Класс реализует систему выезжающих окон. Для работы требуется валидный MessageAdapter.
      */

      class MessageAdapter;
      class CORE_EXPORT Message : public QObject
      {
        Q_OBJECT
        Q_ENUMS(StandardButton)
        Q_FLAGS(StandardButtons)

      public:
        enum Icon {
          NoIcon = 0,
          Information = 1,
          Warning = 2,
          Critical = 3,
          Question = 4
        };

        enum StandardButton {
          // keep this in sync with QDialogButtonBox::StandardButton
          NoButton           = 0x00000000,
          Support            = 0x00000200,
          Ok                 = 0x00000400,
          Save               = 0x00000800,
          SaveAll            = 0x00001000,
          Open               = 0x00002000,
          Yes                = 0x00004000,
          YesToAll           = 0x00008000,
          No                 = 0x00010000,
          NoToAll            = 0x00020000,
          Abort              = 0x00040000,
          Retry              = 0x00080000,
          Ignore             = 0x00100000,
          Close              = 0x00200000,
          Cancel             = 0x00400000,
          Discard            = 0x00800000,
          Help               = 0x01000000,
          Apply              = 0x02000000,
          Reset              = 0x04000000,
          RestoreDefaults    = 0x08000000
        };

        Q_DECLARE_FLAGS(P1::Core::UI::Message::StandardButtons, P1::Core::UI::Message::StandardButton)

        explicit Message(QObject *parent = 0);
        Message(Icon icon, const QString& title, const QString& text, StandardButtons buttons = NoButton, QObject *parent = 0);
        virtual ~Message();

        void addButton(StandardButton button);
        void removeButton(StandardButton button);

        /*
        Синхронный вызов
        Возвращает код нажатой кнопки
        */
        StandardButton exec(); 

        /*
        Асинхронный вызов
        receiver - владелец слота.
        member - слот/сигнал к которому будет подключен сигнал clicked(int)
        После нажатия кнопки, произойдет вызов сигналов 
        */
        void open(QObject* receiver, const char* member); 

        QString text() const;
        void setText(const QString &text);

        QString title() const;
        void setTitle(const QString& title);

        Icon icon() const;
        void setIcon(Icon icon);

        StandardButtons buttons() const;

        static StandardButton critical(const QString& title, const QString& text, StandardButton buttons = Ok);
        static StandardButton information(const QString& title, const QString& text, StandardButton buttons = Ok);
        static StandardButton question(const QString& title, const QString& text, StandardButton buttons = Ok);
        static StandardButton warning(const QString& title, const QString& text, StandardButton buttons = Ok);

        static void setAdapter(MessageAdapter* adapter);

      signals:
        void buttonClicked(int messageId, int id);
        void finished();

      private:
        static StandardButton exec(Icon icon, const QString& title, const QString& text, StandardButtons buttons = NoButton); 
        static int getNextId();

        StandardButtons _buttons;
        QString _text;
        QString _title;
        Icon _icon;

        static QMutex lockMutex;
        static int _messageId;
        static QPointer<MessageAdapter> _adapter;
      };
    }
  }
}

