// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Client.h"
#include "afxsock.h"
#include<string>
#include <stdio.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;



using namespace std;

struct Question {
	string question;
	string choice_A;
	string choice_B;
	string choice_C;
	string choice_D;
	string answer;
};

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CSocket client;
		char sAdd[1000];
		unsigned int port = 1234; //Cung port voi server
		AfxSocketInit(NULL);

		//1. Tao socket
		client.Create();

		// Nhap dic chi IP cua server
		printf("\n Nhap dia chi IP cua server: ");
		fgets(sAdd, 1000, stdin);
		
		if (client.Connect(CA2W(sAdd),port))
		{
			printf("\n Client da ket noi toi server");
			//Nhan tu server, cho biet day la client thu may
			int id;
			client.Receive((char*)&id,sizeof(id),0);
			printf("\nDay la client thu %d\n",id+1);

			// Receive the number of questions
			int num_quest;
			client.Receive((char*)&num_quest, sizeof(int), 0);
			cout << "There are " << num_quest << " questions!" << endl;
  
			
			for (int q = 0; q < num_quest; q++) {
				int MsgSize;
				char *temp;

				client.Receive((char*)&MsgSize, sizeof(int), 0);
				temp = new char[MsgSize + 1];
				client.Receive((char*)temp, MsgSize, 0);
				temp[MsgSize] = '\0';
				cout << temp << endl;
				delete[] temp;
				
			

				client.Receive((char*)&MsgSize, sizeof(int), 0);
				temp = new char[MsgSize + 1];
				client.Receive((char*)temp, MsgSize, 0);
				temp[MsgSize] = '\0';
				cout << "A. " << temp << endl;
				delete[] temp;

				client.Receive((char*)&MsgSize, sizeof(int), 0);
				temp = new char[MsgSize + 1];
				client.Receive((char*)temp, MsgSize, 0);
				temp[MsgSize] = '\0';
				cout << "B. " << temp << endl;
				delete[] temp;

				client.Receive((char*)&MsgSize, sizeof(int), 0);
				temp = new char[MsgSize + 1];
				client.Receive((char*)temp, MsgSize, 0);
				temp[MsgSize] = '\0';
				cout << "C. " << temp << endl;
				delete[] temp;

				client.Receive((char*)&MsgSize, sizeof(int), 0);
				temp = new char[MsgSize + 1];
				client.Receive((char*)temp, MsgSize, 0);
				temp[MsgSize] = '\0';
				cout << "D. " << temp << endl; 
				delete[] temp;

				// Send answer to server
				string ans;
				cout << "Enter your answer: ";
				getline(cin, ans);
				client.Send((char*)&ans, sizeof(ans), 0);

				client.Receive((char*)&MsgSize, sizeof(int), 0);
				temp = new char[MsgSize + 1];
				client.Receive((char*)temp, MsgSize, 0);
				temp[MsgSize] = '\0';
				cout << "Result: " << temp << endl;
				delete[] temp;

			}

			
			
			
			

			//srand( (unsigned)time( NULL ) );
			//int numbers[2];
			//numbers[0]=(int)(((float)rand()/RAND_MAX)*10);
			//numbers[1]=(int)(((float)rand()/RAND_MAX)*10);

			////Gui so thu 1 cho server
			//printf("Gui so thu 1, gia tri %d cho server\n",numbers[0]);
			//client.Send((char*)&numbers[0],sizeof(int),0);
			////Gui so thu 2 cho server
			//printf("Gui so thu 2, gia tri %d cho server\n",numbers[1]);
			//client.Send((char*)&numbers[1],sizeof(int),0);
			////Nhan ket qua tra ve tu server
			//int count;
			//client.Receive((char*)&count,sizeof(count),0);
			//printf("Tong so luong cac so nguyen to TAT CA cac client gui len:%d \n",count);
			client.Close();
		}
		else {
			printf("Khong connect duoc toi server....");
		}
			
		
	}
	getchar();
	return nRetCode;
}
