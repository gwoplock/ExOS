#include "StrCmp.h"

int strcmp(char* str1, char* str2){
    size_t i;
    for(i = 0; i<strlen(str1) && i<strlen(str2); i++ ){
        if (str1[i] != str2[i]){
            break;
        }
    }
  return str1[i] - str2[i];
}