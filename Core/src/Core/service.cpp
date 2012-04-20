#include <Core/service.h>
#include <QDebug>

namespace GGS {
  namespace Core {
    Service::Service(QObject *parent)
      : QObject(parent)
    {
    }

    Service::Service(const Service &service) 
      : _id(service._id)
      , _gameId(service._gameId)
      , _name(service._name)
      , _url(service._url)
      , _torrentUrl(service._torrentUrl)
      , _area(service._area)
      , _torrentFilePath(service._torrentFilePath)
      , _downloadPath(service._downloadPath)
      , _extractionPath(service._extractionPath)
      , _extractorType(service._extractorType) //UNDONE
    {
    }
    
    Service::~Service()
    {
    }

    Service &Service::operator=(const Service &service)
    {
      this->_id = service._id;
      this->_gameId = service._gameId;
      this->_name =service._name;
      this->_url = service._url;

      return *this;
    }

    void Service::setId( const QString &id )
    {
      this->_id = id;
    }

    const QString & Service::id() const
    {
      return this->_id;
    }

    void Service::setGameId( const QString &gameId )
    {
      this->_gameId = gameId;
    }

    const QString & Service::gameId() const
    {
      return this->_gameId;
    }

    void Service::setName( const QString &name )
    {
      this->_name = name;
    }

    const QString & Service::name() const
    {
      return this->_name;
    }

    void Service::setUrl( const QUrl &url )
    {
      this->_url = url;
    }

    const QUrl & Service::url() const
    {
      return this->_url;
    }

    void Service::setTorrentUrl(const QUrl& url)
    {
      this->_torrentUrl = url;
    }

    const QUrl& Service::torrentUrl() const
    {
      return this->_torrentUrl;
    }

    void Service::setArea( Area area )
    {
      this->_area = area;
    }

    const GGS::Core::Service::Area Service::area() const
    {
      return this->_area;
    }

    void Service::setTorrentFilePath(const QString& filePath)
    {
      this->_torrentFilePath = filePath;
    }

    const QString& Service::torrentFilePath() const
    {
      return this->_torrentFilePath;
    }

    void Service::setDownloadPath(const QString& dir)
    {
      this->_downloadPath = dir;
    }

    const QString& Service::downloadPath() const
    {
      return this->_downloadPath;
    }

    void Service::setExtractionPath(const QString& directory)
    {
      this->_extractionPath = directory;
    }

    const QString& Service::extractionPath() const
    {
      return this->_extractionPath;
    }

    void Service::setExtractorType(const QString& type)
    {
      this->_extractorType = type;
    }

    const QString& Service::extractorType() const
    {
      return this->_extractorType;
    }

    const QUrl Service::torrentUrlWithArea() const
    {
      QString area;
      if (Live == this->_area) {
        area = "live";
      } else if (Pts == this->_area) {
        area = "pts";
      } else {
        area = "tst";
      }

      area.append("/");
      return this->_torrentUrl.resolved(QUrl(area));
    }
  }
}