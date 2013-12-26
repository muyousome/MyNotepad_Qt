#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>

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

    void on_actionD_triggered();

    void on_actionClose_triggered();

    void on_actionExit_X_triggered();

    void on_actionU_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionCopy_triggered();

    void on_actionSearch_triggered();

    void show_findText();

    void do_cursorChanged(); //获取光标位置信息


private:
    Ui::MainWindow *ui;

    QLineEdit *find_textLineEdit;

    bool isSaved;   //文件是否保存过，ture为保存过
    QString curFile;    //当前文件名
    void do_file_New(); //新建文件
    void do_file_SaveOrNot(); //修改过的文件是否保存
    void do_file_Save(); //保存文件
    void do_file_SaveAs(); //文件另存为
    bool saveFile(const QString& fileName); //存储文件
    void do_file_Open(); //打开文件
    bool do_file_Load(const QString& fileName); //读取文件

    QLabel* first_statusLabel; //声明两个标签对象，用于显示状态信息
    QLabel* second_statusLabel;

    void init_statusBar(); //初始化状态栏

};

#endif // MAINWINDOW_H
