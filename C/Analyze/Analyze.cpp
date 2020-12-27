#include<iostream>
#include<string>
#include<fstream>
#include<regex> 
#include<iomanip>
#include<Windows.h>

#define max 1000
using namespace std;

int graph[max][max];	//函数嵌套定义邻接矩阵
int visited[max];		//是否被访问
//打开文件名
string name ("./test.c");   
//括号匹配
int  kuohao = 0;
//函数长度计数开关
int flag = 0;
//函数行数
int fun = 0;	
//代码总行数
int line = 0;	
//多行注释标记
int isFind = 0;
//代码行和注释行在一起
int iCode = 0;
//邻接矩阵一维坐标
int xxx = 1;

struct result{	
	int Code = 0;			//代码行		
	int Comments = 0;		//注释行	
	int Blanklines = 0;		//空行
	int scode = 0;			//代码行所占比例
	int scomment = 0;		//注释行所占比例
	int sspace = 0;			//空行所占比例
	int countfun = 0;		//函数个数
	int funlen = 0;			//函数总长度
	int maxlen = 0;			//最长函数长度
	int maxpos = 0;			//最长函数所在行数
	int maxh = 0;			//最大嵌套函数深度
	double avelen = 0;		//函数平均长度
	string funname[max];	//记录函数名
	string maxfun;			//最长函数名
}list;

/*根据获取到的数据，对程序进行评分*/
string evaluate(result l);
/*根据成绩给出相印的评语*/
string remark(char s);
/*统计代码信息*/
void analyze(string s);
/*获取函数名不带定义类型*/
string off(string s);
/*创建邻接矩阵*/
void CreatArry();
/*通过深度优先遍历寻找函数的最大深度*/
void dfs(int i);
void DFSTraverse();
/*展示面板*/
void show();

int main(){	
	int key;
	string str;
	cout << "---------------------------------------------------------------" << endl;
	cout << "    请输入进行分析的程序文件路径及其后缀（可使用相对路径）" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "分析文件路径：";
	// getline(cin, name);
	ifstream in(name);	//读入文件
	system("cls");

	if (!in) {
		cout << "----------------------------------------------------------" << endl;
		cout << "                     文件打开失败                         " << endl;
		cout << "----------------------------------------------------------" << endl;
		Sleep(2000);
		system("cls");
		main();
	}

	while (1) {
		if (in.eof())	break;
		line++;
		getline(in, str);	
		analyze(str);
	}
	in.close();
	show();

	cout << "----------------------------------------------------------" << endl;
	cout << "               1.分析其他程序   2.退出                    " << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "请输入序号 ： ";
	cin >> key;
	if (key == 1) {
		system("cls");	//清屏
		getchar();	  //清除缓存
		main();
	}
    system("pause");
	return 0;
}

/*根据获取到的数据，对程序进行评分*/
string evaluate(result l) {
	string value;
	//代码评级
	if (l.avelen >= 10 && l.avelen <= 15)
		value += 'A';
	else if ((l.avelen >= 8 && l.avelen < 10) || (l.avelen > 15 && l.avelen <= 20))
		value += 'B';
	else if ((l.avelen >= 5 && l.avelen < 8) || (l.avelen > 20 && l.avelen <= 24))
		value += 'C';
	else
		value += 'D';

	//注释评级
	if (list.scomment >= 15 && list.scomment <= 25)
		value += 'A';
	else if ((list.scomment >= 10 && list.scomment < 15) || (list.scomment > 25 && list.scomment <= 30))
		value += 'B';
	else if ((list.scomment >= 5 && list.scomment < 10) || (list.scomment > 30 && list.scomment <= 35))
		value += 'C';
	else
		value += 'D';

	//空行评级
	if (list.sspace >= 15 && list.sspace <= 25)
		value += 'A';
	else if ((list.sspace >= 10 && list.sspace < 15) || (list.sspace > 25 && list.sspace <= 30))
		value += 'B';
	else if ((list.sspace >= 5 && list.sspace < 10) || (list.sspace > 30 && list.sspace <= 35))
		value += 'C';
	else
		value += 'D';

	return value;
}

/*根据成绩给出相印的评语*/
string remark(char s){
	if (s=='A')
		return "Excellent";
	else if (s == 'B')
		return "good";
	else if (s == 'C')
		return  "common";
	else
		return "bad";
}

/*统计代码信息*/
void analyze(string s) {
	//过滤无效符号
	int i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n'){
		i++;
	}

	//匹配到函数定义
	if (regex_match(s, regex("^(\\w{1,10}) ([a-zA-Z_]{1,100})([a-zA-Z0-9_]{0,100})\\((.{0,100})\\).{0,2}"))) {    
		//函数个数+1
		if(!regex_search(s,regex("\\(.*?\\);"))){
			list.countfun++;	
			//记录函数名
			list.funname[list.countfun] = s;
			//开启计数器
			flag = 1;
		}
	}
	//函数开始
	if (regex_search(s, regex("\\{"))) {	
		kuohao++;
	}
	//函数结束
	if (regex_search(s, regex("\\}"))) {
		if (kuohao)		kuohao--;
		if(kuohao==0&&flag){
			fun++;   
			if (fun > list.maxlen) {
				list.maxlen = fun;								//统计最长函数长度
				list.maxfun = list.funname[list.countfun];		//最长函数名
				list.maxpos = line-fun+1;						//最长函数所在位置
			}
			list.funlen += fun;
			fun = 0;
			flag = 0;
		}
	}
	//注释行搜索
	if (!isFind && regex_search(s, regex("//"))) {
		//单行注释
		if(s[i] != '/' && s[i+1] !='/'){
			iCode++;		//统计代码行和注释行在一起的个数
		}
		list.Comments++;
	} else if(!isFind && regex_search(s,regex("/\\*"))){
		//多行注释
		isFind = 1;//找到多行注释开头
	} else if (!isFind && s[i] == '\0'){
		//空行搜索
		list.Blanklines++;		
	} else if(!isFind && s[i] != '\0'){
		//统计代码行
		list.Code++;
	}
	//统计多行注释
	if(isFind){
		if(!regex_search(s,regex("\\*/"))){
			list.Comments++;
		}else{
			list.Comments++;
			isFind = 0;
		}
	}
	//统计单个函数行数
	if (flag) {
		fun++;		
	}
}

/*获取函数名不带定义类型*/
string off(string s){
	string cs;
	int open = 0;
	for (int i = 0;; i++) {
		if (s[i] == '\0'&&open == 1) {
			return cs;
		}
		if (open)	cs += s[i];
		if (s[i] == ' '&&open==0) {
			open = 1;
		}
	}
}

/*创建邻接矩阵*/
void CreatArry(){
	string s;
	ifstream in(name);
	while (1) {
		if (in.eof())	break;
		getline(in,s);
		//过滤无效符号
		int i = 0;
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n'){
			i++;
		}
		//匹配到函数定义
		if (regex_match(s, regex("^(\\w{1,10}) ([a-zA-Z_]{1,100})([a-zA-Z0-9_]{0,100})\\((.{0,100})\\).{0,2}"))) {    
			//函数个数+1
			if(!regex_search(s,regex("\\(.*?\\);"))){
				//开启计数器
				flag = 1;
				getline(in,s);	
			}
		}
		//函数开始
		if (regex_search(s, regex("\\{"))) {	
			kuohao++;
		}
		//函数结束
		if (regex_search(s, regex("\\}"))) {
			if (kuohao)		kuohao--;
			if(kuohao==0&&flag){
				flag = 0;
				xxx++;
			}
		}			
		if (flag){	
			for(int j = 1; j <= list.countfun; j++){
				if(regex_search(s,regex(off(list.funname[j])))){
					graph[xxx][j] = 1;
				}
			}
		}
	}	
	// for(int i = 1; i<=list.countfun;i++){
	// 	for(int j = 1; j<=list.countfun;j++){
	// 		cout<<graph[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
}

/*通过深度优先遍历寻找函数的最大深度*/
void dfs(int i) {
	int j,count = 0;
	visited[i] = 1;
	for (j = 1; j <= list.countfun; j++){
		if (!visited[j] && graph[i][j] == 1){
			dfs(j);
			list.maxh++;
		}	
	}
}

void DFSTraverse(){
	int i;
	for (i = 1; i <= list.countfun; i++)	visited[i] = 0;
	for (i = 1; i <= list.countfun; i++){
		if (!visited[i]){
			dfs(i);
		}		
	}
}

/*展示面板*/
void show() {	
	//创建邻接矩阵
	CreatArry();
	//深度优先遍历统计最大嵌套深度
	DFSTraverse();

	list.scode = (int)((double)list.Code / (list.Code + list.Comments + list.Blanklines)*100+0.5);
	list.scomment = (int)((double)list.Comments / (list.Code + list.Comments + list.Blanklines) * 100 + 0.5);
	list.sspace = 100 - list.scode - list.scomment;
	list.avelen = (double)list.funlen / list.countfun;
	string res = evaluate(list);
	cout << "The result of analysing program file \"" + name + "\":" << endl;
	cout << "    Lines of program :   " << line << endl;
	cout << "    Lines of code :      " << list.Code + iCode<< endl;
	cout << "    Lines of comments :  " << list.Comments << endl;
	cout << "    Blank lines :        " << list.Blanklines << endl;
	cout << "    Code    Comments    Space" << endl;
	cout << "    ====    ========    =====" << endl;
	cout << "     " <<list.scode<< "%   "<<setw(6)<<list.scomment << "%        " << list.sspace<<"%"<< endl;
	cout << "    The program include " << list.countfun << " functions." << endl;
	cout << "    The average length of a section of function is " <<list.avelen<< " lines." << endl;
	cout << "    The longest function is " << list.maxfun << ":" << list.maxlen << " lines." << endl;
	cout << "    The longest function is " <<"on the " <<list.maxpos<<" line"<< endl;	
	cout << "    The maximum function nesting is :" << list.maxh << endl;
	cout << "    Grade " << res[0] <<" "<< remark(res[0]) << " code style." << endl;
	cout << "    Grade " << res[1] <<" "<< remark(res[1]) << " commenting style." << endl;
	cout << "    Grade " << res[2] <<" "<< remark(res[2]) << " white space style." << endl;
}