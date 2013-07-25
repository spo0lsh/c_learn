#include <stdio.h>
#include "aging.h"
#include "switch.h"
#include "db.h"

void fn_aging() {
	#ifdef DEBUG
	printf("Aging procedure ... %d\n", n_aging);
	#endif
	fn_search_rm();
}
