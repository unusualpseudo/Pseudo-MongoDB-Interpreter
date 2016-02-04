#include <bson.h>
#include <stdio.h>


int main (int   argc, char *argv[])
{
   bson_reader_t *reader;
   const bson_t *b;
   bson_error_t error;
   const char *filename;
   char *str;
   int i;

     
      reader = bson_reader_new_from_file ("db/default/users" , false);
      
      while ((b = bson_reader_read (reader, NULL)))
      {
         str = bson_as_json(b, NULL);
         fprintf(stdout, "%s\n", str);
         bson_free(str);
      }

      bson_reader_destroy (reader);

   return 0;
}
