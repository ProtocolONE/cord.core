/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <ResourceHelper/ResourceLoader.h>
#include <ResourceHelper/Decryptor.h>
#include <ResourceHelper/EncryptConfig.h>

#include <QtCore/QDebug>
#include <QtCore/QResource>
#include <QtCore/QFile>
#include <QtCore/QdataStream>

#define CRITICAL_LOG qCritical() << __FILE__ << __LINE__ << __FUNCTION__
#define WARNING_LOG qWarning() << __FILE__ << __LINE__ << __FUNCTION__
#define DEBUG_LOG qDebug() << __FILE__ << __LINE__ << __FUNCTION__

namespace GGS {
  namespace ResourceHelper {

    ResourceLoader::ResourceLoader()
    {
    }

    ResourceLoader::~ResourceLoader()
    {
    }

    void ResourceLoader::load(const QString& filePath)
    {
      QFile file(filePath);
      if (!file.open(QFile::ReadOnly)) {
        WARNING_LOG << "bad resource file" << filePath;
        return;
      }

      QDataStream inStream(&file);
      quint64 version;
      inStream >> version;
      file.close();

      if (version == ENCRYPT_VERSION) {
        Decryptor decryptor;
        this->_array = decryptor.decryptFile(filePath);
        const uchar* rcc = reinterpret_cast<const uchar*>(this->_array.constData());
        QResource::registerResource(rcc);

      } else {
        if (((version >> 32) & 0xFFFFFFFF) == 0x71726573) {
          QResource::registerResource(filePath);
        }
      }
    }

  }
}