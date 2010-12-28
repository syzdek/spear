
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#define BUFF_LEN	1024

int main(int argc, char * argv[]);
int parse(xmlNode * a_node, int level);

int main(int argc, char * argv[])
{
   int       fd;
   int       len;
   char      buff[BUFF_LEN];
   xmlDoc  * doc = NULL;
   xmlNode * root_element = NULL;

   LIBXML_TEST_VERSION;

   if (argc < 2)
   {
      fprintf(stderr, "Usage: %s <file>\n", argv[0]);
      return(1);
   };

   if ((fd = open(argv[1], O_RDONLY)) == -1)
   {
      perror("open()");
      return(1);
   };

   if ((len = read(fd, buff, BUFF_LEN-1)) == -1)
   {
      perror("read()");
      close(fd);
      return(1);
   };
   buff[len] = '\0';

   close(fd);

   if (!(doc = xmlReadMemory(buff, len, NULL, NULL, 0)))
   {
      fprintf(stderr, "unable to parse \"%s\"\n", argv[1]);
      return(1);
   };

   /* Get the root element node */
   root_element = xmlDocGetRootElement(doc);

   parse(root_element, 0);

   /*free the document */
   xmlFreeDoc(doc);
   xmlCleanupParser();

   return(0);
}


int parse(xmlNode * root, int level)
{
   int       i;
   xmlAttr * att;
   xmlNode * cur;

   for(cur = root; cur; cur = cur->next)
   {
      if (cur->type == XML_ELEMENT_NODE)
      {
         for(i = 0; i < level; i++)
            printf("   ");
         printf("<%s", cur->name);
         for(att = cur->properties; att; att = att->next)
         {
            if (att->type == XML_ATTRIBUTE_NODE)
               printf(" %s=\"\"", att->name);
         };
         printf(">\n");
         if (cur->next)
         if (cur->next->content)
            if ((cur->next->content[0] != '\0') && (cur->next->content[0] != '\n'))
               printf("%s\n", cur->next->content);
      };
         parse(cur->children, level + 1);
         //for(i = 0; i < level; i++)
         //   printf("   ");
         //printf("</%s>\n", cur->name);
         //if (cur->content)
         //   if ((cur->content[0] != '\0') && (cur->content[0] != '\n'))
         //      printf("%s\n", cur->content);
   };

   return(0);
}

