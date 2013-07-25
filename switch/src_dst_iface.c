#include "src_dst_iface.h"

int fn_src_dst_iface(int n_src, int n_dst) {
	#ifdef DEBUG
	printf("[src vs dst] %d -> %d\n",n_src,n_dst);
	#endif
	if(n_src==n_dst) {
		#ifdef DEBUG
		printf("[src vs dst] %d == %d, return: 0 !!\n",n_src,n_dst);
		#endif
		return 0;
	} else {
		#ifdef DEBUG
		printf("[src vs dst] %d != %d, return: 1 uff!!\n",n_src,n_dst);
		#endif
		return 1;
	}
}
