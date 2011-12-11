#include <stdio.h>
#include <stdlib.h>
#include "tst.h"

typedef struct tnode {
   unsigned char splitchar;
   Tptr lokid, eqkid, hikid;
} Tnode;


Tptr insert(Tptr p, char *s, void *val)
{
   if (p == 0) {
      p = (Tptr) malloc(sizeof(Tnode));
      if (s)
      {
	 p->splitchar = *s;
      }
      else
      {
	 p->splitchar = 0;
      }
      p->lokid = p->eqkid = p->hikid = 0;
      if (!s)
	 return p;
   }
   if (*s < p->splitchar)
      p->lokid = insert(p->lokid, s, val);
   else if (*s == p->splitchar) {
      if (*s == 0)
	 p->eqkid = (Tptr)val;
      else
	 p->eqkid = insert(p->eqkid, ++s, val);
   } else
      p->hikid = insert(p->hikid, s, val);
   return p;
}

void cleanup(Tptr p)
{   if (p) {
      cleanup(p->lokid);
      if (p->splitchar) cleanup(p->eqkid);
      cleanup(p->hikid);
      free(p);
   }
}

/* iterative search */
Tptr search(Tptr root, char *s)
{
   Tptr p;
   p = root;
   while (p) {
      if (*s < p->splitchar)
	 p = p->lokid;
      else if (*s == p->splitchar)  {
	 if (*s++ == 0)
	    return p;
	 p = p->eqkid;
      } else
	 p = p->hikid;
   }
   return 0;
}

/* recursive search */
int rsearch(Tptr p, char *s)
{   if (!p) return 0;
   if (*s < p->splitchar)
      return rsearch(p->lokid, s);
   else if (*s > p->splitchar)
      return rsearch(p->hikid, s);
   else {
      if (*s == 0) return 1;
      return rsearch(p->eqkid, ++s);
   }
}

#if 0
void pmsearch(Tptr p, char *s)
{   if (!p) return;
   if (*s == '.' || *s < p->splitchar)
      pmsearch(p->lokid, s);
   if (*s == '.' || *s == p->splitchar)
      if (p->splitchar && *s)
	 pmsearch(p->eqkid, s+1);
   if (*s == 0 && p->splitchar == 0)
      srcharr[srchtop++] =
	 (char *) p->eqkid;
   if (*s == '.' || *s > p->splitchar)
      pmsearch(p->hikid, s);
}


void nearsearch(Tptr p, char *s, int d)
{   if (!p || d < 0) return;
   if (d > 0 || *s < p->splitchar)
      nearsearch(p->lokid, s, d);
   if (p->splitchar == 0) {
      if ((int) strlen(s) <= d)
	 srcharr[srchtop++] = (char *) p->eqkid;
   } else
      nearsearch(p->eqkid, *s ? s+1:s,
		 (*s == p->splitchar) ? d:d-1);
   if (d > 0 || *s > p->splitchar)
      nearsearch(p->hikid, s, d);
}
#endif

static char frame[1024];
static char *f = frame;
void traverse(Tptr p)
{
   if (!p) {return;}
   traverse(p->lokid);
   if (p->splitchar)
   {
      *f++ = p->splitchar;
      traverse(p->eqkid);
      f--;
   }
   else
   {
      char *t = frame;
      for (; t<f; t++) printf("%c", *t);
      printf("%s", "\n");
   }
   traverse(p->hikid);
}

Tptr tst_init()
{
   return  insert(0, 0, 0);
}
int tst_attach(Tptr p, void *val)
{
   if (!p->splitchar)
   {
      p->eqkid = (Tptr)val;
      return 0;
   }
   return 1;
}
void* tst_retrieve(Tptr p)
{
   if (!p->splitchar)
   {
      return (void*)(p->eqkid);
   }
   else
   {
      return 0;
   }
}