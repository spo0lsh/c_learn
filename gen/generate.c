#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "generate.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define DEBUG

int main(int argc, char *argv[]){
	int n_i;
	int n_line;
	n_line=0;
	FILE *fp;
	fp=NULL;
	char * pch_line = NULL;
	size_t len = 0;
	ssize_t read;
	int ai_tmp[12];
	
	SFrame s_frame;
	
	/* zerujemy */
	for(n_i=0;n_i<46;++n_i) {
		s_frame.ach_Payload[n_i] = 0x00;
	}
	for(n_i=0;n_i<6;++n_i) {
		s_frame.ach_MACdst[n_i] = 0x00;
		s_frame.ach_MACsrc[n_i] = 0x00;
	}
	for(n_i=0;n_i<4;++n_i) {
		s_frame.ach_crc[n_i] = 0x00;
	}
	//end
	
	
	//unsigned char ach_MACsrc[6];
	//unsigned char ach_MACdst[6];
	if(argc < 3) {
		printf("%s <filename> <bridgeport>\n", argv[0]);
		return(1);
	}
	
	/* static */
	s_frame.ach_Length = 666;
	(void) strcpy(s_frame.ach_Payload,"DUAP");
	/* dynamic */
	printf("Opening %s\n",argv[1]);
	fp=fopen(argv[1], "r");
	if (fp == NULL) {
        perror("Fail open configfile.txt");
    } else {
		while ((read = getline(&pch_line, &len, fp)) != -1) {
			++n_line;
			printf("%d] %s", n_line,pch_line);
			if(pch_line[0] != '\n' ) {
				for(n_i=0;n_i<12;++n_i) {
					if(pch_line[n_i] < 97 ) {
						ai_tmp[n_i] = (pch_line[n_i] - 48 );
					} else {
						ai_tmp[n_i] = (pch_line[n_i] - 87 );
					}
				}
				if(n_line == 1) {
					s_frame.ach_MACsrc[0] = (ai_tmp[0] * 16 + ai_tmp[1]) & 0xFF;
					s_frame.ach_MACsrc[1] = (ai_tmp[2] * 16 + ai_tmp[3]) & 0xFF;
					s_frame.ach_MACsrc[2] = (ai_tmp[4] * 16 + ai_tmp[5]) & 0xFF;
					s_frame.ach_MACsrc[3] = (ai_tmp[6] * 16 + ai_tmp[7]) & 0xFF;
					s_frame.ach_MACsrc[4] = (ai_tmp[8] * 16 + ai_tmp[9]) & 0xFF;
					s_frame.ach_MACsrc[5] = (ai_tmp[10] * 16 + ai_tmp[11]) & 0xFF;
					//printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5]);
				} else {
					s_frame.ach_MACdst[0] = (ai_tmp[0] * 16 + ai_tmp[1]) & 0xFF;
					s_frame.ach_MACdst[1] = (ai_tmp[2] * 16 + ai_tmp[3]) & 0xFF;
					s_frame.ach_MACdst[2] = (ai_tmp[4] * 16 + ai_tmp[5]) & 0xFF;
					s_frame.ach_MACdst[3] = (ai_tmp[6] * 16 + ai_tmp[7]) & 0xFF;
					s_frame.ach_MACdst[4] = (ai_tmp[8] * 16 + ai_tmp[9]) & 0xFF;
					s_frame.ach_MACdst[5] = (ai_tmp[10] * 16 + ai_tmp[11]) & 0xFF;
					//printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5]);
				}
			}
		}
	}
	pch_line=NULL;
	fclose(fp);
	
	/* calc 32 */
	
	//fn_crc_frame(&s_frame);
	unsigned int x = fn_crc_frame(&s_frame);
	unsigned char* pChars;
	pChars = (unsigned char*) &x;
	printf("TO FRAME: %02x %02x %02x %02x\n", pChars[3],pChars[2],pChars[1],pChars[0]);	
	s_frame.ach_crc[0]=pChars[3];
	s_frame.ach_crc[1]=pChars[2];
	s_frame.ach_crc[2]=pChars[1];
	s_frame.ach_crc[3]=pChars[0];

	printf("MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", s_frame.ach_MACdst[0], s_frame.ach_MACdst[1], s_frame.ach_MACdst[2], s_frame.ach_MACdst[3], s_frame.ach_MACdst[4], s_frame.ach_MACdst[5]);
	printf("MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", s_frame.ach_MACsrc[0], s_frame.ach_MACsrc[1], s_frame.ach_MACsrc[2], s_frame.ach_MACsrc[3], s_frame.ach_MACsrc[4], s_frame.ach_MACsrc[5]);
	printf("Length: %d\n", s_frame.ach_Length);
	printf("Payload: %s\n", s_frame.ach_Payload);
	printf("CRC: %02x%02x%02x%02x\n", s_frame.ach_crc[0],s_frame.ach_crc[1],s_frame.ach_crc[2],s_frame.ach_crc[3]);


	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	message_buf sbuf;
	key = 1000 + atoi(argv[2]);
	//key = ftok("/tmp/bridge0", 'b');
	
	//(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,\%#o)\n",key, msgflg);
    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        return(1);
    }
    else 
		(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	
	sbuf.mtype = 1;
	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	sbuf.frame = s_frame;
	printf("Frame Length: %d\n", sbuf.frame.ach_Length);
	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	
	if (msgsnd(msqid, &sbuf, sizeof(sbuf.frame), IPC_NOWAIT) < 0) {
		//printf("%d %"l %l \n", msqid, sbuf.mtype, sizeof(sbuf.frame) );
		perror("msgsnd");
		exit(1);
	} else 
		printf("Message: Sent\n");
	
	return(0);
}


unsigned reverse(unsigned x) {
   x = ((x & 0x55555555) <<  1) | ((x >>  1) & 0x55555555);
   x = ((x & 0x33333333) <<  2) | ((x >>  2) & 0x33333333);
   x = ((x & 0x0F0F0F0F) <<  4) | ((x >>  4) & 0x0F0F0F0F);
   x = (x << 24) | ((x & 0xFF00) << 8) | ((x >> 8) & 0xFF00) | (x >> 24);
   return x;
}

unsigned int fn_crc32(unsigned char *message,int size) {
   int i, j;
   unsigned int byte, crc;

   i = 0;
   j=0;
   crc = 0xFFFFFFFF;
   byte=0;
   for(i=0;i<size;++i) {
      byte = message[i];            // Get next byte.
      byte = reverse(byte);         // 32-bit reversal.
      for (j = 0; j <= 7; j++) {    // Do eight times.
         if ((int)(crc ^ byte) < 0)
              crc = (crc << 1) ^ 0x04C11DB7;
         else crc = crc << 1;
         byte = byte << 1;          // Ready next msg bit.
      }
      i = i + 1;
   }
   #ifdef DEBUG
   printf("cal: %08x %d\n",reverse(~crc),reverse(~crc));
   #endif
   return reverse(~crc);
}

unsigned int fn_crc_frame(SFrame *ps_Frame) {
	#ifdef DEBUG
	printf("[crc] got MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACdst[0], ps_Frame->ach_MACdst[1], ps_Frame->ach_MACdst[2], ps_Frame->ach_MACdst[3], ps_Frame->ach_MACdst[4], ps_Frame->ach_MACdst[5]);
	printf("[crc] got MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACsrc[0], ps_Frame->ach_MACsrc[1], ps_Frame->ach_MACsrc[2], ps_Frame->ach_MACsrc[3], ps_Frame->ach_MACsrc[4], ps_Frame->ach_MACsrc[5]);
	printf("[crc] got Length: %d\n", ps_Frame->ach_Length);
	printf("[crc] got Payload: %s\n", ps_Frame->ach_Payload);
	#endif
	SFrameCRC framecrc;
	int n_i;
	
	for(n_i=0;n_i<46;++n_i) {
		framecrc.ach_Payload[n_i] = 0x00;
	}
	/* przepisywanie */
	for(n_i=0;n_i<6;++n_i) {
		framecrc.ach_MACdst[n_i] = ps_Frame->ach_MACdst[n_i];
		framecrc.ach_MACsrc[n_i] = ps_Frame->ach_MACsrc[n_i];
	}
	framecrc.ach_Length  = ps_Frame->ach_Length;
	strcpy(framecrc.ach_Payload, ps_Frame->ach_Payload);
	#ifdef DEBUG
	printf("[crc] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", framecrc.ach_MACdst[0], framecrc.ach_MACdst[1], framecrc.ach_MACdst[2], framecrc.ach_MACdst[3], framecrc.ach_MACdst[4], framecrc.ach_MACdst[5]);
	printf("[crc] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", framecrc.ach_MACsrc[0], framecrc.ach_MACsrc[1], framecrc.ach_MACsrc[2], framecrc.ach_MACsrc[3], framecrc.ach_MACsrc[4], framecrc.ach_MACsrc[5]);
	printf("[crc] Length: %d\n", framecrc.ach_Length);
	printf("[crc] Payload: %s\n", framecrc.ach_Payload);
	#endif
	//unsigned char *text = (unsigned char*)&framecrc;
	unsigned char *text;
	text = (unsigned char*)&framecrc;
	#ifdef DEBUG
	printf("[crc] ");
	for(n_i=0;n_i<sizeof(framecrc);++n_i) {
		printf("%02X ",text[n_i]);
	}
	printf("\n");
	printf("[crc] CRC32 of frame shouldbe %08x\n",fn_crc32(text,sizeof(framecrc)));
	printf("[crc] CRC of frame is %02x%02x%02x%02x\n",ps_Frame->ach_crc[0],ps_Frame->ach_crc[1],ps_Frame->ach_crc[2],ps_Frame->ach_crc[3]);
	#endif
	/*
	unsigned int x = -293679408;//well, it should be just 1234.
	unsigned char* pChars;
	pChars = (unsigned char*) &x;
	printf("[crc] should be: %02x %02x %02x %02x\n", pChars[3],pChars[2],pChars[1],pChars[0]);
	*/
	//unsigned char *text = (unsigned char*)&framecrc;
	return(fn_crc32(text,sizeof(framecrc)));
}
