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
				int a1;
				int a2;
				int a3;
				int a4;
				int a5;
				int a6;
				if(line[j] < 97) {
					a1 = (line[0] - 48 ) * 16 + (line[1] - 48);
					ach_MACsrc[0] = a1 & 0xFF;
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
				printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x port %d\n", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5], bridgeport);
				printf("\n");
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
	exit(EXIT_SUCCESS);
}
/*

*/
