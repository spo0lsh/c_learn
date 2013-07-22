#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	//char MAC[
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
				for(j=0;j<12;j++) {
					if(line[j] != '\n' ) {
						printf("%c", line[j]);
					}
				}
				bridgeport=atoi(&line[13]);
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
			}
		}
	}
	printf("===============\n");
	printf("Aging %d\n", aging);
	printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x ", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5]);
	printf("Bridgeport %d\n", bridgeport);
	free(line);
	fclose(fp);
	exit(EXIT_SUCCESS);
}
/*

*/
