#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>



char convert(int x){
    
    char c;
    
    c = ' ';

    
    if (   ( x >= 0 ) && ( x <= 9 )  ){
        
        c = 48 + x;
        
    }
    
        
    if (   ( x >= 10 ) && ( x <= 15 )  ){
        
        c =  ( x - 10 ) + 65;
        
    }
    

    return(c);
}




char *decToHex(int x,int width){
    
    static char outputString[256];
    
    char *poutputString;
    
    char c;
    
    static char temp[2];
    
    int n;
    int index;
    int div;
    int res;
    int rem;
    int running;

    n = width;
    
    
    poutputString = &outputString[0];
    
    strcpy(poutputString,"");
    
    
    running = x;
    
    for ( index = ( n - 1 ) ; index >= 0 ; index-- ){
        
        div = pow(16 , index);
        
        res = running / div;

        
        c = convert(res);
        
        temp[0] = c;
        temp[1] = 0;
        
        running = running - ( res * div );
        
        strcat(poutputString,temp);
        
        
    }
    
    
    
    
    
    return(poutputString);
}



char *filtered(char c){

    static char temp[2];
    char *ptemp;
    
    int x;
    
    
    ptemp = &temp[0];
    
    strcpy(ptemp,"");
    
    if ( ( c < 32 ) || ( c > 126 ) ){
        
        x = 46 ;
        
    }else{
        
        
        x = c;
        
    }
        
    
    
    

    ptemp[0] = x;
    ptemp[1] = 0;

    return(ptemp);

}



int main (int argc, char *argv[]){
    
    static char inputFileName[256];
    static char inputString[256];
    static char outputString[256];
    static char cString[256];
    
    char *pinputFileName;
    char *pinputString;
    char *poutputString;
    char *pcString;
    
    
    int c;
    int address;
    int running;
    int inner;
    int remaining;
    int rCount;
    
    
    pinputFileName = &inputFileName[0];
    pinputString = &inputString[0];
    poutputString = &outputString[0];
    pcString = &cString[0];
    
    strcpy(pinputFileName,"");
    strcpy(pinputString,"");
    strcpy(poutputString,"");
    strcpy(pcString,"");
    
    
    
    
    c = 9999;
    
    address = 0;
    
    running = 1;
    
    remaining = 0;
    
    rCount = 0;

    
    
    
    if ( argc != 2 ){
        
        printf("\nERROR: No input file was specified.\n\n\n");
        
        exit(0);
        
    }else{
        
      
        
        strcat(pinputFileName,argv[1]);
        
    
    }
    
    printf("\n\n\nINFO: inputFileName = %s",pinputFileName);
    
    
    FILE* inputFile = fopen(pinputFileName,"rb");
    
    
    
    if ( inputFile == NULL ){
        
        printf("\nERROR: The file named %s does not exist.\n\n\n",pinputFileName);
        
        exit(0);
        
    }
    
    
    

    while( running ){
        
        strcpy(poutputString,"");
        
        strcat(poutputString, decToHex(address,4) );
        
        strcat(poutputString,"  ");
        
        strcpy(pcString,"");
        
        
        for ( inner = 0 ; inner <= 7 ; inner++ ){
        
            c = fgetc(inputFile);
        
            strcat(poutputString,"  ");
        
            strcat(poutputString, decToHex(c,2) );
            
            strcat(pcString,filtered(c));
            
            strcat(pcString," ");
            
            
            
            if (feof(inputFile)){
            
                running = 0;
                
                remaining = 7 - inner;
                
                for ( rCount = 0; rCount < remaining; rCount++ ){
                    
                    strcat(poutputString,"    ");
                
                }
                
                strcat(poutputString,"    ");
            
                strcat(poutputString,pcString);
                
                printf("\n%s",poutputString);
                
                //printf( " inner = %d",inner);
            
                break ;
                
                
                
            }
            
        }
            
            
        

        strcat(poutputString,"    ");
        strcat(poutputString,pcString);
    
        
      
        

        
        //  if (feof(inputFile)){
        //      
        //      running = 0;
        //      
        //      printf("\n%s",poutputString);
        //      
        //      break ;
        //      
        //  }
        
        if ( running == 1 ){
        
            printf("\n%s",poutputString);
            
        }
        
        address = address + 8;
        
    }
        
        

        
    
    
    
    
    
    
    
    fclose(inputFile);

    printf("\nINFO: Done....\n\n\n");
    
   
    
    return(0);
}