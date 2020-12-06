//Date: 2020.06.29
//@author He yuqian
//Version 2.0
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include"user.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)    //����vs��scanf��printf��������ȫ���ж�

void gotoxy(int x, int y);   //����޸ĺ���
void introduce();    //˵��
void crtHaffmanTree(HaffmanTree ht,double w[],int n,char *val);    //������������
void crtHaffmanCode(HaffmanTree ht, HuffmamCode hc, int n);    //���й���������
void load_file(HuffmamCode hc);    //�����ļ�����ѹ
void release_file(HuffmamCode hc);     //�����ļ�����ѹ




int main()
{
	//������������ʼ������
	int ins; char dir;
	HaffmanTree ht; int n = 27; HuffmamCode hc;
	double w[27] = {0,8.19,1.47,  3.83,  3.91 , 12.25 , 2.26 , 1.71, 
		 4.57,  7.10, 0.14 , 0.41 , 3.77 , 3.34 , 7.06 , 7.26 , 2.89 , 0.09 , 6.85 , 6.36 , 9.41 , 2.58 , 1.09 , 1.59, 0.21 , 1.58 , 0.08 };
	char val[27] = { '0','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

	//���ƿ���̨���
	SetConsoleTitleA("����������ѹ��");
	system("color 71");
	system("mode con cols=100 lines=30");
	

	//����������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | 112);
	gotoxy(39, 9);
	printf("****************************");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|112);
	gotoxy(48, 10);
	printf("��ӭʹ��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | 112);
	gotoxy(39, 11);
	printf("****************************");
	gotoxy(39, 12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | 112);
	printf("˵����");
	gotoxy(39, 13);
	printf("1���ó����������Windows����ϵͳ");
	gotoxy(39, 14);
	printf("2���ó�����ɼ��غʹ˳���λ��ͬһ�ļ����µ�.txt�ļ�\n");
	gotoxy(48, 15);
	system("pause");
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 112);
	introduce();
	

	//printf("%s", s); ������
	crtHaffmanTree(ht, w, n, val);
	crtHaffmanCode(ht, hc, n);


Loop:
	printf("�����룺");
      //goto������ʶ
	scanf("%d", &ins);
	switch (ins)
	{
	case 1:
		load_file(hc);
		break;
	case 2:
		release_file(hc);
		break;
	default:
		printf("�޸ù��ܣ����������룺\n");
		//fflush(stdin);      //������뻺����
		goto Loop;
		break;
	}


	printf("---��Space������������˳�---\n");
	dir = getch();    //�������Ե����뺯��
	switch (dir)
	{
	case 32:
		system("cls");
		introduce();
		goto Loop;
		
	default:
		break;
	}
	return 0;
}



//������
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


//����˵��
void introduce()
{
	printf("���ܣ�\n");
	printf("1���������\n");
	printf("2���������\n");
	printf("�����������Ӧ����Ž���ѡ��\n");
}


//������������
void crtHaffmanTree(HaffmanTree ht, double w[], int n,char *val)
{
	int i, j, x1, x2;     double m1, m2; int m = 2 * n - 1;
	//i��j�� ѭ��������m1��m2���������������ͬ������������СȨֵ����Ȩֵ��
	// x1��x2���������������ͬ������������СȨֵ����������е���š�
	for ( i = 1; i <= n; i++)
	{
		ht[i].weight = w[i];
		ht[i].parent = 0;
		ht[i].lchild = 0;
		ht[i].rchild = 0;
		ht[i].value = val[i];
		//printf("%c ", val[i]);
	}
	
	
	for ( i = n + 1; i <= m; i++)
	{
		ht[i].weight = 0;
		ht[i].parent = 0;
		ht[i].lside = ht[i].rside = 2;
		ht[i].lchild = 0;
		ht[i].rchild = 0;
		ht[i].value = '0';
	}
	for (i = 1; i <n; i++)
	{
		m1 = m2 = 10000; x1 = x2 = 0;

		for (j = 1; j < n + i; j++)
		{
			if (ht[j].lchild < m1 && ht[j].parent == 0)
			{
				m2 = m1;
				x2 = x1;
				m1 = ht[i].weight;
				x1 = j;
			}
			else if (ht[j].lchild < m2 && ht[j].parent == 0)
			{
				m2 = ht[j].weight;
				x2 = j;
			}
		}

		//��ʼ�����ҵ��������ڵ�ĸ��ڵ���Ϣ
		ht[x1].parent = n + i;
		ht[x2].parent = n + i;
		ht[n + i].weight = ht[x1].weight + ht[x1].weight;
		ht[n + i].lchild = x1;
		ht[n + i].rchild = x2;
		/*for (int s = 1; s <= n; s++)
		{
			if (ht[n + i].weight == w[s])
			{
				ht[n + i].value = val[s];
			}
		}*/
		//printf("x1.weight and x2.weight in round%d:%3.2lf,%3.2lf,%c,%c\n", i + 1, ht[x1].weight, ht[x2].weight, ht[x1].value,ht[x2].value);  �����ô���
		//printf("%c", val[i]);
	}
	
}




void crtHaffmanCode(HaffmanTree ht, HuffmamCode hc, int n)//����������,hcΪ����
{
	int i;
	char* cd; int start,c,p;
	cd = (char*)malloc(n* sizeof(char));

	cd[n - 1] = '\0';
	for ( i = 1; i <= n; i++)
	{
		start = n - 1;
		c = i; p = ht[i].parent;
		while (p != 0)
		{
			--start;
			if (ht[p].lchild == c)
				cd[start] = '0';
			else
				cd[start] = '1';
			c = p; p = ht[p].parent;
		}
		hc[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(hc[i], &cd[start]);
		//printf("%c%s ",ht[i].value, hc[i]);
	}
	//free(cd);
	//ʹ��free����ȥ�ͷ�cdʱ������ڴ���� 
	
	
}



//�ļ���������ѹ
void load_file(HuffmamCode hc)
{
	FILE* fp, * fn; char fname[20]; char data[500]; int calc = 0;int i,j;
	char ss[27] = { '0','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	//ͨ����������˺������ַ�������ִ������룬ԭ��δ֪�������ڴ˺��������ַ���
	printf("�������ļ���(.txt):");
	scanf("%s", fname);
	fp = fopen(fname, "r"); fn = fopen("trans.txt", "w");
	if (fp == NULL||fn==NULL)
	{
		perror("�ļ���ȡ����!!");
		return;
	}
	 fgets(data,500,fp);
	// printf("%s", ss);
	 for ( i = 0; data[i] != '\0'; i++)
	 {
		 for ( j = 1; j <= 27; j++)
		 {
			 if (data[i] == ss[j]||data[i]-32==ss[j])
			 {
				 fprintf(fn, "%s ",hc[j]);
				 calc++;
				 break;
				 //printf("into here��");
			 }
			 else
			 {
				//printf("%c ", ss[j]);
				 continue;
			 }
		 }
	 }
	 printf("������ɣ�������%d���ַ����������ļ�Ϊtrans.txt\n",calc);
	 fclose(fp); fclose(fn);
}


//�ļ���������ѹ
void release_file(HuffmamCode hc)
{
	char ss[27] = { '0','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	//ͬ��һ������
	FILE* fp, * fn; char fname[20]; int calc = 1; int flag; int m;int i,j;
	char temp[100][20];
	printf("�������ļ���(.txt):");
	scanf("%s", fname);
	fp = fopen(fname,"r");
	fn = fopen("release.txt","w");
	if (fp == NULL || fn == NULL)
	{
		perror("�ļ���ȡ����!!");
		return;
	}
	while (1)
	{
		flag = fscanf(fp, "%s ",temp[calc] );
		if (flag == EOF)
			break;
		calc++;

	}
	printf("������%d������\n", calc - 1);
	m = calc; calc = 0;
	
	for (i=1;i<m;i++)
	{
		for ( j = 1; j <= 27; j++)
		{
			if (strcmp(hc[j], temp[i]) == 0)
			{
				fprintf(fn, "%c", ss[j]);
				calc++;
				//printf("into here");
				break;
			}
		}
	}
	printf("������ɣ������%d�����ݣ��������ļ�Ϊrelease.txt\n", calc);
	fclose(fp); fclose(fn);
}
