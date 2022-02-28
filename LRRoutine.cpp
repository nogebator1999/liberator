#include "LRRoutine.h"

LRRoutine::LRRoutine():
    _thread(nullptr),
    _core(nullptr)
{
    _thread = new QThread();
    _core = new LRCore();
    _core->moveToThread(_thread);
    _core->prepare();
    _thread->start();
}

LRRoutine::~LRRoutine()
{
    _thread->quit();
    _thread->wait();
}

