/*
 * This is a test message.
 */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ltdl.h>

int main(int argc, char * argv[]);
void * my_dlsym(lt_dlhandle handle, const char * name);

int main (int argc, char *argv[])
{
   char          modulepath[1024];
   int         * size;
   int         * pause;
   int         * repeat;
   lt_dlhandle   module;
   const lt_dlinfo   * info;
   int (*wave) (void);

   if (argc < 5)
   {
      fprintf (stderr, "Usage: %s MODULENAME <size> <repeat> <pause>\n", argv[0]);
      return(1);
   };

   if (lt_dlinit())
   {
      fprintf(stderr, "lt_dlinit(): %s\n", lt_dlerror());
      lt_dlexit();
      return(1);
   };

   //LTDL_SET_PRELOADED_SYMBOLS();

   /* Set the module search path. */
   memset(modulepath, 0, 1024);
   getcwd(modulepath, 1023);
   strncat(modulepath, "/",     1023);
   lt_dlsetsearchpath(modulepath);

   printf("DL Data:\n");
   printf("  Search Path:           %s\n", lt_dlgetsearchpath());
   printf("\n");

   /* Load the module. */
   if (!(module = lt_dlopen(argv[1])))
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
   printf("DL Module Data:\n");
   printf("   Opened:               %s\n", argv[1]);
   printf("   File Name:            %s\n", info->filename);
   printf("   Module Name:          %s\n", info->name);
   printf("   Reference Count:      %i\n", info->ref_count);
   printf("   Available Functions:\n");

   size   = my_dlsym(module, "size");
   pause  = my_dlsym(module, "pause");
   repeat = my_dlsym(module, "repeat");
   wave   = my_dlsym(module, "wave");

   printf("\n");

   if (size)
   {
      *size = (int) atol(argv[2]);
      printf("setting size to    argv[2] (%i)\n", *size);
   };
   if (repeat)
   {
      *repeat = (int) atol(argv[3]);
      printf("setting repeat to  argv[3] (%i)\n", *repeat);
   };
   if (pause)
   {
      *pause = (int) atol(argv[4]);
      printf("setting pause to   argv[4] (%i)\n", *pause);
   };

   if (wave)
   {
      printf("running wave()...\n");
      wave();
   };

   if ((lt_dlclose(module)))
   {
      fprintf(stderr, "lt_dlclose(): %s\n", lt_dlerror());
      lt_dlexit();
      return(1);
   };

   lt_dlexit();

  return(0);
}


void * my_dlsym(lt_dlhandle handle, const char * name)
{
   void            * ptr;
   char              newname[1024];
   const lt_dlinfo * info;

   info = lt_dlgetinfo(handle);

   snprintf(newname, 1024, "%s_%s", info->name, name);
   if ((ptr = lt_dlsym(handle, newname)))
   {
      printf("                         %s\n", newname);
      return(ptr);
   };

   snprintf(newname, 1024, "%s_LTX_%s", info->name, name);
   if ((ptr = lt_dlsym(handle, newname)))
   {
      printf("                         %s\n", newname);
      return(ptr);
   };

   if ((ptr = lt_dlsym(handle, name)))
   {
      printf("                         %s\n", name);
      return(ptr);
   };

   return(NULL);
}
