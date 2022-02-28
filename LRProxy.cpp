#include "LRProxy.h"
#include <QFile>
#include <QDebug>


int LRProxy::fromFile(const QString& aPath, LRProxy::List& aOutput)
{
    if (aPath.isEmpty())
        return -1;

    QFile file(aPath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error" << file.errorString();
        return -1;
    }

    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(":");
        if (fields.size() != 2)
            continue;

        QString host = fields[0];
        if (host.isEmpty())
            continue;

        bool ok = false;
        int port = fields[1].toInt(&ok);

        if (!ok)
            continue;

        aOutput.push_back(LRProxy(host, port));
    }

    file.close();

    return (int)aOutput.size();
}
