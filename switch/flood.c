#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "recv.h"
#include "flood.h"
#include "send.h"

void fn_flood(int bridgeport, SFrame *frame) {
	int i;
	for(i=0;i<SWITCH;++i) {
		if(bridgeport != i+1) {
			#ifdef DEBUG
			printf("flooding to bridgeport %d from %d\n",i+1,bridgeport);
			printf("[F] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACdst[0], frame->ach_MACdst[1], frame->ach_MACdst[2], frame->ach_MACdst[3], frame->ach_MACdst[4], frame->ach_MACdst[5]);
			printf("[F] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACsrc[0], frame->ach_MACsrc[1], frame->ach_MACsrc[2], frame->ach_MACsrc[3], frame->ach_MACsrc[4], frame->ach_MACsrc[5]);
			printf("[F] Length: %d\n", frame->ach_Length);
			printf("[F] Payload: %s\n", frame->ach_Payload);
			printf("[F] CRC: %s\n", frame->ach_crc);
			fn_send(i+1, (void *) frame);
			#endif
		}
	}
}
