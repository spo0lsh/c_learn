#ifndef __db_H
#define __db_H


typedef struct {
	unsigned char ach_MACsrc[6];
	int n_Port;
	int n_Age;
	int n_Filter;
} sHashTable;

sHashTable *fn_create_hash(); // return hash?
void fn_destroy_hash(); // status?
int fn_hash(); // HASH
void fn_remove(); // status
void fn_add_srcmac(); // status
void fn_search_rm(); // 
void fn_entry(); // single entry
void fn_readfile(); //

#endif /* __db_H */
