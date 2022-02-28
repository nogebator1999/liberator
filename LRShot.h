#pragma once

#include <QObject>
#include <QNetworkProxy>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "LRNetwork.h"

class LRShot: public QObject
{
    Q_OBJECT
public:

    class IDelegate
    {
    public:
        IDelegate() {}
        virtual ~IDelegate() {}

        virtual void onBulletHit(LRShot* aShot, QNetworkReply::NetworkError aError) = 0;
    };

    explicit LRShot(QObject *parent = nullptr);
    ~LRShot();
    void setNetwork(LRNetwork::Ptr aNet);
    void setProxy(const QString& host, int port, const QString& userName, const QString& password);
    void setURL(const QString& targetURL);
    void run();
    void setDelegate(IDelegate* aDelegate) { _delegate = aDelegate; }
public slots:
    void replyFinished(QNetworkReply *reply);
    void downloadProgress(qint64, qint64);
private:
    void reportSuccess(bool alsoAbort);
private:
    LRNetwork::Ptr _network;
    std::shared_ptr<QNetworkAccessManager> _netManager;
    QNetworkRequest* _request;
    QNetworkReply* _reply;
    QNetworkReply::NetworkError _error;
    IDelegate* _delegate;
};

