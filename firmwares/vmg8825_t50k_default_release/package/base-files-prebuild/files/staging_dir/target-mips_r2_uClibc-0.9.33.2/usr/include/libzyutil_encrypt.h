#ifndef _ZCFG_BE_ENCRYPT_H
#define _ZCFG_BE_ENCRYPT_H

typedef enum {
    Encrypt_SHA256 = 1,
    Encrypt_MD5,
    Encrypt_OPENSSL_MD5
} EncryptAlgo_t;

/*!
 *  get a encrypted string
 *
 *  @param [in] encrypt         encryption algorithm
 *  @param [in] Input           encryption input
 *  @param [out] Output         encryption output
 *
 *  @return     0               successfully
 *              -1              fail
 */
int getExpectedContext(EncryptAlgo_t encrypt, char *Input, unsigned char *Output);

#endif
