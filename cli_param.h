#ifndef _CLI_PARAM_H_
#define _CLI_PARAM_H_

#include <QCoreApplication>
#include <QtGlobal>

qint32 param_handle(QCoreApplication &a);
QString param_get_input_file_path(void);
QString param_get_output_file_path(void);
qint32 param_need_aes_encryption(void);
qint32 param_need_aes_decryption(void);
qint32 param_need_gzip_compression(void);
qint32 param_need_gzip_decompression(void);
#endif
// eof
