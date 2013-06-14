#ifndef __zadanie1_H
#define __zadanie1_H

#define MAXX 1000
#define MAXY 500
#define MAXZ 100

void tab3d(int,int,int);
int ***tab3d_create();
void tab3d_filling(int (***));
void tab3d_print(int (***));
void tab3d_free(int (***));

#endif /* __zadanie1_H */
