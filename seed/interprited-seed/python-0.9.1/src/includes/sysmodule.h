/* System module interface */

object *sysget (char *);
int sysset (char *, object *);
FILE *sysgetfile (char *, FILE *);
void initsys (void);

char *getpythonpath();
void setpythonpath(char *path);
void setpythonargv(int argc, char **argv);
