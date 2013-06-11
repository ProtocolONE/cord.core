#include <MessageAdapterMock.h>
#include <TestEventLoopFinisher.h>

#include <Core/UI/Message.h>
#include <Core/UI/MessageAdapter.h>

#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QFuture>
#include <QtTest/QSignalSpy>

#include <gtest/gtest.h>

#define testString "sdfjnawkfjnaekjrfkejnrfkjenrfkjnekrn"
#define testString2 "sergeergergergadsaaaaaaaaaaaaaaaaaaaaaaa"

using namespace GGS::Core::UI;

TEST(MessageTest, SetterGetterTest)
{
  Message message;
  message.setIcon(Message::Information);
  EXPECT_EQ(message.icon(), Message::Information);

  message.setText(testString);
  EXPECT_EQ(message.text(), testString);

  message.addButton(Message::Ok);
  message.addButton(Message::Cancel);
  message.addButton(Message::Ignore);
  message.removeButton(Message::Cancel);

  EXPECT_EQ(message.buttons(), Message::Ok | Message::Ignore);

  Message newMessage(Message::Question, testString, testString2, Message::NoButton);
  EXPECT_EQ(newMessage.text(), testString2);
  EXPECT_EQ(newMessage.title(), testString);
  EXPECT_EQ(newMessage.icon(), Message::Question);
}

void testMessage(){
  Message message;
  message.setIcon(Message::Information);
  message.setText(testString);
  message.addButton(Message::Ok);

  QEventLoop loop;
  TestEventLoopFinisher loopKiller(&loop, 20000);

  FakeClass* fakeClass = new FakeClass();
  QSignalSpy spy(fakeClass, SIGNAL(SomeSignal(int)));

  EXPECT_TRUE(QObject::connect(fakeClass, SIGNAL(SomeSignal(int)), &loopKiller, SLOT(terminateLoop())));

  message.open(fakeClass, SIGNAL(SomeSignal(int)));

  loop.exec();

  EXPECT_EQ(spy.takeFirst().at(0).toInt(), Message::Help); // Проверяем полученое значение
  ASSERT_FALSE(loopKiller.isKilledByTimeout());
}

TEST(MessageTest, OneThread)
{
  MessageAdapterMock adapterTest;
  Message::setAdapter(&adapterTest);
  
  testMessage();
}

TEST(MessageTest, MultiThread)
{
  MessageAdapterMock adapterTest;
  Message::setAdapter(&adapterTest);

  QFuture<void> future = QtConcurrent::run(&testMessage);
  QFuture<void> future2 = QtConcurrent::run(&testMessage);
  future.waitForFinished();
  future2.waitForFinished();
}