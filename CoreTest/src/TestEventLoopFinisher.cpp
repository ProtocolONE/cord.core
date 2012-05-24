#include "TestEventLoopFinisher.h"
#include <QtCore/QDebug>
#include <QtCore/QTimer>

TestEventLoopFinisher::TestEventLoopFinisher(QEventLoop *loop, int timeout, int count)
  : _loop(loop),
    _timeoutKill(false),
    _count(count)
{
  QTimer::singleShot(timeout, this, SLOT(timeoutTick()));
}


TestEventLoopFinisher::~TestEventLoopFinisher(void)
{
}

void TestEventLoopFinisher::terminateLoop()
{
  if (--this->_count > 0) 
    return;

  if (this->_loop) {
    QTimer::singleShot(100, this->_loop, SLOT(quit()));
    this->_loop->quit();
  } else {
    qCritical() << "loop was not initialized";
  }
}
 
void TestEventLoopFinisher::timeoutTick()
{
  this->_timeoutKill = true;
  this->terminateLoop();
}
