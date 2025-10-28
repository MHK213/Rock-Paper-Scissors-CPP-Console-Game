#include <iostream>
#include <cstdlib>
#include <ctime>  

using namespace std;

// Enum for Difficulty Levels in the game
enum enDifficultyLevel { Easy = 1, Hard = 2 };

// Enum for player's choice in the game
enum enGameChoice { Rock = 1, Paper = 2, Scissors = 3 };

// Enum for round/game winner
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

// Structure to hold data for each round
struct stRoundInfo {
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice LastPlayer1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
    enDifficultyLevel DifficultyLevel;
};

// Structure to summarize results after all rounds
struct stGameResults {
    short GameRounds = 0;
    short Player1WonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
    string LevelName = "";
};

// Generates a random number between From and To
short RandomNumber(short From, short To) {
    short RandNum = rand() % (To - From + 1) + From;

    return RandNum;
}

// Reads difficulty level from user
enDifficultyLevel ReadDifficultyLevel() {
    short DifficultyLevel = 1;

    do {
        cout << "Enter Difficulty Level [1] Easy, [2] Hard ? ";
        cin >> DifficultyLevel;
    } while (DifficultyLevel < 0 || DifficultyLevel > 2);

    return (enDifficultyLevel)DifficultyLevel;
}

// Reads the number of game rounds from the user
short ReadHowManyRounds() {
    short GameRounds = 1;

    do {
        cout << "Enter How Many Rounds 1 to 10 ? \n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);

    return GameRounds;
}

// Reads the player's choice: Rock, Paper, or Scissors
enGameChoice ReadPlayer1Choice() {
    short PlayerChoice = 1;

    do {
        cout << "\nYour Choice: [1]:Rock, [2]:Paper, [3]:Scissors? ";
        cin >> PlayerChoice;
    } while (PlayerChoice < 1 || PlayerChoice > 3);

    return enGameChoice(PlayerChoice);
}

// Generates computer's choice randomly
enGameChoice GetComputerChoice(enDifficultyLevel DifficultyLevel, short RoundNumber, enGameChoice Player1Choice) {
    switch (DifficultyLevel) {
    case enDifficultyLevel::Easy:
        return enGameChoice(RandomNumber(1, 3));
    case enDifficultyLevel::Hard:
        if (RoundNumber == 1)
            return enGameChoice(RandomNumber(1, 3));
        else {
            if (Player1Choice == Rock)
                return enGameChoice(RandomNumber(2, 3));
            else if (Player1Choice == Scissors)
                return enGameChoice(RandomNumber(1, 2));
        }
    default:
        return enGameChoice(RandomNumber(1, 3));
    }
}

string LevelName(enDifficultyLevel DifficultyLevel) {
    switch (DifficultyLevel) {
    case enDifficultyLevel::Easy:
        return "Easy";
    case enDifficultyLevel::Hard:
        return "Hard";
    }
}

// Returns a string version of the enum choice
string ChoiceName(enGameChoice Choice) {
    string arrGameChoice[3] = { "Rock", "Paper", "Scissors" };

    return arrGameChoice[Choice - 1];
}

// Determines the winner of a round based on choices
enWinner HowWonTheRound(stRoundInfo RoundInfo) {
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;
    switch (RoundInfo.Player1Choice) {
    case enGameChoice::Rock:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors) {
            return enWinner::Player1;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Rock) {
            return enWinner::Player1;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper) {
            return enWinner::Player1;
        }
        break;
    }

    return enWinner::Computer;
}

// Converts winner enum to its name
string WinnerName(enWinner Winner) {
    switch (Winner) {
    case enWinner::Player1:
        return "Player1";
    case enWinner::Computer:
        return "Computer";
    case enWinner::Draw:
        return "No Winner";
    default:
        return "Unknown";
    }
}

// Sets console color based on winner
void setWinnerScreenColor(enWinner Winner) {
    switch (Winner) {
    case enWinner::Player1:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    case enWinner::Draw:
        system("color 6F");
        break;
    }
}

// Prints result of a single round
void PrintRoundResult(stRoundInfo RoundInfo) {
    cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1  Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]" << endl;
    cout << "__________________________________\n" << endl;

    setWinnerScreenColor(RoundInfo.Winner);
}

// Determines overall winner of the game
enWinner HowWonTheGame(short PlayerWonTimes, short ComputerWonTimes) {
    if (PlayerWonTimes > ComputerWonTimes)
        return enWinner::Player1;
    else if (PlayerWonTimes < ComputerWonTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

// Prepares final game summary and returns result struct
stGameResults FillGameResults(short HowManyRounds, short PlayerWonTimes, short ComputerWonTimes, short DrawTimes, string LevelName) {
    stGameResults GameResults;

    GameResults.GameRounds = HowManyRounds;
    GameResults.LevelName = LevelName;
    GameResults.Player1WonTimes = PlayerWonTimes;
    GameResults.ComputerWonTimes = ComputerWonTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = HowWonTheGame(PlayerWonTimes, ComputerWonTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

// Clears and resets the screen to default state
void ResetScreen() {
    system("cls");
    system("color 0F");
}

// Plays one full game session with multiple rounds
stGameResults PlayGame(short HowManyRounds) {
    stRoundInfo RoundInfo;
    short Player1WonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;

    RoundInfo.DifficultyLevel = ReadDifficultyLevel();

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
        cout << "\nRound [" << GameRound << "] begins: \n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice(RoundInfo.DifficultyLevel, GameRound, RoundInfo.LastPlayer1Choice);
        RoundInfo.LastPlayer1Choice = RoundInfo.Player1Choice;
        RoundInfo.Winner = HowWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Computer)
            ComputerWonTimes++;
        else if (RoundInfo.Winner == enWinner::Player1)
            Player1WonTimes++;
        else
            DrawTimes++;

        PrintRoundResult(RoundInfo);
    }

    return FillGameResults(HowManyRounds, Player1WonTimes, ComputerWonTimes, DrawTimes, LevelName(RoundInfo.DifficultyLevel));
}

// Returns a tab for formatting
string Tab() {
    return "\t\t";
}

// Shows the "Game Over" message
void ShowGameOverScreen() {
    cout << Tab() << "__________________________________________________________\n\n";
    cout << Tab() << "                     +++ Game Over +++\n";
    cout << Tab() << "__________________________________________________________\n\n";
}

// Displays final statistics and summary after all rounds
void ShowFinalGameScreen(stGameResults GameResults) {

    cout << Tab() << "_____________________ [Game Results] _____________________\n\n";
    cout << Tab() << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tab() << "Difficulty Level   : " << GameResults.LevelName << endl;
    cout << Tab() << "Player1 Won times  : " << GameResults.Player1WonTimes << endl;
    cout << Tab() << "Computer Won times : " << GameResults.ComputerWonTimes << endl;
    cout << Tab() << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tab() << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tab() << "__________________________________________________________\n\n";

    setWinnerScreenColor(GameResults.GameWinner);
}

// Controls the full game loop and replay option
void StartGame() {

    char PlayAgain = 'Y';

    do {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameScreen(GameResults);

        cout << endl << Tab() << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}