// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>

void combine_file(char file_name[100], int n, char location[100]) {
 
  FILE *fp = fopen(file_name, "wb");
  FILE *fp2;
  char name[26], final[150];
  static char againTemp[100];
  strcpy(againTemp, location);
  int c, size = 0, i = 0;
  
  for(i = 0; i < n; i++) {
    sprintf(name, "%d", i);
    strcpy(location, againTemp);
    strcpy(final, strcat(location, name));
    					FILE *fp3 = fopen("logs2.txt", "a");
					if(!fp) {
						fprintf(fp3, "%s\n", file_name);
					}
					fclose(fp3);
    fp2 = fopen(final, "rb");
    while((c = getc(fp2)) != EOF) {
      fputc(c, fp);
      size++;  
    }
   
    fclose(fp2);
  }
  printf("s = %d\n", size);
  fclose(fp);
 
}


