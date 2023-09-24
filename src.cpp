#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
#include<winsock.h>
#include<iostream>
#include<winsock.h>
#include"mysql.h"
using namespace std;
MYSQL mysql;//声明为全局变量，待会在主函数，功能函数中都能对它访问
#pragma warning(disable:4996)
MYSQL_RES* result;
MYSQL_ROW row;

int purchase_book() {
    char bid[3]; char purchasenum[100]; char year[] = "2021"; char month[] = "12"; char date[] = "23";
    char yn[2];
    while (1) {
        char strquery[100] = "select stockn from book where bid= '";//存储查询图书库存的指令
        //读取购买信息，并形成查询图书库存的指令
        printf("\nPlease input book id:"); scanf("%s", &bid); strcat(strquery, bid);
        strcat(strquery, "'; ");
        //查询图书的库存量并自动显示
        mysql_query(&mysql, strquery);
        result = mysql_store_result(&mysql);
        cout << "图书库存量：" << mysql_fetch_row(result)[0] << endl;
        //继续读取购买信息
        printf("Please input purchase quantity:"); scanf("%s", &purchasenum);
        printf("Please input year:"); scanf("%s", &year);
        printf("Please input month:"); scanf("%s", &month);
        printf("Please input date:"); scanf("%s", &date);
        
        //购买图书，即形成减少库存量的指令
        char strquery2[100] = "update book set stockn=stockn-";//存储更新库存量的指令
        strcat(strquery2, purchasenum);
        strcat(strquery2, " where bid = '");
        strcat(strquery2, bid);
        strcat(strquery2, "';");
        //进行购买操作
        //如果购买数量小于库存，则可以购买，执行后续操作则打印销售单，修改库存，并将购买信息添加到日销售表中
        if (mysql_query(&mysql, strquery2) == 0) {//修改库存
            printf("Execute successfully!\n");

            //将购买信息添加到日销售表中
            char strquery3[100] = "insert into purchase(bid,purnum,pyear,pmonth,pdate) values('";//存储将购买信息添加到日销售表中的指令
            char strquery4[100] = "select bname from book where bid ='";//存储查询书名的指令
            strcat(strquery3, bid);
            strcat(strquery3, "','");
            strcat(strquery3, purchasenum);
            strcat(strquery3, "','");
            strcat(strquery3, year);
            strcat(strquery3, "','");
            strcat(strquery3, month);
            strcat(strquery3, "','");
            strcat(strquery3, date);
            strcat(strquery3, "');");//形成指令
            if (mysql_query(&mysql, strquery3) == 0) {//执行指令
                printf("成功添加到日销售表中!\n");
            }
            else {
                printf("添加到日销售表失败!\n");
            }

            //修改库存执行成功，输出销售单
            printf("\n销售单： \n");
            mysql_query(&mysql, "select max(pno) from purchase;");//查询单号
            result = mysql_store_result(&mysql);
            cout << "  " << "销售单号: " << mysql_fetch_row(result)[0] << endl;
            cout << "  " << "图书 id : " << bid << endl;           
            strcat(strquery4, bid);strcat(strquery4, "'; ");mysql_query(&mysql, strquery4);//查询书名
            result = mysql_store_result(&mysql);
            row = mysql_fetch_row(result);
            cout << "  " << "书名    : " << row[0] << endl;
            cout << "  " << "购买数目: " << purchasenum << endl;
            cout << "  " << "购买时间: " << year << "年" << month << "月" << date << "日" << endl;
            cout << endl;            
        }
        //如果购买数量大于内存，无法成功购买，减少库存指令执行失败
        else {
            printf("库存不足，购买失败！\n\n");
        }
        //判断是否继续购书
        printf("Purchase again?(y--yes,n--no):");
        scanf("%s", &yn);
        if (yn[0] == 'y' || yn[0] == 'Y') { continue; }
        else break;
    }
    return 0;
}

int return_book() {
    char bid[] = "001"; char renum[] = "1"; char ryear[] = "2021"; char rmonth[] = "12"; char rdate[] = "23";
    char strquery[100] = "insert into returnbook(bid,renum,ryear,rmonth,rdate) values('";//存储插入退货单的指令
    char yn[2];
    while (1) {
        //读取退书信息，形成插入退货单的指令
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
        //形成更新库存量的指令
        char strquery2[100] = "update book set stockn = stockn - "; //存储更新库存量的指令
        strcat(strquery2, renum);
        strcat(strquery2, " where bid = '");
        strcat(strquery2, bid);
        strcat(strquery2, "';");
        //进行数据修改：增加库存量，并将退货信息加入退货表
        if (mysql_query(&mysql, strquery) == 0 && mysql_query(&mysql, strquery2) == 0) {  
            printf("Execute successfully!\n");
            //执行成功，输出退货单
            printf("\n退货单： \n");
            //查询退货单号
            mysql_query(&mysql,"select max(rno) from returnbook;");
            result = mysql_store_result(&mysql);
            cout << "  " << "退货单号: " << mysql_fetch_row(result)[0] << endl;
            cout << "  " << "图书 id : " << bid << endl;
            cout << "  " << "退货数目: " << renum << endl;
            cout << "  " << "退货时间: " << ryear << "年" << rmonth << "月" << rdate << "日" << endl;
            cout << endl;
        }
        else { printf("Execute falled!\n\n"); }
        //判断是否继续退书
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
    mysql_init(&mysql);//获得或初始化一个MYSQL结构

    //显示功能列表，并根据需求执行相应功能
    if (mysql_real_connect(&mysql, "localhost", "root", "123456", "book_sales_management", 3306, 0, 0)) {
        for (;;) {
            //打印初始化功能界面
            printf("\nWelcome to the Book Sales Management System of Xinhua Booksore!\n");
            printf("Please select the function according to your needs:\n");
            printf("   0--exit.\n");//退出
            printf("   1--purchase books.\n");//购书
            printf("   2--return boooks.\n");//退书
            printf("   3--sales statistics.\n");//统计
            printf("   4--goods in.\n\n");//进货
            fu[0] = '0';
            scanf("%s", &fu);//读取用户功能需求
            //执行相应功能需求，本实验实现的功能是购书与退书功能
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
    mysql_close(&mysql);//访问完毕，关闭mysql
    result = mysql_store_result(&mysql);
    mysql_free_result(result);
    system("pause");
    return 0;
}
