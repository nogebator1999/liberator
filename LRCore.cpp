#include "LRCore.h"
#include <QDir>

LRCore::LRCore(QObject *parent):
    QObject(parent),
    _networkRequests(0),
    _shotsCount(0),
    _on(false),
    _lastUpdateTime(0),
    _rpsNow(0)
{
    _shotsCount = 100;
}

LRCore::~LRCore()
{
    _updateTimer.stop();
}

int LRCore::prepare()
{
    _updateTimer.setInterval(100);
    connect(&_updateTimer, SIGNAL(timeout()), this, SLOT(onUpdateTimerFired()));
    _updateTimer.start();
    _timer.start();
    for (int i = 0; i < kRPSSnapshots; ++i)
        _rps[i] = 0;
    for (int i = 0; i < kRPMHistory; ++i)
        _rpmHistory[i] = 0;

    return 0;
}

void LRCore::onUpdateTimerFired()
{
    if (!_on)
        return;

    int newBulletsToShot = _shotsCount - (int)_shotsInFlight.size();

    if (newBulletsToShot <= 0)
        return;

    for (int i = 0; i < newBulletsToShot; ++i)
    {
        LRShot* shot = new LRShot(this);
        shot->setNetwork(getAvailableNetowrk());
        _shotsInFlight.insert(shot);

        int hostsCount = (int)_hosts.size();
        QString host = _hosts.at(rand() % hostsCount);
        shot->setURL(host);
        shot->setDelegate(this);
        shot->run();
    }

    updateStatus();
}

void LRCore::onBulletHit(LRShot* aShot, QNetworkReply::NetworkError aError)
{
    std::unordered_set<LRShot*>::iterator w = _shotsInFlight.find(aShot);
    if (w == _shotsInFlight.end())
        return;

    _shotsInFlight.erase(w);

    _stats.total++;
    _rpsNow++;
    if (aError != QNetworkReply::NetworkError::NoError)
        _stats.errors++;

    updateStatus();
}

void LRCore::updateStatus()
{
    int now = _timer.elapsed();

    int sinceLastUpdate = now - _lastUpdateTime;

    if (sinceLastUpdate > 1000)
    {
        static const int kTrendList = 3;
        int rpmTrend[kTrendList];
        for (int i = 0; i < kTrendList; ++i)
        {
            int v = _rpmHistory[i] - _rpmHistory[i + 1];
            if (v == 0)
            {
                // do nothing
            }
            else
            {
                v = (v < 0) ? (-1) : (1);
            }
            rpmTrend[i] = v;
        }

        int dirTrend[kTrendList];
        for (int i = 0; i < kTrendList; ++i)
        {
            int v = _dirHistory[i] - _dirHistory[i + 1];
            if (v == 0)
            {
                // do nothing
            }
            else
            {
                v = (v < 0) ? (-1) : (1);
            }
            dirTrend[i] = v;
        }

        for (int i = kRPMHistory - 1; i > 0; --i)
        {
            _rpmHistory[i] = _rpmHistory[i - 1];
            _dirHistory[i] = _dirHistory[i - 1];
        }

        _lastUpdateTime = now;
        for (int i = kRPSSnapshots - 1; i > 0; --i)
            _rps[i] = _rps[i - 1];

        _rps[0] = _rpsNow;
        _rpsNow = 0;

        int rpm = 0;
        for (int i = 0; i < kRPSSnapshots; ++i)
            rpm += _rps[i] * 60;

        rpm /= 5;

        _rpmHistory[0] = rpm;

        _stats.on = _on;
        _stats.rpm = rpm;

        if (_delegate != nullptr)
        {
            _delegate->onStatisticsUpdated(_stats);
        }

        int rpmFactor = 0;
        int dirFactor = 0;
        for (int i = 0; i < kTrendList; ++i)
        {
            rpmFactor += rpmTrend[i];
            dirFactor += dirTrend[i];
        }


        int direction = 1;

        if (rpmFactor < 0 && dirFactor > 1)
            direction = -1;

        _dirHistory[0] = direction;
    }
}

void LRCore::onSwitchStateClicked()
{
    _on = !_on;

    if (_on)
    {
        _stats.total = 0;
        _stats.errors = 0;
    }
}

LRNetwork::Ptr LRCore::getAvailableNetowrk()
{
    for (LRNetwork::Ptr& np : _networks)
    {
        if (np->refCount() < 6)
            return np;
    }

    LRNetwork::Ptr res = std::make_shared<LRNetwork>(this);

    _networks.push_back(res);

    return res;
}
