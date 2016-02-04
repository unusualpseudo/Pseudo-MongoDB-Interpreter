#include <bson.h>
#include <stdlib.h>
#include <stdio.h>


int main ()
{
   bson_json_reader_t *reader;
   bson_error_t error;
   const char *filename;
   bson_t doc = BSON_INITIALIZER;
   int i;
   int b;


      FILE * bson ;
      bson = fopen("db/default/users" , "a");

      reader = bson_json_reader_new_from_file ("json", &error);
      b = bson_json_reader_read (reader, &doc, &error);
         if (b < 0)
         {
            fprintf (stderr, "Error in json parsing:\n%s\n", error.message);
            abort ();
         }

        /* if (fwrite (bson_get_data(&doc), 1, doc.len, stdout) != doc.len) {

            exit (1);
         }*/
         fwrite (bson_get_data(&doc), 1, doc.len, bson);


      bson_json_reader_destroy (reader);
      bson_destroy (&doc);


   return 0;
}
