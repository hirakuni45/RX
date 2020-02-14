//--------------------------------------------------------------------------
// Project: D/AVE
// File:    dave_memory_rx.c (%version: 12 %)
//          created Mon Aug 22 14:53:41 2005 by hh04027
//
// Description:
//  %date_modified: Wed Oct 18 16:58:18 2006 %  (%derived_by:  hh74045 %)
//
// Changes:
//  2006-01-04 CSe  adapted to changes in dave_base.h
//  2006-02-28 CSe  added d1_cacheblockflush function
//  2005-04-12 CSe  fully implemented missing d1 driver functionality
//  2005-05-03 CSe  flush at end of d1_copytovidmem
//  2005-06-09 CSe  flush also in d1_copyfromvidmem
//  2018-01-24      added support for RX
//
//--------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include "dave_base.h"
#include "dave_base_rx.h"

//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//  d1_allocmem
//
void * d1_allocmem(unsigned int size)
{
    unsigned int *ptr;

    ptr = (unsigned int *)malloc((size_t)size);
    if (!ptr)
    {
        return NULL;
    }

    return (void *)ptr;
}

//--------------------------------------------------------------------------
//  d1_freemem
// Release system memory.
//
void d1_freemem(void *ptr)
{
    free(ptr);
}

//--------------------------------------------------------------------------
//   d1_memsize
//
unsigned int d1_memsize(void * ptr)
{
    /* unused arguments */
    INTERNAL_NOT_USED(ptr);

    return 1;
}

//--------------------------------------------------------------------------
//
void * d1_allocvidmem(d1_device *handle, int memtype, unsigned int size)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);
    INTERNAL_NOT_USED(memtype);

    /* read all requests directly to standard heap */
    return (d1_allocmem(size));
}

//--------------------------------------------------------------------------
//
void d1_freevidmem(d1_device *handle, int memtype, void *ptr)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);
    INTERNAL_NOT_USED(memtype);

    /* feed all requests directly to standard heap */
    d1_freemem(ptr);
}

//--------------------------------------------------------------------------
//
int d1_queryvidmem(d1_device *handle, int memtype, int query)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);
    INTERNAL_NOT_USED(memtype);
    INTERNAL_NOT_USED(query);

    return 0;
}

//--------------------------------------------------------------------------
//
int d1_queryarchitecture(d1_device *handle)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);

    return d1_ma_unified;
}

//--------------------------------------------------------------------------
//
void * d1_mapvidmem(d1_device *handle, void *ptr, int flags)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);
    INTERNAL_NOT_USED(flags);

    /* map memory into uncached area (test) */
    return ptr;
}

//--------------------------------------------------------------------------
//
int d1_unmapvidmem(d1_device *handle, void *ptr)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);
    INTERNAL_NOT_USED(ptr);

    /* no unmapping necessary */
    return 1;
}

//--------------------------------------------------------------------------
//
void * d1_maptovidmem(d1_device *handle, void *ptr)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);

    /* nothing special necessary */
    return ptr;
}

//--------------------------------------------------------------------------
//
void * d1_mapfromvidmem(d1_device *handle, void *ptr)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);

    /* map memory into uncached area (test) */
    return ptr;
}

//--------------------------------------------------------------------------
//
int d1_copytovidmem(d1_device *handle, void *dst, const void *src, unsigned int size, int flags)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);
    INTERNAL_NOT_USED(flags);

    /* can use direct memcpy */
    memcpy(dst, src, size);

    return 1;
}

//--------------------------------------------------------------------------
//
int d1_copyfromvidmem(d1_device *handle, void *dst, const void *src, unsigned int size, int flags)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);
    INTERNAL_NOT_USED(flags);

    /* can use direct memcpy */
    memcpy(dst, src, size);

    return 1;
}

//--------------------------------------------------------------------------
//
int d1_cacheflush(d1_device *handle, int memtype)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);
    INTERNAL_NOT_USED(memtype);

    return 1;
}

//--------------------------------------------------------------------------
//
int d1_cacheblockflush(d1_device *handle, int memtype, const void *ptr, unsigned int size)
{
    /* unused arguments */
    INTERNAL_NOT_USED(handle);
    INTERNAL_NOT_USED(memtype);
    INTERNAL_NOT_USED(ptr);
    INTERNAL_NOT_USED(size);

    return 1;
}
