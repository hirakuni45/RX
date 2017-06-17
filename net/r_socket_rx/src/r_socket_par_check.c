/**********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURCOORDE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE COORDSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer *
* Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_socket_par_check.c
* Description  : Functions for checking socket parameter.
*                Although all r_socket functions are based on BSD sockets functions, there are some limitation. Below
*                check functions return "true" if the parameter is supported in r_socket and "false" if not supported.
***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 26.09.2013 1.00    First Release
*         : 17.02.2015 1.01    Add check for select parameter
**********************************************************************************************************************/


/**********************************************************************************************************************
Includes <System Includes>, "Project Includes"
**********************************************************************************************************************/
#include "errno.h"
#include "r_errno.h"
#include "r_socket_par_check.h"

#ifdef R_SOCKET_PAR_CHECK
/**********************************************************************************************************************
Macro definitions
**********************************************************************************************************************/
#define RETURN_VAL_CHECK(condition) {if (condition != true) goto exit;}


/**********************************************************************************************************************
Typedef definitions
**********************************************************************************************************************/


/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
//extern int32_t    errno;

/**********************************************************************************************************************
Exported global variables
**********************************************************************************************************************/


/**********************************************************************************************************************
Private global variables and functions
**********************************************************************************************************************/
static bool sockfd_check(int sockfd);
static bool addr_check(const struct sockaddr *addr);
static bool addrlen_check(socklen_t addrlen);
static bool addrlenp_check(socklen_t *addrlen);
static bool buf_check(const void *buf);
static bool send_len_check(size_t len);
static bool recv_len_check(size_t len);
static bool flags_check(int flags);
static bool fcntl_cmd_check(int cmd);
static bool fcntl_flags_check(int flags);


/**********************************************************************************************************************
* Function Name: socket_par_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool socket_par_check(int domain, int type, int protocol)
{
    bool rtn = true;

    if ((domain != AF_INET) && (domain != AF_NET2))
    {
        rtn = false;
        errno = EAFNOSUPPORT;       /* Address family not supported. */
        goto exit;
    }

    if ((type != SOCK_STREAM) && (type != SOCK_DGRAM))
    {
        rtn = false;
        errno = EPROTOTYPE;         /* The socket type is not supported by the protocol. */
        goto exit;
    }

    if ((protocol != IPPROTO_UDP) && (protocol != IPPROTO_TCP))
    {
        rtn = false;
        errno = EPROTONOSUPPORT;    /* Protocol not supported. */
        goto exit;
    }

exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: bind_par_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool bind_par_check(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    bool rtn = true;
    errno = E_OK;   /* Nothing wrong */

    rtn = sockfd_check(sockfd);
    RETURN_VAL_CHECK(rtn);

    rtn = addr_check(addr);
    RETURN_VAL_CHECK(rtn);

    rtn = addrlen_check(addrlen);
    RETURN_VAL_CHECK(rtn);

exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: connect_par_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool connect_par_check(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    bool rtn = true;

    rtn = sockfd_check(sockfd);
    RETURN_VAL_CHECK(rtn);

    rtn = addr_check(addr);
    RETURN_VAL_CHECK(rtn);

    rtn = addrlen_check(addrlen);
    RETURN_VAL_CHECK(rtn);

exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: listen_par_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool listen_par_check(int sockfd, int backlog)
{
    bool rtn = true;

    rtn = sockfd_check(sockfd);
    RETURN_VAL_CHECK(rtn);

    if (backlog != 1)
    {
        errno = ENOBUFS;    /*  Insufficient resources are available in the system to complete the call.*/
        rtn = false;
        goto exit;
    }

exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: accept_par_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool accept_par_check(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    bool rtn = true;

    rtn = sockfd_check(sockfd);
    RETURN_VAL_CHECK(rtn);

    rtn = addr_check(addr);
    RETURN_VAL_CHECK(rtn);

    rtn = addrlenp_check(addrlen);
    RETURN_VAL_CHECK(rtn);

exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: send_par_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool send_par_check(int sockfd, const void *buf, size_t len, int flags)
{
    bool rtn = true;

    rtn = sockfd_check(sockfd);
    RETURN_VAL_CHECK(rtn);

    rtn = buf_check(buf);
    RETURN_VAL_CHECK(rtn);

    rtn = send_len_check(len);
    RETURN_VAL_CHECK(rtn);

    rtn = flags_check(flags);
    RETURN_VAL_CHECK(rtn);

exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: sendto_check_par
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool sendto_par_check(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen)
{
    bool rtn = true;

    rtn = send_par_check(sockfd, buf, len, flags);
    RETURN_VAL_CHECK(rtn);

    rtn = addr_check(dest_addr);
    RETURN_VAL_CHECK(rtn);

    rtn = addrlen_check(addrlen);
    RETURN_VAL_CHECK(rtn);

exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: recv_par_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool recv_par_check(int sockfd, void *buf, size_t len, int flags)
{
    bool rtn = true;

    rtn = sockfd_check(sockfd);
    RETURN_VAL_CHECK(rtn);

    rtn = buf_check(buf);
    RETURN_VAL_CHECK(rtn);

    rtn = recv_len_check(len);
    RETURN_VAL_CHECK(rtn);

    rtn = flags_check(flags);
    RETURN_VAL_CHECK(rtn);

exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: recvfrom_par_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool recvfrom_par_check(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen)
{
    bool rtn = true;

    rtn = recv_par_check(sockfd, buf, len, flags);
    RETURN_VAL_CHECK(rtn);

    rtn = addr_check(src_addr);
    RETURN_VAL_CHECK(rtn);

    rtn = addrlenp_check(addrlen);
    RETURN_VAL_CHECK(rtn);

exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: shutdown_par_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool shutdown_par_check(int sockfd)
{
    bool rtn = true;

    rtn = sockfd_check(sockfd);
    RETURN_VAL_CHECK(rtn);

exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: closesocket_par_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool closesocket_par_check(int sockfd)
{
    bool rtn = true;

    rtn = sockfd_check(sockfd);
    RETURN_VAL_CHECK(rtn);

exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: fcntl_par_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool fcntl_par_check(int sockfd, int cmd, int flags)
{
    bool rtn = true;

    rtn = sockfd_check(sockfd);
    RETURN_VAL_CHECK(rtn);

    rtn = fcntl_cmd_check(cmd);
    RETURN_VAL_CHECK(rtn);

    rtn = fcntl_flags_check(flags);
    RETURN_VAL_CHECK(rtn);

exit:
    return rtn;
}
/**********************************************************************************************************************
* Function Name: select_par_check
* Description  : nfds - not check
*              : readfds - if not NULL, check each fd is valid sockfd
*              : writefds - if not NULL, check each fd is valid sockfd
*              : errorfds - if not NULL, check each fd is valid sockfd
*              : timeout - not check
* Arguments    :
* Return Value :
**********************************************************************************************************************/
bool select_par_check( int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
                       struct timeval *timeout)
{
    bool    rtn = true;

    if ( readfds != NULL )
    {
        if ( (nfds  < 0) || (nfds > TOTAL_BSD_SOCKET))  /* Shouldnt exceed the total number of */
        {
            rtn = false;
            goto exit;
        }
    }
    if ( writefds != NULL )
    {
        if ( (nfds  < 0) || (nfds > TOTAL_BSD_SOCKET))  /* Shouldnt exceed the total number of */
        {
            rtn = false;
            goto exit;
        }
    }
    if ( errorfds != NULL )
    {
        if ( (nfds  < 0) || (nfds > TOTAL_BSD_SOCKET))  /* Shouldnt exceed the total number of */
        {
            rtn = false;
            goto exit;
        }
    }
exit:
    return rtn;
}

/**********************************************************************************************************************
* Function Name: sockfd_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
static bool sockfd_check(int sockfd)
{
    bool rtn = true;

    if ((sockfd < 0) || (sockfd >= TOTAL_BSD_SOCKET))
    {
        errno = ENOTSOCK;   /* Not a socket. */
        rtn = false;
    }

    return rtn;
}

/**********************************************************************************************************************
* Function Name: addr_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
static bool addr_check(const struct sockaddr *addr)
{
    bool rtn = true;

    if (addr == NULL)
    {
        errno = EADDRNOTAVAIL;  /* Address not available. */
        rtn = false;
    }

    return rtn;
}

/**********************************************************************************************************************
* Function Name: addrlen_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
static bool addrlen_check(socklen_t addrlen)
{
    bool rtn = true;

    if ((addrlen == 0) || ((unsigned)addrlen > sizeof(struct sockaddr)))
    {
        errno = EFAULT;     /* Bad address. */
        rtn = false;
    }

    return rtn;
}

/**********************************************************************************************************************
* Function Name: addrlenp_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
static bool addrlenp_check(socklen_t *addrlen)
{
    bool rtn = true;

    if (addrlen == NULL)
    {
        errno = EADDRNOTAVAIL;      /* Address not available. */
        rtn = false;
    }

    return rtn;
}

/**********************************************************************************************************************
* Function Name: buf_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
static bool buf_check(const void *buf)
{
    bool rtn = true;

    if (buf == NULL)
    {
        errno = ENOBUFS;        /* No buffer space available. */
        rtn = false;
    }

    return rtn;
}

/**********************************************************************************************************************
* Function Name: send_len_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
static bool send_len_check(size_t len)
{
    bool rtn = true;

    if ((len == 0) /*|| (len > BSD_SND_BUFSZ)*/)
    {
        errno = ENODATA;
        rtn = false;
    }

    return rtn;
}

/**********************************************************************************************************************
* Function Name: recv_len_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
static bool recv_len_check(size_t len)
{
    bool rtn = true;

    if (len <= 0)
    {
        errno = ENOBUFS;    /* No buffer space available. */
        rtn = false;
    }

    return rtn;
}

/**********************************************************************************************************************
* Function Name: flags_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
static bool flags_check(int flags)
{
    bool rtn = true;

    if (flags != 0)
    {
        rtn = false;
    }

    return rtn;
}

/**********************************************************************************************************************
* Function Name: fcntl_cmd_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
static bool fcntl_cmd_check(int cmd)
{
    bool rtn = true;

    if ((cmd != F_GETFL) && (cmd != F_SETFL))
    {
        errno = EINVAL;
        rtn = false;
    }

    return rtn;
}

/**********************************************************************************************************************
* Function Name: fcntl_flags_check
* Description  :
* Arguments    :
* Return Value :
**********************************************************************************************************************/
static bool fcntl_flags_check(int flags)
{
    bool rtn = true;

    if ((flags != O_NONBLOCK) && (flags != O_BLOCK))
    {
        errno = EINVAL;
        rtn = false;
    }

    return rtn;
}
#endif  /* R_SOCKET_PAR_CHECK */
