#include<stdio.h>
#include"C:\BasicProgramming\DanhSachList\CacPhepToanList.cpp"
#include"C:\BasicProgramming\LyThuyetDoThi/tvDoThiVoHuong.c"
#define maxlengthstack 50		//Do dai toi da cua ngan xep 
/*Danh sach luu tru dinh ke cua dinh x trong do thi*/
List listneighbour(Graph *G,int x){
	List L;
	Makenull_List(&L);
	int i;
	for(i=1;i<=G->n;i++){
		if(CheckAdjacent(G,x,i)==1){
			Insert_List(i,End_List(L),&L);
		}
	}
	return L;
}
void printlistneighbour(Graph *G){
	int i,j;
	printf("\nDanh sach cac dinh ke nhau\n");
	for(i=1;i<=G->n;i++){
		List L=listneighbour(G,i);
		printf("\n%d:",i);
		for(j=1;j<=L.Last;j++){
			printf(" %d",Retrieve(j,L));
		}
	}
}
/*---Tao mot cau truc ngan xep---*/
	typedef struct{
		int DataStack[maxlengthstack];
		int top;
	}NganXep;
	//tao ngan xep rong
	void makenullstack(NganXep *S){
		S->top=0;
	}
	//Kiem tra ngan xep rong
	int emptystack(NganXep S){
		return S.top==0;
	}
	//Them phan tu X vao dinh dau ngan xep
	void Push_stack(NganXep *S,int x){
		S->DataStack[S->top]=x;
		S->top++;
	}
	//xoa phan tu o dau ngan xep
	void Pop_stack(NganXep *S){
		S->top--;
	}
	//Lay phan tu dau o ngan xep
	int Top_stack(NganXep S){
		return S.DataStack[S.top-1];
	}
//Duyet theo chieu sau cua mot dinh bat ky
List DFS(Graph *G,int x,int parent[]){
	//Su dung danh sach de luu tru cac dinh da duoc duyet
	List l;
	Makenull_List(&l);
	printf("\nDuyet theo chieu sau(Deep first search).Su dung ngan xep:\n");
	int i,j,k=1,mark[maxverties];
	NganXep S;
	makenullstack(&S);
	//Khoi tao tat ca cac dinh chua duoc duyet 
	for(i=1;i<=G->n;i++){
		mark[i]=0;
	}
	Push_stack(&S,x);//Dua mot dinh bat ky vao trong ngan xep
	parent[x]=0;	//Vi co mot dinh duyet dau tien(Nut goc) nen ta gan dinh do co cha bang 0
	/*Vong lap chinh*/
	while(!emptystack(S)){
		int u=Top_stack(S);//Lay 1 dinh ra khoi ngan xep
		Pop_stack(&S);
		//Neu dinh nay da duoc duyet thi bao qua cac dong len cuoi
		if(mark[u]==1){
			continue;
		}
		//Neu chua duoc duyet thi danh dau da duyet 
		//printf(" %d.Duyet %d\n",k,u);
		Insert_List(u,End_List(l),&l);
		mark[u]=1;
		k++;
		//Tim cac dinh ke V cua U
		List L=listneighbour(G,u);
		for(j=1;j<=L.Last;j++){
			int v=Retrieve(j,L);
			if(mark[v]==0){
				Push_stack(&S,v);
				parent[v]=u;//Cap nhap lai cha cua cac dinh ke V la dinh U(cha cua V la U)
			}
		}
	}
	return l;// tra ve danh dach luu tru cac dinh da duoc duyet
}
int main(){
	int m,u,v;
	FILE *F;
	F=fopen("DataGraph.txt","r");
	if(F!=NULL){
		Graph G;
		fscanf(F,"%d%d",&G.n,&m);
		creategraph(&G);
		int i;
		for(i=1;i<=m;i++){
			fscanf(F,"%d%d",&u,&v);
			addedges(&G,u,v);
		}
		PrintGraph(&G);
		printlistneighbour(&G);
		int x;
		//Khai bao dinh cha luu tru cac dinh V
		int parent[50];
		for(i=1;i<=G.n;i++){
			parent[i]=-1;	//Ban dau chua co dinh nao co cha het
		}
		//printf("\nNhap vao mot dinh bat ky de duoc duyet: ");scanf("%d",&x);
	//Duyet them cac dinh nam ngoai do thi chinh,de dem so bo phan lien thong 
		int MARK[50],j;
		for(i=1;i<=G.n;i++){
			MARK[i]=0;	//Chua duoc duyet thi danh so 0
		}
		for(i=1;i<=G.n;i++){
			if(MARK[i]==0){
				List L=DFS(&G,i,parent);
				for(j=1;j<=L.Last;j++){
					printf("%d.Duyet: %d\n",j,Retrieve(j,L));
					MARK[Retrieve(j,L)]=1;
				}
			}
		}
		printf("\nIn ra cha cua tat ca cac dinh:\n");
		for(i=1;i<=G.n;i++){
			printf(" Parent %d: %d\n",i,parent[i]);
		}
	}else printf("Loi Mo Tep!!!");
	fclose(F);
}
