#include <Core/System/TaskList/TaskManager.h>
#include <Core/System/TaskList/TaskItem.h>

#include <QtCore/QList>
#include <QtCore/QCoreApplication>

#include <shlobj.h>
#include <Propvarutil.h>
#include <Propsys.h>

namespace GGS {
  namespace Core {
    namespace System {
      namespace TaskList {

        TaskManager::TaskManager(QObject *parent)
          : QObject(parent),
          _internalCategoryCounter(1),
          _internalTaskItemCounter(0)
        {
        }

        TaskManager::~TaskManager() 
        {
          Q_FOREACH(IShellLink* link, this->_removedItems)
            link->Release();
        }

        bool TaskManager::isOScompatible() 
        {
#ifdef Q_WS_WIN
          return QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7;
#endif
          return false;
        }

        int TaskManager::addCategory( const QString& name) 
        {
          this->_categories.insert(this->_internalCategoryCounter, name);

          return this->_internalCategoryCounter++;
        }

        void TaskManager::removeCategory(int id) 
        {
          this->_categories.remove(id);
        }

        int TaskManager::addItem(int categoryId, const TaskItem& item) {
          if (categoryId > 0 && !this->_categories.contains(categoryId))
            return -1;

          if (!this->_items.contains(categoryId)) {
            QList<TaskItem> list;
            this->_items.insert(categoryId, list);
          }

          this->_items[categoryId].append(item);
          this->_internalItems.insert(this->_internalTaskItemCounter, item);

          return _internalTaskItemCounter++;
        }

        int TaskManager::addTask(const TaskItem& item) 
        {
          return this->addItem(0, item);
        }

        void TaskManager::setGuid(const QString& guid) 
        {
          this->_guid = guid;
        }

        void TaskManager::removeAllTasks() 
        {
          this->_items[0].clear();
        }

        void TaskManager::removeAll() 
        {
          this->_items.clear();
        }

        void TaskManager::apply() 
        {
          if (!this->isOScompatible() || this->_guid.isEmpty())
            return;

          UINT max_count = 0;
          IObjectArray* objectArray;
          ICustomDestinationList* destinationList;

          CoInitialize(NULL);
          CoCreateInstance(CLSID_DestinationList, NULL, CLSCTX_INPROC, IID_ICustomDestinationList, reinterpret_cast<void**>(&destinationList));

          destinationList->BeginList(&max_count, IID_IObjectArray, reinterpret_cast<void**>(&objectArray));

          IObjectCollection* objCollection;
          CoCreateInstance(CLSID_EnumerableObjectCollection, NULL,
            CLSCTX_INPROC, IID_IObjectCollection, reinterpret_cast<void**> (&objCollection));

          IObjectArray* object_array;
          objCollection->QueryInterface(IID_IObjectArray, reinterpret_cast<void**>(&object_array));

          Q_FOREACH(int category, this->_items.keys() ) {
            QList<TaskItem> items = this->_items.value(category);

            objCollection->Clear();

            Q_FOREACH(TaskItem item, items) {
              objCollection->AddObject(this->createShellLink(&item));
            }

            if (!items.isEmpty()) {
              if (category > 0) 
                destinationList->AppendCategory(this->_categories[category].toStdWString().c_str(), object_array);
              else
                destinationList->AddUserTasks(object_array);
            }
          }

          destinationList->CommitList();

          object_array->Release();
          objCollection->Release();
          objectArray->Release();
          destinationList->Release();
          CoUninitialize();
        }

        IShellLink* TaskManager::createShellLink(TaskItem* item) 
        {
          IShellLink* shellLink = NULL;
          CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, reinterpret_cast<void**>(&shellLink));

          shellLink->SetPath(QCoreApplication::applicationFilePath().toStdWString().c_str());
          shellLink->SetArguments(item->params().toStdWString().c_str());
          shellLink->SetIconLocation(item->icon().toStdWString().c_str(), 0);
          shellLink->SetDescription(item->description().toStdWString().c_str());

          PROPVARIANT pv;
          IPropertyStore* propStore = NULL;
          shellLink->QueryInterface(IID_IPropertyStore, reinterpret_cast<void**> (&propStore));

          PROPERTYKEY pkeyTitle;
          CLSIDFromString(this->_guid.utf16(), &(pkeyTitle.fmtid));
          pkeyTitle.pid = 2;

          InitPropVariantFromString(item->name().toStdWString().c_str(), &pv);
          propStore->SetValue(pkeyTitle, pv);
          propStore->Commit();

          this->_removedItems.append(shellLink);

          return shellLink;
        }
      }
    }
  }
}