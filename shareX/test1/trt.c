// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>

void trt(char file_name[50], char location[100]) {
  FILE *fp = fopen(file_name, "rb");
  FILE *fp2;
  char name[25], final[150];
  int c, size = 0, i = 0;
  static char againTemp[100];
  strcpy(againTemp, location);
  
  while(1) {
    size = 0;
    sprintf(name,"%d",i); 
    strcpy(location, againTemp);

    strcpy(final, strcat(location, name));
        				
    fp2 = fopen(final, "wb");
    for(; size != 175000  && (c = getc(fp)) != EOF; size++) {
         fputc(c, fp2);
    }   
    
    if(c==EOF)
      break;
    fclose(fp2); 
    i++;
  }
  printf("s = %d\n", size);
  fclose(fp);
  fclose(fp2);

}

