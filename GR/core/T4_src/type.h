#pragma once
#include <stdint.h>

#define TRUE  1
#define FALSE  0

/* Little Endian */
#if defined(R8C) || defined(M16C) || defined(M16C80) || defined(M32C80) ||\
 (defined(_SH4) && defined(_LIT)) ||\
 (defined(_SH4A) && defined(_LIT)) ||\
 (defined(__RX) && defined(__LIT)) ||\
    defined(__v850)
#define  BIGENDIAN 0

/* Big Endian */
#elif defined(__300HA__) || defined (__2600A__) ||\
   defined(_SH2) || defined(_SH2A) || defined(_SH2AFPU) ||\
   (defined(_SH4) && defined(_BIG)) ||\
   (defined(_SH4A) && defined(_BIG)) ||\
   (defined(__RX) && defined(__BIG))
#define  BIGENDIAN 1
#endif


/*** IP address/Port No. information ***/
typedef struct t_ipv4ep
{
    uint32_t  ipaddr;    /* IP address */
    uint16_t  portno;    /* Port number */
} T_IPV4EP;


#define T_IPVxEP T_IPV4EP

#define IP_ALEN    4
typedef uint8_t IPaddr[IP_ALEN]; /*  IP address */

#define EP_ALEN    6
typedef uint8_t Eaddr[EP_ALEN];  /*  MAC address */



#if BIGENDIAN == 1
#define hs2net(x) (x)
#define net2hs(x) (x)
#define hl2net(x) (x)
#define net2hl(x) (x)
void net2hl_yn_xn(void *y, void *x);
#define hl2net_yn_xn(y, x) net2hl_yn_xn(y, x)

#else /* BIGENDIAN == 0 */

#define hs2net(x) ((uint16_t)((x)>>8)  | (uint16_t)((x)<<8))
#define net2hs(x) ((uint16_t)((x)>>8)  | (uint16_t)((x)<<8))
#define hl2net(x) ((uint32_t)((x)>>24) | (uint32_t)((0xff0000&(x))>>8) \
                   | (uint32_t)((0x00ff00&(x))<<8) | (uint32_t)((x)<<24))
#define net2hl(x) ((uint32_t)((x)>>24) | (uint32_t)((0xff0000&(x))>>8) \
                   | (uint32_t)((0x00ff00&(x))<<8) | (uint32_t)((x)<<24))

void net2hl_yn_xn(void *y, void *x);
#define hl2net_yn_xn(y, x) net2hl_yn_xn(y, x)
#define net2hl_xn_xn(x)\
    {\
        register tmp1; \
        register tmp2; \
        register uint8_t *a0 = (uint8_t *)x; \
        tmp1 = *((uint8_t*)a0    );\
        tmp2 = *((uint8_t*)a0 + 3);\
        *((uint8_t*)a0    ) = tmp2;\
        *((uint8_t*)a0 +3 ) = tmp1;\
        tmp1 = *((uint8_t*)a0 + 1);\
        tmp2 = *((uint8_t*)a0 + 2);\
        *((uint8_t*)a0 + 1) = tmp2;\
        *((uint8_t*)a0 + 2) = tmp1;\
    }
#endif

/*
 * Macro function
 */
#if defined(M16C) || defined(M16C80) || defined(M32C80) || defined(R8C) ||\
 defined(__300HA__) || defined(__2600A__) ||\
 defined(_SH2) || defined(_SH2A) || defined(_SH2AFPU) || defined(_SH4) || defined(_SH4A) ||\
 defined(__RX) || defined(__v850) || defined(__GNUC__) || defined(GRSAKURA)
/* same as memcmp(x, y, IP_ALEN) */

#if defined (_SH2) || defined(_SH2A) || defined(_SH2AFPU) || defined(_SH4) || defined(_SH4A) ||\
 defined(__RX) || defined(__v850) || defined(__GNUC__) || defined(GRSAKURA)
#define _cmp_ipaddr(x,y) memcmp(x,y,(size_t)IP_ALEN)
#else
#define _cmp_ipaddr(x, y)  ( ((*(((uint16_t *)(x))  )) ^ (*(((uint16_t *)(y))  ))) |  \
                             ((*(((uint16_t *)(x))+1)) ^ (*(((uint16_t *)(y))+1)))  )
#endif
/* same as memcpy(x, y, IP_ALEN) */
#if defined (_SH2) || defined(_SH2A) || defined(_SH2AFPU) || defined(_SH4) || defined(_SH4A) ||\
 defined(__RX) || defined(__v850) || defined(__GNUC__) || defined(GRSAKURA)
#define _cpy_ipaddr(x ,y) memcpy(x,y,IP_ALEN)
#else
#define _cpy_ipaddr(x, y)  *((uint32_t *)(x)) = *((uint32_t *)(y))
#endif
/* same as memcpy(x, y, EP_ALEN) */
#if defined (_SH2) || defined(_SH2A) || defined(_SH2AFPU) || defined(_SH4) || defined(_SH4A) ||\
 defined(__RX) || defined(__v850) || defined(__GNUC__) || defined(GRSAKURA)
#define _cpy_eaddr(x, y) memcpy(x,y,EP_ALEN);
#else
#define _cpy_eaddr(x, y)   *(((uint32_t *)(x))  ) = *(((uint32_t *)(y))  ); \
    *(((uint16_t *)(x))+2) = *(((uint16_t *)(y))+2);
#endif
#define _cmp_ipv6addr(x, y)   ( ((*(((uint32_t *)(x))  )) ^ (*(((uint32_t *)(y))  ))) |  \
                                ((*(((uint32_t *)(x))+1)) ^ (*(((uint32_t *)(y))+1))) |  \
                                ((*(((uint32_t *)(x))+2)) ^ (*(((uint32_t *)(y))+2))) |  \
                                ((*(((uint32_t *)(x))+3)) ^ (*(((uint32_t *)(y))+3)))  )
#define _cpy_ipv6addr(x, y)  *(((uint32_t *)(x))  ) = *(((uint32_t *)(y))  ); \
    *(((uint32_t *)(x))+1) = *(((uint32_t *)(y))+1); \
    *(((uint32_t *)(x))+2) = *(((uint32_t *)(y))+2); \
    *(((uint32_t *)(x))+3) = *(((uint32_t *)(y))+3);
#endif
