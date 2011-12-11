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
   //tst = insert(0, "laser", NULL);
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
   p = search(tst, "laser");
   if (p)
   {
      printf("found %s\n", "laser");
   }
   cleanup(tst);
   return 0;
}
