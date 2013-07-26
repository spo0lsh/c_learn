#include <stdio.h>
#include <stdlib.h>
#include "db.h"
#include "switch.h"
#include "uni_br_multi.h"
#include <memory.h>


int fn_unicast_broadcast_multicast(int n_bridgeport, SFrame *ps_Frame) {
	/* something to check MAC addresses */
	int n_hash;
	n_hash=0;
	#ifdef DEBUG
	printf("fn_unicast_broadcast_multicast %d\n",n_bridgeport);
	printf("[U_BR_MC] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACdst[0], ps_Frame->ach_MACdst[1], ps_Frame->ach_MACdst[2], ps_Frame->ach_MACdst[3], ps_Frame->ach_MACdst[4], ps_Frame->ach_MACdst[5]);
	printf("[U_BR_MC] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACsrc[0], ps_Frame->ach_MACsrc[1], ps_Frame->ach_MACsrc[2], ps_Frame->ach_MACsrc[3], ps_Frame->ach_MACsrc[4], ps_Frame->ach_MACsrc[5]);
	printf("[U_BR_MC] Length: %d\n", ps_Frame->ach_Length);
	printf("[U_BR_MC] Payload: %s\n", ps_Frame->ach_Payload);
	printf("[LEARN] CRC: %02x%02x%02x%02x\n",ps_Frame->ach_crc[0],ps_Frame->ach_crc[1],ps_Frame->ach_crc[2],ps_Frame->ach_crc[3]);
	#endif
	if((ps_Frame->ach_MACdst[0] % 2 ) == 1 ) {
		#ifdef DEBUG
		printf("[U_BR_MC] broadcast or multicast\n");
		#endif
		return 1;
	} else {
		#ifdef DEBUG
		printf("[U_BR_MC] unicast\n");
		#endif
		n_hash = fn_hash(ps_Frame->ach_MACdst);
		#ifdef DEBUG
		printf("[U_BR_MC] hash %d\n",n_hash+1);
		#endif
		if(pas_HASH[n_hash].n_Port == 0 ) {
			#ifdef DEBUG
			printf("[U_BR_MC] MACdst: %02x:%02x:%02x:%02x:%02x:%02x not found!\n", ps_Frame->ach_MACdst[0], ps_Frame->ach_MACdst[1], ps_Frame->ach_MACdst[2], ps_Frame->ach_MACdst[3], ps_Frame->ach_MACdst[4], ps_Frame->ach_MACdst[5]);
			#endif
			return 1;
		} else {
			#ifdef DEBUG
			printf("[U_BR_MC] MACdst: %02x:%02x:%02x:%02x:%02x:%02x found on port %d\n", ps_Frame->ach_MACdst[0], ps_Frame->ach_MACdst[1], ps_Frame->ach_MACdst[2], ps_Frame->ach_MACdst[3], ps_Frame->ach_MACdst[4], ps_Frame->ach_MACdst[5],pas_HASH[n_hash].n_Port);
			#endif
			return 0;
		}
		
	}
}
