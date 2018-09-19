#include <Core/UI/Message.h>
#include <Core/UI/MessageAdapter.h>
#include <QtCore/QEventLoop>
#include <QtCore/QDebug>
#include <QtCore/QMutex>

namespace P1 {
  namespace Core {
    namespace UI {

      QPointer<MessageAdapter> Message::_adapter = 0;
      int Message::_messageId = 0;
      QMutex Message::lockMutex;

      Message::Message(QObject* parent) : QObject(parent)
      {
        this->_buttons = NoButton;
        this->_icon = NoIcon;
        this->_title = QString();
        this->_text = QString();
      }

      Message::Message(Icon icon, const QString& title, const QString& text, StandardButtons buttons, QObject *parent)
        : QObject(parent)
      {
        this->_icon = icon;
        this->_title = title;
        this->_text = text;
        this->_buttons = buttons;
      }

      Message::~Message()
      {
      }

      QString Message::text() const 
      { 
        return this->_text;
      }

      QString Message::title() const 
      { 
        return this->_title; 
      }

      Message::Icon Message::icon() const 
      { 
        return this->_icon; 
      }

      int Message::getNextId()
      {
        QMutexLocker locker(&lockMutex);
        return Message::_messageId++;
      }

      void Message::addButton(StandardButton button)
      {
        this->_buttons = this->_buttons | button;
      }

      void Message::removeButton(StandardButton button)
      {
        if (this->_buttons.testFlag(button))
          this->_buttons ^= button;
      }

      void Message::setTitle(const QString& title)
      {
        this->_title = title;
      }

      void Message::setText(const QString &text)
      {
        this->_text = text;
      }

      void Message::setIcon(Icon icon)
      {
        this->_icon = icon;
      }

      P1::Core::UI::Message::StandardButtons Message::buttons() const
      {
        return this->_buttons;
      }

      void Message::open(QObject* receiver, const char* member)
      {
        if (Message::_adapter.isNull()){
          WARNING_LOG << "Trying to call message, but MessageAdapter not set."; 
          return;
        }

        int nextMessageID = getNextId();
        Message::_adapter->show(_title, _text, _buttons, _icon, nextMessageID, receiver, member);
      }

      Message::StandardButton Message::exec()
      {
        return this->exec(this->_icon, this->_title, this->_text, this->_buttons);
      }

      Message::StandardButton Message::exec(Icon icon, const QString& title, const QString& text, StandardButtons buttons)
      {
        if (Message::_adapter.isNull()){
          WARNING_LOG << "Trying to call message, but MessageAdapter not set."; 
          return NoButton;
        }

        int nextMessageID = Message::getNextId();

        QEventLoop loop;
        Message::_adapter->show(title, text, buttons, icon, nextMessageID, &loop, SLOT(quit()));
        loop.exec();

        if (Message::_adapter.isNull())
          return NoButton;

        return Message::_adapter->buttonClicked(nextMessageID);
      }

      void Message::setAdapter(P1::Core::UI::MessageAdapter* adapter)
      {
        Q_CHECK_PTR(adapter);
        Message::_adapter = adapter;
      }

      Message::StandardButton Message::critical(const QString& title, const QString& text, StandardButton buttons)
      { 
        return Message::exec(Critical, title, text, buttons);
      }

      Message::StandardButton Message::information(const QString& title, const QString& text, StandardButton buttons)
      {
        return Message::exec(Information, title, text, buttons);
      }

      Message::StandardButton Message::question(const QString& title, const QString& text, StandardButton buttons)
      {
        return Message::exec(Question, title, text, buttons);
      }

      Message::StandardButton Message::warning(const QString& title, const QString& text, StandardButton buttons)
      {    
        return Message::exec(Warning, title, text, buttons);             
      }
    }
  }
}