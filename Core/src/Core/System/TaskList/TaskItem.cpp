#include <Core/System/TaskList/TaskItem.h>

namespace GGS {
  namespace Core {
    namespace System {
      namespace TaskList {

        TaskItem::TaskItem() 
        {

        }

        TaskItem::~TaskItem() 
        {

        }

        QString TaskItem::icon() const
        {
          return this->_icon;
        }

        QString TaskItem::name() const
        {
          return this->_name;
        }

        QString TaskItem::description() const
        {
          return this->_description;
        }

        QString TaskItem::url() const
        {
          return this->_url;
        }

        QString TaskItem::params() const
        {
          return this->_params;
        }

        void TaskItem::setIcon(const QString& icon)
        {
          this->_icon = icon;
        }

        void TaskItem::setName(const QString& name)
        {
          this->_name = name;
        }

        void TaskItem::setDescription(const QString& description)
        {
          this->_description = description;
        }

        void TaskItem::setUrl(const QString& url)
        {
          this->_url = url;
        }

        void TaskItem::setParams(const QString& params)
        {
          this->_params = params;
        }

      }
    }
  }
}
