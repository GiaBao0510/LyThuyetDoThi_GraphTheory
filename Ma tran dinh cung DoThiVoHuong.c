#include<stdio.h>
#include"C:\BasicProgramming\LyThuyetDoThi\tvMaTranDinhCungDTVH.c"
#include"C:\BasicProgramming\DanhSachList\CacPhepToanList.cpp"
//Dem tat ca cac bac trong do thi vo huong
void verticesdegree(Graph G){
	int i,min,max,a=1,b=1;
	min=max=Degreevertices(G,1);			// Gan Min,Max bang so bac dinh dau tien 
	printf("\nBac cua tat ca cac dinh trong do thi.\n");
	for(i=1;i<=G.n;i++){
		if(max<Degreevertices(G,i)){		//So sanh gia tri tim bac lon nhat trong dinh
			max=Degreevertices(G,i);
			a=i;
		}
		if(min>Degreevertices(G,i)){		//So sanh gia tri tim bac nho nhat trong dinh
			min=Degreevertices(G,i);
			b=i;
		}
		printf("Degree vertices %d: %d\n",i,Degreevertices(G,i));
	}
	printf("\nDinh co bac lon nhat %d - %d\n",a,max);
	printf("\nDinh co bac nho nhat %d - %d\n",b,min);
}
//Danh sach luu truu cac dinh lien ke cua dinh X
List neighbour(Graph *G,int x){
	List L;
	Makenull_List(&L);
	int i,j;
	for(i=1;i<=G->n;i++){		//Bat dau cho chay tu dinh dau, de so sanh voi dinh X
		if(i==x){				//Neu X va I trung nhau (X == I), thi bo qua 
			continue;
		}
		else 
			for(j=1;j<=G->m;j++){					//Chay xet kiem tra tung cung
				if(G->A[x][j]==1 &&G->A[i][j]==1){	//Ca hai dinh co chung mot cung thi them vao danh sach
					Insert_List(i,End_List(L),&L);
				}
			}
	}
	return L;
}
void Printneighbour(Graph G){
	int i,j;
	printf("\nTat ca cac dinh lien ke\n");
	for(i=1;i<=G.n;i++){		//Chay het tat ca cac dinh trong do thi
		printf("\nNeighbour %d: ",i);
		List L=neighbour(&G,i);
		for(j=1;j<=L.Last;j++){
			printf("%d ",Retrieve(j,L));
		}
	}
}
int main(){
	Graph G;
	int m,n;
	freopen("DataGraph.txt","r",stdin);
	scanf("%d%d",&G.n,&G.m);
	Creategraph(&G);
	int i,a,b;
		//Doc dun lieu tu file
	for(i=1;i<=G.m;i++){
		scanf("%d%d",&a,&b);
		Addedges(&G,i,a,b);
	}
	Printgraph(G);
	verticesdegree(G);
	Printneighbour(G);
}
