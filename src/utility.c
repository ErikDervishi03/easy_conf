#include <ctype.h>
#include <string.h>

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

int parse_string(char* input, char* rule, char* setting){
  int sep = 0;
  int idx = 0;
  int error = 0;
  int sep_count = 0;

  for(int i=0;input[i]!=0 && input[i]!='\n';i++){
    if(idx >= 49){// setting or value exedeed the maximum len
      error++;
      break;
    }

    if(input[i] == '='){
      sep_count++;

      if(sep_count > 1){
        error++;
        break;
      }

      sep = 1;
      idx=0;
      continue;
    }

    if(!sep){
      rule[idx] = input[i];
    }else{
      setting[idx] = input[i];
    }
    idx++;
  }

  return error;
}