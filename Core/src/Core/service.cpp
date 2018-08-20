#include <Core/Service.h>
#include <QtCore/QDir>
#include <QtCore/QDebug>

namespace P1 {
  namespace Core {
    Service::Service(QObject *parent)
      : QObject(parent)
    {
    }

    Service::Service(const Service &service) 
      : _id(service._id)
      , _gameId(service._gameId)
      , _name(service._name)
      , _displayName(service._displayName)
      , _url(service._url)
      , _torrentUrl(service._torrentUrl)
      , _torrentFilePath(service._torrentFilePath)
      , _area(service._area)
      , _downloadPath(service._downloadPath)
      , _installPath(service._installPath)
      , _extractorType(service._extractorType)
      , _isDownloadable(service._isDownloadable)
      , _hashDownloadPath(service._hashDownloadPath)
      , _isDefaultInstallPath(service._isDefaultInstallPath)
      , _externalDependencyList(service._externalDependencyList) 
      , _gameSize(service._gameSize)
      , _urlTemplate(service._urlTemplate)
    {
    }
    
    Service::~Service()
    {
    }

    Service& Service::operator=(const Service &service)
    {
      if (this == &service)      // Same object?
        return *this; 

      this->_id                   = service._id;
      this->_gameId               = service._gameId;
      this->_name                 = service._name;
      this->_displayName          = service._displayName;
      this->_url                  = service._url;
      this->_torrentUrl           = service._torrentUrl;
      this->_torrentFilePath      = service._torrentFilePath;
      this->_area                 = service._area;
      this->_downloadPath         = service._downloadPath;
      this->_installPath          = service._installPath;
      this->_extractorType        = service._extractorType;
      this->_isDownloadable       = service._isDownloadable;
      this->_hashDownloadPath     = service._hashDownloadPath;
      this->_isDefaultInstallPath = service._isDefaultInstallPath;
      this->_externalDependencyList = service._externalDependencyList;
      this->_gameSize             = service._gameSize;
      this->_urlTemplate          = service._urlTemplate;

      return *this;
    }

    void Service::setId(const QString &id)
    {
      this->_id = id;
    }

    const QString& Service::id() const
    {
      return this->_id;
    }

    void Service::setGameId(const QString &gameId)
    {
      this->_gameId = gameId;
    }

    const QString& Service::gameId() const
    {
      return this->_gameId;
    }

    void Service::setName(const QString &name)
    {
      this->_name = name;
    }

    const QString& Service::name() const
    {
      return this->_name;
    }

    void Service::setDisplayName(const QString &displayName)
    {
      this->_displayName = displayName;
    }

    const QString& Service::displayName() const
    {
      return this->_displayName;
    }

    void Service::setUrl(const QUrl &url)
    {
      this->_url = url;
    }

    const QUrl& Service::url() const
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

    void Service::setArea(Area area)
    {
      this->_area = area;
    }

    const P1::Core::Service::Area Service::area() const
    {
      return this->_area;
    }

    void Service::setTorrentFilePath(const QString& filePath)
    {
      this->_torrentFilePath = QDir::cleanPath(filePath);
    }

    const QString& Service::torrentFilePath() const
    {
      return this->_torrentFilePath;
    }

    void Service::setDownloadPath(const QString& dir)
    {
      this->_downloadPath = QDir::cleanPath(dir);
    }

    const QString& Service::downloadPath() const
    {
      return this->_downloadPath;
    }

    void Service::setInstallPath(const QString& directory)
    {
      this->_installPath = QDir::cleanPath(directory);
    }

    const QString& Service::installPath() const
    {
      return this->_installPath;
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
      QString area = this->areaString();
      area.append("/");
      return this->_torrentUrl.resolved(QUrl(area));
    }

    QString Service::areaString() const
    {
      switch(this->_area){
       case P1::Core::Service::Pts:
        return QString("pts");
       case P1::Core::Service::Tst:
        return QString("tst");
       case P1::Core::Service::Live: // не с проста пропущен break
       default:
         return QString("live");
      };
    }

    void Service::setIsDownloadable(bool isDownloadable)
    {
      this->_isDownloadable = isDownloadable;
    }

    bool Service::isDownloadable() const
    {
      return this->_isDownloadable;
    }

    bool Service::hashDownloadPath() const
    {
      return this->_hashDownloadPath;
    }

    void Service::setHashDownloadPath(bool hashDownloadPath)
    {
      this->_hashDownloadPath = hashDownloadPath;
    }

    bool Service::isDefaultInstallPath() const
    {
      return this->_isDefaultInstallPath;
    }

    void Service::setIsDefaultInstallPath(bool isDefaultInstallPath)
    {
      this->_isDefaultInstallPath = isDefaultInstallPath;
    }

    const QString& Service::externalDependencyList() const
    {
      return this->_externalDependencyList;
    }

    void Service::setExternalDependencyList(const QString& externalDependencyList)
    {
      this->_externalDependencyList = externalDependencyList;
    }

    quint64 Service::gameSize() const
    {
      return this->_gameSize;
    }

    void Service::setGameSize(quint64 val)
    {
      this->_gameSize = val;
    }

    const QString& Service::urlTemplate() const
    {
      return this->_urlTemplate;
    }

    void Service::setUrlTemplate(const QString& val)
    {
      this->_urlTemplate = val;
    }

  }
}