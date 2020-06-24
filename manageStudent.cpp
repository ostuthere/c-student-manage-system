#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<windows.h>

using namespace std;

typedef struct student {
  char name[20];
  char grade[20];
  char gender[20];
  char birthDay[20];
} student;

typedef struct listPoint {
  student *information;
  listPoint *next;
} listPoint;

// create students' list
listPoint *create_list();

listPoint *delete_list(listPoint *pHead);

// append students' information
void append_point(listPoint *pHead);

// delete student's information
void delete_point(listPoint *pHead);

// search for someone
void find_point(listPoint *pHead);

// print all students' information
void print_all_points(listPoint *pHead);

// print a student's information
void print_one_point(listPoint *point);

// save the list to file
void write_to_file(listPoint *pHead);

listPoint *read_from_file();

void show_menu();

int main() {
  listPoint *head = NULL;

  cout<<"------------------------------create theList------------------------------"<<endl;
  cout<<"Create a students' list: 1. input by yourself  2. read from file"<<endl;
  cout<<"Please choose the methods: ";
  int m;
  cin>>m;
  if(m == 1) {
    head = create_list();
  } else {
    head = read_from_file();
  }
  int k = 1;
  while(k) {
    show_menu();
    cout<<"Please choose a number: ";
    int flag;
    cin>>flag;
    switch (flag) {
      case 1:
        append_point(head);
        break;
      case 2:
        delete_point(head);
        break;
      case 3:
        find_point(head);
        break;
      case 4:
        print_all_points(head);
        break;
      case 5:
        write_to_file(head);
        break;
      case 6:
        head = read_from_file();
        break;
      case 7:
        k = 0;
        delete_list(head);
        break;
    }
  }
  system("pause");
  return 0;
}

listPoint *create_list() {
  listPoint *head, *normal, *end;

  head = (listPoint*)malloc(sizeof(listPoint));
  if (head == NULL) {
    cout<<"failed!exit system";
    exit(-1);
  }
  head -> information = (student*)malloc(sizeof(student));
  end = head;

  cout<<"How many students you want to input: ";
  int n;
  cin>>n;
  for (int i=0; i<n; i++) {
    normal = (listPoint*)malloc(sizeof(listPoint));
    normal -> information = (student*)malloc(sizeof(student));
    cout<<"Please input the "<<i+1<<" student's name: ";
    cin>>normal->information->name;
    cout<<"Please input the "<<i+1<<" student's grade: ";
    cin>>normal->information->grade;
    cout<<"Please input the "<<i+1<<" student's gender(male or female): ";
    cin>>normal->information->gender;
    cout<<"Please input the "<<i+1<<" student's birthday(such as 1989-12-13): ";
    cin>>normal->information->birthDay;

    end -> next = normal;
    end = normal;
  }
  end -> next = NULL;

  print_all_points(head);
  return head;
}

listPoint *delete_list(listPoint *pHead) {
  listPoint *p;
  while (pHead != NULL) {
    p = pHead;
    pHead = pHead -> next;
    free(p);
  }
  print_all_points(pHead);
  return pHead;
}

void append_point(listPoint *pHead) {
  cout<<"------------------------------append student------------------------------"<<endl;
  listPoint *p,*pNew;
  p = pHead;
  while(p -> next != NULL){
    p = p -> next;
  }

  // append to the end
  int n;
  cout<<"How many students you want to add: ";
  cin>>n;

  for (int i=0; i<n; i++) {
    pNew = (listPoint*)malloc(sizeof(listPoint));
    pNew -> information = (student*)malloc(sizeof(student));
    cout<<"the "<<i+1<<" student's name: ";
    cin>>pNew->information->name;
    cout<<"the "<<i+1<<" student's grade: ";
    cin>>pNew->information->grade;
    cout<<"the "<<i+1<<" student's gender(male or female): ";
    cin>>pNew->information->gender;
    cout<<"the "<<i+1<<" student's birthday(such as 1989-12-13): ";
    cin>>pNew->information->birthDay;

    p -> next = pNew;
    p = pNew;
  }
  p -> next = NULL;
  print_all_points(pHead);
}

void delete_point(listPoint *pHead) {
  cout<<"------------------------------delete student------------------------------"<<endl;
  listPoint *p,*temp;
  p = pHead;

  if (pHead == NULL) {
    cout<<"The list is null,can't delete point!"<<endl;
    exit(-1);
  }

  char name[20];
  cout<<"Please input the student's NAME you want to delete: ";
  cin>>name;

  int flag = 0;
  while (p != NULL)
  {
    if (strcmp(p->information->name, name) == 0) {
      flag = 1;
      break;
    }
    temp = p;
    p = p -> next;
  }

  if (flag) {
    // the point is the head
    if (p == pHead) {
      pHead = p -> next;
    } else {
      temp -> next = p -> next;
    }
    free(p);
    p = NULL;
    cout<<"Delete SUCCESSFUL!"<<endl;
    print_all_points(pHead);
  } else {
    cout<<"Delete FAILED! There is no student named "<<name<<endl;
  }
}

void find_point(listPoint *pHead) {
  cout<<"------------------------------search student------------------------------"<<endl;
  listPoint *p;
  p = pHead;

  char name[20];
  cout<<"Please input the student's NAME you want to find: ";
  cin>>name;

  int flag = 0;
  while (p != NULL) {
    if (strcmp(p->information->name, name) == 0) {
      flag = 1;
      print_one_point(p);
      break;
    }
    p = p -> next;
  }
  if (!flag) {
    cout<<"There is no student named "<<name<<endl;
  }
}

void print_all_points(listPoint *pHead) {
  listPoint *p;
  p = pHead;
  if(pHead == NULL){
    cout << "There is nothing to print!"<<endl;
    return;
  }
  cout<<"----------name----------grade----------gender----------birthday----------"<<endl;
  while((p = p->next) != NULL) {
    cout<<"          "<<p->information->name;
    int strname = strlen(p->information->name);
    for (int i=0; i<(14-strname); i++) {
      cout<<" ";
    }
    cout<<p->information->grade;
    int strgrade = strlen(p->information->grade);
    for (int i=0; i<(15-strgrade); i++) {
      cout<<" ";
    }
    cout<<p->information->gender;
    int strgender = strlen(p->information->gender);
    for (int i=0; i<(16-strgender); i++) {
      cout<<" ";
    }
    cout<<p->information->birthDay<<endl;
  }
}

void print_one_point(listPoint *point) {
  listPoint *p;
  p = point;

  cout<<"----------name----------grade----------gender----------birthday----------"<<endl;
  cout<<"          "<<p->information->name;
  int strname = strlen(p->information->name);
  for (int i=0; i<(14-strname); i++) {
    cout<<" ";
  }
  cout<<p->information->grade;
  int strgrade = strlen(p->information->grade);
  for (int i=0; i<(15-strgrade); i++) {
    cout<<" ";
  }
  cout<<p->information->gender;
  int strgender = strlen(p->information->gender);
  for (int i=0; i<(16-strgender); i++) {
    cout<<" ";
  }
  cout<<p->information->birthDay<<endl;
}

void write_to_file(listPoint *pHead){
  listPoint *p;
  p = pHead;
  if(pHead == NULL){
    cout << "There is nothing to write!"<<endl;
    return;
  }

  cout<<"Which file you want to write to: ";
  char fileName[20];
  cin>>fileName;

  FILE *fp = fopen(fileName, "w");
  while((p = p->next) != NULL) {
    fputs("\n",fp);
    fputs(p->information->name,fp);
    fputs(" ",fp);
    fputs(p->information->grade,fp);
    fputs(" ",fp);
    fputs(p->information->gender,fp);
    fputs(" ",fp);
    fputs(p->information->birthDay,fp);
  }
  fclose(fp);
  cout <<"Write to file successful!"<<endl;
}

listPoint *read_from_file(){
  cout<<"which file you want to read: ";
  char fileName[20];
  cin>>fileName;

  FILE *fp;
  if((fp = fopen(fileName, "r")) == NULL){
    cout<<"Cannot open "<<fileName;
    exit(-1);
  }
  char name[20][20];
  char grade[20][20];
  char gender[20][20];
  char birthDay[20][20];
  int num = 0;
  while(!feof(fp)){
    if(fscanf(fp,"%s%s%s%s",name[num],grade[num],gender[num],birthDay[num]) != 4){
      break;
    }
    num++;
  }
  fclose(fp);

  listPoint *head, *normal, *end;
  head = (listPoint*)malloc(sizeof(listPoint));
  if (head == NULL) {
    cout<<"failed!exit system";
    exit(-1);
  }
  head -> information = (student*)malloc(sizeof(student));
  end = head;
  for(int j = 0 ; j < num ; j++){
    normal = (listPoint*)malloc(sizeof(listPoint));
    if (normal == NULL) {
      cout<<"failed!exit system";
      exit(-1);
    }
    normal -> information = (student*)malloc(sizeof(student));
    strcpy(normal->information->name,name[j]);
    strcpy(normal->information->grade,grade[j]);
    strcpy(normal->information->gender,gender[j]);
    strcpy(normal->information->birthDay,birthDay[j]);
    // cout<<name[j];
    end -> next = normal;
    end = normal;
  }
  end -> next = NULL;
  print_all_points(head);
  return head;
}

void show_menu() {
  cout<<endl;
  cout<<"------------------------------manage student------------------------------"<<endl;
  cout<<"                        1 append students' information                    "<<endl;
  cout<<"                        2 delete student's information                    "<<endl;
  cout<<"                        3 search student's information                    "<<endl;
  cout<<"                        4 print students' information                     "<<endl;
  cout<<"                        5 write to file                                   "<<endl;
  cout<<"                        6 read from file                                  "<<endl;
  cout<<"                        7 exit system                                     "<<endl;
  cout<<"--------------------------------------------------------------------------"<<endl;
}
