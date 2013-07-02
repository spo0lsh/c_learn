#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "recv.h"
#include "flood.h"
#include "send.h"


int main() {
	int bridge;
	SFrame frame;
	/*
	receive frame
	*/
	bridge=1;
	fn_recv(bridge,&frame);
	printf("[D] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", frame.ach_MACdst[0], frame.ach_MACdst[1], frame.ach_MACdst[2], frame.ach_MACdst[3], frame.ach_MACdst[4], frame.ach_MACdst[5]);
	printf("[D] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", frame.ach_MACsrc[0], frame.ach_MACsrc[1], frame.ach_MACsrc[2], frame.ach_MACsrc[3], frame.ach_MACsrc[4], frame.ach_MACsrc[5]);
	printf("[D] Length: %d\n", frame.ach_Length);
	printf("[D] Payload: %s\n", frame.ach_Payload);
	printf("[D] CRC: %s\n", frame.ach_crc);
	/*
	learn or refresh
	*/

	/*
	unicast broadcast multicast
	*/	
	/*
	flood
	*/
	bridge=1;
	fn_send(bridge,&frame);

    return(EXIT_SUCCESS);
}
