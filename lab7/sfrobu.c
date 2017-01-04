#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // To use read and write
#include <sys/stat.h>

unsigned int comparisons = 0;



int frobcmp(char const * a, char const * b){

  comparisons++;
  
    while (1){
        
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
    char* cin_array;// = (char*)malloc(sizeof(char)*memsize);
    int alpha = 0;


    struct stat filestat;
    fstat(0, &filestat);

    int file_size = filestat.st_size;

    if(S_ISREG(filestat.st_mode)) {
     cin_array = (char*)malloc(sizeof(char)*file_size);

      if(cin_array == NULL) {
	fprintf(stderr, "Error allocating memory.");
	  memsize = file_size; 
	exit(1);
      }
    }
    else{
      cin_array= (char*)malloc(sizeof(char)*memsize);


      if(cin_array == NULL) {
	fprintf(stderr, "Error allocating memory.");
	exit(1);
      }
    }
    
    char character;
        
    while (1) {
        
      if (read(0, &character, 1) <= 0) {
	  
	  if (cin_array[i] != ' ' && i != 0){

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
	if (cin_array[i] != ' ')
	{
	  alpha =1;
	}
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
    }//end of while
    
    
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
    
    if (alpha == 1) {
    for ( int k = 0; k < word_count; k++){

      char * fpointer = word_array[k];

        
        while ( *fpointer != ' ' && *fpointer != EOF){
	    write(1, (fpointer), 1);
	    fpointer++;
        }
	write(1, (fpointer), 1);
    }
    
}
    
    
    free(cin_array);
    free(word_array);

    fprintf(stderr, "Comparisons: %d\n", comparisons);
    
    
}//end of main


