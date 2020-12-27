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
string name ("F:/Microsoft VS Code/CCode/experiment/Experient/test.c");   
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

//邻接表创建
typedef struct ArcNode {
	int adjvex;					//邻接点域
	struct ArcNode *next; 		//指向下一个邻接点	
}ArcNode; 		//边表节点

typedef struct VertexNode{
	string Fname; 		//存储顶点数据信息
	ArcNode *ftrstNode; //边表头指针
}VertexNode, AdjList[max];

typedef struct{
    AdjList adjlist;    //定义邻接表
}GraphAdjList;

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

//更新主串S
void changeString(char* S, char* T);
// 返回子串T在主串S第pos个字符之后的位置若不存在，则返回0
int Index_KMP(char* T, char* S, int index);
//获取next数组
void get_next(char* T, int *next);
/*根据获取到的数据，对程序进行评分*/
string evaluate(result l);
/*根据成绩给出相印的评语*/
string remark(char s);
/*统计代码信息*/
void analyze(string s);
/*创建邻接表*/
void CreateAdjListGraph(GraphAdjList &G);
void PrintfGraphAdjList(GraphAdjList G);
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
	getline(cin, name);
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

/*创建邻接表*/
void CreateAdjListGraph(GraphAdjList &G){
	ArcNode *e;
	for(int i = 1; i <= list.countfun; i++){		//建立顶点节点	
		G.adjlist[i].Fname = list.funname[i];		//输入顶点信息
		G.adjlist[i].ftrstNode = NULL;				//将表边指针置为空
	}	
	for(int j = 1; j <= list.countfun; j++){		//建立边表节点
		string str;
		ifstream in(name);	//读入文件
		while (1) {
			if (in.eof())	break;
			getline(in, str);
			for(int k = 1; k <= list.countfun; k++){
				if(regex_search(str,regex(off(list.funname[k])))){
					e = (ArcNode *)malloc(sizeof(ArcNode));
					e->adjvex = k;
					e->next = G.adjlist[j].ftrstNode;
					G.adjlist[j].ftrstNode = e;
				}
			}				
		}
	}		
}	
void PrintfGraphAdjList(GraphAdjList G)
{
    for(int i = 1; i <= list.countfun; i++)
    {
        ArcNode *p = G.adjlist[i].ftrstNode;
        cout << G.adjlist[i].Fname << '\t';
        while(p)
        {
            cout << p->adjvex << ' ' << '\t';
            p = p->next;
        }
        cout << endl;
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
	for(int i = 1; i<=list.countfun;i++){
		for(int j = 1; j<=list.countfun;j++){
			cout<<graph[i][j]<<" ";
		}
		cout<<endl;
	}
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

void get_next(char* T, int *next){
/*  未改进的获取next的方法
    next[1]=0;
    next[2]=1;
    int i=2, j=1;
    while (i < strlen(T)) {
        if (j == 0 || T[i-1] == T[j-1]) {
            i++;
            j++;
            next[i] = j;
        } else{
            j = next[j];
        }
    }
*/

//改进后的获取next的方法    
    next[1]=0;
    next[2]=1;
    int i=2;
    int j=1;
    while (i<strlen(T)) {
        if (j==0||T[i-1]==T[j-1]) {
            i++;
            j++;
            if (T[i-1]!=T[j-1]) {
               next[i]=j;
            }
            else{
                next[i]=next[j];
            }
        }else{
            j=next[j];
        }
    }
}

// 返回子串T在主串S第pos个字符之后的位置
// 若不存在，则返回0
int Index_KMP(char* T, char* S, int index){
	int i = index;
	int j = 1;
	int next[255];
	get_next(T,next);
	while(i <= strlen(S) && j <= strlen(T)){
		if(j == 0 || S[i-1] == T[j-1]){
			i++;
			j++;
		}else{
			j = next[j];
		}
	}
    if(j > strlen(T))    return i - strlen(T);
	else            return 0;
}

//更新主串S
void changeString(char* S, char* T){
    int i = strlen(S), j = strlen(T)-1;
    for(int k = 0; k < j; k++){
        S[i] = S[k];
        i++;
    }
}

