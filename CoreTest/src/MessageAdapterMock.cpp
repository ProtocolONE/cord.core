#include <MessageAdapterMock.h>
#include <TestEventLoopFinisher.h>

#include <QtCore/QTimer>
#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QDateTime>

MessageAdapterMock::MessageAdapterMock(QObject *parent)
  : MessageAdapter(parent)
{
}

MessageAdapterMock::~MessageAdapterMock()
{
}

void MessageAdapterMock::show(const QString& title, const QString& text, P1::Core::UI::Message::StandardButtons buttons, P1::Core::UI::Message::Icon icon, int messageId, QObject* reciever, const char* member)
{
  connect(this, SIGNAL(testSignal(int)), reciever, member, Qt::QueuedConnection);
  emit this->testSignal(Message::Help);
}

void MessageAdapterMock::buttonClicked(int messageId, int id)
{
}