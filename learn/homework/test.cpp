#include<iostream>
#include<string>

using namespace std;
const int M = 1e3;


struct HNode            //静态三叉链表
{
	int weight;         //结点权值
	int parent;         //双亲数组下标
	int LChild;         //左孩子数组下标
	int RChild;         //右孩子数组下标
};

struct HCode            //编码表中的元素
{
	char data;          //结点表示的字符
	string code;        //结点编码
};

class Huffman
{
private:
	HNode* HTree;                                  //哈夫曼树（数组）
	HCode* HCodeTable;                             //存储编码表（数组）
	int N;                                         //叶子结点数
	void code(int i, string newcode);              //递归函数，对第i个结点编码
public:
	void CreateHTree(int a[], int n, char name[]); //创建哈夫曼树
	void CreateCodeTable();                        //创建编码表
	void Encode(char* s, char* d);                 //编码
	void Decode(char* s, char* d);                 //解码
	void select(int &x, int &y, int a, int b);     //挑出最小的两个数       
	char name[25];
	~Huffman() {
		delete[] HTree;
		HTree = nullptr;
		delete[] HCodeTable;
		HCodeTable = nullptr;
	}
};

int main()
{
	Huffman m_tree;
	char str[] = "ABCDBBDC";
	int a[] = { 1,3,2,2 };
	char name[] = { 'A','B','C','D' };
	m_tree.CreateHTree(a, 4, name);
	m_tree.CreateCodeTable();
	char d[M];
	m_tree.Encode(str, d);
	cout << "编码结果为：" << endl;
	for (int i = 3; i >= 0; i--)
	{
		cout << d[i];
	}

}



void Huffman::CreateHTree(int a[], int n, char name[])//a[]存储每种字符的权值，n为字符的数量，name为字符的内容
{
	N = n;
	HCodeTable = new HCode[N];
	HTree = new HNode[2 * N - 1];
	for (int i = 0; i < N; i++)           //初始化哈夫曼树
	{
		HTree[i].weight = a[i];
		HTree[i].LChild = HTree[i].RChild = HTree[i].parent = -1;
		HCodeTable[i].data = name[i];
	}
	int x, y;
	for (int i = N; i < 2 * N - 1; i++)
	{
		select(x,y,0,i);
		HTree[x].parent = HTree[y].parent = i;
		HTree[i].weight = HTree[x].weight + HTree[y].weight;
		HTree[i].LChild = x;
		HTree[i].RChild = y;
		HTree[i].parent = -1; 
	}
}

void Huffman::select(int &x,int &y,int a,int b)
{
	int m1 = M, m2 = M;
	for (int i = a; i < b; i++)
	{
		if (HTree[i].parent==-1)
		{
			m1 = min(HTree[i].weight, m1);
		}
	}
	for (int i = a; i < b; i++)
	{
		if (HTree[i].parent == -1 && HTree[i].weight != m2)
		{
			m2 = min(HTree[i].weight, m2);
		}
	}
	for (int i = a; i < b; i++)
	{
		if (HTree[i].weight == m1)
			x = i;
		if (HTree[i].weight == m2)
			y = i;
	}
}


void Huffman::code(int i, string newcode)               //递归函数，从第i个结点开始往下编码
{
	if (HTree[i].LChild == -1)                          //没有孩子，return
	{
		HCodeTable[i].code = newcode;
		return;
	}
	code(HTree[i].LChild, newcode + "0");               //左孩子编码为0
	code(HTree[i].RChild, newcode + "1");               //右孩子编码为1
}

void Huffman::CreateCodeTable()                        //从根结点开始生成编码表
{
	code(2 * N - 2, "");
}

void Huffman::Encode(char* s, char* d)                 //s为原字符串，d为编码串
{
	while (*s != '\0')
	{
		for (int i = 0; i < N; i++)
		{
			if (*s == HCodeTable[i].data)
			{
				*d = HCodeTable[i].code[0];
				cout << *d << endl;
				d++;
				int temp = HTree[i].parent;
				while (HTree[temp].parent != -1)
				{
					*d = HCodeTable[temp].code[0];
					cout << *d << endl;
					temp = HTree[temp].parent;
					d++;
				}
			}
		}
		s++;
	}
}


void Huffman::Decode(char* s, char* d)                  //s为编码串，d为解码后的字符串
{
	while (*s != '\0')                                  //遍历编码串
	{
		int parent = 2 * N - 2;                         //从根结点开始
		while (HTree[parent].LChild != -1)              //不是叶子结点
		{
			if (*s == '0')
				parent = HTree[parent].LChild;
			else
				parent = HTree[parent].RChild;
			s++;
		}
		*d = HCodeTable[parent].data;                   //解码
		d++;
	}
}