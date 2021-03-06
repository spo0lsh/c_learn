#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "recv.h"
#include "flood.h"
#include "send.h"

/* flooding */
void fn_flood(int n_bridgeport, SFrame *ps_Frame) {
	int n_i;
	for(n_i=0;n_i<SWITCH;++n_i) { // all interfaces
		if(n_bridgeport != n_i+1) { // if next is not source -> TRUE
			#ifdef DEBUG
			printf("flooding to bridgeport %d -> %d\n",n_bridgeport,n_i+1);
			printf("[FLOOD] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACdst[0], ps_Frame->ach_MACdst[1], ps_Frame->ach_MACdst[2], ps_Frame->ach_MACdst[3], ps_Frame->ach_MACdst[4], ps_Frame->ach_MACdst[5]);
			printf("[FLOOD] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACsrc[0], ps_Frame->ach_MACsrc[1], ps_Frame->ach_MACsrc[2], ps_Frame->ach_MACsrc[3], ps_Frame->ach_MACsrc[4], ps_Frame->ach_MACsrc[5]);
			printf("[FLOOD] Length: %d\n", ps_Frame->ach_Length);
			printf("[FLOOD] Payload: %s\n", ps_Frame->ach_Payload);
			printf("[FLOOD] CRC: %02x%02x%02x%02x\n",ps_Frame->ach_crc[0],ps_Frame->ach_crc[1],ps_Frame->ach_crc[2],ps_Frame->ach_crc[3]);
			#endif
			fn_send(n_i+1, (void *) ps_Frame); // send frame
		}
	}
}
