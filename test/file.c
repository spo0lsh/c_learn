#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

int main() {
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;	
	int i;
	i=0;
	int j;
	j=0;
	int aging;
	aging=0;
	//char cMAC[6];
	//char MAC;
	//int iMAC;
	int bridgeport;
	bridgeport=0;
	unsigned char ach_MACsrc[6];
	ach_MACsrc[0] = 0;
	ach_MACsrc[1] = 0;
	ach_MACsrc[2] = 0;
	ach_MACsrc[3] = 0;
	ach_MACsrc[4] = 0;
	ach_MACsrc[5] = 0;
	
	fp=fopen("test.txt", "r");
	if (fp == NULL) {
        perror("Nie udalo sie otworzyc pliku test.txt");
        return 1;
    }
	while ((read = getline(&line, &len, fp)) != -1) {
		++i;
		printf("Retrieved line %d of length %zu :\n", i, read);
		if(i == 1) {
			aging=atoi(line);
			printf("%s", line);
		} else {
			printf("%s", line);
			if(line[0] != '\n' ) {
				/*for(j=0;j<12;j++) {
					if(line[j] != '\n' ) {
						printf("%c", line[j]);
					}
				} */
				int a1;
				int a2;
				int a3;
				int a4;
				int a5;
				int a6;
				/*
				for(j=0;j<12;j++) {
					if(line[j] < 97) {
						printf("(%d %c) ", line[j]-48,line[j]);
					} else {
						printf(" (%d\ %c)", line[j]-87,line[j]);
					}
					if(j % 2 != 0) {
						printf("\n");
					}
				}*/
				if(line[j] < 97) {
					a1 = (line[0] - 48 ) * 16 + (line[1] - 48);
					ach_MACsrc[0] = a1 & 0xFF;
					//printf("[d] %02x\n", ach_MACsrc[0]);
					a2 = (line[2] - 48 ) * 16 + (line[3] - 48);
					ach_MACsrc[1] = a2 & 0xFF;
					a3 = (line[4] - 48 ) * 16 + (line[5] - 48);
					ach_MACsrc[2] = a3 & 0xFF;
					a4 = (line[6] - 48 ) * 16 + (line[7] - 48);
					ach_MACsrc[3] = a4 & 0xFF;
					a5 = (line[8] - 48 ) * 16 + (line[9] - 48);
					ach_MACsrc[4] = a5 & 0xFF;
					a6 = (line[10] - 48 ) * 16 + (line[11] - 48);
					ach_MACsrc[5] = a6 & 0xFF;
				} else {
					a1 = (line[0] - 87 ) * 16 + (line[1] - 87);
					ach_MACsrc[0] = a1 & 0xFF;
					//printf("[d] %02x\n", ach_MACsrc[0]);
					a2 = (line[2] - 87 ) * 16 + (line[3] - 87);
					ach_MACsrc[1] = a2 & 0xFF;
					a3 = (line[4] - 87 ) * 16 + (line[5] - 87);
					ach_MACsrc[2] = a3 & 0xFF;
					a4 = (line[6] - 87 ) * 16 + (line[7] - 87);
					ach_MACsrc[3] = a4 & 0xFF;
					a5 = (line[8] - 87 ) * 16 + (line[9] - 87);
					ach_MACsrc[4] = a5 & 0xFF;
					a6 = (line[10] - 87 ) * 16 + (line[11] - 87);
					ach_MACsrc[5] = a6 & 0xFF;
				}
				bridgeport=atoi(&line[13]);
				printf("%02d:%02d:%02d:%02d:%02d:%02d %d\n",a1,a2,a3,a4,a5,a6,bridgeport);
				printf("\n");
				/*
				printf("0x%c%c ", line[0], line[1]);
				printf("0x%c%c ", line[2], line[3]);
				printf("0x%c%c ", line[4], line[5]);
				printf("0x%c%c ", line[6], line[7]);
				printf("0x%c%c ", line[8], line[9]);
				printf("0x%c%c\n", line[10], line[11]);
				*/
				//strcut(ach_MACsrc[0],line[0]);
				//memcpy(cMAC,line,2);
				//printf("MAC: %c%c\n",cMAC[0],cMAC[1]);
				//memcpy((int)iMAC,cMAC,2);
				//printf("MAC: %d\n",iMAC);
				//int a;
				//int b;
				//a=atoi(&line[0]);
				//b=atoi(&line[1]);
				//strncpy(&MAC,line,1);
				//printf("%c\n", MAC);
				//strncpy(&cMAC,line,2);
				//printf("%c%c\n", cMAC[0],cMAC[1]);
				
				//char str[] = "0xff";
				//int num;
				//sscanf(str, "%x", &num);
				//printf("0x%x %i\n", num, num); 
				//MAC = (int)((line[0] << 8) + line[1]);
				//MAC=(int)((line[0] * 256) + line[1]);
				//MAC=(atoi(&line[0] * 256)) + atoi(&line[1]);
				//printf("MAC: %d %02x\n",MAC,MAC);
				//num = 256;
				/*
				char text[8];
				sprintf(text, "0x%c%c", line[0],line[1]); // puts "0x500" in text
				printf("%s ", text);
				sprintf(text, "0x%c%c", line[2],line[3]); // puts "0x500" in text
				printf("%s ", text);
				sprintf(text, "0x%c%c", line[4],line[5]); // puts "0x500" in text
				printf("%s ", text);
				sprintf(text, "0x%c%c", line[6],line[7]); // puts "0x500" in text
				printf("%s ", text);
				sprintf(text, "0x%c%c", line[8],line[9]); // puts "0x500" in text
				printf("%s ", text);
				sprintf(text, "0x%c%c", line[10],line[11]); // puts "0x500" in text
				printf("%s ", text);
				printf("\n");
				*/
				//ach_MACsrc[5] = 0x5f;
				//sprintf(ach_MACsrc[5], "0x%c%c", line[10],line[11]);
				//sprintf(MAC, 0x%c%c, line[10],line[11]);
				//int a,b;
				//a=atoi(&line[10]);
				//b=atoi(&line[11]);
				//sprintf((unsigned char)ach_MACsrc[5], "0x%d%d", a,b);
				//int x = 300;
				//char out[4];
				//memcpy(out, &x, sizeof(int));
				//printf("
				
				//ach_MACsrc[5] = (atoi(line[10]) << 4);
				//ach_MACsrc[5] = ((line[10] - '0') << 4) | (line[11] - '0');
				
				//unsigned char bytes[4];
				//unsigned long n = 95;
				//int n = 95;
				//unsigned int a;
				//unsigned int b;
				//a=atoi(&line[10]);
				//b=atoi(&line[11]);
				
				//bytes[0] = (n >> 24) & 0xFF;
				//bytes[1] = (n >> 16) & 0xFF;
				//bytes[2] = (n >> 8) & 0xFF;
				//bytes[3] = n & 0xFF;
				//printf("%x %x %x %x\n", bytes[0], bytes[1], bytes[2], bytes[3]);
				//printf("%x\n", bytes[3]);
				
			}
		}
	}
	printf("===============\n");
	printf("Aging %d\n", aging);
	printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x ", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5]);
	printf("Bridgeport %d\n", bridgeport);
	free(line);
	fclose(fp);
	printf("===============\n");
	/*
	char dupa[] = "0123456789abcdef";
	//printf("%d\n", dupa[0] - 87);
	for(i=0;i<strlen(dupa);++i) {
		printf("%d %c ", dupa[i],dupa[i]);
		if(dupa[i] < 97) {
			printf("%d\t%c\n", dupa[i]-48,dupa[i]);
		} else {
			printf("%d\t%c\n", dupa[i]-87,dupa[i]);
		}
	}
	*/
	exit(EXIT_SUCCESS);
}
/*

*/
