#include "mainwindow.h"

#include <QApplication>
#include "LRRootController.h"

int main(int argc, char *argv[])
{

    LRRootController root(argc, argv);
    return root.run();
}
