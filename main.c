#include <stdio.h>
#include <stdlib.h>
#include "tst.h"

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
	 insert(tst, t, NULL);
	 s = t;
      } else
	 *s++ = i;
   }
   *s++ = 0;
   insert(tst, t, NULL);
   /* examine tst */
   traverse(tst);
   /* insertion */
   tst = insert(tst, "laser", NULL);
   tst = insert(tst, "lasec", NULL);
   /* search */
   p = search(tst, "laser");
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
   p = search(tst, "laser");
   if (p)
   {
      printf("found %s\n", "laser");
   }
   else
   {
      printf("not found %s\n", "laser");
   }
   p = search(tst, "lasec");
   if (p)
   {
      printf("found %s\n", "lasec");
   }
   else
   {
      printf("not found %s\n", "lasec");
   }
   tst_delete(tst, "lax");
   p = search(tst, "laxative");
   p = search(tst, "lax");
   /* remove */
   cleanup(tst);
   return 0;
}
