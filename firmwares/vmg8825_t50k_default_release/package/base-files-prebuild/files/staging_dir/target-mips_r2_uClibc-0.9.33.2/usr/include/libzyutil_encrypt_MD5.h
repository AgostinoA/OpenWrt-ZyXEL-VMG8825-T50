#ifndef _ZCFG_BE_ENCRYPT_MD5_H
#define _ZCFG_BE_ENCRYPT_MD5_H

/*!
 *  get a MD5 encrypted string
 *
 *  @param [in] input               input of MD5 encryption
 *  @param [out] expected           output of MD5 encryption
 *
 */
void getExpectedContext_Openssl_MD5(char *input, unsigned char *expected);

#endif //_ZCFG_BE_ENCRYPT_MD5_H

