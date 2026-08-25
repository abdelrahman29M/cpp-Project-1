
#include <iostream>
#include<cstdlib>
#include<ctime>

using namespace std;


enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1 , Computer = 2 , Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults
{
	short GameRound = 0;
	short Player1WinTime = 0;
	short ComputerWinTime = 0;
	short DrawTime = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { " Player1 " , " Computer " , " NoWinner (Draw) " };
	return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	
	}

	return enWinner::Player1;
}

string ChoiceName(enGameChoice Choice)
{
	string arrGameChoices[3] = { " Stone " , " Paper " , " Scissors " };
	return arrGameChoices[Choice - 1];
}

void SetWinnerScreenColors(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");          //turn screen to GREEN
		break;

	case enWinner::Computer:         //turn screen to RED 
		system("color 4F");
		cout << "\a";
		break;

	default:
		system("color 6F");          //turn screen to YELLOW
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << " \n________________________Round[" << RoundInfo.RoundNumber << "]____________________________\n\n";
	cout << " Player1 Choice : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << " Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << " Round Winner : [" << RoundInfo.WinnerName << "]\n";
	cout << "________________________________________________________________________________________________\n" << endl;

	SetWinnerScreenColors(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short Player1WinTime, short ComputerWinTime)
{
	if (Player1WinTime > ComputerWinTime)
		return enWinner::Player1;
	else if (ComputerWinTime > Player1WinTime)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResults FillGameResults(int GameRound, short Player1WinTime, short ComputerWinTime, short DrawTime)
{
	stGameResults GameResults;

	GameResults.GameRound = GameRound;
	GameResults.Player1WinTime = Player1WinTime;
	GameResults.ComputerWinTime = ComputerWinTime;
	GameResults.DrawTime = DrawTime;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTime, ComputerWinTime);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;
	do
	{
		cout << "\n Your Choice : [1]:Stone, [2]:Paper, [3]:Scissors ?";
		cin >> Choice;
	} while (Choice < 1 || Choice>3);

	return enGameChoice(Choice);
}

enGameChoice GetComputerChoice()
{
	return enGameChoice(RandomNumber(1, 3));
}

stGameResults PlayGame(short HowManyRound)
{
	stRoundInfo RoundInfo;
	short Player1WinTime = 0, ComputerWinTime = 0, DrawTime = 0;
	
	for (int GameRound = 1;GameRound <= HowManyRound;GameRound++)
	{
		cout << "\n Round [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		//Increase Win/Draw Counters

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTime++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTime++;
		else
			DrawTime++;

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(HowManyRound, Player1WinTime, ComputerWinTime, DrawTime);
}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1;i < NumberOfTabs;i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "___________________________________________________________\n\n";
	cout << Tabs(2) << "                 +++ G a m e O v e r  +++                 \n\n";
	cout << Tabs(2) << "___________________________________________________________\n\n";


}

void ShowFinalGameResults(stGameResults GameResults)
	{
		cout << Tabs(2) << "_____________________________[GameResults]_______________________________\n\n";
		cout << Tabs(2) << " Game Rounds   : " << GameResults.GameRound << endl;
		cout << Tabs(2) << " Player1 Won Times :  " << GameResults.Player1WinTime << endl;
		cout << Tabs(2) << " Computer Won Times  : " << GameResults.ComputerWinTime << endl;
		cout << Tabs(2) << "Draw Times :  " << GameResults.DrawTime << endl;
		cout << Tabs(2) << " Final Winner   : " << GameResults.WinnerName << endl;
		cout << "_______________________________________________________________________________________________\n\n";


		SetWinnerScreenColors(GameResults.GameWinner);
	}

short ReadHowManyRounds()
{
	short GameRounds = 1;
	do
	{
		cout << " How Many Rounds 1 to 10 ? \n";
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds>10);

	return GameRounds;
}

void ResetScreen()
{
	system("cls");                  //clean screen
	system("color 0F");                     

}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << " Do You Want to play again?  Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();


	return 0;


}
