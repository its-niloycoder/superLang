/* Module support interface */

extern object *initmodule (char *, struct methodlist *);
extern int getintarg(object *v, int *a);
extern void fatal(char *msg);
extern int getstrarg(object *v, object **a);