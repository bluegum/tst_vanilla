#include <stdio.h>
#include <stdlib.h>
#include "tst.h"

static void
print_key (char *k, void* val)
{
   printf("%s\n", k);
}

int main(int argc, char *argv[])
{
   int	i;
   char t[1024], *s=t, *fname;
   FILE *fp;
   Tptr tst, p;

   if (argc == 1)
   { /* no args */
      fp = stdin;
   }
   else /* at least one arg: file name */
   {
      fname = argv[1];
      if ((fp = fopen(fname, "r")) == NULL) {
	 fprintf(stderr, "  Can't open file\n");
	 exit(1);
      }
   }
   setbuf(stdout, 0);
   /* populate tst */
   tst = tst_init();
   while ((i = getc(fp)) != EOF) 
   {
      if (i == '\n') {
	 *s++ = 0;
	 tst_insert(tst, t, NULL);
	 s = t;
      } else
	 *s++ = i;
   }
   *s++ = 0;
   tst_insert(tst, t, NULL);
   /* examine tst */
   tst_traverse(tst, print_key);
   /* insertion */
   tst = tst_insert(tst, "laser", NULL);
   tst = tst_insert(tst, "lasec", NULL);
   /* search */
   p = tst_search(tst, "laser");
   if (p)
   {
      printf("found %s\n", "laser");
   }
   else
   {
      printf("not found %s\n", "laser");
   }
   /* deletion */
   tst_delete(tst, "laser");
   tst_delete(tst, "lasec");
   p = tst_search(tst, "laser");
   if (p)
   {
      printf("found %s\n", "laser");
   }
   else
   {
      printf("not found %s\n", "laser");
   }
   p = tst_search(tst, "lasec");
   if (p)
   {
      printf("found %s\n", "lasec");
   }
   else
   {
      printf("not found %s\n", "lasec");
   }
   tst_delete(tst, "lax");
   p = tst_search(tst, "laxative");
   p = tst_search(tst, "lax");
   /* data functions */
   {
     void *d;
     p = tst_insert(tst, "mydata", (void*) 0xff);
     p = tst_search(tst, "mydata");
     d = tst_retrieve(p);
     tst_attach(p, (void*)0xffff);
     d = tst_retrieve(p);
   }
   /* remove */
   tst_cleanup(tst);
   return 0;
}
