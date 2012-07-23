#ifndef _GGS_CORE_SYSTEM_REGISTRY_REGISTRYKEY_H_
#define _GGS_CORE_SYSTEM_REGISTRY_REGISTRYKEY_H_

#include <Core/core_global>

#include <QtCore/QString>

#include <windows.h>

namespace GGS{
  namespace Core {
    namespace System {
      namespace Registry {

        /*!
          \class RegistryKey
          \brief Класс необходим для записи из 32х битного приложения в 64х битный реестр. В том числе класс решает
                 проблему с заменной классом QSettings \ на /. На данный момент клас всегда создает ключ в 64х битном
                 реестре.
          \author Ilya.Tkachenko
          \date 24.07.2012
        */
        class CORE_EXPORT RegistryKey 
        {

        public:
          enum RegistryHive 
          {
            HKCR = 0,
            HKCU,
            HKLM
          };


          /*!
            \fn RegistryKey::RegistryKey(RegistryHive hive, const QString& key);
            \brief Constructor.
            \author Ilya.Tkachenko
            \date 24.07.2012
            \param hive Основной раздел реестра.
            \param key  Ключ в указанном разделе.
          */
          RegistryKey(RegistryHive hive, const QString& key);
          ~RegistryKey();


          /*!
            \fn bool RegistryKey::isValid();
            \brief Возвращает true, если удалось открыть указанную ветку реестра.
            \author Ilya.Tkachenko
            \date 24.07.2012
            \return true if valid, false if not.
          */
          bool isValid();

          bool setValue(const QString& paramName, const QString& value);
          bool value(const QString& paramName, QString& result);

          bool setValue(const QString& paramName, DWORD value);
          bool value(const QString& paramName, DWORD& result);

        private:
          HKEY _key;
          bool _isValid;
        };
      }
    }
  }
}

#endif // _GGS_CORE_SYSTEM_REGISTRY_REGISTRYKEY_H_