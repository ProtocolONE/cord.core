#pragma once

#include <Core/core_global>

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>

#include <shlobj.h>

namespace GGS {
  namespace Core {
    namespace System {
      namespace TaskList {

        class TaskItem;
        class CORE_EXPORT TaskManager : public QObject
        {
          Q_OBJECT

        public:
          explicit TaskManager(QObject *parent = 0);
          virtual ~TaskManager();

          int addCategory(const QString& name);
          void removeCategory(int id);

          int addItem(int categoryId, const TaskItem& item); 
          int addTask(const TaskItem& item);

          void setGuid(const QString& guid);

          void removeAllTasks();
          void removeAll();

          void apply();

        private:
          IShellLink* createShellLink(TaskItem* item);
          bool isWinVistaOrLater();

          QMap<int, QList<TaskItem>> _items;
          QMap<int, QString> _categories;
          QMap<int, TaskItem> _internalItems;
          QList<IShellLink*> _removedItems;

          int _internalCategoryCounter;
          int _internalTaskItemCounter;

          QString _guid;
        };

      }
    }
  }
}
