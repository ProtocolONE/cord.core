/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <Core/Marketing.h>

#include <QtCore/QMutexLocker>

namespace GGS {
  namespace Core {

    Marketing *Marketing::_instance = 0;
    QMutex Marketing::_mutex;
    QString Marketing::_nullId = "0";

    Marketing::Marketing(QObject* parent) : QObject(parent)
    {
    }

    Marketing::~Marketing()
    {
    }

    Marketing* Marketing::instance()
    {
      if (_instance)
        return _instance;

      QMutexLocker locker(&_mutex);
      if (_instance)
        return _instance;

      _instance = new Marketing();
      return _instance;
    }

    void Marketing::send(MarketingTargets target)
    {
      QString id("");
      QVariantMap emptyParams;
      send(target, id, emptyParams);
    }

    void Marketing::send(MarketingTargets target, const QString& serviceId)
    {
      QVariantMap emptyParams;
      send(target, serviceId, emptyParams);
    }

    void Marketing::send(MarketingTargets target, const QVariantMap& params)
    {
      QString id("");
      send(target, id, params);
    }

    void Marketing::send(MarketingTargets target, const QString& serviceId, const QVariantMap& params)
    {
      Marketing *instance = Marketing::instance();
      emit instance->marketingRequest(target, serviceId.isEmpty() ? _nullId : serviceId, params);
    }

    void Marketing::sendOnce(MarketingTargets target)
    {
      QString id("");
      QVariantMap emptyParams;
      sendOnce(target, id, emptyParams);
    }

    void Marketing::sendOnce(MarketingTargets target, const QString& serviceId)
    {
      QVariantMap emptyParams;
      sendOnce(target, serviceId, emptyParams);
    }

    void Marketing::sendOnce(MarketingTargets target, const QVariantMap& params)
    {
      QString id("");
      sendOnce(target, id, params);
    }

    void Marketing::sendOnce(MarketingTargets target, const QString& serviceId, const QVariantMap& params)
    {
      Marketing *instance = Marketing::instance();
      emit instance->sendOnceMarketingRequest(target, serviceId.isEmpty() ? _nullId : serviceId, params);
    }

    void Marketing::sendOnceByService(MarketingTargets target, const QString& serviceId)
    {
      QVariantMap emptyParams;
      sendOnceByService(target, serviceId, emptyParams);
    }

    void Marketing::sendOnceByService(MarketingTargets target, const QString& serviceId, const QVariantMap& params)
    {
      if (serviceId.isEmpty())
        return;

      Marketing *instance = Marketing::instance();
      emit instance->sendOnceByServiceMarketingRequest(target, serviceId, params);
    }
  }
}