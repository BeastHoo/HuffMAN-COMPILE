#define N 20
#define M 2*N-1
typedef char* HuffmamCode[N + 1];
typedef struct
{
	double weight;
	int parent;
	int lside;
	int rside;
	int lchild;
	int rchild;
	char value;
}HTNode, HaffmanTree[M+1];
