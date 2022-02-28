#pragma once

#include <QObject>
#include <QList>
#include <QString>
#include <QTimer>
#include <QElapsedTimer>
#include <unordered_set>
#include <memory>

#include "LRShot.h"
#include "LRProxy.h"
#include "IUIDelegate.h"
#include "LRNetwork.h"

class LRCore : public QObject, public LRShot::IDelegate, public IUIDelegate
{
    Q_OBJECT
public:
    static const int kRPSSnapshots = 5;
    static const int kRPMHistory = 10;

public:

    explicit LRCore(QObject *parent = nullptr);
    ~LRCore();

    int prepare();

    void setTargetHosts(const QStringList& aHosts) { _hosts = aHosts; }

    void setOn(bool aOn) { _on = aOn; }

    bool isOn() const { return _on; }

    void onBulletHit(LRShot* aShot, QNetworkReply::NetworkError aError) override;

    void updateStatus();

    void onSwitchStateClicked() override;

    void setDelegate(ICoreDelegate* aDelegate) { _delegate = aDelegate; }

public slots:

    void onUpdateTimerFired();

signals:

private:
    LRNetwork::Ptr getAvailableNetowrk();

private:
    std::unordered_set<LRShot*> _shotsInFlight;
    LRProxy::List _proxies;
    ICoreDelegate* _delegate;
    int _networkRequests;

    QStringList _hosts;
    int _shotsCount;
    bool _on;

    QTimer _updateTimer;
    Stats _stats;

    int _sinceLastUpdate;
    QElapsedTimer _timer;
    int _lastUpdateTime;
    int _rps[kRPSSnapshots];
    int _rpsNow;
    int _rpmHistory[kRPMHistory];
    int _dirHistory[kRPMHistory];

    std::vector<LRNetwork::Ptr> _networks;
};

