#include <stdio.h>

int main() {
	char *line = NULL;
	int i;
	unsigned char ach_MAC[6];
	ach_MAC[0] = 0;
	ach_MAC[1] = 0;
	ach_MAC[2] = 0;
	ach_MAC[3] = 0;
	ach_MAC[4] = 0;
	ach_MAC[5] = 0;
	//unsigned char* pChars;
	
	line="ffffffffffff";
	printf("string: %s %d \n",line,(unsigned int)line);
	
	line="012345678901";
	printf("string: %s %d \n",line,(unsigned int)line);
	
	line="aabbccddeeff";
	printf("string: %s %d \n",line,(unsigned int)line);
	
	line="f00000000000";
	printf("string: %s %d \n",line,(unsigned int)line);
	
	line="a0a0a0a0a0a0";
	printf("string: %s %d \n",line,(unsigned int)line);
	
	line="0a0a0a0a0a0a";
	printf("string: %s %d \n",line,(unsigned int)line);

	int a1[12];
	for(i=0;i<12;++i) {
		if(line[i] < 97) {
			a1[i] = (line[i] - 48 );
		} else {
			a1[i] = (line[i] - 87 );
		}
	}
	ach_MAC[0] = (a1[0] * 16 + a1[1]) & 0xFF;
	ach_MAC[1] = (a1[2] * 16 + a1[3]) & 0xFF;
	ach_MAC[2] = (a1[4] * 16 + a1[5]) & 0xFF;
	ach_MAC[3] = (a1[6] * 16 + a1[7]) & 0xFF;
	ach_MAC[4] = (a1[8] * 16 + a1[9]) & 0xFF;
	ach_MAC[5] = (a1[10] * 16 + a1[11]) & 0xFF;
	
	printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", ach_MAC[0], ach_MAC[1], ach_MAC[2], ach_MAC[3], ach_MAC[4], ach_MAC[5]);
	return(0);
}
