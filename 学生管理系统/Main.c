#include "DataBase.h"


/*
��Ҫʵ�ֵĹ���
0.��ʾ����ѧ����Ϣ
1.����
2.����ѧ��
3.����������
4.����ѧ��
5.�޸�ѧ����Ϣ
6.��ȡѧ����Ϣ
7.����ѧ����Ϣ
*/

int main()
{
	int list[1500];				//����,���汣�����ѧ�����±�
	int list2[1500];
	int list3[1500];
	int n;
	int temp,temp2;
	char *temp3;

	ReadIni("data.ini");		//��ȡdata.ini
	GetList(list, &n);			//ȡ��һ������

	
	//���Դ���,����ȥ��ע�ͽ��в���

	printf("����������������\n");
	Sort(list, n, SearchHeadIndex("����"), 0);
	display(list, n);
	
	/*

	printf("\n����������������\n");
	Sort(list, n, SearchHeadIndex("����"), 1);
	display(list, n);

	printf("\n����ѧ����������\n");
	Sort(list, n, SearchHeadIndex("ѧ��"), 0);
	display(list, n);

	printf("\n����ѧ�Ž�������\n");
	Sort(list, n, SearchHeadIndex("ѧ��"), 1);
	display(list, n);

	printf("\n���ճɼ�1��������\n");
	Sort(list, n, SearchHeadIndex("�ɼ�1"), 0);
	display(list, n);

	printf("\n���ճɼ�1��������\n");
	Sort(list, n, SearchHeadIndex("�ɼ�1"), 1);
	display(list, n);

	printf("\n�ҵ��ɼ�1Ϊ65�ֵ�\n");
	temp=Search(list, n, list2, SearchHeadIndex("�ɼ�1"), "65");
	display(list2, temp);

	printf("\n�ҵ��ɼ�1Ϊ65��,���ҳɼ�2Ϊ56�ֵ�\n");
	temp2 = Search(list2, temp, list3, SearchHeadIndex("�ɼ�2"), "56");
	display(list3, temp2);

	printf("\n����һ����ɼ�3\n");
	NewUnit("�ɼ�3", 3, '0');
	display(list, n);

	printf("\n����һ��ѧ��\n");
	NewStudent(list, &n);
	display(list, n);

	*/
	printf("��������ɾ����һ��ͬѧ����Ϣ\n");
	DeleteStudentInList(list, &n, list[0], 1);
	display(list, n);

	printf("\n����n���˵�������Ϊ���Ǻ�\n");
	temp3 = GetString(list, n - 1, SearchHeadIndex("����"));
	strcpy(temp3, "���Ǻ�");
	display(list, n);
	
	printf("\nȡ�õ�n���˵�����\n");
	printf("%s\n", GetString(list, n-1, SearchHeadIndex("����")));

	printf("�����ݱ��浽new.ini\n");
	WriteIni("new.ini", list, n);

	//�ͷ��ڴ�֮��,�����ٶԱ���в���
	DestroyStudentList();
	system("pause");
}