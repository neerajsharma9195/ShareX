#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void tmkr(char file_name[50])
{int gbg;
    int c,size=0;
    int i=0;
    FILE *fp = fopen(file_name, "rb");
    FILE *fp2;
    char name[25];
   fp2 = fopen("output.sg", "w");
    fprintf(fp2,"%s",file_name);
    fprintf(fp2,"\n");
    while(1)
    {size=0;
        for( ;size!=175000 && (c=getc(fp))!=EOF;size++)
        {
            gbg=0;
        }
    i++;
    if(c==EOF)
        break;
        //fclose(fp2);
    }
    
  fprintf(fp2,"%d",i);
    fprintf(fp2,"\n");
int iter=1;
while(iter<i)
{printf("hell %d",i);
      fprintf(fp2,"175000");
    fprintf(fp2,"\n");
    iter++;
}
  fprintf(fp2,"%d",size);
    printf("s = %d\n", size);
    fclose(fp);
    fclose(fp2);
    
}

int main() {
    char file_name[] = "Portfiolio.mp4";
    tmkr(file_name);
}
