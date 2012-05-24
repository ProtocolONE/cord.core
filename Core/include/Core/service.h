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

      void setInstallPath(const QString& directory);
      const QString& installPath() const;

      void setExtractorType(const QString& type);
      const QString& extractorType() const;


      /*!
        \fn QString Service::areaString() const;
        \brief Возвращает зону сервиса ввиде строк "live", "pts", "tst".
        \author Ilya.Tkachenko
        \date 17.05.2012
        \return Строковое представление зоны сервиса.
      */
      QString areaString() const;


      /*!
        \fn void Service::setIsDownloadable(bool isDownloadable);
        \brief Если сервис необходимо скачивать выставить в true, иначе false.
        \author Ilya.Tkachenko
        \date 17.05.2012
        \param isDownloadable true if is downloadable.
      */
      void setIsDownloadable(bool isDownloadable);


      /*!
        \fn bool Service::isDownloadable() const;
        \brief Возвращает true, если преред запуском сервис необходимо скачать, иначе false.
        \author Ilya.Tkachenko
        \date 17.05.2012
        \return true if downloadable, false if not.
      */
      bool isDownloadable() const;


      /*!
        \fn bool Service::hashDownloadPath() const;
        \brief Возвращает true, если сервис скачивается в отдельную директорию, иначе false.
        \author Ilya.Tkachenko
        \date 18.05.2012
        \return true if it succeeds, false if it fails.
      */
      bool hashDownloadPath() const;


      /*!
        \fn void Service::setHashDownloadPath(bool hashDownloadPath);
        \brief Устанавливает надо ли ставить сервис в отдельную папку.
        \author Ilya.Tkachenko
        \date 18.05.2012
        \param hashDownloadPath true to hash download path.
      */
      void setHashDownloadPath(bool hashDownloadPath);


      /*!
        \fn bool Service::isDefaultInstallPath() const;
        \brief Возвращает true, если пользователь не менял папку для установки ни разу, иначе false.
        \author Ilya.Tkachenko
        \date 23.05.2012
        \return true if default install path, false if not.
      */
      bool isDefaultInstallPath() const;

      /*!
        \fn void Service::setIsDefaultInstallPath(bool isDefaultInstallPath);
        \brief Задает менял ли папку для установки игры пользовател. Если менял то true, иначе false.
        \author Ilya.Tkachenko
        \date 23.05.2012
        \param isDefaultInstallPath true if is default install path.
      */
      void setIsDefaultInstallPath(bool isDefaultInstallPath);


      /*!
        \fn const QString& Service::externalDependencyList() const;
        \brief Возвращает строку, в которой через разделитель перечислены имена ехе запускаем после установки игры.
        \author Ilya.Tkachenko
        \date 24.05.2012
        \return .
      */
      const QString& externalDependencyList() const;


      /*!
        \fn void Service::setExternalDependencyList(const QString& externalDependencyList);
        \brief Задает список зависимостей игры.
        \author Ilya.Tkachenko
        \date 24.05.2012
        \param externalDependencyList List of external dependencies.
      */
      void setExternalDependencyList(const QString& externalDependencyList);

    private:
      QString _id;
      QString _gameId;
      QString _name;
      QUrl _url;
      QUrl _torrentUrl;
      QString _torrentFilePath;
      Area _area;
      QString _downloadPath;
      QString _installPath;
      QString _extractorType;
      bool _isDownloadable;
      bool _hashDownloadPath;
      bool _isDefaultInstallPath;
      QString _externalDependencyList;
    };
  }
}

Q_DECLARE_METATYPE(GGS::Core::Service);
Q_DECLARE_METATYPE(GGS::Core::Service*);
Q_DECLARE_METATYPE(const GGS::Core::Service*);
#endif //_GGS_CORE_SERVICE_H

