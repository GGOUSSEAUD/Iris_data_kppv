#include "alg.h"

int main(int argc,char* argv[]){
  int val[3];
  int val2[3];
  FILE* poo=fopen("poo.murshee","r");
  for(;(fscanf(poo,"%d;%d;%d",&val[0],&val[1],&val[2])) && (fscanf(poo,"%d;%d;%d",&val2[0],&val2[1],&val2[2]))!=EOF;){
    printf("%d;%d;%d\n",val[0],val[1],val[2]);
    printf("%d;%d;%d\n",val2[0],val2[1],val2[2]);
    }
    return 0;
}
