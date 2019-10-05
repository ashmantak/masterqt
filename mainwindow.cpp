#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QProcess>
#include <QTextStream>

QString filename;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // create the executable qt project
    //Select the location where you want to create the executable
    QString tempfolder="/home/ashmantak/temp/";
    QString exefolder="/home/ashmantak/temp/executable";
    QString slavefolder="/home/ashmantak/temp/executable/slave";
    QString resourcedir="/home/ashmantak/temp/resource";
    QString resourcefilename=resourcedir+"/qtres.qrc";



    QString resourcecompilecommand="rcc -binary qtres.qrc -o qtres.rcc";


     if(!QDir(resourcedir).exists()){
         QDir().mkdir(resourcedir);
     }

     QFile resourcefileold(resourcefilename);

    if(resourcefileold.exists()){
        resourcefileold.remove();
    }

    QFile resourcefile(resourcefilename);


    if ( resourcefile.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &resourcefile );
        stream << "<RCC>\n";
        stream<< "<qresource>\n";
        stream<<"<file>file.xlsm</file>\n";
        stream<<"</qresource>\n";
        stream<<"</RCC>";
    }



 QProcess::execute(resourcecompilecommand);

    if(!QDir(exefolder).exists()){
        QDir().mkdir(exefolder);
    }

    QDir().mkdir(slavefolder);

    // QDir().setCurrent(slavefolder);


    filename=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/home/ashmantak/qtcreator/myfiles",
                "All Files(*.*);Xcel Macro(*.xlsm)"
                );
    QMessageBox::information(this,tr("File Name"),filename);

    QString destfilename=slavefolder+"/worker.cpp";
    QString projectfilestring=slavefolder+"/slave.pro";


    QFile::copy(":/code/worker.cpp" ,destfilename );

    QString inputfilename=resourcedir+"/file.xlsm";

    QFile inputfile(inputfilename);

    if(inputfile.exists()){
        inputfile.remove();
    }

    QFile::copy(filename,resourcedir+"/file.xlsm");

    QDir().setCurrent(resourcedir);
    QProcess::execute(resourcecompilecommand);

    QDir().setCurrent(slavefolder);

    QString qmakecommand="qmake -project \"QT += widgets\" && qmake && make";

    QProcess::execute(qmakecommand);

   // QProcess::execute(qmake && make);

    //QProcess::execute("xdg-open "+filename);

    //QMessageBox::information(this,tr("The executable is created at "),filename);
}
