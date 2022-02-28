#include "LRNetwork.h"


LRNetwork::LRNetwork(QObject *parent):
    QObject(parent),
    _network(nullptr),
    _refCount(0)
{
    _network = std::make_shared<QNetworkAccessManager>(this);
}

LRNetwork::~LRNetwork()
{

}

