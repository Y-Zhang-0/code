#include<iostream>
#include<string>
#include<fstream>
#include<regex> 
#include<iomanip>
#include<Windows.h>

#define max 1000
using namespace std;

int graph[max][max];	//����Ƕ�׶����ڽӾ���
int visited[max];		//�Ƿ񱻷���
//���ļ���
string name ("./test.c");   
//����ƥ��
int  kuohao = 0;
//�������ȼ�������
int flag = 0;
//��������
int fun = 0;	
//����������
int line = 0;	
//����ע�ͱ��
int isFind = 0;
//�����к�ע������һ��
int iCode = 0;
//�ڽӾ���һά����
int xxx = 1;

struct result{	
	int Code = 0;			//������		
	int Comments = 0;		//ע����	
	int Blanklines = 0;		//����
	int scode = 0;			//��������ռ����
	int scomment = 0;		//ע������ռ����
	int sspace = 0;			//������ռ����
	int countfun = 0;		//��������
	int funlen = 0;			//�����ܳ���
	int maxlen = 0;			//���������
	int maxpos = 0;			//�������������
	int maxh = 0;			//���Ƕ�׺������
	double avelen = 0;		//����ƽ������
	string funname[max];	//��¼������
	string maxfun;			//�������
}list;

/*���ݻ�ȡ�������ݣ��Գ����������*/
string evaluate(result l);
/*���ݳɼ�������ӡ������*/
string remark(char s);
/*ͳ�ƴ�����Ϣ*/
void analyze(string s);
/*��ȡ������������������*/
string off(string s);
/*�����ڽӾ���*/
void CreatArry();
/*ͨ��������ȱ���Ѱ�Һ�����������*/
void dfs(int i);
void DFSTraverse();
/*չʾ���*/
void show();

int main(){	
	int key;
	string str;
	cout << "---------------------------------------------------------------" << endl;
	cout << "    ��������з����ĳ����ļ�·�������׺����ʹ�����·����" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "�����ļ�·����";
	// getline(cin, name);
	ifstream in(name);	//�����ļ�
	system("cls");

	if (!in) {
		cout << "----------------------------------------------------------" << endl;
		cout << "                     �ļ���ʧ��                         " << endl;
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
	cout << "               1.������������   2.�˳�                    " << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "��������� �� ";
	cin >> key;
	if (key == 1) {
		system("cls");	//����
		getchar();	  //�������
		main();
	}
    system("pause");
	return 0;
}

/*���ݻ�ȡ�������ݣ��Գ����������*/
string evaluate(result l) {
	string value;
	//��������
	if (l.avelen >= 10 && l.avelen <= 15)
		value += 'A';
	else if ((l.avelen >= 8 && l.avelen < 10) || (l.avelen > 15 && l.avelen <= 20))
		value += 'B';
	else if ((l.avelen >= 5 && l.avelen < 8) || (l.avelen > 20 && l.avelen <= 24))
		value += 'C';
	else
		value += 'D';

	//ע������
	if (list.scomment >= 15 && list.scomment <= 25)
		value += 'A';
	else if ((list.scomment >= 10 && list.scomment < 15) || (list.scomment > 25 && list.scomment <= 30))
		value += 'B';
	else if ((list.scomment >= 5 && list.scomment < 10) || (list.scomment > 30 && list.scomment <= 35))
		value += 'C';
	else
		value += 'D';

	//��������
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

/*���ݳɼ�������ӡ������*/
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

/*ͳ�ƴ�����Ϣ*/
void analyze(string s) {
	//������Ч����
	int i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n'){
		i++;
	}

	//ƥ�䵽��������
	if (regex_match(s, regex("^(\\w{1,10}) ([a-zA-Z_]{1,100})([a-zA-Z0-9_]{0,100})\\((.{0,100})\\).{0,2}"))) {    
		//��������+1
		if(!regex_search(s,regex("\\(.*?\\);"))){
			list.countfun++;	
			//��¼������
			list.funname[list.countfun] = s;
			//����������
			flag = 1;
		}
	}
	//������ʼ
	if (regex_search(s, regex("\\{"))) {	
		kuohao++;
	}
	//��������
	if (regex_search(s, regex("\\}"))) {
		if (kuohao)		kuohao--;
		if(kuohao==0&&flag){
			fun++;   
			if (fun > list.maxlen) {
				list.maxlen = fun;								//ͳ�����������
				list.maxfun = list.funname[list.countfun];		//�������
				list.maxpos = line-fun+1;						//���������λ��
			}
			list.funlen += fun;
			fun = 0;
			flag = 0;
		}
	}
	//ע��������
	if (!isFind && regex_search(s, regex("//"))) {
		//����ע��
		if(s[i] != '/' && s[i+1] !='/'){
			iCode++;		//ͳ�ƴ����к�ע������һ��ĸ���
		}
		list.Comments++;
	} else if(!isFind && regex_search(s,regex("/\\*"))){
		//����ע��
		isFind = 1;//�ҵ�����ע�Ϳ�ͷ
	} else if (!isFind && s[i] == '\0'){
		//��������
		list.Blanklines++;		
	} else if(!isFind && s[i] != '\0'){
		//ͳ�ƴ�����
		list.Code++;
	}
	//ͳ�ƶ���ע��
	if(isFind){
		if(!regex_search(s,regex("\\*/"))){
			list.Comments++;
		}else{
			list.Comments++;
			isFind = 0;
		}
	}
	//ͳ�Ƶ�����������
	if (flag) {
		fun++;		
	}
}

/*��ȡ������������������*/
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

/*�����ڽӾ���*/
void CreatArry(){
	string s;
	ifstream in(name);
	while (1) {
		if (in.eof())	break;
		getline(in,s);
		//������Ч����
		int i = 0;
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n'){
			i++;
		}
		//ƥ�䵽��������
		if (regex_match(s, regex("^(\\w{1,10}) ([a-zA-Z_]{1,100})([a-zA-Z0-9_]{0,100})\\((.{0,100})\\).{0,2}"))) {    
			//��������+1
			if(!regex_search(s,regex("\\(.*?\\);"))){
				//����������
				flag = 1;
				getline(in,s);	
			}
		}
		//������ʼ
		if (regex_search(s, regex("\\{"))) {	
			kuohao++;
		}
		//��������
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

/*ͨ��������ȱ���Ѱ�Һ�����������*/
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

/*չʾ���*/
void show() {	
	//�����ڽӾ���
	CreatArry();
	//������ȱ���ͳ�����Ƕ�����
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