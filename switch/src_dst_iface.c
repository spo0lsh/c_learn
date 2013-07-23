#include "src_dst_iface.h"

int fn_src_dst_iface(int src, int dst) {
	#ifdef DEBUG
	printf("[src vs dst] %d -> %d\n",src,dst);
	#endif
	if(src==dst) {
		return 0;
	} else {
		return 1;
	}
}
