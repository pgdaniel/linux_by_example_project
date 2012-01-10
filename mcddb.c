#include <db.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mcddb.h"

static DB *db;

int open_db(char *dbpath)
{
    int ret;
    char *defpath = "./mcd.db";

    if (!dbpath){
        if ((dbpath = malloc(strlen(defpath) + 1)) != NULL) {
            strcpy(dbpath, defpath);
        }
        else {
            return -1;
        }
    }


    ret = open(dbpath, DB_BTREE, DB_CREATE, 0600, NULL, NULL, &db);
    if (ret != 0) {
        return ret;
    }
    else
        puts("OPEN");

    return 0;
}

int add_rec(char *kbuf, char *vbuf)
{
    DBT key, value;
    int ret;

    memset(&key, 0, sizeof(DBT));
    memset(&value, 0, sizeof(DBT));

    key.data = kbuf;
    key.size = strlen(kbuf);
    value.data = vbuf;
    value.size = strlen(vbuf);

    ret = db->put(db, NULL, &key, &value, DB_NOOVERWRITE);
    if (ret == DB_KEYEXIST)
        return 1;

    else if (ret != 0)
        return ret;

    db->sync(db, 0);

    return 0;
}

int del_rec(char *kbuf)
{
    int ret;
    DBT key;

    memset(&key, 0, sizeof(DBT));
    key.data = kbuf;
    key.size = strlen(kbuf);

    ret = db->del(db, NULL, &key, 0);
    if (ret != 0) {
        if (ret == DB_NOTFOUND) {
            return 1;
        }
        else 
            return ret;
    }
    db->sync(db, 0);
    
    return 0;
}

int find_rec(char *kbuf, DBT *value)
{
    int ret;
    DBT key;
    DBC *dbc = NULL;

    ret = db->cursor(db, NULL, &dbc, 0);
    if (ret != 0)
        return ret;

    memset(&key, 0, sizeof(DBT));
    key.data = kbuf;
    key.size = strlen(kbuf);

    
    while ((ret = dbc->c_get(dbc, &key, value, DB_NEXT)) != DB_NOTFOUND) {
        if (!strncmp(key.data, kbuf, strlen(kbuf))) {
            if (key.size == strlen(kbuf)) {
                    break;
            }
        }

    }
        if (ret == DB_NOTFOUND) {
            return 1;
        }

    return 0;
}


int get_rec(char *kbuf, DBT *value)
{
    int ret;
    DBT key;


    memset(&key, 0, sizeof(DBT));
    key.data = kbuf;
    key.size = strlen(kbuf);


    ret = db->get(db, NULL, &key, value, 0);
    switch(ret) {
        case 0:
            return 0;
        case DB_NOTFOUND:
            return 1;
        default:
            return ret;
    }
}


int count_recs(void)
{
    int ret, cnt = 0;
    DBT key, value;
    DBC *dbc = NULL;

    ret = db->cursor(db, NULL, &dbc, 0);
    if (ret != 0)
        return ret;

    memset(&key, 0, sizeof(DBT));
    memset(&value, 0, sizeof(DBT));

    while ((dbc->c_get(dbc, &key, &value, DB_NEXT)) != DB_NOTFOUND) {
        ++cnt;
    }
    return cnt;
}

int list_recs(char **keys, char **values)
{
    int ret, cnt = 0;
    DBT key, value;
    DBC *dbc = NULL;

    ret = db->cursor(db, NULL, &dbc, 0);
    
    if (ret != 0) {

    }
}












