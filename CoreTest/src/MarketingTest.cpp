#include "TestEventLoopFinisher.h"

#include <Core/Marketing.h>

#include <QtCore/QEventLoop>
#include <QtTest/QSignalSpy>

#include <gtest/gtest.h>

using namespace P1::Core;

class MarketingTest : public ::testing::Test 
{
public:
  void SetUp() {
    spy = new QSignalSpy(Marketing::instance(), SIGNAL(marketingRequest(P1::Core::Marketing::MarketingTargets, const QString&, QVariantMap)));
    spyOnceByService = new QSignalSpy(Marketing::instance(), SIGNAL(sendOnceByServiceMarketingRequest(P1::Core::Marketing::MarketingTargets, const QString&, QVariantMap)));
    spyOnceByTarget = new QSignalSpy(Marketing::instance(), SIGNAL(sendOnceMarketingRequest(P1::Core::Marketing::MarketingTargets, const QString&, QVariantMap)));
    this->nullId = "0";
  }

  void exec() {
    QEventLoop loop;
    TestEventLoopFinisher killer(&loop, 5000, 1);
    QObject::connect(Marketing::instance(), SIGNAL(marketingRequest(P1::Core::Marketing::MarketingTargets, const QString&, QVariantMap)),
      &killer, SLOT(terminateLoop()));

    ASSERT_FALSE(killer.isKilledByTimeout());
  }

  QString nullId;
  QSignalSpy *spy;
  QSignalSpy *spyOnceByService;
  QSignalSpy *spyOnceByTarget;
};

TEST_F(MarketingTest, allParamTest)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  QString id("someId");
  QVariantMap params;
  params["someId1"] = "someValue1";
  params["someId2"] = "someValue2";
  params["someId3"] = "someValue3";
  Marketing::send(target, id, params);
  exec();

  ASSERT_EQ(1, spy->count());
  QList<QVariant> args = spy->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(id, args.at(1).toString());

  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(params, paramsResult);
  ASSERT_EQ(0, spyOnceByService->count());
  ASSERT_EQ(0, spyOnceByTarget->count());
}

TEST_F(MarketingTest, nothing)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  Marketing::send(target);
  
  exec();

  ASSERT_EQ(1, spy->count());
  QList<QVariant> args = spy->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(nullId, args.at(1).toString());
  
  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(0, paramsResult.count());
  ASSERT_EQ(0, spyOnceByService->count());
  ASSERT_EQ(0, spyOnceByTarget->count());
}

TEST_F(MarketingTest, sendWithId)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  QString id("someId");
  Marketing::send(target, id);
  exec();

  ASSERT_EQ(1, spy->count());
  QList<QVariant> args = spy->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(id, args.at(1).toString());

  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(0, paramsResult.count());
  ASSERT_EQ(0, spyOnceByService->count());
  ASSERT_EQ(0, spyOnceByTarget->count());
}

TEST_F(MarketingTest, sendWithParams)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  QVariantMap params;
  params["someId1"] = "someValue1";
  params["someId2"] = "someValue2";
  params["someId3"] = "someValue3";
  Marketing::send(target, params);
  exec();

  ASSERT_EQ(1, spy->count());
  QList<QVariant> args = spy->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(nullId, args.at(1).toString());

  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(params, paramsResult);
  ASSERT_EQ(0, spyOnceByService->count());
  ASSERT_EQ(0, spyOnceByTarget->count());
}

TEST_F(MarketingTest, allParamTestWithNullId)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  QString id("");
  QVariantMap params;
  params["someId1"] = "someValue1";
  params["someId2"] = "someValue2";
  params["someId3"] = "someValue3";
  Marketing::send(target, id, params);
  exec();

  ASSERT_EQ(1, spy->count());
  QList<QVariant> args = spy->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(nullId, args.at(1).toString());

  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(params, paramsResult);
  ASSERT_EQ(0, spyOnceByService->count());
  ASSERT_EQ(0, spyOnceByTarget->count());
}

TEST_F(MarketingTest, allParamTestSendOnce)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  QString id("someId");
  QVariantMap params;
  params["someId1"] = "someValue1";
  params["someId2"] = "someValue2";
  params["someId3"] = "someValue3";
  Marketing::sendOnce(target, id, params);
  exec();

  ASSERT_EQ(1, spyOnceByTarget->count());
  QList<QVariant> args = spyOnceByTarget->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(id, args.at(1).toString());

  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(params, paramsResult);
  ASSERT_EQ(0, spyOnceByService->count());
  ASSERT_EQ(0, spy->count());
}

TEST_F(MarketingTest, nothingSendOnce)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  Marketing::sendOnce(target);

  exec();

  ASSERT_EQ(1, spyOnceByTarget->count());
  QList<QVariant> args = spyOnceByTarget->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(nullId, args.at(1).toString());

  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(0, paramsResult.count());
  ASSERT_EQ(0, spyOnceByService->count());
  ASSERT_EQ(0, spy->count());
}

TEST_F(MarketingTest, sendWithIdSendOnce)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  QString id("someId");
  Marketing::sendOnce(target, id);
  exec();

  ASSERT_EQ(1, spyOnceByTarget->count());
  QList<QVariant> args = spyOnceByTarget->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(id, args.at(1).toString());

  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(0, paramsResult.count());
  ASSERT_EQ(0, spyOnceByService->count());
  ASSERT_EQ(0, spy->count());
}

TEST_F(MarketingTest, sendWithParamsSendOnce)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  QVariantMap params;
  params["someId1"] = "someValue1";
  params["someId2"] = "someValue2";
  params["someId3"] = "someValue3";
  Marketing::sendOnce(target, params);
  exec();

  ASSERT_EQ(1, spyOnceByTarget->count());
  QList<QVariant> args = spyOnceByTarget->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(nullId, args.at(1).toString());

  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(params, paramsResult);
  ASSERT_EQ(0, spyOnceByService->count());
  ASSERT_EQ(0, spy->count());
}

TEST_F(MarketingTest, allParamTestWithNullIdSendOnce)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  QString id("");
  QVariantMap params;
  params["someId1"] = "someValue1";
  params["someId2"] = "someValue2";
  params["someId3"] = "someValue3";
  Marketing::sendOnce(target, id, params);
  exec();

  ASSERT_EQ(1, spyOnceByTarget->count());
  QList<QVariant> args = spyOnceByTarget->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(nullId, args.at(1).toString());

  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(params, paramsResult);
  ASSERT_EQ(0, spyOnceByService->count());
  ASSERT_EQ(0, spy->count());
}

TEST_F(MarketingTest, sendWithIdSendOnceByService)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  QString id("someId");
  Marketing::sendOnceByService(target, id);
  exec();

  ASSERT_EQ(1, spyOnceByService->count());
  QList<QVariant> args = spyOnceByService->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(id, args.at(1).toString());

  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(0, paramsResult.count());
  ASSERT_EQ(0, spyOnceByTarget->count());
  ASSERT_EQ(0, spy->count());
}

TEST_F(MarketingTest, sendWithParamsSendOnceByService)
{
  Marketing::MarketingTargets target = Marketing::AnyStartLauncher;
  QVariantMap params;
  QString id("someId");
  params["someId1"] = "someValue1";
  params["someId2"] = "someValue2";
  params["someId3"] = "someValue3";
  Marketing::sendOnceByService(target, id, params);
  exec();

  ASSERT_EQ(1, spyOnceByService->count());
  QList<QVariant> args = spyOnceByService->takeFirst();
  ASSERT_EQ(target, args.at(0).value<P1::Core::Marketing::MarketingTargets>());
  ASSERT_EQ(id, args.at(1).toString());

  QVariantMap paramsResult = args.at(2).value<QVariantMap>();
  ASSERT_EQ(params, paramsResult);
  ASSERT_EQ(0, spyOnceByTarget->count());
  ASSERT_EQ(0, spy->count());
}
