/*
 * Soft:        Keepalived is a failover program for the LVS project
 *              <www.linuxvirtualserver.org>. It monitor & manipulate
 *              a loadbalanced server pool using multi-layer checks.
 *
 * Part:        ipvswrapper.c include file.
 *
 * Version:     $Id: ipvswrapper.h,v 0.5.6 2002/04/13 06:21:33 acassen Exp $
 *
 * Author:      Alexandre Cassen, <acassen@linux-vs.org>
 *
 *              This program is distributed in the hope that it will be useful,
 *              but WITHOUT ANY WARRANTY; without even the implied warranty of
 *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *              See the GNU General Public License for more details.
 *
 *              This program is free software; you can redistribute it and/or
 *              modify it under the terms of the GNU General Public License
 *              as published by the Free Software Foundation; either version
 *              2 of the License, or (at your option) any later version.
 */

#ifndef _IPVSWRAPPER_H
#define _IPVSWRAPPER_H

/* system includes */
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <arpa/inet.h>
#include <asm/types.h>

#include <net/if.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>

#ifdef _KRNL_2_2_
  #include <linux/ip_fw.h>
  #include <net/ip_masq.h>
#endif
#include <net/ip_vs.h>

/* locale includes */
#include "scheduler.h"
#include "data.h"

#define IPVS_ERROR	0
#define IPVS_SUCCESS	1
#define IPVS_CMD_DELAY	3

#ifdef _KRNL_2_2_
  #define IPVS_STARTDAEMON	1
  #define IPVS_STOPDAEMON	2
  #define IPVS_MASTER		3
  #define IPVS_BACKUP		4
#else
  #define IPVS_STARTDAEMON	IP_VS_SO_SET_STARTDAEMON
  #define IPVS_STOPDAEMON	IP_VS_SO_SET_STOPDAEMON
  #define IPVS_MASTER		IP_VS_STATE_MASTER
  #define IPVS_BACKUP		IP_VS_STATE_BACKUP
#endif

extern thread_master *master;

/* prototypes */
extern int parse_timeout(char *buf, unsigned *timeout);
extern int string_to_number(const char *s, int min, int max);
extern int ipvs_cmd(int cmd, virtual_server *vserver, real_server *rserver);
extern int ipvs_syncd_cmd(int cmd, char *ifname, int state);
extern int ipvs_syncd_master_thread(thread *thread);
extern int ipvs_syncd_backup_thread(thread *thread);

#endif
