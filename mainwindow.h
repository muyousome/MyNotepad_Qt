#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_action_N_triggered();

    void on_actionSave_S_triggered();

    void on_actionSave_As_S_triggered();

private:
    Ui::MainWindow *ui;
    bool isSaved;   //文件是否保存过，ture为保存过
    QString curFile;    //当前文件名
    void do_file_New(); //新建文件
    void do_file_SaveOrNot(); //修改过的文件是否保存
    void do_file_Save(); //保存文件
    void do_file_SaveAs(); //文件另存为
    bool saveFile(const QString& fileName); //存储文件
};

#endif // MAINWINDOW_H
