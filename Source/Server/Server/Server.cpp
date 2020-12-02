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

bool nameCompare(char *a, char* b) {
	if (strlen(a) != strlen(b)) return false;
	for (int i = 0;i < strlen(a);++i)
	{
		if (toupper(a[i]) != toupper(b[i])) return false;
	}
	return true;
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

		//ok
		bool *ok = new bool[num_client];
		for (int q = 0;q < num_client;++q)
		{
			ok[q] = true;
		}

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


		for (int q = 0; q < num_quest; q++){
			cout << "Question " << q + 1 << ": " << data[q].question << endl;
			cout << "A. " << data[q].choice_A << endl;
			cout << "B. " << data[q].choice_B << endl;
			cout << "C. " << data[q].choice_C << endl;
			cout << "D. " << data[q].choice_D << endl;
			
			for (i = 0; i < num_client; i++) {
				if (!ok[i]) continue;
				else
				{
					int MsgSize;
					//Question
					MsgSize = data[q].question.length();
					char *Msg = new char[MsgSize + 1];
					strcpy(Msg, data[q].question.c_str());
					// Gui di do dai thong diep de Server biet duoc do dai nay
					sockClients[i].Send(&MsgSize, sizeof(MsgSize), 0);
					// Gui di thong diep voi do dai la MsgSize
					sockClients[i].Send(Msg, MsgSize, 0);

					delete[] Msg;
					//A
					MsgSize = data[q].choice_A.length();
					Msg = new char[MsgSize + 1];
					strcpy(Msg, data[q].choice_A.c_str());
					// Gui di do dai thong diep de Server biet duoc do dai nay
					sockClients[i].Send(&MsgSize, sizeof(MsgSize), 0);
					// Gui di thong diep voi do dai la MsgSize
					sockClients[i].Send(Msg, MsgSize, 0);
					delete[] Msg;
					//B
					MsgSize = data[q].choice_B.length();
					Msg = new char[MsgSize + 1];
					strcpy(Msg, data[q].choice_B.c_str());
					// Gui di do dai thong diep de Server biet duoc do dai nay
					sockClients[i].Send(&MsgSize, sizeof(MsgSize), 0);
					// Gui di thong diep voi do dai la MsgSize
					sockClients[i].Send(Msg, MsgSize, 0);
					//C
					MsgSize = data[q].choice_C.length();
					Msg = new char[MsgSize + 1];
					strcpy(Msg, data[q].choice_C.c_str());
					// Gui di do dai thong diep de Server biet duoc do dai nay
					sockClients[i].Send(&MsgSize, sizeof(MsgSize), 0);
					// Gui di thong diep voi do dai la MsgSize
					sockClients[i].Send(Msg, MsgSize, 0);
					//D
					MsgSize = data[q].choice_D.length();
					Msg = new char[MsgSize + 1];
					strcpy(Msg, data[q].choice_D.c_str());
					// Gui di do dai thong diep de Server biet duoc do dai nay
					sockClients[i].Send(&MsgSize, sizeof(MsgSize), 0);
					// Gui di thong diep voi do dai la MsgSize
					sockClients[i].Send(Msg, MsgSize, 0);

				}
			}
			// After 30s
			string *player_answers = new string[num_client];
			for (i = 0; i < num_client; i++) {
				sockClients[i].Receive((char*)&player_answers[i], sizeof(string), 0);
				if ( player_answers[i] != data[q].answer) {
					cout << "Player " << i << " got the wrong answer!" << endl;
					ok[i] = false;
					char c[10] = "Incorrect";
					int tm = 10;
					sockClients[i].Send(&tm, sizeof(tm), 0);
					sockClients[i].Send(c, tm, 0);
				}
				else {
					cout << "Player " << i << " got the right answer!" << endl;
					char c[8] = "Correct";
					int tm = 8;
					sockClients[i].Send(&tm, sizeof(tm), 0);
					sockClients[i].Send(c, tm, 0);
				}
			}
			int dem = 0, winner;
			for (int k = 0;k < num_client;k++) {
				if (ok[k]) {
					dem++;
					winner = k;
					}
				}
			if (dem == 1) {
				cout << "Game Over!!! Player " << winner << " wins!!" <<endl;
				goto EXIT;
			}
			if (dem == 0) {
				cout << "Game Over!!! No one wins!!" <<endl;
				goto EXIT;
			}
		}
		cout << "Winners: "<<endl;
		for (int k = 0;k < num_client;k++) {
			if (ok[k]) cout << "- Player " << k << endl;
		}
	EXIT:
		system("pause");
		getchar();
		return nRetCode;
	}
}
