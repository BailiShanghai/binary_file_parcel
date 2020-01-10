#include <QCoreApplication>
#include <QDebug>
#include "cli_param.h"
#include "parcel.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("binary_file_parcel");
    QCoreApplication::setApplicationVersion("ver1.0.2");

    if(false == param_handle(a))
    {
        qDebug() << "parameter setting exceptional";
        return 1;
    }
    parcle_handle();

    return a.exec();
}
// eof

