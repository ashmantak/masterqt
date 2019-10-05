#include <QtGui>
#include <QApplication>
#include <QLabel>


void updatebinary(){
    // create the executable qt project

    QString slavefolder="/home/ashmantak/temp/executable/slave";
    QString resourcedir="/home/ashmantak/temp/resource";
    QString resourcefilename=resourcedir+"/qtres.qrc";

    QDir().setCurrent(resourcedir);

    //QProcess::execute("qmake-project");

    //recompile the resource to binary
    QFile resourcefile(resourcefilename);
    if(resourcefile.exists()){
        resourcefile.remove();
    }

    if ( resourcefile.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &resourcefile );
        stream << "<RCC version>"+
                  "<qresource>"+
                      "<file>file.xlsm</file>"+
                  "</qresource>"+
                  "</RCC>" << endl;
    }

    QProcess::execute("qmake && make");

    QDir().setCurrent(resourcedir);

    QString resourcecompilecommand="rcc -binary qtres.qrc -o qtres.rcc";


    QProcess::execute(resourcecompilecommand);


    //QProcess::execute("xdg-open "+filename);

    //QMessageBox::information(this,tr("The executable is created at "),filename);

}



int main(int argc, char **argv) {
    QApplication app(argc, argv);
    //QLabel label("Hello, world!");
    //label.show();
    QString resourcedir="/home/ashmantak/temp/resource";
    QString resourcecompiledfile="/home/ashmantak/temp/resource/qtres.rcc";



    QResource::registerResource(resourcecompiledfile);

    QFile::copy(":/MyFiles/file1.xlsm" , "/home/ashmantak/temp/file1.xlsm");

    QFile("/home/ashmantak/temp/file1.xlsm").setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);

    //  QProcess process;
    //  process.start("gnome-open",QStringList() << "/tmp/file.xlsm");

    QProcess::execute("xdg-open /home/ashmantak/temp/file1.xlsm");
    //:wq sQProcess::execute("xdg-open :/MyFiles/file.xlsm");
    updatebinary();
    return app.exec();
}


