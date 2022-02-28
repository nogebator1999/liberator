#include "LRShot.h"

LRShot::LRShot(QObject *parent):
    QObject(parent),
    _request (nullptr),
    _reply (nullptr),
    _delegate (nullptr)
{
    _request = new QNetworkRequest();
}


LRShot::~LRShot()
{
    if (_network != nullptr)
    {
        _network->release();
        _network = nullptr;
    }
}

void LRShot::setProxy(const QString& host, int port, const QString& userName, const QString& password)
{
    QNetworkProxy proxy = _network->network()->proxy();

    if (host.isEmpty())
    {
        proxy.setType(QNetworkProxy::DefaultProxy);
    }
    else
    {
        proxy.setHostName(host);
        proxy.setPort(port);
        if (!userName.isEmpty() && !password.isEmpty())
        {
            proxy.setUser(userName);
            proxy.setPassword(password);
        }
        proxy.setType(QNetworkProxy::HttpProxy);
    }

    _network->network()->setProxy(proxy);
}

void LRShot::setURL(const QString& targetURL)
{
    _request->setUrl(QUrl(targetURL));
}

void LRShot::run()
{
    if (_reply != nullptr)
        return;

    _netManager = nullptr;
    if (_network.get() != nullptr)
        _netManager = _network->network();


    if (_netManager.get() == nullptr)
        _netManager = std::make_shared<QNetworkAccessManager>(this);

    connect(_netManager.get(),
            SIGNAL(finished(QNetworkReply*)), this,
            SLOT(replyFinished(QNetworkReply*)), Qt::ConnectionType::DirectConnection);

    _reply = _netManager->get(*_request);

    connect(_reply,
            SIGNAL(downloadProgress(qint64,qint64)), this,
            SLOT(downloadProgress(qint64,qint64)), Qt::ConnectionType::DirectConnection);
}

void LRShot::replyFinished(QNetworkReply *reply)
{
    reportSuccess(false);
}

void LRShot::downloadProgress(qint64, qint64)
{
    reportSuccess(true);
}

void LRShot::reportSuccess(bool alsoAbort)
{
    if (_reply == nullptr)
        return;

    _error = _reply->error();

    if (_delegate != nullptr)
    {
        _delegate->onBulletHit(this, _error);
    }

    if (alsoAbort)
        _reply->abort();
    _reply = nullptr;

    if (_network != nullptr)
    {
        _network->release();
        _network = nullptr;
    }
}

void LRShot::setNetwork(LRNetwork::Ptr aNetwork)
{
    if (_network != nullptr)
        _network->release();

    _network = aNetwork;
    if (_network != nullptr)
        _network->retain();
}
