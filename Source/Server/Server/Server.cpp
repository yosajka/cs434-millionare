// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Server.h"
#include "afxsock.h"
#include "math.h"
#include<fstream>
#include<string>

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

void getQuestions(Question *data, ifstream &fin, int total_quest) {

	for (int i = 0; i < total_quest; i++) {
		getline(fin, data[i].question, '\n');
		getline(fin, data[i].choice_A, '\n');
		getline(fin, data[i].choice_B, '\n');
		getline(fin, data[i].choice_C, '\n');
		getline(fin, data[i].choice_D, '\n');
		getline(fin, data[i].answer, '\n');
	}
}


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	//Create the question database
	ifstream fin("questions.txt");
	int num_quest = 15;
	int total_quest = 30;
	Question *data;
	if (!fin.is_open()) {
		return -1;
	}
	else {
		data = new Question[total_quest];
		getQuestions(data, fin, total_quest);
	}


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
		CSocket server, s;
		unsigned int port = 1234;
		int i;
		AfxSocketInit(NULL);

		server.Create(port);
		server.Listen(5);

		//Nhap so luong client
		int num_client;
		cout << "Enter number of clients: ";
		cin >> num_client;
		cout << "Listening..." << endl;
		//Tao mang chua cac socket client
		CSocket * sockClients = new CSocket[num_client];
		for (i = 0; i < num_client; i++) {
			server.Accept(sockClients[i]);
			cout << "Client " << i + 1 << "/" << num_client << " accepted" << endl;
			//printf("Da tiep nhan client %d/%d\n",i+1,num_client);

			//Bao cho client biet minh la client thu may
			sockClients[i].Send((char*)&i, sizeof(int), 0);
			//Send number of question to client
			sockClients[i].Send((char*)&num_quest, sizeof(int), 0);
		}

		
		int isStart = 1;
		if (isStart) {
			cout << "Starting the game..." << endl;
		}

		

		// Now the game starts
		// There are 30 questions in total
		// A player has 30s to answer
		// If wrong, the player is eliminated
		// If right, the player proceeds to the next question
		//


		for (int q = 0; q < num_quest; q++) {
			cout << "Question " << q + 1 << ": " << data[q].question << endl;
			cout << "A. " << data[q].choice_A << endl;
			cout << "B. " << data[q].choice_B << endl;
			cout << "C. " << data[q].choice_C << endl;
			cout << "D. " << data[q].choice_D << endl;
			
			for (i = 0; i < num_client; i++) {
				/*sockClients[i].Send((Question*)&data[q], sizeof(data[q]), 0);
				cout << "Question sent" << endl;*/
				sockClients[i].Send((char*)&data[q].question, sizeof(data[q].question), 0);
				//sockClients[i].Send(data[i].question.c_str(), data[i].question.length());
				//sockClients[i].Send((char*)&data[q].choice_A, sizeof(data[q].choice_A), 0);
				//sockClients[i].Send((char*)&data[q].choice_B, sizeof(data[q].choice_B), 0);
				//sockClients[i].Send((char*)&data[q].choice_C, sizeof(data[q].choice_C), 0);
				//sockClients[i].Send((char*)&data[q].choice_D, sizeof(data[q].choice_D), 0);
				//sockClients[i].Send((char*)&data[q].answer, sizeof(data[q].answer), 0);
			}

			// After 30s
			string *player_answers = new string[num_client];
			for (i = 0; i < num_client; i++) {
				sockClients[i].Receive((char*)&player_answers[i], sizeof(string), 0);
				if ( player_answers[i] != data[q].answer) {
					cout << "Player " << i << " got the wrong answer!" << endl;
					sockClients[i].Close();
					num_client -= 1;
				}
				else {
					cout << "Player " << i << " got the right answer!" << endl;
				}
			}
			if (num_client < 1)
				break;

		}
		


		//	//Moi client se gui 2 so, tuan tu tung client
		//	//Tao mang chua cac so client gui
		//	int * numbers = new int[num_client*2];

		//	//Lan 1
		//	for (i = 0; i < num_client; i++)
		//	{
		//		sockClients[i].Receive((char*)&numbers[i],sizeof(int),0);
		//		printf("Da nhan tu client %d lan 1, so %d\n",i+1,numbers[i]);
		//	}

		//	//Lan 2
		//	for (i=0;i<num_client;i++){
		//		sockClients[i].Receive((char*)&numbers[i+num_client],sizeof(int),0);
		//		printf("Da nhan tu client %d lan 2, so %d\n",i+1,numbers[i+num_client]);
		//	}

		//	//Den so luong cac so nguyen to
		//	int count=0;
		//	for (i=0;i<num_client*2;i++){
		//		if (isPrime(numbers[i])){
		//			count++;
		//		}
		//	}
		//	printf("Danh sach cac so ma clients da gui:");
		//	for (i=0;i<num_client*2;i++){
		//		printf("%d;",numbers[i]);
		//	}
		//	printf("\r\nSo luong cac so nguyen to TAT CA client gui den %d\n",count);
		//	//Gui ket qua cho tung client
		//	for (i=0;i<num_client;i++){
		//		printf("Gui ket qua cho client %d\n",i+1);
		//		sockClients[i].Send((char*)&count,sizeof(int),0);
		//		//Ngat ket noi voi client do
		//		//sockClients[i].ShutDown(2); //Ngat ca chieu Gui va Nhan
		//		sockClients[i].Close();
		//	}
		//	getchar();
		//	server.Close();
		//}
		getchar();
		return nRetCode;
	}
}
