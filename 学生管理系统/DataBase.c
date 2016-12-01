#include "DataBase.h"

/*
Create By ZCR
2016-12-01
*/

/*
在调用函数时,会要求传入一个*list,
这是一个保存学生在表中的实际存放顺序的下标的数组
它保存的数据是一个个下标,这些数据的顺序不会改变表本身,但是它会关系到显示和保存数据
*/
#define WRONGEXIT(x) {printf("%s,程序将会退出",x);system("pause");exit(1);}
#define ADDITIONAL 10		//一次增加10个学生

/*
在存档文件中,
第一行第一个数字代表学生的人数n,第二个数字代表每个人的属性的个数unit
第二行有unit组数据,每组数据由2个数据组成,分别是一个字符串(表头)和一个数字(代表这个单元的限制长度)
接下来有n组数据,一直到文件结尾,每组数据分别有unit个数据,他们的值就是表头定义的值
注意表头的长度限制为31个英文字符
*/

/*
指向字符串数组的指针
*/
char ***StudentList;

char **ListHead;			//表头名称的字符串数组
int *ListLHeadlimits;		//单元字符限制(数组)
int HeadCount;
int StudentCount;
int StudentCapacity;		//用于记录StudentList的容量(提高效率,避免多次分配)

/*
从文件读取数据
File 要读取的文件路径
*/
void ReadIni(char *File)
{
	FILE *f;
	int n, unit;
	int a, b;
	char temp;
	f = fopen(File, "r");
	if (!f)
		WRONGEXIT("打开文件失败")
		fscanf(f, "%d%d", &n, &unit);	//从文件中读取两个值
	HeadCount = unit;
	StudentCount = n;
	StudentCapacity = n;
	//初始化表头
	ListHead = (char**)malloc(sizeof(char*) * unit);
	ListLHeadlimits = (int*)malloc(sizeof(int)*unit);
	if (!(ListHead&&ListLHeadlimits))
		WRONGEXIT("内存不足")

		for (a = 0; a < unit; a++) {
			*(ListHead + a) = (char*)malloc(sizeof(char) * 32);
			if (!(*(ListHead + a)))
				WRONGEXIT("内存不足")
				fscanf(f, "%s%c%d", *(ListHead + a), &temp, ListLHeadlimits + a);
		}
	//开始初始化表并读取数据
	StudentList = (char***)malloc(sizeof(char**)*n);
	if (!StudentList)
		WRONGEXIT("内存不足")
		for (a = 0; a < n; a++) {
			StudentList[a] = (char**)malloc(sizeof(char*)*unit);
			if (!StudentList[a])
				WRONGEXIT("内存不足")
				for (b = 0; b < unit; b++) {
					StudentList[a][b] = (char*)malloc(sizeof(char)*(ListLHeadlimits[b] + 1));
					if (!StudentList[a][b])
						WRONGEXIT("内存不足")
						fscanf(f, "%s", StudentList[a][b]);
				}
		}
	fclose(f);
}

/*
写入数据到文件
File要进行写入的文件路径,
list 当前正在处理的学生的下标集合
n list中元素的个数
*/
void WriteIni(char* File,int *list, int n)
{
	FILE *f;
	int a, b;
	f = fopen(File, "w+");
	if (!f)
		WRONGEXIT("打开文件失败")
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
新增一个表列
title新增列的表头
UnitLimits 新增数据长度限制
Default 表中的初始值,必须为非空白字符
*/
void NewUnit(char *title, int UnitLimits, char Default)
{
	int newUnitCount = HeadCount + 1;
	char **temp;
	int *temp2;
	int a, b;

	//创建表头
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

	//为每个学生的相应属性分配内存
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
加入一个新的学生
list 当前正在处理的学生的下标集合
n list中元素的个数
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
		StudentList[StudentCount][a][0] = '0';		//初始化单元格数据
		StudentList[StudentCount][a][1] = 0;
	}
	list[*n] = StudentCount;
	*n+=1;
	StudentCount++;
	return *n;
}

/*
两个字符串进行比较,兼容数字比较
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
		//两个数字进行比较
		if (lenA != lenB) {
			return lenA - lenB;
		}
		else {
			return strcmp(A, B);
		}
	}
	else {
		//非数字进行比较
		return strcmp(A, B);
	}
}

/*
通过表头的标题找到表头对应的编号
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
传入一个下标数组,存储学生按指定的基准进行排序后新的顺序,list中仅储存这个学生在数据库中的实际顺序
list 当前正在处理的学生的下标集合
n list中元素的个数
Order==0 升序排序
Order==1 降序排序
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
查找符合条件的学生
返回值为找到的学生数
Sourcelist 当前正在处理的学生的下标集合
n list中元素的个数
Resultlist 处理之后返回的学生的下标集合(允许与Sourcelist一样)
destin 寻找的目标字符串
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
取得整张表的原理就是把所有索引都传递出去
list用于返回学生名单
n返回学生数
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
根据list显示学生信息
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
