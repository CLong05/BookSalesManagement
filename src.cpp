#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
#include<winsock.h>
#include<iostream>
#include<winsock.h>
#include"mysql.h"
using namespace std;
MYSQL mysql;//����Ϊȫ�ֱ����������������������ܺ����ж��ܶ�������
#pragma warning(disable:4996)
MYSQL_RES* result;
MYSQL_ROW row;

int purchase_book() {
    char bid[3]; char purchasenum[100]; char year[] = "2021"; char month[] = "12"; char date[] = "23";
    char yn[2];
    while (1) {
        char strquery[100] = "select stockn from book where bid= '";//�洢��ѯͼ�����ָ��
        //��ȡ������Ϣ�����γɲ�ѯͼ�����ָ��
        printf("\nPlease input book id:"); scanf("%s", &bid); strcat(strquery, bid);
        strcat(strquery, "'; ");
        //��ѯͼ��Ŀ�������Զ���ʾ
        mysql_query(&mysql, strquery);
        result = mysql_store_result(&mysql);
        cout << "ͼ��������" << mysql_fetch_row(result)[0] << endl;
        //������ȡ������Ϣ
        printf("Please input purchase quantity:"); scanf("%s", &purchasenum);
        printf("Please input year:"); scanf("%s", &year);
        printf("Please input month:"); scanf("%s", &month);
        printf("Please input date:"); scanf("%s", &date);
        
        //����ͼ�飬���γɼ��ٿ������ָ��
        char strquery2[100] = "update book set stockn=stockn-";//�洢���¿������ָ��
        strcat(strquery2, purchasenum);
        strcat(strquery2, " where bid = '");
        strcat(strquery2, bid);
        strcat(strquery2, "';");
        //���й������
        //�����������С�ڿ�棬����Թ���ִ�к����������ӡ���۵����޸Ŀ�棬����������Ϣ��ӵ������۱���
        if (mysql_query(&mysql, strquery2) == 0) {//�޸Ŀ��
            printf("Execute successfully!\n");

            //��������Ϣ��ӵ������۱���
            char strquery3[100] = "insert into purchase(bid,purnum,pyear,pmonth,pdate) values('";//�洢��������Ϣ��ӵ������۱��е�ָ��
            char strquery4[100] = "select bname from book where bid ='";//�洢��ѯ������ָ��
            strcat(strquery3, bid);
            strcat(strquery3, "','");
            strcat(strquery3, purchasenum);
            strcat(strquery3, "','");
            strcat(strquery3, year);
            strcat(strquery3, "','");
            strcat(strquery3, month);
            strcat(strquery3, "','");
            strcat(strquery3, date);
            strcat(strquery3, "');");//�γ�ָ��
            if (mysql_query(&mysql, strquery3) == 0) {//ִ��ָ��
                printf("�ɹ���ӵ������۱���!\n");
            }
            else {
                printf("��ӵ������۱�ʧ��!\n");
            }

            //�޸Ŀ��ִ�гɹ���������۵�
            printf("\n���۵��� \n");
            mysql_query(&mysql, "select max(pno) from purchase;");//��ѯ����
            result = mysql_store_result(&mysql);
            cout << "  " << "���۵���: " << mysql_fetch_row(result)[0] << endl;
            cout << "  " << "ͼ�� id : " << bid << endl;           
            strcat(strquery4, bid);strcat(strquery4, "'; ");mysql_query(&mysql, strquery4);//��ѯ����
            result = mysql_store_result(&mysql);
            row = mysql_fetch_row(result);
            cout << "  " << "����    : " << row[0] << endl;
            cout << "  " << "������Ŀ: " << purchasenum << endl;
            cout << "  " << "����ʱ��: " << year << "��" << month << "��" << date << "��" << endl;
            cout << endl;            
        }
        //����������������ڴ棬�޷��ɹ����򣬼��ٿ��ָ��ִ��ʧ��
        else {
            printf("��治�㣬����ʧ�ܣ�\n\n");
        }
        //�ж��Ƿ��������
        printf("Purchase again?(y--yes,n--no):");
        scanf("%s", &yn);
        if (yn[0] == 'y' || yn[0] == 'Y') { continue; }
        else break;
    }
    return 0;
}

int return_book() {
    char bid[] = "001"; char renum[] = "1"; char ryear[] = "2021"; char rmonth[] = "12"; char rdate[] = "23";
    char strquery[100] = "insert into returnbook(bid,renum,ryear,rmonth,rdate) values('";//�洢�����˻�����ָ��
    char yn[2];
    while (1) {
        //��ȡ������Ϣ���γɲ����˻�����ָ��
        printf("\nPlease input book id:"); scanf("%s", &bid); strcat(strquery, bid);
        strcat(strquery, "','");
        printf("Please input renum:"); scanf("%s", &renum); strcat(strquery, renum);
        strcat(strquery, "','");
        printf("Please input year:"); scanf("%s", &ryear); strcat(strquery, ryear);
        strcat(strquery, "','");
        printf("Please input month:"); scanf("%s", &rmonth); strcat(strquery, rmonth);
        strcat(strquery, "','");
        printf("Please input date:"); scanf("%s", &rdate); strcat(strquery, rdate);
        strcat(strquery, "');");
        //�γɸ��¿������ָ��
        char strquery2[100] = "update book set stockn = stockn - "; //�洢���¿������ָ��
        strcat(strquery2, renum);
        strcat(strquery2, " where bid = '");
        strcat(strquery2, bid);
        strcat(strquery2, "';");
        //���������޸ģ����ӿ�����������˻���Ϣ�����˻���
        if (mysql_query(&mysql, strquery) == 0 && mysql_query(&mysql, strquery2) == 0) {  
            printf("Execute successfully!\n");
            //ִ�гɹ�������˻���
            printf("\n�˻����� \n");
            //��ѯ�˻�����
            mysql_query(&mysql,"select max(rno) from returnbook;");
            result = mysql_store_result(&mysql);
            cout << "  " << "�˻�����: " << mysql_fetch_row(result)[0] << endl;
            cout << "  " << "ͼ�� id : " << bid << endl;
            cout << "  " << "�˻���Ŀ: " << renum << endl;
            cout << "  " << "�˻�ʱ��: " << ryear << "��" << rmonth << "��" << rdate << "��" << endl;
            cout << endl;
        }
        else { printf("Execute falled!\n\n"); }
        //�ж��Ƿ��������
        printf("Return again?(y--yes,n--no):");
        scanf("%s", &yn);
        if (yn[0] == 'y' || yn[0] == 'Y') { continue; }
        else break;
    }
    return 0;
}

int main(int argc, char** argv, char** envp)
{
    int num = 0;
    char fu[2];
    mysql_init(&mysql);//��û��ʼ��һ��MYSQL�ṹ

    //��ʾ�����б�����������ִ����Ӧ����
    if (mysql_real_connect(&mysql, "localhost", "root", "123456", "book_sales_management", 3306, 0, 0)) {
        for (;;) {
            //��ӡ��ʼ�����ܽ���
            printf("\nWelcome to the Book Sales Management System of Xinhua Booksore!\n");
            printf("Please select the function according to your needs:\n");
            printf("   0--exit.\n");//�˳�
            printf("   1--purchase books.\n");//����
            printf("   2--return boooks.\n");//����
            printf("   3--sales statistics.\n");//ͳ��
            printf("   4--goods in.\n\n");//����
            fu[0] = '0';
            scanf("%s", &fu);//��ȡ�û���������
            //ִ����Ӧ�������󣬱�ʵ��ʵ�ֵĹ����ǹ��������鹦��
            if (fu[0] == '0')exit(0);
            if (fu[0] == '1')purchase_book();
            if (fu[0] == '2')return_book();
            if (fu[0] == '3')printf("\nSorry, this function is unavailable.\n");
            if (fu[0] == '4')printf("\nSorry, this function is unavailable.\n");
            //system("pause");
       }
    }
    else {
        printf("Sorry, the database doesn't exist.");
    }
    mysql_close(&mysql);//������ϣ��ر�mysql
    result = mysql_store_result(&mysql);
    mysql_free_result(result);
    system("pause");
    return 0;
}
