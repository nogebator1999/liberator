#ifndef LRROOTCONTROLLER_H
#define LRROOTCONTROLLER_H

#include <QApplication>
#include "IUIDelegate.h"
#include "LRCore.h"
#include "mainwindow.h"


class LRRootController: public IUIDelegate, public ICoreDelegate
{
public:
    LRRootController(int argc, char** argv);
    void onSwitchStateClicked() override;

    void onStatisticsUpdated(const Stats& aStats) override;

    int run();
private:
    QApplication _app;
    LRCore _core;
    MainWindow* _window;
};

#endif // LRROOTCONTROLLER_H
