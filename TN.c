#include<stdio.h>
#define maxverties 50
typedef struct{
	int n,m;
	int c[maxverties][maxverties];//Kha nang lon nhat ci the di qua cung
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
void GT (graph* G, int s, int t) {
	int u,v,sum_flow = 0;
	Queue Q;
	do {
		for (u = 1; u <= G->n; u++){
			label[u].mark = 0;	
		}
		label[s].mark = 1;
		label[s].p = s;
		label[s].sigma = 99999;
		makeNullQueue(&Q);
		pushQueue(&Q,s);
		int found = 0;
		while(!emptyQueue(&Q)) {
			int u = frontQueue (&Q);
			deleteQueue(&Q);
			for (v = 1; v <= G->n ; v++) {
				if (label[v].mark == 0 && G->c[u][v] != -1 && G->f[u][v] < G->c[u][v] ) {
					label[v].mark = 1;
					label[v].p = u;
					label[v].sigma = Min(label[u].sigma, G->c[u][v] - G->f[u][v]);
					pushQueue(&Q,v);
				}
				if (label[v].mark == 0 && G->c[v][u] != -1 && G->f[v][u] > 0) {
					label[v].mark = -1;
					label[v].p= u;
					label[v].sigma = Min(label[u].sigma, G->f[u][v]);
					pushQueue(&Q,v);
				}
			}
			if(label[t].mark != 0) {
				found = 1;
				break;
			}
		}
		if (found == 1) {
			int x = t;
			int sigma = label[t].sigma;
			sum_flow += sigma;
			while(x!=s) {
				int u = label[x].p;
				if (label[x].mark>0){
					G->f[u][x] += sigma;
				}
				else{
					G->f[x][u] -= sigma;
				}
				x = u;
			}
		}else break;
	}while(1);
	printf("\n%d",sum_flow);
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
		printf("\nIn cac anh:\n");
		for(i=1;i<=G.n;i++){
			list Anh = DSAnh(&G,i);
			printf("\n%d:",i);
			for(j=1;j<=Anh.size;j++){
				printf("%2d",elementList(Anh,j));
			}
		}
		printf("\nIn cac tao anh:\n");
		for(i=1;i<=G.n;i++){
			list TaoAnh = DSTaoAnh(&G,i);
			printf("\n%d:",i);
			for(j=1;j<=TaoAnh.size;j++){
				printf("%2d",elementList(TaoAnh,j));
			}
		}
//-------------------------------------------------------------------------
		
		GT(&G,1,G.n);
	}
	else{
		printf("Loi mo tep");
	}
}
