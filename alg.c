#include "alg.h"
Tpos distance
(FILE* l_data,FILE* t_data){
  int i,j;
  float i_val[4];
  float t_val[4];
  Tpos res_eu;
  for(j=0;fscanf(t_data,"%f;%f;%f;%f;",&t_val[0],&t_val[1],&t_val[2],&t_val[3])!=EOF;j++){
    fseek(l_data,0,SEEK_SET);
    for(i=0;fscanf(l_data,"%f;%f;%f;%f;",&i_val[0],&i_val[1],&i_val[2],&i_val[3])!=EOF;i++){
      res_eu.tab[i][j]=sqrt((pow((i_val[0]-t_val[0]),2)+pow((i_val[1]-t_val[1]),2)+pow((i_val[2]-t_val[2]),2)+pow((i_val[3]-t_val[3]),2)));
      res_eu.pos[i][j]=i;
    }
  }
  return res_eu;
}

Tpos tri_tab(Tpos matrix){
  int i,j,scrambled=true;
  float tmp=0;
  for(i=0;i<10;i++){
    scrambled=true;
    while(scrambled){
      scrambled=false;
      for(j=0; j<139;j++){
	if(matrix.tab[j][i]>matrix.tab[j+1][i]){
	  tmp=matrix.tab[j+1][i];
	  matrix.tab[j+1][i]=matrix.tab[j][i];
	  matrix.tab[j][i]=tmp;
	  tmp=matrix.pos[j+1][i];
	  matrix.pos[j+1][i]=matrix.pos[j][i];
	  matrix.pos[j][i]=(int)tmp;
	  scrambled=true;
	}
      }
    }
  }
  return matrix;
}
	  
	    
int * remplirtab_class(FILE* file,int k){
  int * tab,i;
  tab=malloc(sizeof(*tab)*k);
  for(i=0;fscanf(file,"%d;",&tab[i])!=EOF;i++);
  return tab;
}

void affichetab(Tpos matrix){
  int i,j;
  for(i=0;i<10;i++){
    for(j=0;j<140;j++){
      printf("val=%f pos=%d\n",matrix.tab[j][i],matrix.pos[j][i]);
    }
  }
}

int max3(int a,int b,int c){
  if(a>b && a>c)return 0;
  if(b>a && b>c)return 1;
  if(c>a && c>b)return 2;
  if(a==b)return -12;
  if(a==c)return -13;
  if(b==c)return -23;
}

void k_ppv
(int k,Tpos matrix,int * l_class,int * t_class,FILE* results){
  Mini mini;
 int i,j,c0=0,c1=0,c2=0,reussite=0,rec;
Serial serie;
  mini.tmini=malloc(sizeof(*mini.tmini)*k*2);
  mini.ind=malloc(sizeof(*mini.ind)*3);
  fprintf(results,"Pour k=%d:\n",k);
  for(i=0;i<10;i++){
    serie.val=matrix.tab[0][i];
    rec=0;
    c0=0;
    c1=0;
    c2=0;
    mini.ind[0]=-1;
    mini.ind[1]=-1;
    mini.ind[2]=-1;
    serie.num=-1;
    fprintf(results,"Pour le %d data:\n",i);
    for(j=0;j<k;j++){
      mini.tmini[j]=matrix.pos[j][i];
      if(serie.val!=matrix.tab[j][i])
	serie.num=j;
      serie.val=matrix.tab[j][i];
      if(l_class[matrix.pos[j][i]]==0){
	c0++;
	if(mini.ind[0]<0)
	  mini.ind[0]=j;
      }
      if(l_class[matrix.pos[j][i]]==1){
	c1++;
	if(mini.ind[1]<0)
	  mini.ind[1]=j;
      }
      if(l_class[matrix.pos[j][i]]==2){
	c2++;
	if(mini.ind[2]<0)
	  mini.ind[2]=j;
      }
    }
  rewind:
    if((max3(c0,c1,c2)>=0) && (matrix.tab[k-2][i]!=matrix.tab[k-1][i] || rec==1)){
      fprintf(results,"\nPour le data num %d sa classe est %d\n",i,t_class[i]);
      fprintf(results,"\nLa classe trouvée pour k=%d est %d\n",k,max3(c0,c1,c2));
      if(max3(c0,c1,c2)==t_class[i])
	reussite++;
    }
   
    if((max3(c0,c1,c2)<0) && (matrix.tab[k-2][i]!=matrix.tab[k-1][i]|| rec==1)){
    
      if(max3(c0,c1,c2)==-12){
	if(mini.ind[0]<mini.ind[1]){
	  fprintf(results,"\nPour le data num %d sa classe est %d\n",i,t_class[i]);
	  fprintf(results,"\nLa classe trouvée pour k=%d est %d\n",k,l_class[mini.ind[0]]);
	  if(l_class[mini.ind[0]]==t_class[i])
	    reussite++;
	}
	else{
	  fprintf(results,"\nPour le data num %d sa classe est %d\n",i,t_class[i]);
	  fprintf(results,"\nLa classe trouvée pour k=%d est %d\n",k,l_class[mini.ind[1]]);
	  if(l_class[mini.ind[1]]==t_class[i])
	    reussite++;
	}
      }
     
      if(max3(c0,c1,c2)==-13){

	if(mini.ind[0]<mini.ind[2]){
	  fprintf(results,"\nPour le data num %d sa classe est %d\n",i,t_class[i]);
	  fprintf(results,"\nLa classe trouvée pour k=%d est %d\n",k,l_class[mini.ind[0]]);
	  if(l_class[mini.ind[0]]==t_class[i])
	    reussite++;
	}
	else{
	  fprintf(results,"\nPour le data num %d sa classe est %d\n",i,t_class[i]);
	  fprintf(results,"\nLa classe trouvée pour k=%d est %d\n",k,l_class[mini.ind[2]]);
	  if(l_class[mini.ind[2]]==t_class[i])
	    reussite++;
	}
      }
      if(max3(c0,c1,c2)==-23){
	
	if(mini.ind[1]<mini.ind[2]){
	  fprintf(results,"\nPour le data num %d sa classe est %d\n",i,t_class[i]);
	  fprintf(results,"\nLa classe trouvée pour k=%d est %d\n",k,l_class[mini.ind[1]]);
	  if(l_class[mini.ind[1]]==t_class[i])
	    reussite++;
	}
	else{
	  fprintf(results,"\nPour le data num %d sa classe est %d\n",i,t_class[i]);
	  fprintf(results,"\nLa classe trouvée pour k=%d est %d\n",k,l_class[mini.ind[2]]);
	  if(l_class[mini.ind[2]]==t_class[i])
	    reussite++;
	}
      }
    }
    if(matrix.tab[k-1][i]==matrix.tab[k-2][i] && rec==0){
      int c0_aux,c1_aux,c2_aux,w;
      c0_aux=0;
      c1_aux=0;
      c2_aux=0;
      w=serie.num;
      rec=1;
      do
  	{
  	if(l_class[matrix.pos[j][i]]==0)
  	  c0_aux++;
  	if(l_class[matrix.pos[j][i]]==1)
  	  c1_aux++;
  	if(l_class[matrix.pos[j][i]]==2)
  	  c2_aux++;
  	w++;
  	}while(matrix.tab[w][i]==matrix.tab[w-1][i]);
      if(max3(c0_aux,c1_aux,c2_aux)==0){
  	c0++;
  	goto rewind;
      }
      if(max3(c0_aux,c1_aux,c2_aux)==1){
  	c1++;
  	goto rewind;
      }
      if(max3(c0_aux,c1_aux,c2_aux)==2){
  	c2++;
  	goto rewind;
      }
    }
  }
  reussite*=10;
  fprintf(results,"Le pourcentage de réussite est de %d%%\n",reussite);
}
    
int main(int argc,char* argv[]){
  Tpos val;
  FILE* i_l_d=fopen("iris_learn_data","r");
  FILE* i_t_d=fopen("iris_test_data","r");
  FILE* i_l_l=fopen("iris_learn_label","r");
  FILE* i_t_l=fopen("iris_test_label","r");
  FILE* results=fopen("results.txt","w+");
  if((i_l_d==NULL) || (i_l_l==NULL) || (i_t_d==NULL) || (i_t_l==NULL) || (results==NULL)){
    printf("Il vous manque un ou plusieurs fichier(s) dans votre dossier pour compiler\n");
    exit(0);
  }
  int * l_class=NULL; //140
  int * t_class=NULL; // 10
  l_class=remplirtab_class(i_l_l,140);
  fclose(i_l_l);
  t_class=remplirtab_class(i_t_l,10);
  fclose(i_t_l);
  val=distance(i_l_d,i_t_d);
  fclose(i_l_d);
  fclose(i_t_d);
  val=tri_tab(val);
  //affichetab(val);
  k_ppv(2,val,l_class,t_class,results);
  k_ppv(3,val,l_class,t_class,results);
  k_ppv(4,val,l_class,t_class,results);
  k_ppv(5,val,l_class,t_class,results);
  k_ppv(6,val,l_class,t_class,results);
  k_ppv(7,val,l_class,t_class,results);
  k_ppv(8,val,l_class,t_class,results);
  k_ppv(9,val,l_class,t_class,results);
  k_ppv(10,val,l_class,t_class,results);
  fclose(results);
}
  
