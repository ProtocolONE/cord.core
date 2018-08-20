#pragma once

#include <Core/core_global.h>
#include <QObject>

namespace P1 {
  namespace Core {
    namespace System {
      namespace TaskList {

        class CORE_EXPORT TaskItem 
        {

        public:
          TaskItem();

          virtual ~TaskItem();

          QString icon() const;
          QString name() const;
          QString description() const;
          QString url() const;
          QString params() const;

          void setIcon(const QString& icon);
          void setName(const QString& name);
          void setDescription(const QString& description);
          void setUrl(const QString& url);
          void setParams(const QString& params);

        private:
          QString _icon;
          QString _name;
          QString _description;
          QString _url;
          QString _params;
        };

      }
    }
  }
}