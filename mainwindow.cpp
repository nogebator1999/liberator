#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _delegate(nullptr)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    connect(ui->switchButton,
            SIGNAL(clicked(bool)), this,
            SLOT(onSwitchClicked(bool)), Qt::ConnectionType::QueuedConnection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSwitchClicked(bool checked)
{
    if (_delegate != nullptr)
    {
        _delegate->onSwitchStateClicked();
    }
}

void MainWindow::displayStatistics(const Stats& aStats)
{
    ui->lblSent->setText(QString::number(aStats.total));
    ui->lblErrors->setText(QString::number(aStats.errors));
    int percent = 0;
    if (aStats.total > 0 && aStats.errors > 0)
        percent = 100 * aStats.errors / aStats.total;

    ui->lblPercentErrors->setText(QString::number(percent) + "%");
    ui->lblRPM->setText(QString::number(aStats.rpm));
    ui->lblStatus->setText(aStats.on ? "Вкл" : "Выкл");
}
