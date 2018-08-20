#pragma once 

#include <QtCore/QObject>
#include <QtCore/QEventLoop>

class TestEventLoopFinisher : public QObject
{
  Q_OBJECT
public:
  TestEventLoopFinisher(QEventLoop *loop, int timeout, int count = 0);
  ~TestEventLoopFinisher();
  
  bool isKilledByTimeout() const { return this->_timeoutKill; }

public slots:
  void terminateLoop();
  
private slots:
  void timeoutTick();

private:
  int _count;
  bool _timeoutKill;
  QEventLoop *_loop;
};
