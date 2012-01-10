#ifdef MCDDB_H_
#define MCDDB_H_

#include <db.h>

int open_db(char *dbpath);

int close_db(void);

int add_rec(char *kbuf, char *vbuf);

int del_rec(char *kbuf);

int find_rec(char *kbuf, DBT *value);

int get_rec(char *kbuf, DBT *value);

int count_recs(void);

int list_recs(char **keys, char **values);

#endif



