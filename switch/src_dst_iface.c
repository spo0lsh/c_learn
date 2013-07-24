#include "src_dst_iface.h"

int fn_src_dst_iface(int n_src, int n_dst) {
	#ifdef DEBUG
	printf("[src vs dst] %d -> %d\n",n_src,n_dst);
	#endif
	if(n_src==n_dst) {
		return 0;
	} else {
		return 1;
	}
}
