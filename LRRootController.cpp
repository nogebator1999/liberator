#include "LRRootController.h"

LRRootController::LRRootController(int argc, char** argv):
    _app(argc, argv),
    _core (),
    _window (nullptr)
{
    QStringList hosts;
    hosts.append("https://gamedev.ru/");

    _core.prepare();
    _core.setTargetHosts(hosts);
    _core.setDelegate(this);
    _window = new MainWindow();
    _window->setDelegate(this);
}

int LRRootController::run()
{
    _window->show();
    return _app.exec();
}

void LRRootController::onSwitchStateClicked()
{
    _core.onSwitchStateClicked();
}

void LRRootController::onStatisticsUpdated(const Stats& aStats)
{
    _window->displayStatistics(aStats);
}
