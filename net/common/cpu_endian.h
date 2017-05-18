/**
 * @file cpu_endian.h
 * @brief Byte order conversion
 *
 * @section License
 *
 * Copyright (C) 2010-2017 Oryx Embedded SARL. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.7.6
 **/

#ifndef _CPU_ENDIAN_H
#define _CPU_ENDIAN_H

//Dependencies
#include "os_port.h"

//Undefine conflicting definitions
#ifdef HTONS
   #undef HTONS
#endif

#ifdef HTONL
   #undef HTONL
#endif

#ifdef htons
   #undef htons
#endif

#ifdef htonl
   #undef htonl
#endif

#ifdef NTOHS
   #undef NTOHS
#endif

#ifdef NTOHL
   #undef NTOHL
#endif

#ifdef ntohs
   #undef ntohs
#endif

#ifdef ntohl
   #undef ntohl
#endif

#ifdef HTOLE16
   #undef HTOLE16
#endif

#ifdef HTOLE32
   #undef HTOLE32
#endif

#ifdef HTOLE64
   #undef HTOLE64
#endif

#ifdef htole16
   #undef htole16
#endif

#ifdef htole32
   #undef htole32
#endif

#ifdef htole64
   #undef htole64
#endif

#ifdef LETOH16
   #undef LETOH16
#endif

#ifdef LETOH32
   #undef LETOH32
#endif

#ifdef LETOH64
   #undef LETOH64
#endif

#ifdef letoh16
   #undef letoh16
#endif

#ifdef letoh32
   #undef letoh32
#endif

#ifdef letoh64
   #undef letoh64
#endif

#ifdef HTOBE16
   #undef HTOBE16
#endif

#ifdef HTOBE32
   #undef HTOBE32
#endif

#ifdef HTOBE64
   #undef HTOBE64
#endif

#ifdef htobe16
   #undef htobe16
#endif

#ifdef htobe32
   #undef htobe32
#endif

#ifdef htobe64
   #undef htobe64
#endif

#ifdef BETOH16
   #undef BETOH16
#endif

#ifdef BETOH32
   #undef BETOH32
#endif

#ifdef BETOH64
   #undef BETOH64
#endif

#ifdef betoh16
   #undef betoh16
#endif

#ifdef betoh32
   #undef betoh32
#endif

#ifdef betoh64
   #undef betoh64
#endif

//Load unaligned 16-bit integer (little-endian encoding)
#define LOAD16LE(p) ( \
   ((uint16_t)(((uint8_t *)(p))[0]) << 0) | \
   ((uint16_t)(((uint8_t *)(p))[1]) << 8))

//Load unaligned 16-bit integer (big-endian encoding)
#define LOAD16BE(p) ( \
   ((uint16_t)(((uint8_t *)(p))[0]) << 8) | \
   ((uint16_t)(((uint8_t *)(p))[1]) << 0))

//Load unaligned 24-bit integer (little-endian encoding)
#define LOAD24LE(p) ( \
   ((uint32_t)(((uint8_t *)(p))[0]) << 0)| \
   ((uint32_t)(((uint8_t *)(p))[1]) << 8) | \
   ((uint32_t)(((uint8_t *)(p))[2]) << 16))

//Load unaligned 24-bit integer (big-endian encoding)
#define LOAD24BE(p) ( \
   ((uint32_t)(((uint8_t *)(p))[0]) << 16) | \
   ((uint32_t)(((uint8_t *)(p))[1]) << 8) | \
   ((uint32_t)(((uint8_t *)(p))[2]) << 0))

//Load unaligned 32-bit integer (little-endian encoding)
#define LOAD32LE(p) ( \
   ((uint32_t)(((uint8_t *)(p))[0]) << 0) | \
   ((uint32_t)(((uint8_t *)(p))[1]) << 8) | \
   ((uint32_t)(((uint8_t *)(p))[2]) << 16) | \
   ((uint32_t)(((uint8_t *)(p))[3]) << 24))

//Load unaligned 32-bit integer (big-endian encoding)
#define LOAD32BE(p) ( \
   ((uint32_t)(((uint8_t *)(p))[0]) << 24) | \
   ((uint32_t)(((uint8_t *)(p))[1]) << 16) | \
   ((uint32_t)(((uint8_t *)(p))[2]) << 8) | \
   ((uint32_t)(((uint8_t *)(p))[3]) << 0))

//Load unaligned 64-bit integer (little-endian encoding)
#define LOAD64LE(p) ( \
   ((uint64_t)(((uint8_t *)(p))[0]) << 0) | \
   ((uint64_t)(((uint8_t *)(p))[1]) << 8) | \
   ((uint64_t)(((uint8_t *)(p))[2]) << 16) | \
   ((uint64_t)(((uint8_t *)(p))[3]) << 24) | \
   ((uint64_t)(((uint8_t *)(p))[4]) << 32) | \
   ((uint64_t)(((uint8_t *)(p))[5]) << 40) | \
   ((uint64_t)(((uint8_t *)(p))[6]) << 48) | \
   ((uint64_t)(((uint8_t *)(p))[7]) << 56))

//Load unaligned 64-bit integer (big-endian encoding)
#define LOAD64BE(p) ( \
   ((uint64_t)(((uint8_t *)(p))[0]) << 56) | \
   ((uint64_t)(((uint8_t *)(p))[1]) << 48) | \
   ((uint64_t)(((uint8_t *)(p))[2]) << 40) | \
   ((uint64_t)(((uint8_t *)(p))[3]) << 32) | \
   ((uint64_t)(((uint8_t *)(p))[4]) << 24) | \
   ((uint64_t)(((uint8_t *)(p))[5]) << 16) | \
   ((uint64_t)(((uint8_t *)(p))[6]) << 8) | \
   ((uint64_t)(((uint8_t *)(p))[7]) << 0))

//Store unaligned 16-bit integer (little-endian encoding)
#define STORE16LE(a, p) \
   ((uint8_t *)(p))[0] = ((uint16_t)(a) >> 0) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint16_t)(a) >> 8) & 0xFF

//Store unaligned 32-bit integer (big-endian encoding)
#define STORE16BE(a, p) \
   ((uint8_t *)(p))[0] = ((uint16_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint16_t)(a) >> 0) & 0xFF

//Store unaligned 24-bit integer (little-endian encoding)
#define STORE24LE(a, p) \
   ((uint8_t *)(p))[0] = ((uint32_t)(a) >> 0) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint32_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint32_t)(a) >> 16) & 0xFF

//Store unaligned 24-bit integer (big-endian encoding)
#define STORE24BE(a, p) \
   ((uint8_t *)(p))[0] = ((uint32_t)(a) >> 16) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint32_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint32_t)(a) >> 0) & 0xFF

//Store unaligned 32-bit integer (little-endian encoding)
#define STORE32LE(a, p) \
   ((uint8_t *)(p))[0] = ((uint32_t)(a) >> 0) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint32_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint32_t)(a) >> 16) & 0xFF, \
   ((uint8_t *)(p))[3] = ((uint32_t)(a) >> 24) & 0xFF

//Store unaligned 32-bit integer (big-endian encoding)
#define STORE32BE(a, p) \
   ((uint8_t *)(p))[0] = ((uint32_t)(a) >> 24) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint32_t)(a) >> 16) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint32_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[3] = ((uint32_t)(a) >> 0) & 0xFF

//Store unaligned 64-bit integer (little-endian encoding)
#define STORE64LE(a, p) \
   ((uint8_t *)(p))[0] = ((uint64_t)(a) >> 0) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint64_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint64_t)(a) >> 16) & 0xFF, \
   ((uint8_t *)(p))[3] = ((uint64_t)(a) >> 24) & 0xFF, \
   ((uint8_t *)(p))[4] = ((uint64_t)(a) >> 32) & 0xFF, \
   ((uint8_t *)(p))[5] = ((uint64_t)(a) >> 40) & 0xFF, \
   ((uint8_t *)(p))[6] = ((uint64_t)(a) >> 48) & 0xFF, \
   ((uint8_t *)(p))[7] = ((uint64_t)(a) >> 56) & 0xFF

//Store unaligned 64-bit integer (big-endian encoding)
#define STORE64BE(a, p) \
   ((uint8_t *)(p))[0] = ((uint64_t)(a) >> 56) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint64_t)(a) >> 48) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint64_t)(a) >> 40) & 0xFF, \
   ((uint8_t *)(p))[3] = ((uint64_t)(a) >> 32) & 0xFF, \
   ((uint8_t *)(p))[4] = ((uint64_t)(a) >> 24) & 0xFF, \
   ((uint8_t *)(p))[5] = ((uint64_t)(a) >> 16) & 0xFF, \
   ((uint8_t *)(p))[6] = ((uint64_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[7] = ((uint64_t)(a) >> 0) & 0xFF

//Swap a 16-bit integer
#define SWAPINT16(x) ( \
   (((x) & 0x00FF) << 8) | \
   (((x) & 0xFF00) >> 8))

//Swap a 32-bit integer
#define SWAPINT32(x) ( \
   (((x) & 0x000000FFUL) << 24) | \
   (((x) & 0x0000FF00UL) << 8) | \
   (((x) & 0x00FF0000UL) >> 8) | \
   (((x) & 0xFF000000UL) >> 24))

//Swap a 64-bit integer
#define SWAPINT64(x) ( \
   (((x) & 0x00000000000000FFULL) << 56) | \
   (((x) & 0x000000000000FF00ULL) << 40) | \
   (((x) & 0x0000000000FF0000ULL) << 24) | \
   (((x) & 0x00000000FF000000ULL) << 8) | \
   (((x) & 0x000000FF00000000ULL) >> 8) | \
   (((x) & 0x0000FF0000000000ULL) >> 24) | \
   (((x) & 0x00FF000000000000ULL) >> 40) | \
   (((x) & 0xFF00000000000000ULL) >> 56))

//Big-endian machine?
#ifdef _CPU_BIG_ENDIAN

//Host byte order to network byte order
#define HTONS(value) (value)
#define HTONL(value) (value)
#define htons(value) ((uint16_t) (value))
#define htonl(value) ((uint32_t) (value))

//Network byte order to host byte order
#define NTOHS(value) (value)
#define NTOHL(value) (value)
#define ntohs(value) ((uint16_t) (value))
#define ntohl(value) ((uint32_t) (value))

//Host byte order to little-endian byte order
#define HTOLE16(value) SWAPINT16(value)
#define HTOLE32(value) SWAPINT32(value)
#define HTOLE64(value) SWAPINT64(value)
#define htole16(value) swapInt16((uint16_t) (value))
#define htole32(value) swapInt32((uint32_t) (value))
#define htole64(value) swapInt64((uint64_t) (value))

//Little-endian byte order to host byte order
#define LETOH16(value) SWAPINT16(value)
#define LETOH32(value) SWAPINT32(value)
#define LETOH64(value) SWAPINT64(value)
#define letoh16(value) swapInt16((uint16_t) (value))
#define letoh32(value) swapInt32((uint32_t) (value))
#define letoh64(value) swapInt64((uint64_t) (value))

//Host byte order to big-endian byte order
#define HTOBE16(value) (value)
#define HTOBE32(value) (value)
#define HTOBE64(value) (value)
#define htobe16(value) ((uint16_t) (value))
#define htobe32(value) ((uint32_t) (value))
#define htobe64(value) ((uint64_t) (value))

//Big-endian byte order to host byte order
#define BETOH16(value) (value)
#define BETOH32(value) (value)
#define BETOH64(value) (value)
#define betoh16(value) ((uint16_t) (value))
#define betoh32(value) ((uint32_t) (value))
#define betoh64(value) ((uint64_t) (value))

//Little-endian machine?
#else

//Host byte order to network byte order
#define HTONS(value) SWAPINT16(value)
#define HTONL(value) SWAPINT32(value)
#define htons(value) swapInt16((uint16_t) (value))
#define htonl(value) swapInt32((uint32_t) (value))

//Network byte order to host byte order
#define NTOHS(value) SWAPINT16(value)
#define NTOHL(value) SWAPINT32(value)
#define ntohs(value) swapInt16((uint16_t) (value))
#define ntohl(value) swapInt32((uint32_t) (value))

//Host byte order to little-endian byte order
#define HTOLE16(value) (value)
#define HTOLE32(value) (value)
#define HTOLE64(value) (value)
#define htole16(value) ((uint16_t) (value))
#define htole32(value) ((uint32_t) (value))
#define htole64(value) ((uint64_t) (value))

//Little-endian byte order to host byte order
#define LETOH16(value) (value)
#define LETOH32(value) (value)
#define LETOH64(value) (value)
#define letoh16(value) ((uint16_t) (value))
#define letoh32(value) ((uint32_t) (value))
#define letoh64(value) ((uint64_t) (value))

//Host byte order to big-endian byte order
#define HTOBE16(value) SWAPINT16(value)
#define HTOBE32(value) SWAPINT32(value)
#define HTOBE64(value) SWAPINT64(value)
#define htobe16(value) swapInt16((uint16_t) (value))
#define htobe32(value) swapInt32((uint32_t) (value))
#define htobe64(value) swapInt64((uint64_t) (value))

//Big-endian byte order to host byte order
#define BETOH16(value) SWAPINT16(value)
#define BETOH32(value) SWAPINT32(value)
#define BETOH64(value) SWAPINT64(value)
#define betoh16(value) swapInt16((uint16_t) (value))
#define betoh32(value) swapInt32((uint32_t) (value))
#define betoh64(value) swapInt64((uint64_t) (value))

#endif

//Byte order conversion functions
uint16_t swapInt16(uint16_t value);
uint32_t swapInt32(uint32_t value);
uint64_t swapInt64(uint64_t value);

//Bit reversal functions
uint8_t reverseInt4(uint8_t value);
uint8_t reverseInt8(uint8_t value);
uint16_t reverseInt16(uint16_t value);
uint32_t reverseInt32(uint32_t value);
uint64_t reverseInt64(uint64_t value);

#endif
