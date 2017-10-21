#include <iostream>
#include <string.h>
using namespace std;
//typedef struct student *Nextstd;
//typedef struct student *Laststd;
//typedef struct student{
//	Laststd laststd;
//	int id;
//	char name[5];
//	char *introduct[10];
//	Nextstd nextstd;
//} Student;

class Student{
	public:
		int id;
		char name[5];
		char introduct[10];
	public:
		Student *laststd;
		Student *nextstd;
	Student()
	{
		cout<<"请输入学号："<<endl;
		cin>>this->id;
		cout<<"请输入姓名："<<endl;
		cin>>this->name;
		cout<<"请输入备注："<<endl;
		cin>>this->introduct;
		cout<<"学生："<<this->name<<"添加完成"<<endl;
	}
	
	~Student(){
		if(this != NULL){
//			delete(this->id);
//			delete(this->name);
//			delete(this->introduct);
		}
	}
	void showname(){
		cout<<"该学生名为："<<this->name<<endl;
	}
	void showid(){
		cout<<"该学生学号为："<<this->id<<endl;
	}
	void showintroduct(){
		cout<<"该学生的简介为："<<this->introduct<<endl;
	}
	
	
};

class Manage{
	private:
		char forwho[5];
	public:
		bool charcmp(char *priarr, char *arr)
		{
			int i;
			for(i = 0;priarr[i] != 0;i++){
				if(priarr[i] != arr[i]){
					return false;
				}
			}
			return true;
		}
	Student* addstu(Student *L){
		if (L==NULL){
			L = new Student();
			L->laststd = NULL;
			L->nextstd = NULL;
		}else {
			L->nextstd = new Student();
			L->nextstd->nextstd = NULL;
			L->nextstd->laststd = L;
			L = L->nextstd;
		}
		return L;
	}
	
	Student * delstu(Student *L){
		Student *p = searchstu(1,L);
		if(p != NULL){
			if(p->laststd != NULL && p->nextstd != NULL){
				p->laststd->nextstd = p->nextstd;
				p->nextstd->laststd = p->laststd;
//				free(p);
				return L;
			}else if(p->laststd == NULL && p->nextstd != NULL){
				L = p->nextstd;
				p->nextstd->laststd = NULL;
				p->nextstd = NULL;
//				free(p);
				return L;
			}else if(p->nextstd == NULL && p->laststd != NULL){
				L = p->laststd;
				p->laststd->nextstd = NULL;
				p->laststd = NULL;
//				free(p);
				return L;
			}else if(p->laststd == NULL && p->nextstd == NULL){
//				free(p);
				return NULL;
			}
			
		}
	}
	
	void liststu(Student *L){
		if(L == NULL){
			cout<<"未查找到任何记录"<<endl;
		}else{
			cout<<"如下为已录入的所有学生信息："<<endl;
			int i = 0;
			Student *q;
			for(q = L;q != NULL;q = q->laststd){
				cout<<"################第"<<i+1<<"名学生###############"<<endl;
//				cout<<"姓名："<<q->name<<endl;
//				cout<<"学号："<<q->id<<endl;
//				cout<<"备注："<<q->introduct<<endl;
				q->showname();
				q->showid();
				q->showintroduct();
				cout<<"############################################"<<endl;
				i++;
			}
		}
	}
	Student* searchstu(int mark,Student *L){
		switch(mark){
		case 1:strcpy(forwho,"删除");break;
		case 2:strcpy(forwho,"搜索");break;
		}
		cout<<"输入1通过姓名查找需要"<<forwho<<"的学生"<<endl;
		cout<<"输入2通过学号查找需要"<<forwho<<"的学生"<<endl;
		int choose;
		cin>>choose;
		system("cls");
		cout<<"您正在搜索某学生"<<endl;
		switch(choose){
		case 1:return findstdbyname(L);break;
		case 2:return findstdbyid(L);break;
		default: cout<<"please give me an right num"<<endl;break;
		}
	}
	Student* findstdbyname(Student *L){
		cout<<"请输入待"<<forwho<<"的学生的姓名：";
		char searchname[5];
		cin>>searchname;
		Student *p = NULL;
		Student *q;
		for(q = L;q != NULL;q = q->laststd){
//			cout<<"################"<<endl;
//			cout<<"姓名："<<q->name<<endl;
//			cout<<"学号："<<q->id<<endl;
//			cout<<"备注："<<q->introduct<<endl;
//			cout<<"################"<<endl;
			if(charcmp(searchname,q->name))
			p = q;
		}
		if(p != NULL){
			cout<<"已查找到姓名为："<<searchname<<"的学生"<<endl<<"信息如下："<<endl;
//			cout<<"姓名："<<p->name<<endl;
//			cout<<"学号："<<p->id<<endl;
//			cout<<"备注："<<p->introduct<<endl;
			p->showname();
			p->showid();
			p->showintroduct();
		}else{
			cout<<"未找到相关学生，请检查您的查找信息。"<<endl;
		} 
		return p;
	}
	Student* findstdbyid(Student *L){
		cout<<"请输入待"<<forwho<<"的学生的学号：";
		int searchid;
		cin>>searchid;
		Student *p = NULL;
		Student *q;
		for(q = L;q != NULL;q = q->laststd){
			if(q->id == searchid)
			p = q;
		}
		if(p != NULL){
			cout<<"已查找到学号为："<<searchid<<"的学生"<<endl<<"信息如下："<<endl;
//			cout<<"姓名："<<p->name<<endl;
//			cout<<"学号："<<p->id<<endl;
//			cout<<"备注："<<p->introduct<<endl;
			p->showname();
			p->showid();
			p->showintroduct();
		}else{
			cout<<"未找到相关学生，请检查您的查找信息。"<<endl;
		} 
		return p;
	}
	Manage(int i,Student **L){
		switch(i){
		case 1: cout<<"您正在执行添加学生的操作"<<endl;*L = this->addstu(*L);break;
		case 2: cout<<"您正在执行删除学生的操作"<<endl;*L = this->delstu(*L);break;
		case 3: this->liststu(*L);break;
		case 4: cout<<"您正在搜索某学生"<<endl;this->searchstu(2,*L);break;
		default: cout<<"请按照要求输入正确的选项！！！"<<endl;break;
		}
	}
};

int main(){
	Student *L = NULL;
	while(1){
		system("cls");
		cout<<"输入1添加学生"<<endl;
		cout<<"输入2删除学生"<<endl;
		cout<<"输入3列出学生"<<endl;
		cout<<"输入4搜索指定学生"<<endl;
		int choice;
		cin>>choice;
		system("cls");
		Manage M = Manage(choice,&L);
		cout<<"按任意键回到选择菜单。。。";
		system("pause>nul");
	}
	return 0;
};
