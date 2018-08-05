#include "utils.h"

QStringList readText(QString name)
{
    QFile file(name);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox msg;
        msg.setWindowTitle("Warning");
        msg.setText("The file coun't be opened! (Utils)         ");
        msg.exec();
    }
    QTextStream in(&file);
    QString line = in.readAll();
    QStringList list = line.split("\n");
    return list;
}
