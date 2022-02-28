#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "IUIDelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setDelegate(IUIDelegate* aDelegate) { _delegate = aDelegate; }
    void displayStatistics(const Stats& aStats);

public slots:
    void onSwitchClicked(bool checked);

private:
    Ui::MainWindow *ui;
    IUIDelegate* _delegate;
};
#endif // MAINWINDOW_H
