#include <stdio.h>
#include <stdlib.h>
#include "db.h"
#include "switch.h"
#include "uni_br_multi.h"
#include <memory.h>


int fn_unicast_broadcast_multicast(int bridgeport, SFrame *s_Frame) {
	/* something to check MAC addresses */
	int n_hash;
	n_hash=0;
	#ifdef DEBUG
	printf("fn_unicast_broadcast_multicast %d\n",bridgeport);
	printf("[U_BR_MC] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", s_Frame->ach_MACdst[0], s_Frame->ach_MACdst[1], s_Frame->ach_MACdst[2], s_Frame->ach_MACdst[3], s_Frame->ach_MACdst[4], s_Frame->ach_MACdst[5]);
	printf("[U_BR_MC] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", s_Frame->ach_MACsrc[0], s_Frame->ach_MACsrc[1], s_Frame->ach_MACsrc[2], s_Frame->ach_MACsrc[3], s_Frame->ach_MACsrc[4], s_Frame->ach_MACsrc[5]);
	printf("[U_BR_MC] Length: %d\n", s_Frame->ach_Length);
	printf("[U_BR_MC] Payload: %s\n", s_Frame->ach_Payload);
	printf("[U_BR_MC] CRC: %s\n", s_Frame->ach_crc);
	#endif
	if((s_Frame->ach_MACdst[0] % 2 ) == 1 ) {
		#ifdef DEBUG
		printf("[U_BR_MC] broadcast or multicast\n");
		#endif
		return 1;
	} else {
		#ifdef DEBUG
		printf("[U_BR_MC] unicast\n");
		#endif
		n_hash = fn_hash(s_Frame->ach_MACdst);
		printf("[U_BR_MC] hash %d\n",n_hash+1);
		if(asHASH[n_hash].n_Port == 0 ) {
			printf("[U_BR_MC] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n not found!\n", s_Frame->ach_MACdst[0], s_Frame->ach_MACdst[1], s_Frame->ach_MACdst[2], s_Frame->ach_MACdst[3], s_Frame->ach_MACdst[4], s_Frame->ach_MACdst[5]);
			return 1;
		} else {
			printf("[U_BR_MC] MACdst: %02x:%02x:%02x:%02x:%02x:%02x found on port %d\n", s_Frame->ach_MACdst[0], s_Frame->ach_MACdst[1], s_Frame->ach_MACdst[2], s_Frame->ach_MACdst[3], s_Frame->ach_MACdst[4], s_Frame->ach_MACdst[5],asHASH[n_hash].n_Port);
			return 0;
		}
		
	}
}
