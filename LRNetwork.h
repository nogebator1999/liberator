#ifndef LRNETWORK_H
#define LRNETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <memory>

class LRNetwork: public QObject
{
    Q_OBJECT
public:
    typedef std::shared_ptr<LRNetwork> Ptr;
public:
    LRNetwork(QObject *parent = nullptr);
    ~LRNetwork();

    void retain() { _refCount++; }
    void release() { _refCount--; }
    int refCount() { return _refCount; }

    std::shared_ptr<QNetworkAccessManager> network() { return _network; }

private:

    std::shared_ptr<QNetworkAccessManager> _network;
    int _refCount;
};

#endif // LRNETWORK_H
