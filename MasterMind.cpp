#include "MasterMind.h"

int main()
{
	//Variable Initialization
	int counter[4];
	counter[0] = R; counter[1] = G; counter[2] = B; counter[3] = O; //initial guess, used to iterate through combinations
	bool solved = false;
	vector<MM_Guess> prevGuesses; //stores all previous guesses
	MM_Guess curGuess; //stores info for current guess
	MM_Guess correctAnswer = ReadColours(); //Get input from the user (the solution), used to verify guesses
	
	while (!solved)
	{
		curGuess.SetGuess(counter);
		
		CheckGuess(curGuess, correctAnswer);
		prevGuesses.push_back(curGuess);
		
		if (curGuess.Correct())
			solved = true;
		else
			solved = !GetNextGuess(counter, prevGuesses);
	}
	
	PrintGuesses(prevGuesses);
	
	system("PAUSE");
	
	return 0;
}

MM_Guess ReadColours()
{
	char c[4];
	int colours[4];
	MM_Guess ret;
	cout << "Input 4 different colours (R G B O Y P W):\n";
	cin >> c[0] >> c[1] >> c[2] >> c[3];
	if (c[0] != c[1] && c[0] != c[2] && c[0] != c[3] && c[1] != c[2] && c[1] != c[3] && c[2] != c[3])
	{
		for (int i = 0; i < 4; i++)
		{
			switch (c[i])
			{
				case 'R': colours[i] = R; break;
				case 'G': colours[i] = G; break;
				case 'B': colours[i] = B; break;
				case 'O': colours[i] = O; break;
				case 'Y': colours[i] = Y; break;
				case 'P': colours[i] = P; break;
				case 'W': colours[i] = W; break;
				default: return ReadColours();
			}
		}
		ret.SetGuess(colours);
		ret.SetResult(4, 0);
		return ret;
	}
	else
		return ReadColours();
}
	
void CheckGuess(MM_Guess& current, MM_Guess correct)
{
	int nCorrect = 0, nWrong = 0;
	int *guess = current.GetGuess(), *answer = correct.GetGuess();
	for (int i = 0; i < 4; i++)
	{
		if (guess[i] == answer[i])
			nCorrect++;
		else
		{
			for (int j = 0; j < 4; j++)
			{
				if (j == i)
					continue;
				else if (guess[i] == answer[j])
					nWrong++;
			}
		}
	}
	current.SetResult(nCorrect, nWrong);
}

bool GetNextGuess(int* colours, vector<MM_Guess> prevGuesses)
{
	bool done = false;
	while (!done)
	{
		//iterate colours
		colours[3] = (colours[3] + 1) % 7;
		if (colours[3] == 0) //addition carry over
		{
			colours[2] = (colours[2] + 1) % 7;
			if (colours[2] == 0)
			{
				colours[1] = (colours[1] + 1) % 7;
				if (colours[1] == 0)
				{
					colours[0] = (colours[0] + 1) % 7;
					if (colours[0] == 0) //cycled through all possible combinations
						return false;
				}
			}
		}
		
		//check for duplicate colours
		if (colours[0] != colours[1] && colours[0] != colours[2] && colours[0] != colours[3] && 
			colours[1] != colours[2] && colours[1] != colours[3] && colours[2] != colours[3])
		{
			//compare with results from previous guesses
			int correctSpot, wrongSpot, *prevColours, i;
			for (i = 0; i < prevGuesses.size(); i++)
			{
				//Get previous information
				prevGuesses[i].GetResult(correctSpot, wrongSpot);
				prevColours = prevGuesses[i].GetGuess();
				
				for (int j = 0; j < 4; j++)
				{
					if (colours[j] == prevColours[j])
						correctSpot--;
					else
					{
						for (int k = 0; k < 4; k++)
						{
							if (k == j)
								continue;
							else if (colours[j] == prevColours[k])
							{
								wrongSpot--;
								break;
							}
						}
					}
				}
				if (correctSpot < 0 || wrongSpot < 0)
					break;
			}
			if (i == prevGuesses.size())
				done = true;
		}
	}
	return true;
}

void PrintGuesses(vector<MM_Guess> prevGuesses)
{
	int* guess, correctSpot, wrongSpot;
	for (size_t i = 0; i < prevGuesses.size(); i++)
	{
		guess = prevGuesses[i].GetGuess();
		for (int j = 0; j < 4; j++)
		{
			switch (guess[j])
			{
				case R: cout << "R "; break;
				case G: cout << "G "; break;
				case B: cout << "B "; break;
				case O: cout << "O "; break;
				case Y: cout << "Y "; break;
				case P: cout << "P "; break;
				case W: cout << "W "; break;
				default: cout << "ERROR "; break;
			}
		}
		prevGuesses[i].GetResult(correctSpot, wrongSpot);
		cout << "Correct: " << correctSpot << "  Wrong Spot: " << wrongSpot << endl;
	}
}
	
	

