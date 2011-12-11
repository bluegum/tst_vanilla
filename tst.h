/* TERNARY SEARCH TREE ALGS */

typedef struct tnode *Tptr;

extern Tptr tst_insert(Tptr p, char *s, void *val);
extern Tptr tst_search(Tptr p, char *s);
extern int tst_rsearch(Tptr p, char *s);
extern void * tst_delete(Tptr p, char *s);
extern void tst_cleanup(Tptr p);

/* user data */
extern Tptr tst_init();
extern int tst_attach(Tptr, void *val);
extern void* tst_retrieve(Tptr);
