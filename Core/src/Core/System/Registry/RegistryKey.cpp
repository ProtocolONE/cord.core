#include <Core/System/Registry/RegistryKey.h>

#include <QtCore/QDebug>

namespace GGS{
  namespace Core {
    namespace System {
      namespace Registry {

        RegistryKey::RegistryKey(RegistryHive hive, const QString& key)
          : _key(0)
          , _isValid(false)
        {
          if (key.size() <= 0)
            return;

          HKEY rootKey;
          switch(hive)
          {
          case HKCR:
            rootKey = HKEY_CLASSES_ROOT;
            break;
          case HKCU:
            rootKey = HKEY_CURRENT_USER;
            break;
          case HKLM:
            rootKey = HKEY_LOCAL_MACHINE;
            break;
          default:
            DEBUG_LOG << "Unsupported hive" << hive;
            return;
          }

          wchar_t *tmp = new wchar_t[key.size() + 1];
          key.toWCharArray(tmp);
          tmp[key.size()] = L'\0';

          DWORD res = RegCreateKeyEx(
            rootKey, 
            tmp, 
            0, 
            NULL, 
            REG_OPTION_NON_VOLATILE, 
            KEY_WOW64_64KEY | KEY_READ | KEY_WRITE, 
            NULL, 
            &this->_key, 
            NULL);

          delete [] tmp;

          if (res != ERROR_SUCCESS) {
            DEBUG_LOG << "Can't open " << key << "Error:" << res;
            return;
          }

          this->_isValid = true;
        }

        RegistryKey::~RegistryKey()
        {
          if (this->_isValid)
            RegCloseKey(this->_key);
        }

        bool RegistryKey::isValid()
        {
          return this->_isValid;
        }

        bool RegistryKey::setValue(const QString& paramName, const QString& value)
        {
          if (!this->_isValid) {
            DEBUG_LOG << "Key is invalid";
            return false;
          }

          wchar_t *paramArray = new wchar_t[paramName.size() + 1];
          wchar_t *valueArray = new wchar_t[value.size() + 1];

          paramName.toWCharArray(paramArray);
          value.toWCharArray(valueArray);

          paramArray[paramName.size()] = L'\0';
          valueArray[value.size()] = L'\0';
          DWORD res = RegSetValueEx(
            this->_key, 
            paramArray, 
            0, 
            REG_SZ, 
            reinterpret_cast<BYTE*>(valueArray), 
            value.size()*2 + 2);
          
          delete [] paramArray;
          delete [] valueArray;

          if (res != ERROR_SUCCESS) {
            DEBUG_LOG << "Can't setStringValue " << paramName << "value" << value << "Error:" << res;
            return false;
          }

          return true;
        }
        
        bool RegistryKey::value(const QString& paramName, QString& result)
        {
          if (!this->_isValid) {
            DEBUG_LOG << "Key is invalid";
            return false;
          }

          wchar_t *paramArray = new wchar_t[paramName.size() + 1];
          paramName.toWCharArray(paramArray);
          paramArray[paramName.size()] = L'\0';

          DWORD type;
          DWORD expectedSize;
          DWORD res = RegQueryValueExW(this->_key, paramArray, 0, &type, 0, &expectedSize);

          if (res != ERROR_SUCCESS || expectedSize <= 0 || type != REG_SZ) {
            delete [] paramArray;
            DEBUG_LOG << "Can't getStringValue " << paramName << "Error:" << res;
            return false;
          }

          unsigned char *valueArray = new unsigned char[expectedSize + 2];
          ZeroMemory(valueArray, expectedSize + 2);
          res = RegQueryValueExW(this->_key, paramArray, 0, &type, valueArray, &expectedSize);
          delete [] paramArray;

          if (res != ERROR_SUCCESS) {
            delete [] valueArray;
            DEBUG_LOG << "Can't getStringValue " << paramName << "Error:" << res;
            return false;
          }

          result = QString::fromWCharArray(reinterpret_cast<wchar_t *>(valueArray));
          delete [] valueArray;
          return true; 
        }

        bool RegistryKey::setValue(const QString& paramName, DWORD value)
        {
          if (!this->_isValid) {
            DEBUG_LOG << "Key is invalid";
            return false;
          }

          wchar_t *paramArray = new wchar_t[paramName.size() + 1];
          paramName.toWCharArray(paramArray);
          paramArray[paramName.size()] = L'\0';

          DWORD res = RegSetValueEx(
            this->_key, 
            paramArray, 
            0, 
            REG_DWORD, 
            reinterpret_cast<BYTE*>(&value),
            sizeof(DWORD));

          delete [] paramArray;

          if (res != ERROR_SUCCESS) {
            DEBUG_LOG << "Can't setDwordValue " << paramName << "value" << value << "Error:" << res;
            return false;
          }

          return true;
        }

        bool RegistryKey::value(const QString& paramName, DWORD& result)
        {
          wchar_t *paramArray = new wchar_t[paramName.size() + 1];
          paramName.toWCharArray(paramArray);
          paramArray[paramName.size()] = L'\0';

          DWORD type;
          DWORD expectedSize;
          DWORD res = RegQueryValueExW(this->_key, paramArray, 0, &type, 0, &expectedSize);

          if (res != ERROR_SUCCESS || expectedSize != sizeof(DWORD) || type != REG_DWORD) {
            delete [] paramArray;
            DEBUG_LOG << "Can't getDwordValue " << paramName << "Error:" << res;
            return false;
          }

          res = RegQueryValueExW(this->_key, paramArray, 0, &type, reinterpret_cast<BYTE*>(&result), &expectedSize);
          delete [] paramArray;

          if (res != ERROR_SUCCESS) {
            DEBUG_LOG << "Can't getDwordValue " << paramName << "Error:" << res;
            return false;
          }

          return true;
        }

      }
    }
  }
}