#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// remove trailing cr-lf
void trim(char *line) {
  size_t n = strlen(line);
  while (n > 0 && (line[n-1] == '\n' || line[n-1] == '\r')) {
    --n;
  }
  line[n]='\0';
}

int test(const char *pattern, const char *samples, int expected) {
  regex_t regex;
  int retval = 0;

  retval = regcomp(&regex, pattern, REG_EXTENDED);
  if (retval) {
    fprintf(stderr, "Could not compile regex\n");
    return retval;
  }

  FILE *file = fopen(samples, "r");  // Open the file for reading
  if (file == NULL) {
    printf("Failed to open file %s",samples);
    return -1;
  }

  char *line = NULL;
  size_t capacity = 0;
  ssize_t read;

  while ((read = getline(&line, &capacity, file)) != -1) {
    trim(line);
    int match = ! regexec(&regex, line , 0, NULL, 0);
    
    printf("%s %s\n",line,((match) ? "matches pattern" : "does not match pattern"));
    if (match != expected) {
      retval = 3;
    }
  }
  
  free(line);  // Free the allocated line buffer
  fclose(file);  // Close the file

  if (retval != 0) {
    printf("unexpected results.\n");
  }
  
  return retval;
}

int main(int argc, const char *argv[]) {
  const char *pattern = "^\"([^\\\\\\\"]|\\\\[nrt\\\"])*\"$";

  int retval = 0;

  retval = test(pattern,"matches.txt",1) || retval;
  retval = test(pattern,"mismatches.txt",0) || retval;
  return retval;
}

