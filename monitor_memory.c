#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PAGE_SIZE   4096

int main (int argc, char **argv)
{
  int pid ;
  int frequency ;
  char file_name [64] ;
  FILE *f ;

  int size, resident, shared, text, lib, data, dt ;
  int nb ;
  
  if (argc != 3)
    {
      fprintf (stderr, "usage: monitor_memory freq pid\n") ;
      exit (-1) ;
    }

  frequency = atoi (argv [1]) ;
  pid = atoi (argv [2]) ;

  sprintf (file_name, "/proc/%d/statm", pid) ;
  printf ("frequency = %d pid %d file_name %s\n", frequency, pid,file_name) ;
    
  f = fopen (file_name, "r") ;
  
  if (f == NULL)
    {
      fprintf (stderr, "error opening %s\n", file_name) ;
      exit (-1) ;
    }
  
  while (1)
    {
      nb = fscanf (f, "%d %d %d %d %d %d %d", &size, &resident, &shared, &text, &lib, &data, &dt) ;
      
      printf ("virtual size %d KB resident %d KB  shared %d KB\n", (size * PAGE_SIZE)/1024 , (resident * PAGE_SIZE)/1024, (shared * PAGE_SIZE)/1024) ;
      sleep (frequency) ;

      fseek (f, 0L, SEEK_SET) ;
      
    }
          
  fclose (f) ;
  exit (0) ;

}
