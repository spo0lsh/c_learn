#include <stdio.h>
#include "switch.h"
#include "learn.h"
#include "aging.h"
#include "db.h"

void fn_learn_or_refresh(int n_bridgeport, SFrame *ps_frame) {
	#ifdef DEBUG
	printf("fn_learn or refresh bridgeport %d\n",n_bridgeport);
	printf("[LEARN] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_frame->ach_MACdst[0], ps_frame->ach_MACdst[1], ps_frame->ach_MACdst[2], ps_frame->ach_MACdst[3], ps_frame->ach_MACdst[4], ps_frame->ach_MACdst[5]);
	printf("[LEARN] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_frame->ach_MACsrc[0], ps_frame->ach_MACsrc[1], ps_frame->ach_MACsrc[2], ps_frame->ach_MACsrc[3], ps_frame->ach_MACsrc[4], ps_frame->ach_MACsrc[5]);
	printf("[LEARN] Length: %d\n", ps_frame->ach_Length);
	printf("[LEARN] Payload: %s\n", ps_frame->ach_Payload);
	printf("[LEARN] CRC: %s\n", ps_frame->ach_crc);
	printf("[LEARN] add SRC: %02x:%02x:%02x:%02x:%02x:%02x iface: %d aging: %d HASH: %d\n",ps_frame->ach_MACsrc[0], ps_frame->ach_MACsrc[1], ps_frame->ach_MACsrc[2], ps_frame->ach_MACsrc[3], ps_frame->ach_MACsrc[4], ps_frame->ach_MACsrc[5],n_bridgeport,n_aging,fn_hash(ps_frame->ach_MACsrc)+1 );
	#endif
	fn_add_srcmac(ps_frame->ach_MACsrc,n_bridgeport,0);
}
