#ifndef _GGS_CORE_SERVICE_H
#define _GGS_CORE_SERVICE_H

#include <Core/core_global.h>

#include <QMetaType>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>

namespace GGS {
  namespace Core {
    class CORE_EXPORT Service : public QObject
    {
      Q_OBJECT
    public:
      Q_ENUMS(GGS::Core::Service::Area);

      enum Area {
        Live = 0,
        Pts,
        Tst
      };

      explicit Service(const Service &service);
      Service(QObject *parent = 0);
      ~Service();

      Service &operator = (const Service &);

      void setId(const QString &id);
      const QString &id() const;

      void setGameId(const QString &gameId);
      const QString &gameId() const;

      void setName(const QString &name);
      const QString &name() const;

      void setUrl(const QUrl &url);
      const QUrl &url() const;

      void setTorrentUrl(const QUrl& url);
      const QUrl& torrentUrl() const;
      
      const QUrl torrentUrlWithArea() const;

      void setArea(Area area);
      const Area area() const;

      void setTorrentFilePath(const QString& filePath);
      const QString& torrentFilePath() const;
            
      void setDownloadPath(const QString& dir);
      const QString& downloadPath() const;

      void setExtractionPath(const QString& directory);
      const QString& extractionPath() const;

      void setExtractorType(const QString& type);
      const QString& extractorType() const;

    private:
      QString _id;
      QString _gameId;
      QString _name;
      QUrl _url;
      QUrl _torrentUrl;
      QString _torrentFilePath;
      Area _area;
      QString _downloadPath;
      QString _extractionPath;
      QString _extractorType;
    };
  }
}

Q_DECLARE_METATYPE(GGS::Core::Service);
Q_DECLARE_METATYPE(GGS::Core::Service*);
Q_DECLARE_METATYPE(const GGS::Core::Service*);
#endif //_GGS_CORE_SERVICE_H

