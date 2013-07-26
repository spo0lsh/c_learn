#include <stdio.h>
#include "aging.h"
#include "switch.h"
#include "db.h"

/* aging */
void fn_aging() {
	#ifdef DEBUG
	printf("Aging procedure ... %d\n", n_aging);
	#endif
	fn_search_rm(); // remove expired 
	fn_mac_show(); // show mac table (without empty) -> only in debug?
}
