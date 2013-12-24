#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>   //import chinese
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());    //加入中文支持
    MainWindow w;
    w.show();
    
    return a.exec();
}
