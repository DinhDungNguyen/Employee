//#include "stdafx.h"
#include<iostream>
#include<string>
#include<math.h>
#include<conio.h>
#include<fstream>
using namespace std;
class person{
	public:
		int id;
		int birthday;
		string name,quequan;
		virtual void input(){
			cout<<"nhap ten: ";
			cin.ignore();
			getline(cin,name);
			cout<<"nhap id: ";
			cin>>id;
			cout<<"nhap que quan:";
			cin.ignore();
			getline(cin,quequan);
			cout<<"nhap nam sinh:";
			cin>>birthday;
			}
		virtual void output(){
			cout<<"NAME: "<<name<<endl;
			cout<<"ID: "<<id<<endl;
			cout<<"QUE QUAN: "<<quequan<<endl;
			cout<<"NAM SINH: "<<birthday<<endl;
		}

	}
	float MaxSalary2(){
		return s2.thuong();
	}
	int tim1(){
		return s2.id;
		}
	void out2(){
		ofstream f;
		f.open("D:\\test1.txt",ios::out);
		f<<"ten: "<<s2.name<<"\nID: "<<s2.id<<"\nnam sinh:"<<s2.birthday<<"\nidkt:"<<s2.idkt<<"\nque quan:"<<s2.quequan<<"\nso ngay tang ca:"<<s2.ntc<<"\nluong:"<<s2.thuong()<<endl;
		f<<"---------------------"<<endl;
		f.close();
}
};
int _tmain(int argc, _TCHAR* argv[]){
	listPerson s3[5];
	int n;
	int n1;
	//cout<<"so nguoi muon nhap: ";
//	cin>>n;
	ofstream f;
	string name1;
	int x;
	int x1=0;
	int max=0;
	int chon;
	do
	{
		system("cls");
		cout << "1. Nhap nv ban hang." << endl;
		cout << "2. Nhap nv ke toan." << endl;
		cout << "0. Exit." << endl;
		cout << "Moi chon: ";
		cin >> chon;
		switch (chon){
		case 1:
			{
				cout<<"so nguoi muon nhap: ";
				cin>>n;
				cout<<"------------NHAP THONG TIN BAN HANG------------"<<endl;
				for(int i=0;i<n;i++){
				s3[i].inputList1();
			cout<<"------------------------"<<endl;
		}
		break;
		}
		case 2:
			{
				cout<<"so nguoi muon nhap: ";
				cin>>n1;
				cout<<"-----------NHAP THONG TIN KE TOAN-------------"<<endl;
				for(int i=0;i<n1;i++){
				s3[i].inputList2();
				cout<<"------------------------"<<endl;
		}
		break;
			}
		case 0:
			{
				break;
			}
		}
	}
	while (chon!=0);
	do
	{
		system("cls");
		cout << "1.xuat nhan vien ban hang." << endl;
		cout << "2.Xuat nhan vien ke toan." << endl;
		cout << "3.tong tien."<<endl;
		cout << "4.tim nhan vien ." << endl;
		cout << "Moi chon: ";
		cin >> chon;
		switch (chon){
		case 1:
			{
				cout<<"--------------------------NHAN VIEN BAN HANG----------------------"<<endl;
				for(int i=0;i<n;i++){
				s3[i].outputList1();
				cout<<"==="<<endl;
				s3[i].display();
				cout<<"\n-----------------"<<endl;
}
				system("pause");
				break;
}
		case 2:
			{
				cout<<"--------------------------NHAN VIEN KE TOAN----------------------"<<endl;
				for(int i=0;i<n1;i++){
				s3[i].outputList2();
				cout<<"==="<<endl;
				s3[i].display1();
				cout<<"\n-----------------"<<endl;
}
				system("pause");
				break;
}
		case 4:
			{
				do{
					system("cls");
					cout<<"1.tim nhan vien ban hang."<<endl;
					cout<<"2.tim nhan vien ke toan."<<endl;
					cout<<"0.exit."<<endl;
					cout<<"moi chon: ";
					cin>>chon;
					switch(chon){
						case 1:
							{
								system("cls");
								cout<<"nhap id tim: ";
								cin>>x;
								cout<<"-------NGUOI CAN TIM LA--------"<<endl;
								for(int i=0;i<n;i++){
								if(x==s3[i].tim()){
								s3[i].outputList1();
								cout<<"===";
								s3[i].display();
								cout<<" "<<endl;
								s3[i].out1();			
				}
								else
								cout<<"chua chieu mo "<<endl;
}
								system("pause");
								break;	
							}
						case 2:
						{
								system("cls");
								cout<<"nhap id tim: ";
								cin>>x;
								cout<<"-------NGUOI CAN TIM LA--------"<<endl;
								for(int i=0;i<n1;i++){
								if(x==s3[i].tim1()){
								s3[i].outputList2();
								cout<<"===";
								s3[i].display1();
								cout<<" "<<endl;
								s3[i].out2();		
				}
								else
								cout<<"chua chieu mo "<<endl;
}
								system("pause");
								break;	
							}
						case 0:
						{
							break;
							}	
					}
				}while(chon!=0);			
				system("pause");
				break;			
}
		case 3:
			{
								system("cls");
								for(int i=0;i<n;i++){
								x1=x1+s3[i].MaxSalary1();
					}
								for(int i=0;i<n1;i++){
								x1=x1+s3[i].MaxSalary2();
					}
								cout<<"tong tien phai tra la: "<<x1<<endl;
								system("pause");
								break;
			}
		}
	}while (chon!=0);
}
