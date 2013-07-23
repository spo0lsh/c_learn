#ifndef __db_H
#define __db_H


typedef struct {
	unsigned char ach_MACsrc[6];
	int n_Port;
	int n_Age;
	int n_Filter;
} sHashTable;

sHashTable *asHASH;
int aging;
sHashTable *fn_create_hash(); // return hash?
void fn_destroy_hash(sHashTable *); // status?
int fn_hash(unsigned char[6]); // HASH
void fn_remove(int); // status
void fn_add_srcmac(unsigned char *,int,int ); // status
void fn_search_rm(); // 
void fn_entry(); // single entry
void fn_readfile(); //
//void fn_hash_show(sHashTable *); // show mac table
void fn_hash_show(); // show mac table

#endif /* __db_H */
