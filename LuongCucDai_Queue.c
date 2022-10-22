#include<stdio.h>
#define maxverties 50
typedef struct{
	int n,m;
	int c[maxverties][maxverties];//Kha nang lon nhat co the di qua cung
	int f[maxverties][maxverties];//Luong co the qua cung 0 <= f <= c
}graph;//Do thi co huong
//1.Khoi tao do thi
void createGraph(graph *G){
	int i,j;
	for(i=1;i<=G->n;i++){
		for(j=1;j<=G->n;j++){
			G->c[i][j]= -1;
			G->f[i][j]=0;
		}
	}
}
//2.Them cung
void addEdges(graph *G,int x,int y,int w){
	G->c[x][y]=w;
}
//3.In ma tran
void printGraph(graph G){
	int i,j;
	for(i=1;i<=G.n;i++){
	printf("\n%d:",i);
		for(j=1;j<=G.n;j++){
			printf("%3d",G.c[i][j]);
		}
	}
}
	//Danh sach
	typedef struct{
		int size,DS[50];
	}list;
	void makeNullList(list *L){
		L->size=0;
	}
	int emptyList(list l){
		return l.size==0;
	}
	void insertList(list *l,int x){
		l->DS[l->size]=x;
		l->size++;
	}
	int elementList(list l,int p){
		return l.DS[p-1];
	}
	/*-----Hang doi-----*/
	typedef struct{
		int front,rear,dataQ[50];
	}Queue;
	//1.Hang doi rong
	void makeNullQueue(Queue *Q){
		Q->front = 0;
		Q->rear = -1;
	}
	//2.Kiem tra hang doi co rong khong
	int emptyQueue(Queue *Q){
		return Q->front > Q->rear;
	}	
	//3.Day dinh X bat ky vao cuoi hang doi
	void pushQueue(Queue *Q,int x){
		Q->rear++;
		Q->dataQ[Q->rear]=x;
	
	}
	//4.Xoa dinh dau hang doi
	void deleteQueue(Queue *Q){
		Q->front++;
	}
	//5. tra ve gia tri dau hang doi
	int frontQueue(Queue *Q){
		return Q->dataQ[Q->front];
	}
//3.Kiem tra co phai Anh cua X khong
int kiemTraAnh(graph *G,int x,int v){
	if(G->c[x][v] != -1){
		return 1;
	}
	return 0;
}	
//4.Kiem tra co phai Tao Anh cua X khong
int kiemTraTaoAnh(graph *G,int x,int v){
	if(G->c[v][x] != -1){
		return 1;
	}
	return 0;
}
//5.danh sah Anh cua dinh x
list DSAnh(graph *G,int x){
	int i;
	list L;
	makeNullList(&L);
	for(i=1;i<=G->n;i++){
		if(kiemTraAnh(G, x,i) == 1){
			insertList(&L,i);
		}
	}
	return L;
}
//6.danh sah Tao Anh cua dinh x
list DSTaoAnh(graph *G,int x){
	int i;
	list L;
	makeNullList(&L);
	for(i=1;i<=G->n;i++){
		if(kiemTraTaoAnh(G,x,i) == 1){
			insertList(&L,i);
		}
	}
	return L;
}
//Cau truc bo sung
typedef struct{
	int mark,	//De kiem tra xem nhan cua dinh X da xet hay chua
		sigma,	//luong tang luong
		p;		//Cha cua dinh X bat ky nao do
}Label;
Label label[50];	//Nhan cua cac dinh
//Tra ve min
int Min(int a,int b){
	return (a<b)? a:b;
}
//tim luong cuc dai
void giaiThuat_FordFulkerson(graph* G, int s, int t) {
	int i,j,tong=0;
	Queue Q;
	//Lap den khi khong con duong tang luong
	do{
	//1.Khoi dau
		for(i=1;i<=G->n;i++){
			label[i].mark=0;
		}
		//1.1 Bat dau tu nguon cung cap (dinh dau S)
		label[s].mark=1;
		label[s].p=s;
		label[s].sigma=9999;
		//1.2 la hang doi rong va sau do day S vao hang doi
		makeNullQueue(&Q);
		pushQueue(&Q,s);
	//2. Tim duong tang luong
		int conDuongTangLuong=0;//Kiem tra xem co duong tang luong nao khong
		while(!emptyQueue(&Q)){
			int U = frontQueue(&Q);
			deleteQueue(&Q);
			list Anh= DSAnh(G,U);//Danh sach Anh V de tim thay co T khong
			for(j=1;j<=Anh.size;j++){
				int V = elementList(Anh,j);
				//2.1 Dieu kien neu dinh ke V chua co nhan va duong tu U -> V khong rong va C(u,v) > F(u,v) 
				if(label[V].mark == 0 && G->c[U][V]!= -1 && G->c[U][V] > G->f[U][V]){
					label[V].mark=1;
					label[V].p=U;
					label[V].sigma=Min(label[U].sigma, G->c[U][V] - G->f[U][V]);
					pushQueue(&Q,V);//Day vao hang doi
				}
			}
			//2.2 Tim thay duong tang luong => Thoat vong lap
			if(label[t].mark != 0){
				conDuongTangLuong=1;
				break;
			}
		}
	//3. tang luong
		//3.1 Tim thay T(dinh cuoi hoac dau nhan) => tang luong
		if(conDuongTangLuong == 1){
			int sigma = label[t].sigma;
			tong+=sigma;
			int x = t;
			while(x!=s){//Neu root cua X khac S thi tiep tuc tim
				int y = label[x].p;
				if(label[x].mark == 1){
					G->f[y][x] += sigma;
				}
				x = y;
			}
		}
		//3.2 Khong tim thay T => thoat khoi vong lap => Dung lai
		else break;
	}while(1);
	printf("\nLuong cuc dai la: %d",tong);
}
int main(){
	FILE *f = fopen("DataGraphWeight.txt","r");
	if(f!=NULL){
		graph G;
		fscanf(f,"%d %d",&G.n,&G.m);
		createGraph(&G);
		int i,j,u,v,w;
		for(i=1;i<=G.m;i++){
			fscanf(f,"%d%d%d",&u,&v,&w);
			addEdges(&G,u,v,w);
		}
		printGraph(G);
//-------------------------------------------------------------------------
		giaiThuat_FordFulkerson(&G,1,G.n);
	}
	else{
		printf("Loi mo tep");
	}
}
