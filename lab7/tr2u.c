#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char * argv[])
{
  if ( argc != 3){
    fprintf(stderr,"Incorrect number of arguements\n");
    exit(1);
  }

  int fromlen = strlen(argv[1]);
  int tolen = strlen(argv[2]);

  if (fromlen != tolen){
    fprintf(stderr,"Input arguements have different length values\n");
    exit(1);

  }

  char *from = argv[1];
  char *to = argv[2];

  for(int i = 0; i < fromlen; i++){
    for(int j = 0; j < fromlen; j++){

      if( (int) from[i] == (int) from[j]  && j != i ){
	fprintf(stderr,"Dupilcate bytes found in from string\n");
	  exit(1);
      }
    }
  }
  
    
//////// TR2U /////// unbuffered
    
    
  char input;
  int change;
  while (1){

    int readchar = read(0, &input, 1);
    int writechar;
    if(readchar < 0){
      fprintf(stderr,"read function call failed");
      exit(1);
    }
    else if(readchar == 0){
      exit(1);
    }
    int i = 0;
    for (; i < fromlen; i++){
      
      if ((int)input == (int)from[i]){

	change = 1;
	break;
    }
      else{
	change = 0;

        continue;
      }
	
      
    }//end of for

    if(change == 1)
     writechar = write(1, &to[i], 1);//putchar(to[i]);
    else
     writechar = write(1, &input, 1);//putchar(input);

    if (writechar < 0)
      fprintf(stderr, "write function call error");
    
   }//end of while
}


////// TR2B ////// bufferred


char input;
int change;
while ((input = getchar()) != EOF){
    int i =0;
    for (; i < fromlen; i++){
        
        if ((int)input == (int)from[i]){
            
            change = 1;
            break;
        }
        else{
            change = 0;
            
            continue;
        }
        
        
    }//end of for
    
    if(change == 1)
        putchar(to[i]);
        else
            putchar(input);
            }//end of while
}

