#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

qint32 has_parcel_header_flag = 0;
QString input_file_path = "";
QString output_file_path = "";
qint32 gzip_zip_flag = -1;
qint32 aes_cipher_flag = -1;

QString param_get_input_file_path(void)
{
    return input_file_path;
}

QString param_get_output_file_path(void)
{
    return output_file_path;
}

qint32 param_need_aes_encryption(void)
{
    return (1 == aes_cipher_flag);
}

qint32 param_need_aes_decryption(void)
{
    return (0 == aes_cipher_flag);
}

qint32 param_need_gzip_compression(void)
{
    return (1 == gzip_zip_flag);
}

qint32 param_need_gzip_decompression(void)
{
    return (0 == gzip_zip_flag);
}

qint32 param_handle(QCoreApplication &a)
{
    bool ok;
    QCommandLineParser parser;

    parser.setApplicationDescription("pareling_binary");
    parser.addHelpOption();
    parser.addVersionOption();
    ok = parser.addOptions(
    {
        {   {"i", "in"},
            QCoreApplication::translate("main", "input file"),
            QCoreApplication::translate("main", "input"),
            "image.bin"
        },
        {   {"o", "out"},
            QCoreApplication::translate("main", "output file"),
            QCoreApplication::translate("main", "output"),
            "image_parcel.bin"
        },
        {   {"g", "gzip"},
            QCoreApplication::translate("main", "gzip 1:compress; 0:decompress"),
            QCoreApplication::translate("main", "zip")
        },
        {   {"a", "aes"},
            QCoreApplication::translate("main", "aes 1:encrypt; 0:decrypt"),
            QCoreApplication::translate("main", "cipher")
        },
        {   {"d", "header"},
            QCoreApplication::translate("main", "header field")
        },
    });
    Q_ASSERT_X((true == ok), "addOptions", "add exception");
    parser.process(a);

    input_file_path = parser.values("i").at(0);
    output_file_path = parser.values("o").at(0);
    has_parcel_header_flag = parser.isSet("header");
    gzip_zip_flag = parser.values("g").at(0).toLong();
    aes_cipher_flag = parser.values("a").at(0).toLong();

    if(gzip_zip_flag != aes_cipher_flag)
    {
        return false;
    }

    return true;
}
