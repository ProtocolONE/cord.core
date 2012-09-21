/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <ResourceHelper/Encryptor.h>
#include <ResourceHelper/EncryptConfig.h>

#include <QtCore/QDebug>
#include <QtCore/QFile>

#define CRITICAL_LOG qCritical() << __FILE__ << __LINE__ << __FUNCTION__
#define WARNING_LOG qWarning() << __FILE__ << __LINE__ << __FUNCTION__
#define DEBUG_LOG qDebug() << __FILE__ << __LINE__ << __FUNCTION__

namespace GGS {
  namespace ResourceHelper {

    Encryptor::Encryptor()
    {
    }

    Encryptor::~Encryptor()
    {
    }

    QByteArray Encryptor::encrypt(const QByteArray& input)
    {
      QByteArray output;
      int size = input.size();
      int mod = KEY_SIZE;

      output.resize(size);
      unsigned char startKey = 0xFF;
      int keyIndex = 0;

      for (int i = 0; i < size; ++i) {
        unsigned char b = input[i];
        output[size - i - 1] = startKey ^ b ^ key[keyIndex];
        startKey = b;
        keyIndex += 1;
        if (keyIndex >= mod) 
          keyIndex = 0;
      }

      return output;
    }

    void Encryptor::encryptFile(const QString& input, const QString& output)
    {
      QFile inputFile(input);
      QFile outputFile(output);

      if (!inputFile.open(QFile::ReadOnly) ) {
        CRITICAL_LOG << " failed to open file " << input;
        return;
      }

      if (!outputFile.open(QFile::ReadWrite)) {
        CRITICAL_LOG << " failed to create file " << output;
        return;
      }

      QByteArray inBuffer = inputFile.readAll();
      inputFile.close();

#ifdef COMPRESS_ENABLED
      QByteArray outBuffer = encrypt(inBuffer);
      QByteArray compressed = qCompress(outBuffer, COMPRESS_LEVEL);
#else
      QByteArray compressed = encrypt(inBuffer);
#endif 

      QDataStream outStream(&outputFile);
      quint64 version = ENCRYPT_VERSION;
      outStream << version;
      outStream << compressed;
      outputFile.close();  
    }

  }
}