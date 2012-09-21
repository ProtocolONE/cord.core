/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <ResourceHelper/Decryptor.h>
#include <ResourceHelper/EncryptConfig.h>

#include <QtCore/QFile>
#include <QtCore/QDataStream>
#include <QtCore/QDebug>

#define CRITICAL_LOG qCritical() << __FILE__ << __LINE__ << __FUNCTION__
#define WARNING_LOG qWarning() << __FILE__ << __LINE__ << __FUNCTION__
#define DEBUG_LOG qDebug() << __FILE__ << __LINE__ << __FUNCTION__

namespace GGS {
  namespace ResourceHelper {

    Decryptor::Decryptor()
    {
    }

    Decryptor::~Decryptor()
    {
    }

    QByteArray Decryptor::decrypt(const QByteArray& input)
    {
      QByteArray output;
      int size = input.size();
      int mod = KEY_SIZE;
      int keyIndex = 0;

      output.resize(size);
      unsigned char startKey = 0xFF;

      for (int i = size - 1; i >= 0; --i) {
        unsigned char b = startKey ^ input[i] ^ key[keyIndex];
        output[size - i - 1] = b;
        startKey = b;
        keyIndex += 1;
        if (keyIndex >= mod) 
          keyIndex = 0;
      }

      return output;
    }

    QByteArray Decryptor::decryptFile(const QString& input)
    {
       QFile inputFile(input);
       QByteArray output;
       if (!inputFile.open(QFile::ReadOnly) ) {
         CRITICAL_LOG << " failed to open file " << input;
         return output;
       }

       QDataStream inStream(&inputFile);
       QByteArray compressed;
       quint64 version;

       inStream >> version;
       if (version != ENCRYPT_VERSION) {
         CRITICAL_LOG << "unknown encryption version" << version;
         return output;
       }

       inStream >> compressed;
       inputFile.close();

#ifdef COMPRESS_ENABLED
       QByteArray uncompressed = qUncompress(compressed);
       output = decrypt(uncompressed);
#else
       output = decrypt(compressed);
#endif

       return output;
    }

  }
}