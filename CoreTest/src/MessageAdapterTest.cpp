#include <QtCore/QTimer>
#include <QtCore/QtConcurrentRun>
#include <QtCore/QDateTime>

#include <MessageAdapterTest.h>

MessageAdapterTest::MessageAdapterTest(QObject *parent)
  : MessageAdapter(parent){
}

MessageAdapterTest::~MessageAdapterTest(){
}

void MessageAdapterTest::show(const QString& title, const QString& text, Message::StandardButtons buttons, Message::Icon icon, int messageId, QObject* reciever, const char* member){
  _bindSlots[messageId] = qMakePair(reciever, member);
  this->buttonClicked(messageId, Message::Help);

  connect(this, SIGNAL(testSignal(int)), reciever, member, Qt::QueuedConnection);

  // igor bugaev 17.06.2012
  // т.к в этом месте локальный event loop в клкссе Message еще не запущен, 
  // использовать QTimer нет возможности. Вместо этого, запускаем слот в другом потоке

  QtConcurrent::run(this, &MessageAdapterTest::testSlot);
}

void MessageAdapterTest::testSlot(){
  quint64 time = QDateTime::currentMSecsSinceEpoch();

  while (QDateTime::currentMSecsSinceEpoch() - time < 500);

  emit this->testSignal(Message::Help);
}

void MessageAdapterTest::buttonClicked(int messageId, int id){
  _returnButtons[messageId] = static_cast<GGS::Core::UI::Message::StandardButton>(id);  
}