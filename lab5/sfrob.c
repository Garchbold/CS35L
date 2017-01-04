#include <stdio.h>
#include <stdlib.h>


int frobcmp(char const * a, char const * b){
    
    while (1){//(*a != 32) && (*b != 32) ){
        
        if ( *a == 32)
            return 1;
        if ( *b == 32)
            return -1;
        
        if ( (*a^42) > (*b^42) )
            return 1;
        
        else if ( (*a^42) < (*b^42) )
            return -1;
        
        a++;
        b++;
    }
    if ( *a == 32 && *b != 32)
        return -1;
    
    if ( *a != 32 && *b == 32)
        return 1;
    return 0;
}

int qsortwrap(const void * a, const void * b){
    const char const* word1 = *(const char const**) a;
    const char const* word2 = *(const char const**) b;
    
    return frobcmp(word1, word2);
}

int main (void) {
    
    int memsize = 100;
    int i = 0;
    char* cin_array = (char*)malloc(sizeof(char)*memsize);
    
    if (cin_array  == NULL){
        fprintf(stderr,"Memory allocation error");
        exit(1);
    }
    
    char character;
    
    while (1) {
        
        if ((character = getchar()) == EOF) {

	  if ( cin_array[i-1] != ' '){

	    cin_array = (char*)realloc(cin_array, memsize + 1);

	    if ( cin_array == NULL){
	      fprintf(stderr,"Memory allocation error");
	      exit(1);
	    }

	    cin_array[i] = ' ';
	    i++;
	  }
	  
	  break;
        }
        else{

        cin_array[i] = character;
        i++;
        
        if (i == memsize){
            cin_array = (char*)realloc(cin_array, memsize * 4);
	    memsize = memsize * 4;
        }
        
        if (cin_array  == NULL){
            fprintf(stderr,"Memory allocation error");
            exit(1);
        }
        }
    }
    
    char** word_array = malloc(memsize);
    int word_count = 0;
    
    for(int j = 0; j < i; j++){
        
        if( j==0 || ( cin_array[j-1] == ' ' && cin_array[j] != ' ' ) ){
            
	  word_array = realloc(word_array, sizeof(char*) * (word_count + 1));
            
            if ( cin_array == NULL){
                fprintf(stderr,"Memory allocation error");
                exit(1);
            }
            
            word_array[word_count] = &cin_array[j];
            word_count++;
        }
    }    
    qsort(word_array, word_count, sizeof(char*), qsortwrap);  
    
    
    for ( int k = 0; k < word_count; k++){

      char * fpointer = word_array[k];

        
        while ( *fpointer != ' ' && *fpointer != EOF){
            
            putchar(*fpointer);
	    fpointer++;
        }
	putchar(*fpointer);
    }
    
    free(cin_array);
    free(word_array);
    
    
}//end of main


