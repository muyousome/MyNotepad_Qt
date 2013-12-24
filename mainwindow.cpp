#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isSaved = false; //初始化文件为未保存过状态
    curFile = tr("Untitled.txt"); //初始化文件名为“未命名.txt”     ps:用“Untitled"，中文乱码
    setWindowTitle(curFile); //初始化主窗口的标题
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::do_file_New()
{
    do_file_SaveOrNot();
    isSaved = false;
    curFile = tr("Untitled.txt");
    setWindowTitle(curFile);
    ui->textEdit->clear();
    //ui->textEdit->show();
    ui->textEdit->setVisible(true);     //show与setVisible区别
}


void MainWindow::do_file_SaveOrNot()
{
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox box;
        box.setWindowTitle(tr("警告"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile + tr("尚未保存，是否保存？"));
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        if(box.exec() == QMessageBox::Yes) //如果选择保存文件，则执行保存操作
        {
            do_file_Save();
        }

    }
}

void MainWindow::do_file_Save() //保存文件
{
    if(isSaved)
    { //如果文件已经被保存过，直接保存文件
        saveFile(curFile);
    }
    else
    {
        do_file_SaveAs(); //如果文件是第一次保存，那么调用另存为
    }
}


void MainWindow::do_file_SaveAs() //文件另存为
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("另存为"),curFile);
    //获得文件名
    if(!fileName.isEmpty()) //如果文件名不为空，则保存文件内容
    {
    saveFile(fileName);
    }
}


bool MainWindow::saveFile(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    //以只写方式打开文件，如果打开失败则弹出提示框并返回
    {
        QMessageBox::warning(this,tr("保存文件"),
        tr("无法保存文件 %1:\n %2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);   //新建流对象，指向选定的文件
    out << ui->textEdit->toPlainText();   //将文本编辑器里的内容以纯文本的形式输出到流对象中
    isSaved = true;
    curFile = QFileInfo(fileName).canonicalFilePath(); //获得文件的标准路径
    setWindowTitle(curFile); //将窗口名称改为现在窗口的路径
    return true;
}

void MainWindow::on_action_N_triggered()
{
    do_file_New();
}

void MainWindow::on_actionSave_S_triggered()
{
    do_file_Save();
}

void MainWindow::on_actionSave_As_S_triggered()
{
    do_file_SaveAs();
}
