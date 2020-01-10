#include <QDebug>
#include "qcompressor.h"

int demo_main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    QString initialPlainText = "This is a test program for verifying that the QCompressor class works fine!";

    qDebug() << "Initial plain text is: " << initialPlainText;

    QByteArray compressed;

    if(QCompressor::gzipCompress(initialPlainText.toLatin1(), compressed))
    {
        qDebug() << "Compressed text length is:" << compressed.length();

        QByteArray decompressed;

        if(QCompressor::gzipDecompress(compressed, decompressed))
        {
            qDebug() << "Decompressed text is: " << QString::fromLatin1(decompressed);
        }
        else
            qDebug() << "Can't decompress";
    }
    else
        qDebug() << "Can't compress";
}
