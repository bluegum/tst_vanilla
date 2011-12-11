/* TERNARY SEARCH TREE ALGS */

typedef struct tnode *Tptr;

extern Tptr insert(Tptr p, char *s, void *val);
extern Tptr search(Tptr p, char *s);
extern int rsearch(Tptr p, char *s);
extern void cleanup(Tptr p);

/* user data */
extern Tptr tst_init();
extern int tst_attach(Tptr, void *val);
extern void* tst_retrieve(Tptr);
