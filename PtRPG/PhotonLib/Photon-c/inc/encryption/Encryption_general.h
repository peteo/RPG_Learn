#ifndef __ENCRYPTION_H
#define __ENCRYPTION_H

#ifdef __cplusplus
extern "C"
{
#endif

void _xor(nByte* value1, nByte* value2, int length, nByte** result);
int padding(nByte* data, int dataSize);

#ifdef __cplusplus
}
#endif

#endif // __ENCRYPTION_H__