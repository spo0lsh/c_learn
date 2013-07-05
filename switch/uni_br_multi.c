#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "uni_br_multi.h"
#include <memory.h>

int fn_unicast_broadcast_multicast(int bridgeport, SFrame *frame) {
	unsigned char mac_br[6]  = {0xff,0xff,0xff,0xff,0xff,0xff};
	unsigned char mac_mc1[6] = {0x01,0x00,0x5e,0x00,0x00,0x00};
	unsigned char mac_mc2[6] = {0x01,0x00,0x5e,0x7f,0xff,0xff};
	/* something to check MAC addresses */
	#ifdef DEBUG
	printf("fn_unicast_broadcast_multicast %d\n",bridgeport);
	printf("[U_BR_MC] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACdst[0], frame->ach_MACdst[1], frame->ach_MACdst[2], frame->ach_MACdst[3], frame->ach_MACdst[4], frame->ach_MACdst[5]);
	printf("[U_BR_MC] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACsrc[0], frame->ach_MACsrc[1], frame->ach_MACsrc[2], frame->ach_MACsrc[3], frame->ach_MACsrc[4], frame->ach_MACsrc[5]);
	printf("[U_BR_MC] Length: %d\n", frame->ach_Length);
	printf("[U_BR_MC] Payload: %s\n", frame->ach_Payload);
	printf("[U_BR_MC] CRC: %s\n", frame->ach_crc);
	#endif
	
	if(memcmp(frame->ach_MACdst, mac_br,6) == 0) {
		#ifdef DEBUG
		printf("[U_BR_MC] broadcast\n");
		#endif
		return(1);
	}
	else if(memcmp(frame->ach_MACdst, mac_mc1,6) >= 0 && memcmp(frame->ach_MACdst, mac_mc2,6) <= 0) {
		#ifdef DEBUG
		printf("[U_BR_MC] multicast\n");
		#endif
		return(1);
	} else {
		#ifdef DEBUG
		printf("[U_BR_MC] unicast\n");
		#endif
		return(0);
	}
}
