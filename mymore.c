/*
 * mymore.c -- simplified version of Linux more command
 * This command read a file and print the first 24 lines.
 * Then, the program pause for a few special commands to continue or quit.
 */
#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 4 /* macro definition, allow constant values to be \
 declared for use throughout your code */
#define LINELEN 512

void do_more(FILE *); /* Forward declaration for a function. It tells
 the compiler you're going to define the function
 later. The function could be in a different file.
 Forward declaration let you use the function before
 it is defined */
int see_more();
/* The main function */
int main(int ac, char *av[])
{
  FILE *fp; /* A file pointer with variable name of fp */
  if (ac == 1)
  {
    /* No file provided... */
    printf("No file name provided.\n");
    return 1;
  }
  else
    /* Browse through provided files*/
    while (--ac)
    {
      printf("%i", ac);
      if ((fp = fopen(*++av, "r")) != NULL)
      {
        do_more(fp);
        fclose(fp);
      }
      else
      {
        if (ac > 1)
        {
          printf("File %s could not be found. Continuing...\n", *av);
        }
        else
        {
          printf("File %s could not be found.\n", *av);
          exit(1); // exit, 1 means something wrong
        }
      }
    }
  return 0; // 0 means every OK
}
/* read PAGELEN lines, then call see_more() for further instructions */
void do_more(FILE *fp)
{
  char line[LINELEN]; // an array
  int num_of_lines = 0;
  int reply;
  while (fgets(line, LINELEN, fp))
  {
    if (num_of_lines == PAGELEN)
    {
      reply = see_more();
      if (reply == 0)
      {
        break;
      }

      num_of_lines -= reply;
    }

    if (fputs(line, stdout) == EOF) // EOF: End of File
    {
      exit(1);
    }
    num_of_lines++;
  }
}
/* print message, wait for response, return # of lines to advance
 q: quit, space: next page, enter key: next line */
int see_more()
{
  int c;
  printf("\033[7m more? \033[m"); // reverse the monitor
  while ((c = getchar()) != EOF)  // get response
  {
    if (c == 'q')
      return 0;
    if (c == ' ')
      return PAGELEN;
    if (c == 'h')
      return PAGELEN / 2;
    if (c == '\n')
      return 1;
  }
  return 0;
}
// answer, add one more if statement, return 15 or page length / 2???
//