#include "DataBase.h"

/*
Create By ZCR
2016-12-01
*/

/*
�ڵ��ú���ʱ,��Ҫ����һ��*list,
����һ������ѧ���ڱ��е�ʵ�ʴ��˳����±������
�������������һ�����±�,��Щ���ݵ�˳�򲻻�ı����,���������ϵ����ʾ�ͱ�������
*/
#define WRONGEXIT(x) {printf("%s,���򽫻��˳�",x);system("pause");exit(1);}
#define ADDITIONAL 10		//һ������10��ѧ��

/*
�ڴ浵�ļ���,
��һ�е�һ�����ִ���ѧ��������n,�ڶ������ִ���ÿ���˵����Եĸ���unit
�ڶ�����unit������,ÿ��������2���������,�ֱ���һ���ַ���(��ͷ)��һ������(���������Ԫ�����Ƴ���)
��������n������,һֱ���ļ���β,ÿ�����ݷֱ���unit������,���ǵ�ֵ���Ǳ�ͷ�����ֵ
ע���ͷ�ĳ�������Ϊ31��Ӣ���ַ�
*/

/*
ָ���ַ��������ָ��
*/
char ***StudentList;

char **ListHead;			//��ͷ���Ƶ��ַ�������
int *ListLHeadlimits;		//��Ԫ�ַ�����(����)
int HeadCount;
int StudentCount;
int StudentCapacity;		//���ڼ�¼StudentList������(���Ч��,�����η���)

/*
���ļ���ȡ����
File Ҫ��ȡ���ļ�·��
*/
void ReadIni(char *File)
{
	FILE *f;
	int n, unit;
	int a, b;
	char temp;
	f = fopen(File, "r");
	if (!f)
		WRONGEXIT("���ļ�ʧ��")
		fscanf(f, "%d%d", &n, &unit);	//���ļ��ж�ȡ����ֵ
	HeadCount = unit;
	StudentCount = n;
	StudentCapacity = n;
	//��ʼ����ͷ
	ListHead = (char**)malloc(sizeof(char*) * unit);
	ListLHeadlimits = (int*)malloc(sizeof(int)*unit);
	if (!(ListHead&&ListLHeadlimits))
		WRONGEXIT("�ڴ治��")

		for (a = 0; a < unit; a++) {
			*(ListHead + a) = (char*)malloc(sizeof(char) * 32);
			if (!(*(ListHead + a)))
				WRONGEXIT("�ڴ治��")
				fscanf(f, "%s%c%d", *(ListHead + a), &temp, ListLHeadlimits + a);
		}
	//��ʼ��ʼ������ȡ����
	StudentList = (char***)malloc(sizeof(char**)*n);
	if (!StudentList)
		WRONGEXIT("�ڴ治��")
		for (a = 0; a < n; a++) {
			StudentList[a] = (char**)malloc(sizeof(char*)*unit);
			if (!StudentList[a])
				WRONGEXIT("�ڴ治��")
				for (b = 0; b < unit; b++) {
					StudentList[a][b] = (char*)malloc(sizeof(char)*(ListLHeadlimits[b] + 1));
					if (!StudentList[a][b])
						WRONGEXIT("�ڴ治��")
						fscanf(f, "%s", StudentList[a][b]);
				}
		}
	fclose(f);
}

/*
д�����ݵ��ļ�
FileҪ����д����ļ�·��,
list ��ǰ���ڴ����ѧ�����±꼯��
n list��Ԫ�صĸ���
*/
void WriteIni(char* File,int *list, int n)
{
	FILE *f;
	int a, b;
	f = fopen(File, "w+");
	if (!f)
		WRONGEXIT("���ļ�ʧ��")
		fprintf(f, "%d %d\n", n, HeadCount);
	for (a = 0; a < HeadCount; a++) {
		fprintf(f, "%s %d ", ListHead[a], ListLHeadlimits[a]);
	}
	fprintf(f, "\n");
	for (a = 0; a < n; a++) {
		for (b = 0; b < HeadCount; b++)
			fprintf(f, "%s ", StudentList[list[a]][b]);
		fprintf(f, "\n");
	}
	fclose(f);
	return;
}

/*
����һ������
title�����еı�ͷ
UnitLimits �������ݳ�������
Default ���еĳ�ʼֵ,����Ϊ�ǿհ��ַ�
*/
void NewUnit(char *title, int UnitLimits, char Default)
{
	int newUnitCount = HeadCount + 1;
	char **temp;
	int *temp2;
	int a, b;

	//������ͷ
	temp = (char**)malloc(sizeof(char*)*newUnitCount);
	for (a = 0; a < HeadCount; a++)
		temp[a] = ListHead[a];
	temp[a] = (char*)malloc(sizeof(char) * 32);
	strcpy(temp[a], title);
	free(ListHead);
	ListHead = temp;

	temp2 = (int*)malloc(sizeof(int)*newUnitCount);
	for (a = 0; a < HeadCount; a++)
		temp2[a] = ListLHeadlimits[a];
	temp2[a] = UnitLimits;
	free(ListLHeadlimits);
	ListLHeadlimits = temp2;

	//Ϊÿ��ѧ������Ӧ���Է����ڴ�
	for (a = 0; a < StudentCount; a++) {
		temp = (char**)malloc(sizeof(char*)*newUnitCount);
		for (b = 0; b < HeadCount; b++)
			temp[b] = StudentList[a][b];
		temp[b] = (char*)calloc(sizeof(char)*(UnitLimits + 1), sizeof(char)*(UnitLimits + 1));
		temp[b][0] = Default;
		temp[b][1] = 0;
		free(StudentList[a]);
		StudentList[a] = temp;
	}
	HeadCount++;
	return;
}

/*
����һ���µ�ѧ��
list ��ǰ���ڴ����ѧ�����±꼯��
n list��Ԫ�صĸ���
*/
int NewStudent(int *list, int *n)
{
	char ***temp;
	int a;
	if (StudentCapacity <= StudentCount) {
		StudentCapacity += ADDITIONAL;
		temp = (char***)malloc(sizeof(char**)*StudentCapacity);
		for (a = 0; a < StudentCount; a++)
			temp[a] = StudentList[a];
		free(StudentList);
		StudentList = temp;
	}
	StudentList[StudentCount] = (char**)malloc(sizeof(char*)*HeadCount);
	for (a = 0; a < HeadCount; a++) {
		StudentList[StudentCount][a] = (char*)malloc(sizeof(char)*(ListLHeadlimits[a] + 1));
		StudentList[StudentCount][a][0] = '0';		//��ʼ����Ԫ������
		StudentList[StudentCount][a][1] = 0;
	}
	list[*n] = StudentCount;
	*n+=1;
	StudentCount++;
	return *n;
}

/*
�����ַ������бȽ�,�������ֱȽ�
*/
int StrCmp(const char *A, const char *B)
{
	int isNumA = 1, isNumB = 1;
	int lenA = 0, lenB = 0;
	char *A2 = (char*)A, *B2 = (char*)B;
	while (*A2) {
		if (isNumA && (*A2<'0' || *B2>'9'))
			isNumA = 0;
		lenA++;
		A2++;
	}
	while (*B2) {
		if (isNumB && (*B2<'0' || *B2>'9'))
			isNumB = 0;
		lenB++;
		B2++;
	}
	if (isNumA*isNumB == 1) {
		//�������ֽ��бȽ�
		if (lenA != lenB) {
			return lenA - lenB;
		}
		else {
			return strcmp(A, B);
		}
	}
	else {
		//�����ֽ��бȽ�
		return strcmp(A, B);
	}
}

/*
ͨ����ͷ�ı����ҵ���ͷ��Ӧ�ı��
*/
int SearchHeadIndex(const char *ListHeadName)
{
	int a;
	for (a = 0; a < HeadCount; a++) {
		if (!strcmp(ListHead[a], ListHeadName))
			return a;
	}
	return -1;
}

/*
����һ���±�����,�洢ѧ����ָ���Ļ�׼����������µ�˳��,list�н��������ѧ�������ݿ��е�ʵ��˳��
list ��ǰ���ڴ����ѧ�����±꼯��
n list��Ԫ�صĸ���
Order==0 ��������
Order==1 ��������
*/
void Sort(int *list, int n, int sortBase, int Order)
{
	int j, k;
	int temp;
	switch (Order) {
	case 0:
		for (j = 0; j < n; j++) {
			for (k = j; k < n; k++) {
				if (StrCmp(StudentList[list[j]][sortBase], StudentList[list[k]][sortBase]) > 0) {
					temp = list[j];
					list[j] = list[k];
					list[k] = temp;
				}
			}
		}
		break;
	case 1:
		for (j = 0; j < n; j++) {
			for (k = j; k < n; k++) {
				if (StrCmp(StudentList[list[j]][sortBase], StudentList[list[k]][sortBase]) < 0) {
					temp = list[j];
					list[j] = list[k];
					list[k] = temp;
				}
			}
		}
		break;
	}
	return;
}

/*
���ҷ���������ѧ��
����ֵΪ�ҵ���ѧ����
Sourcelist ��ǰ���ڴ����ѧ�����±꼯��
n list��Ԫ�صĸ���
Resultlist ����֮�󷵻ص�ѧ�����±꼯��(������Sourcelistһ��)
destin Ѱ�ҵ�Ŀ���ַ���
*/
int Search(int *Sourcelist, int n, int *Resultlist, int SearchUnit, const char *destin)
{
	int a;
	int list_p = 0;
	for (a = 0; a < n; a++) {
		if (!strcmp(StudentList[Sourcelist[a]][SearchUnit], destin)) {
			Resultlist[list_p++] = Sourcelist[a];
		}
	}
	return list_p;
}

/*
ȡ�����ű��ԭ����ǰ��������������ݳ�ȥ
list���ڷ���ѧ������
n����ѧ����
*/
void GetList(int *list, int *n)
{
	int a;
	*n = StudentCount;
	for (a = 0; a < StudentCount; a++) {
		list[a] = a;
	}
	return;
}

/*
����list��ʾѧ����Ϣ
*/
void display(int *list, int n)
{
	int a, b;
	for (a = 0; a < HeadCount; a++) {
		printf("%-*s ", ListLHeadlimits[a], ListHead[a]);
	}
	printf("\n");
	for (a = 0; a < n; a++) {
		for (b = 0; b < HeadCount; b++) {
			printf("%-*s ", ListLHeadlimits[b], StudentList[list[a]][b]);
		}
		printf("\n");
	}
	return;
}
