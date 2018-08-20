#include <Core/UI/MessageAdapter.h>

namespace P1 {
  namespace Core {
    namespace UI {

      MessageAdapter::MessageAdapter(QObject *parent)
        : QObject(parent)
      {
      }

      MessageAdapter::~MessageAdapter()
      {
      }

      Message::StandardButton MessageAdapter::buttonClicked(int messageId) 
      { 
        return this->_returnButtons.take(messageId); // Возврат и сразу же удаление, дабы не засорять память 
      }
    }
  }
}