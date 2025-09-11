#ifndef PARAM_C
#define PARAM_C

#include "../include/macro.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/params.h"

// remove from input file white/empty lines and comments
// comments start with the character #

void remove_white_lines_and_comments(FILE *input) {
  int temp_i;

  temp_i = getc(input);
  if (temp_i == '\n' || temp_i == ' ' ||
      temp_i == '\043') // scan for white lines and comments
  {
    ungetc(temp_i, input);

    temp_i = getc(input);
    if (temp_i == '\n' || temp_i == ' ') // white line
    {
      do {
        temp_i = getc(input);
      } while (temp_i == '\n' || temp_i == ' ');
    }
    ungetc(temp_i, input);

    temp_i = getc(input);
    if (temp_i == '\043') // comment, \043 = ascii oct for #
    {
      do {
        temp_i = getc(input);
      } while (temp_i != '\n');
    } else {
      ungetc(temp_i, input);
    }

    remove_white_line_and_comments(input);
  } else {
    ungetc(temp_i, input);
  }
}

void readinput(char *in_file)

#endif