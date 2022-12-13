#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <mysql.h> // mysql文件

MYSQL mysql;    //数据库句柄
MYSQL_RES* res; //查询结果集
MYSQL_ROW row;  //记录结构体

void Insert(char name[50], int age);
char* Select(char name[50]);
MYSQL* SelectAll();
void Delete(char name[50]);
void Delete(int age);
void Update(char newname[50], int newage, char oldname[50], int oldage);

void Insert(char name[50], int age) {
	int n = 0;  int ret;
	char s1[2048];
	n += sprintf(s1, "insert into huawei values");
	n += sprintf(s1 + n, "('%s',%d);", name, age);
	//printf("%s", s1);
	ret = mysql_query(&mysql, s1); printf("ret: %d\n", ret);//测试语句是否符合sql语法
	ret = mysql_query(&mysql, "select * from huawei;");
	res = mysql_store_result(&mysql);
	while (row = mysql_fetch_row(res))
	{
		printf("%s  ", row[0]); 
		printf("%s  \n", row[1]); 
		
	}
	mysql_free_result(res);
}
char* Select(char name[50]) {
	int n = 0; int ret;
	char s1[2048];
	n += sprintf(s1, "select * from huawei where name='%s' limit 0,1", name);
	ret = mysql_query(&mysql, s1);// printf("ret: %d\n", ret);
	ret = mysql_query(&mysql, "select * from huawei;");
	res = mysql_store_result(&mysql);
	while (row = mysql_fetch_row(res))
	{
		printf("%s  ", row[0]);  
		printf("%s  \n", row[1]);  
	}
	mysql_free_result(res);
	return s1;
}
MYSQL* SelectAll() {
	int ret = mysql_query(&mysql, "select * from huawei;");
	//printf("ret: %d\n", ret);
	res = mysql_store_result(&mysql);
	while (row = mysql_fetch_row(res))
	{
		printf("%s  ", row[0]);
		printf("%s  \n", row[1]);
	}
	mysql_free_result(res);
	return &mysql;
}
void Delete(char name[50]) {
	int n = 0; int ret;
	char s1[2048];
	n += sprintf(s1, "delete from huawei where name='%s'", name);
	ret = mysql_query(&mysql, s1); printf("ret: %d\n", ret);
	ret = mysql_query(&mysql, "select * from huawei;");
	res = mysql_store_result(&mysql);
	while (row = mysql_fetch_row(res))
	{
		printf("%s  ", row[0]);
		printf("%s  \n", row[1]);
	}
	mysql_free_result(res);
}
void Delete(int age) {
	int n = 0; int ret;
	char s1[2048];
	n += sprintf(s1, "delete from huawei where age=%d", age);
	ret = mysql_query(&mysql, s1); printf("ret: %d\n", ret);
	ret = mysql_query(&mysql, "select * from huawei;");
	res = mysql_store_result(&mysql);
	while (row = mysql_fetch_row(res))
	{
		printf("%s  ", row[0]);
		printf("%s  \n", row[1]);
	}
	mysql_free_result(res);
}
void Update(char newname[50], int newage, char oldname[50], int oldage) {
	int n = 0; int ret;
	char s1[2048];
	n += sprintf(s1, "update huawei set name='%s',age=%d where name='%s' and age=%d", newname, newage, oldname, oldage);
	ret = mysql_query(&mysql, s1); printf("ret: %d\n", ret);
	ret = mysql_query(&mysql, "select * from huawei;");
	res = mysql_store_result(&mysql);
	while (row = mysql_fetch_row(res))
	{
		printf("%s  ", row[0]);
		printf("%s  \n", row[1]);
	}
	mysql_free_result(res);
}
int main(void)
{
	

	//初始化数据库
	mysql_init(&mysql);

	//设置字符编码
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	//连接数据库
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "a13752347", "huawei", 3306, NULL, 0) == NULL) {
		printf("错误原因： %s\n", mysql_error(&mysql));
		printf("连接失败！\n");
		exit(-1);
	}

	//查询数据
	int ret = mysql_query(&mysql, "select * from huawei;");
	//printf("ret: %d\n", ret);
	//获取结果集
	res = mysql_store_result(&mysql);
	//给ROW赋值，判断ROW是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res))
	{
		printf("%s  ", row[0]); 
		printf("%s  \n", row[1]);  
	}
	//释放结果集
	mysql_free_result(res);

	//*********************函数测试
	char name1[50] = "Constantine";
	char name2[50] = "Jack";
	printf("\n Insert:\n");
	Insert(name1, 99);
	printf("\n Insert:\n");
	Insert(name2, 70);
	printf("\nSelect:\n");
	Select(name2);
	printf("\n SelectAll:\n");
	SelectAll();
	printf("\n Delete:\n");
	Delete(name1);
	printf("\n Delete:\n");
	Delete(20);
	printf("\n Update:\n");
	char newname[50] = "Dante";
	char oldname[50] = "Bob";
	Update(newname, 200, oldname, 19);
	//****************************
    //重置数据库
	ret = mysql_query(&mysql, "delete from huawei;");
	ret= mysql_query(&mysql, "insert into huawei values('Jack',20),('Bob',19),('Jade',23),('Dick',20);");
	ret = mysql_query(&mysql, "select * from huawei;");
	res = mysql_store_result(&mysql);
	//给ROW赋值，判断ROW是否为空，不为空就打印数据。
	printf("数据库重置后：\n");
	while (row = mysql_fetch_row(res))
	{
		printf("%s  ", row[0]);  
		printf("%s  \n", row[1]);  
	}
	//释放结果集
	mysql_free_result(res);
	//关闭数据库
	mysql_close(&mysql);
	system("pause");
	return 0;
}
