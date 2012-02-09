#ifndef BASE64_H
#define BASE64_H

extern unsigned char *base64_encode(const unsigned char *, int, int *);
extern unsigned char *base64_decode(const unsigned char *, int, int *);

#endif /* BASE64_H */