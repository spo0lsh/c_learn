#include <stdio.h>
#include "switch.h"
#include "crc.h"
#include <string.h>


/* reverses bits */
unsigned fn_reverse(unsigned x) {
   x = ((x & 0x55555555) <<  1) | ((x >>  1) & 0x55555555); // operation on bits -> magic
   x = ((x & 0x33333333) <<  2) | ((x >>  2) & 0x33333333);
   x = ((x & 0x0F0F0F0F) <<  4) | ((x >>  4) & 0x0F0F0F0F);
   x = (x << 24) | ((x & 0xFF00) << 8) | ((x >> 8) & 0xFF00) | (x >> 24);
   return x;
}

/* calc crc32 */
unsigned int fn_crc32(unsigned char * pch_message,int n_size) {
	int n_i;
	int n_j;
	unsigned int n_byte;
	unsigned int n_crc;

	n_i=0;
	n_j=0;
	n_crc=0xFFFFFFFF;
	n_byte=0;
	// more less magic in bits
	for(n_i=0;n_i<n_size;++n_i) {              // size of pch_message
		n_byte = pch_message[n_i];            // Get next byte.
		n_byte = fn_reverse(n_byte);         // 32-bit reversal
	for (n_j=0; n_j <= 7; n_j++) {          // do eight times
		if ((int)(n_crc ^ n_byte) < 0) {
			n_crc = (n_crc << 1) ^ 0x04C11DB7; // normal polynomial for CRC-32 -> 0x04C11DB7
		} else {
			n_crc = n_crc << 1;
		}
		n_byte = n_byte << 1;          // go to next msg bit
	}
	n_i = n_i + 1;
	}
	#ifdef DEBUG
	printf("cal: %08x %d\n",fn_reverse(~n_crc),fn_reverse(~n_crc));
	#endif
	return fn_reverse(~n_crc);
}

/* calc crc for frame */
int fn_crc_frame(SFrame *ps_Frame) {
	int n_i;
	unsigned char *pch_text;
	unsigned int n_x;
	unsigned char* pChars;
	
	#ifdef DEBUG
	printf("[crc] got MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACdst[0], ps_Frame->ach_MACdst[1], ps_Frame->ach_MACdst[2], ps_Frame->ach_MACdst[3], ps_Frame->ach_MACdst[4], ps_Frame->ach_MACdst[5]);
	printf("[crc] got MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACsrc[0], ps_Frame->ach_MACsrc[1], ps_Frame->ach_MACsrc[2], ps_Frame->ach_MACsrc[3], ps_Frame->ach_MACsrc[4], ps_Frame->ach_MACsrc[5]);
	printf("[crc] got Length: %d\n", ps_Frame->ach_Length);
	printf("[crc] got Payload: %s\n", ps_Frame->ach_Payload);
	#endif
	SFrameCRC s_framecrc;
	
	/* important! zero this F..ine Payload or bug! */
	for(n_i=0;n_i<46;++n_i) {
		s_framecrc.ach_Payload[n_i] = 0x00;
	}
	/* rewriting */
	for(n_i=0;n_i<6;++n_i) {
		s_framecrc.ach_MACdst[n_i] = ps_Frame->ach_MACdst[n_i];
		s_framecrc.ach_MACsrc[n_i] = ps_Frame->ach_MACsrc[n_i];
	}
	s_framecrc.ach_Length  = ps_Frame->ach_Length;
	strcpy(s_framecrc.ach_Payload, ps_Frame->ach_Payload);
	#ifdef DEBUG
	printf("[crc] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", s_framecrc.ach_MACdst[0], s_framecrc.ach_MACdst[1], s_framecrc.ach_MACdst[2], s_framecrc.ach_MACdst[3], s_framecrc.ach_MACdst[4], s_framecrc.ach_MACdst[5]);
	printf("[crc] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", s_framecrc.ach_MACsrc[0], s_framecrc.ach_MACsrc[1], s_framecrc.ach_MACsrc[2], s_framecrc.ach_MACsrc[3], s_framecrc.ach_MACsrc[4], s_framecrc.ach_MACsrc[5]);
	printf("[crc] Length: %d\n", s_framecrc.ach_Length);
	printf("[crc] Payload: %s\n", s_framecrc.ach_Payload);
	#endif

	pch_text = (unsigned char*)&s_framecrc; // cast struct to byte array -> magic
	#ifdef DEBUG
	printf("[crc] ");
	for(n_i=0;n_i<sizeof(s_framecrc);++n_i) {
		printf("%02X ",pch_text[n_i]);
	}
	printf("\n");
	#endif
	n_x = fn_crc32(pch_text,sizeof(s_framecrc)); // write crc32 to n_x
	pChars = (unsigned char*) &n_x;             // cast -> magic
	#ifdef DEBUG
	//printf("TO FRAME: %02x %02x %02x %02x\n", pChars[3],pChars[2],pChars[1],pChars[0]);	
	printf("[crc] CRC32 of frame shouldbe %08x\n",fn_crc32(pch_text,sizeof(s_framecrc)));
	printf("[crc] CRC of frame is %02x%02x%02x%02x\n",ps_Frame->ach_crc[0],ps_Frame->ach_crc[1],ps_Frame->ach_crc[2],ps_Frame->ach_crc[3]);
	#endif
	// compare frame CRC with calc frame CRC -> TRUE if the same
	if(ps_Frame->ach_crc[0] == pChars[3] && ps_Frame->ach_crc[1] == pChars[2] && ps_Frame->ach_crc[2] == pChars[1] && ps_Frame->ach_crc[3] == pChars[0]) {
		#ifdef DEBUG
		printf("%08x == %02x%02x%02x%02x\n",fn_crc32(pch_text,sizeof(s_framecrc)),ps_Frame->ach_crc[0],ps_Frame->ach_crc[1],ps_Frame->ach_crc[2],ps_Frame->ach_crc[3]);
		#endif
		return(1);
	} else {
		#ifdef DEBUG
		printf("%08x != %02x%02x%02x%02x\n",fn_crc32(pch_text,sizeof(s_framecrc)),ps_Frame->ach_crc[0],ps_Frame->ach_crc[1],ps_Frame->ach_crc[2],ps_Frame->ach_crc[3]);
		#endif
		return(0);
	}
	return(0);
}
