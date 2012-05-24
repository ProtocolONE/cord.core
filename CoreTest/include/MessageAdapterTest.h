#ifndef MESSAGEADAPTERTEST_H
#define MESSAGEADAPTERTEST_H

#include <QObject>
#include <QMap>
#include <QPair>
#include <Core/UI/MessageAdapter.h>

using namespace GGS::Core::UI;

class FakeClass : public QObject{
  Q_OBJECT
public:
  FakeClass(){}
  ~FakeClass(){}

signals:
  void SomeSignal(int);
};

class MessageAdapterTest : public MessageAdapter
{
  Q_OBJECT
  Q_ENUMS(Message::StandardButton)

public:
    MessageAdapterTest(QObject *parent = 0);
    ~MessageAdapterTest();

public slots:
  void show(const QString& title, const QString& text, Message::StandardButtons buttons, Message::Icon icon, int messageId, QObject* reciever, const char* bindFunc);   
  void buttonClicked(int messageId, int id);

  void testSlot();

signals:
  void testSignal(int buttonId);

private:
  QMap<int, QPair<QObject*, const char*> > _bindSlots;
};

#endif // MESSAGEADAPTERTEST_H
