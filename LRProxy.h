#ifndef LRPROXY_H
#define LRPROXY_H

#include <vector>
#include <QString>


class LRProxy
{
public:
    typedef std::vector<LRProxy> List;
public:
    LRProxy(): _port(-1) {}
    LRProxy(const QString& aHost, int aPort):
        _host(aHost),
        _port(aPort)
    {}
    LRProxy(const QString& aHost, int aPort, const QString& aUsername, const QString& aPassword):
        _host(aHost),
        _port(aPort),
        _username(aUsername),
        _password(aPassword)
    {}
    ~LRProxy() {}

    const QString& host() const { return _host; }
    int port() const { return _port; }
    const QString& username() const { return _username; }
    const QString& password() const { return _password; }

    static int fromFile(const QString& aPath, LRProxy::List& output);

private:
    QString _host;
    int _port;
    QString _username;
    QString _password;
};

#endif // LRPROXY_H
