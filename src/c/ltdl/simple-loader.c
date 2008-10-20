#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ltdl.h>

int main (int argc, const char *argv[])
{
   int           i;
   char          modulepath[1024];
   int         * value;
   lt_dlhandle   module;
   const lt_dlinfo   * info;

   int (*add) (int a);

   if (argc < 3)
   {
      fprintf (stderr, "USAGE: main MODULENAME <num1> <num2> ... <numN>\n");
      exit(1);
   };

   /* Set the module search path. */
   memset(modulepath, 0, 1024);
   getcwd(modulepath, 1023);
   strncat(modulepath, "/",     1023);
   strncat(modulepath, argv[1], 1023);
   strncat(modulepath, ".la",   1023);

   if (lt_dlinit())
   {
      fprintf(stderr, "lt_dlinit(): %s\n", lt_dlerror());
      lt_dlexit();
      return(1);
   };

   /* Load the module. */
   if (!(module = lt_dlopen(modulepath)))
   {
      fprintf(stderr, "lt_dlopen(): %s\n", lt_dlerror());
      lt_dlexit();
      return(1);
   };

   if (!(info = lt_dlgetinfo(module)))
   {
      fprintf(stderr, "lt_dlgetinfo(): %s\n", lt_dlerror());
      lt_dlexit();
      return(1);
   };
   printf("DL Info:\n");
   printf("   File Name:         %s\n", info->filename);
   printf("   Module Name:       %s\n", info->name);
   printf("   Reference Count:   %i\n", info->ref_count);

   if (!(value = lt_dlsym(module, "mod_simple_value")))
   {
      fprintf(stderr, "lt_dlsym(value): %s\n", lt_dlerror());
      lt_dlexit();
      return(1);
   };

   if (!(add = lt_dlsym(module, "mod_simple_add")))
   {
      fprintf(stderr, "lt_dlsym(add): %s\n", lt_dlerror());
      lt_dlexit();
      return(1);
   };

   (*value) = 0;
   for(i = 2; i < argc; i++)
      add(atol(argv[i]));
   printf("bar:  %i\n", *value);

   if ((lt_dlclose(module)))
   {
      fprintf(stderr, "lt_dlclose(): %s\n", lt_dlerror());
      lt_dlexit();
      return(1);
   };

   lt_dlexit();

  return(0);
}

