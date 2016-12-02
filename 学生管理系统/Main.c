#include "DataBase.h"


/*
需要实现的功能
0.显示所有学生信息
1.排序
2.查找学生
3.新增数据列
4.新增学生
5.修改学生信息
6.读取学生信息
7.保存学生信息
*/

int main()
{
	int list[1500];				//名单,里面保存的是学生的下标
	int list2[1500];
	int list3[1500];
	int n;
	int temp,temp2;
	char *temp3;

	ReadIni("data.ini");		//读取data.ini
	GetList(list, &n);			//取得一个名单

	
	//测试代码,自行去掉注释进行测试

	printf("按照姓名升序排序\n");
	Sort(list, n, SearchHeadIndex("姓名"), 0);
	display(list, n);
	
	/*

	printf("\n按照姓名降序排序\n");
	Sort(list, n, SearchHeadIndex("姓名"), 1);
	display(list, n);

	printf("\n按照学号升序排序\n");
	Sort(list, n, SearchHeadIndex("学号"), 0);
	display(list, n);

	printf("\n按照学号降序排序\n");
	Sort(list, n, SearchHeadIndex("学号"), 1);
	display(list, n);

	printf("\n按照成绩1升序排序\n");
	Sort(list, n, SearchHeadIndex("成绩1"), 0);
	display(list, n);

	printf("\n按照成绩1降序排序\n");
	Sort(list, n, SearchHeadIndex("成绩1"), 1);
	display(list, n);

	printf("\n找到成绩1为65分的\n");
	temp=Search(list, n, list2, SearchHeadIndex("成绩1"), "65");
	display(list2, temp);

	printf("\n找到成绩1为65分,并且成绩2为56分的\n");
	temp2 = Search(list2, temp, list3, SearchHeadIndex("成绩2"), "56");
	display(list3, temp2);

	printf("\n新增一个项成绩3\n");
	NewUnit("成绩3", 3, '0');
	display(list, n);

	printf("\n新增一个学生\n");
	NewStudent(list, &n);
	display(list, n);

	*/
	printf("从名单中删除第一个同学的信息\n");
	DeleteStudentInList(list, &n, list[0], 1);
	display(list, n);

	printf("\n将第n个人的姓名改为黄智豪\n");
	temp3 = GetString(list, n - 1, SearchHeadIndex("姓名"));
	strcpy(temp3, "黄智豪");
	display(list, n);
	
	printf("\n取得第n个人的姓名\n");
	printf("%s\n", GetString(list, n-1, SearchHeadIndex("姓名")));

	printf("将数据保存到new.ini\n");
	WriteIni("new.ini", list, n);

	//释放内存之后,不能再对表进行操作
	DestroyStudentList();
	system("pause");
}