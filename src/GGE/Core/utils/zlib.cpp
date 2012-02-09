#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <zlib/zlib.h>

#include  <GGE/Core/utils/zlib.hpp>

/**
 * Inflates either zlib or gzip deflated memory. The inflated memory is
 * expected to be freed by the caller.
 */
int inflateMemory(unsigned char *in, unsigned int inLength,
                  unsigned char *&out, unsigned int &outLength)
{
    int bufferSize = 256 * 1024;
    int ret;
    z_stream strm;

    out = (unsigned char*) malloc(bufferSize);

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = in;
    strm.avail_in = inLength;
    strm.next_out = out;
    strm.avail_out = bufferSize;

    ret = inflateInit2(&strm, 15 + 32);

    if (ret != Z_OK)
        return ret;

    do
    {
        if (strm.next_out == NULL)
        {
            inflateEnd(&strm);
            return Z_MEM_ERROR;
        }

        ret = inflate(&strm, Z_NO_FLUSH);
        assert(ret != Z_STREAM_ERROR);

        switch (ret)
        {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void) inflateEnd(&strm);
                return ret;
        }

        if (ret != Z_STREAM_END)
        {
            out = (unsigned char*) realloc(out, bufferSize * 2);

            if (out == NULL)
            {
                inflateEnd(&strm);
                return Z_MEM_ERROR;
            }

            strm.next_out = out + bufferSize;
            strm.avail_out = bufferSize;
            bufferSize *= 2;
        }
    }
    while (ret != Z_STREAM_END);
    assert(strm.avail_in == 0);

    outLength = bufferSize - strm.avail_out;
    (void) inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int inflateMemory(unsigned char *in, unsigned int inLength,
                  unsigned char *&out)
{
    unsigned int outLength = 0;
    int ret = inflateMemory(in, inLength, out, outLength);

    if (ret != Z_OK || out == NULL)
    {
        if (ret == Z_MEM_ERROR)
        {
            std::cerr << "Error: Out of memory while decompressing data!" << std::endl;
        }
        else if (ret == Z_VERSION_ERROR)
        {
            std::cerr << "Error: Incompatible zlib version!" << std::endl;
        }
        else if (ret == Z_DATA_ERROR)
        {
            std::cerr << "Error: Incorrect zlib compressed data!" << std::endl;
        }
        else
        {
            std::cerr << "Error: Unknown error while decompressing data!" << std::endl;
        }

        free(out);
        out = NULL;
        outLength = 0;
    }

    return outLength;
}

void *loadCompressedFile(const std::string &filename, int &filesize)
{
    std::ifstream file;
    file.open(filename.c_str(), std::ios::in);

    if (file.is_open())
    {
        // Get length of file
        file.seekg (0, std::ios::end);
        filesize = file.tellg();
        file.seekg(0, std::ios::beg);

        char *buffer = (char *) malloc(filesize);

        file.read(buffer, filesize);
        file.close();

        unsigned char *inflated;
        unsigned int inflatedSize;

        if (inflated && filename.find(".gz", filename.length() - 3)
                != std::string::npos)
        {
            // Inflate the gzipped map data
            inflatedSize =
                inflateMemory((unsigned char*) buffer, filesize, inflated);
            free(buffer);

            if (inflated == NULL)
            {
                std::cerr << "Could not decompress file: " << filename.c_str() << std::endl;
                return NULL;
            }

            filesize = inflatedSize;
            return inflated;
        }
        else
        {
            return buffer;
        }
    }
    else
    {
        std::cerr << "Error loading file from drive: " << filename.c_str() << std::endl;
    }

    return NULL;
}
