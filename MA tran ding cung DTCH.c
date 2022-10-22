#include<stdio.h>
#include"C:\BasicProgramming\LyThuyetDoThi\tvMaTranDinhCungDTCH.c"
int main(){
	FILE *f=fopen("DataGraph.txt","r");
	if(f!=NULL){
		int i,j,u,v;
		Graph G;
		fscanf(f,"%d%d",&G.n,&G.m);
		Creategraph(&G);
		for(i=1;i<=G.m;i++){
			fscanf(f,"%d%d",&u,&v);
			 Addedges(&G,i,u,v);
		}
		Printgraph(G);
		printf("\nSo anh cua tat ca cac dinh trong do thi:\n");
		for(i=1;i<=G.n;i++){
			printf("[%d] = %d\n",i,countpictures(&G,i));
		}
		printf("Danh sach anh cua tat ca cac dinh trong do thi:\n");
		for(i=1;i<=G.n;i++){
			List L=danhsachAnh(&G,i);
			printf("\n[%d] = ",i);
			for(j=1;j<=L.size;j++){
				printf(" %d",element_list(&L,j));
			}
		}
		printf("\nSo tao anh cua tat ca cac dinh trong do thi:\n");
		for(i=1;i<=G.n;i++){
			printf("[%d] = %d\n",i,countcreatepictures(&G,i));
		}
		printf("Danh sach tao anh cua tat ca cac dinh trong do thi:\n");
		for(i=1;i<=G.n;i++){
			List L=danhsachTaoAnh(&G,i);
			printf("\n[%d] = ",i);
			for(j=1;j<=L.size;j++){
				printf(" %d",element_list(&L,j));
			}
		}
	}
}
