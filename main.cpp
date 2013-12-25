#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>   //import chinese
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // QTextCodec::setCodecForTr(QTextCodec::codecForLocale());    //加入中文支持
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
    MainWindow w;
    w.show();
    
    return a.exec();
}
