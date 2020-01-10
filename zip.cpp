#include <QCoreApplication>
#include <zlib.h>
#include <QByteArray>

QByteArray gzip_compress(QByteArray postBody)
{
    QByteArray outBuf;
    z_stream c_stream;
    int err = 0;
    int GZIP_ENCODING = 16;

    outBuf.clear();
    if (postBody.isEmpty())
    {
        return outBuf;
    }

    c_stream.zalloc = (alloc_func)NULL;
    c_stream.zfree = (free_func)NULL;
    c_stream.opaque = (voidpf)NULL;
    c_stream.next_in = (Bytef *)postBody.data();
    c_stream.avail_in = postBody.size();

    if (deflateInit2(&c_stream,
                     Z_DEFAULT_COMPRESSION,
                     Z_DEFLATED,
                     MAX_WBITS + GZIP_ENCODING,
                     8,
                     Z_DEFAULT_STRATEGY) != Z_OK)
    {
        return QByteArray();
    }

    for (;;)
    {
        char destBuf[4096] = { 0 };

        c_stream.next_out = (Bytef *)destBuf;
        c_stream.avail_out = 4096;

        err = deflate(&c_stream, Z_FINISH);
        outBuf.append(destBuf, 4096 - c_stream.avail_out);
        if (err == Z_STREAM_END || err != Z_OK)
        {
            break;
        }
    }

    auto total = c_stream.total_out;
    deflateEnd(&c_stream);
    total = c_stream.total_out;

    (void)total;
    return outBuf;
}

QByteArray gzip_uncompress(QByteArray src)
{
    QByteArray outBuffer;
    z_stream strm;

    strm.zalloc = 0;
    strm.zfree = 0;
    strm.opaque = 0;
    strm.avail_in = src.size();
    strm.next_in = (Bytef *)src.data();

    int err = -1;
    err = inflateInit2(&strm, MAX_WBITS + 16);
    if (err == Z_OK)
    {
        while (true)
        {
            char buffer[4096] = { 0 };
            strm.avail_out = 4096;
            strm.next_out = (Bytef *)buffer;
            int code = inflate(&strm, Z_FINISH);
            outBuffer.append(buffer, 4096 - strm.avail_out);
            if (Z_STREAM_END == code || Z_OK != code)
            {
                break;
            }
        }
    }
    inflateEnd(&strm);

    return outBuffer;
}
