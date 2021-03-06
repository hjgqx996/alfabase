/**
 *  Copyright (c) 2016 AlfaLoop Technology Co., Ltd. All Rights Reserved.
 *
 *  Unauthorized copying of this file, via any medium is strictly prohibited
 *  Proprietary and confidential.
 *
 *  Attribution - You must give appropriate credit, provide a link to the license, and
 *  indicate if changes were made. You may do so in any reasonable manner, but not in any
 *  way that suggests the licensor endorses you or your use.
 *
 *  NonCommercial - You may not use the material for commercial purposes under unauthorized.
 *
 *  NoDerivatives - If you remix, transform, or build upon the material, you may not
 *  distribute the modified material.
 */
#ifndef _XOR_H__
#define _XOR_H__

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
unsigned char
static inline calculate_xor(unsigned char  *data, unsigned int len)
{
  unsigned char  XOR = 0;
  for (int i = 0; i < len; i++)
  {
    XOR = XOR ^ data[i];
  }
  return XOR;
}


#ifdef __cplusplus
}
#endif

#endif // _XOR_H__
