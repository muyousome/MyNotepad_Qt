#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isSaved = false; //初始化文件为未保存过状态
    curFile = tr("未命名.txt"); //初始化文件名为“未命名.txt”     ps:用“Untitled"，中文乱码
    setWindowTitle(curFile); //初始化主窗口的标题
    init_statusBar();
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(do_cursorChanged()));
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
    second_statusLabel->setText(tr("保存文件成功"));
    return true;
}


void MainWindow::do_file_Open()
{
    do_file_SaveOrNot();
    QString fileName = QFileDialog::getOpenFileName(this);
    //获得要打开的文件的名字
    if(!fileName.isEmpty())//如果文件名不为空
    {
        do_file_Load(fileName);
    }
    ui->textEdit->setVisible(true);//文本编辑器可见
}


bool MainWindow::do_file_Load(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,tr("读取文件"),tr("无法读取文件 %1:\n%2.").arg(fileName).arg(file.errorString()));
        return false;      //如果打开文件失败，弹出对话框，并返回
    }
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());      //将文件中的所有内容都写到文本编辑器中
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    second_statusLabel->setText(tr("打开文件成功"));
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

void MainWindow::on_actionD_triggered()
{
    do_file_Open();
}

void MainWindow::on_actionClose_triggered()
{
    do_file_SaveOrNot();
    ui->textEdit->setVisible(false);
    setWindowTitle("MyNotepd");
    first_statusLabel->setText(tr("文本编辑器已关闭"));
}



void MainWindow::on_actionExit_X_triggered()
{
    on_actionClose_triggered();     //先执行关闭操作
    qApp->quit();    //再退出系统，qApp是指向应用程序的全局指针
}


void MainWindow::on_actionU_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionSearch_triggered()
{
    QDialog *findDlg = new QDialog(this);
    //新建一个对话框，用于查找操作，this表明它的父窗口是MainWindow。

    findDlg->setWindowTitle(tr("查找"));
    //设置对话框的标题

    find_textLineEdit = new QLineEdit(findDlg);
    //将行编辑器加入到新建的查找对话框中

    QPushButton *find_Btn = new QPushButton(tr("查找下一个"),findDlg);
    //加入一个“查找下一个”的按钮

    QVBoxLayout* layout = new QVBoxLayout(findDlg);
    layout->addWidget(find_textLineEdit);
    layout->addWidget(find_Btn);
    //新建一个垂直布局管理器，并将行编辑器和按钮加入其中

    findDlg ->show();
    //显示对话框

    connect(find_Btn,SIGNAL(clicked()),this,SLOT(show_findText()));
    //设置“查找下一个”按钮的单击事件和其槽函数的关联

    second_statusLabel->setText(tr("正在进行查找"));
}

void MainWindow::show_findText()
{
    QString findText = find_textLineEdit->text();

    //将行编辑器中的内容在文本编辑器中进行查找
    if(!ui->textEdit->find(findText,QTextDocument::FindBackward))
    {
        QMessageBox::warning(this,tr("查找"),tr("找不到 %1").arg(findText));
    }
}


void MainWindow::init_statusBar()
{
    QStatusBar* bar = ui->statusBar; //获取状态栏

    first_statusLabel = new QLabel; //新建标签
    first_statusLabel->setMinimumSize(150,20); //设置标签最小尺寸
    //first_statusLabel->setFrameShape(QFrame::WinPanel); //设置标签形状
    first_statusLabel->setFrameShadow(QFrame::Sunken); //设置标签阴影

    second_statusLabel = new QLabel;
    second_statusLabel->setMinimumSize(150,20);
    //second_statusLabel->setFrameShape(QFrame::WinPanel);
    second_statusLabel->setFrameShadow(QFrame::Sunken);

    bar->addWidget(first_statusLabel);
    bar->addWidget(second_statusLabel);

    first_statusLabel->setText(tr("欢迎使用MyNotepad")); //初始化内容
    second_statusLabel->setText(tr(""));
}


void MainWindow::do_cursorChanged()
{
    int rowNum = ui->textEdit->document()->blockCount();
    //获取光标所在行的行号

    const QTextCursor cursor = ui->textEdit->textCursor();
    int colNum = cursor.columnNumber();
    //获取光标所在列的列号

    first_statusLabel->setText(tr("%1行 %2列").arg(rowNum).arg(colNum));
    //在状态栏显示光标位置
}
