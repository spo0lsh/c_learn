#include <stdio.h>
#include "switch.h"
#include "learn.h"
#include "aging.h"
#include "db.h"

void fn_learn_or_refresh(int bridgeport, SFrame *frame) {
	#ifdef DEBUG
	printf("fn_learn or refresh bridgeport %d\n",bridgeport);
	printf("[LEARN] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACdst[0], frame->ach_MACdst[1], frame->ach_MACdst[2], frame->ach_MACdst[3], frame->ach_MACdst[4], frame->ach_MACdst[5]);
	printf("[LEARN] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACsrc[0], frame->ach_MACsrc[1], frame->ach_MACsrc[2], frame->ach_MACsrc[3], frame->ach_MACsrc[4], frame->ach_MACsrc[5]);
	printf("[LEARN] Length: %d\n", frame->ach_Length);
	printf("[LEARN] Payload: %s\n", frame->ach_Payload);
	printf("[LEARN] CRC: %s\n", frame->ach_crc);
	printf("[LEARN] add SRC: %02x:%02x:%02x:%02x:%02x:%02x iface: %d aging: %d HASH: %d\n",frame->ach_MACsrc[0], frame->ach_MACsrc[1], frame->ach_MACsrc[2], frame->ach_MACsrc[3], frame->ach_MACsrc[4], frame->ach_MACsrc[5],bridgeport,AGING,fn_hash(frame->ach_MACsrc)+1 );
	#endif
	fn_add_srcmac(frame->ach_MACsrc,bridgeport,0);
}
