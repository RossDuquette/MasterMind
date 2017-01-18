#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

typedef enum eColour
{
	R,
	G,
	B,
	O,
	Y,
	P,
	W
} eColour;

class MM_Guess
{
	private:
		int Colours[4];
		int nCorrect;
		int nWrong;
		
	public:
		MM_Guess();
		void SetGuess(int* colours);
		void SetResult(int nCorrectSpot, int nWrongSpot);
		int* GetGuess();
		void GetResult(int& nCorrectSpot, int& nWrongSpot);
		bool Correct();	
};

MM_Guess ReadColours();
void CheckGuess(MM_Guess& current, MM_Guess correct);
bool GetNextGuess(int* colours, vector<MM_Guess> prevGuesses);
void PrintGuesses(vector<MM_Guess> prevGuesses);

MM_Guess::MM_Guess()
{
	nCorrect = 0;
	nWrong = 0;
	Colours[0] = -1;
	Colours[1] = -1;
	Colours[2] = -1;
	Colours[3] = -1;
}

void MM_Guess::SetGuess(int* colours)
{
	memcpy(Colours, colours, sizeof(int)*4);
}

void MM_Guess::SetResult(int nCorrectSpot, int nWrongSpot)
{
	nCorrect = nCorrectSpot;
	nWrong = nWrongSpot;
}

int* MM_Guess::GetGuess()
{
	return Colours;
}

void MM_Guess::GetResult(int& nCorrectSpot, int& nWrongSpot)
{
	nCorrectSpot = nCorrect;
	nWrongSpot = nWrong;
}

bool MM_Guess::Correct()
{
	return (nCorrect == 4);
}
