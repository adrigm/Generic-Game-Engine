#ifndef UTILS_ZLIB_H
#define UTILS_ZLIB_H

#include <string>

/**
 * Inflates either zlib or gzip deflated memory. The inflated memory is
 * expected to be freed by the caller.
 */
int inflateMemory(unsigned char *in, unsigned int inLength,
                  unsigned char *&out, unsigned int &outLength);

int inflateMemory(unsigned char *in, unsigned int inLength,
                  unsigned char *&out);

/**
 * Loads the given file from the filesystem, uncompressing if it ends in ".gz".
 *
 * @param filename The name of the file to be loaded and uncompressed
 * @param filesize The size of the file that was loaded and uncompressed.
 *
 * @return An allocated byte array containing the data that was loaded and
 *         uncompressed, or <code>NULL</code> on fail.
 */
void *loadCompressedFile(const std::string &filename, int &filesize);

#endif // UTILS_ZLIB_H