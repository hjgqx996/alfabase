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
#include <stddef.h> /* for size_t */
#include "symbol-std.h"
#include "symtab.h"
#include "string.h"

// STDLib System Call API
/*void *memcpy(void *dest, const void *src, size_t n)
{
    char *dp = dest;
    const char *sp = src;
    while (n--)
        *dp++ = *sp++;
    return dest;
}
int memcmp(const void* s1, const void* s2,size_t n)
{
    const unsigned char *p1 = s1, *p2 = s2;
    while(n--)
        if( *p1 != *p2 )
            return *p1 - *p2;
        else
            p1++,p2++;
    return 0;
}
void *memchr(const void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char*)s;
    while( n-- )
        if( *p != (unsigned char)c )
            p++;
        else
            return p;
    return 0;
}
void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char tmp[n];
    memcpy(tmp,src,n);
    memcpy(dest,tmp,n);
    return dest;
}
void *memset(void *s, int c, size_t n)
{
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}
int strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1==*s2))
        s1++,s2++;
    return *(const unsigned char*)s1-*(const unsigned char*)s2;
}
size_t strlen(const char *s) {
    const char *p = s;
    while (*s) ++s;
    return s - p;
}
int strncmp(const char* s1, const char* s2, size_t n)
{
    while(n--)
        if(*s1++!=*s2++)
            return *(unsigned char*)(s1 - 1) - *(unsigned char*)(s2 - 1);
    return 0;
}
static struct symbols symbol_memchr = {
	.name = "memchr",
	.value = (void *)&memchr
};

static struct symbols symbol_memcmp = {
	.name = "memcmp",
	.value = (void *)&memcmp
};

static struct symbols symbol_memcpy = {
	.name = "memcpy",
	.value = (void *)&memcpy
};

static struct symbols symbol_memmove = {
	.name = "memmove",
	.value = (void *)&memmove
};

static struct symbols symbol_memset = {
	.name = "memset",
	.value = (void *)&memset
};

static struct symbols symbol_strcmp = {
	.name = "strcmp",
	.value = (void *)&strcmp
};

static struct symbols symbol_strlen = {
	.name = "strlen",
	.value = (void *)&strlen
};

static struct symbols symbol_strncmp = {
	.name = "strncmp",
	.value = (void *)&strncmp
};

static struct symbols symbolOSMemcpy = {
	.name = "strncmp",
	.value = (void *)&strncmp
};
*/
void
symbol_std_init(void)
{
	/*symtab_add(&symbol_memchr);
	symtab_add(&symbol_memcmp);
	symtab_add(&symbol_memcpy);
	symtab_add(&symbol_memmove);
	symtab_add(&symbol_memset);
	symtab_add(&symbol_strcmp);
	symtab_add(&symbol_strlen);
	symtab_add(&symbol_strncmp);*/
}
