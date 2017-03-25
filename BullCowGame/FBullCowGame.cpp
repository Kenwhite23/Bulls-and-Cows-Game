#include "FBullCowGame.h"
#include <map>
#include <ctype.h>
#include <time.h>
#define Tmap std::map


FBullCowGame::FBullCowGame() { Reset(); }


int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }


bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


int32 FBullCowGame::GetMaxTries() const 
{
	Tmap<int32, int32> WordLengthToMaxTries { {3,5},{4,7},{5,10},{6,16},{7,20},{8,25} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

EGuessStatus FBullCowGame::IsGuessValid(Fstring Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::not_isogram;
	}
	else if (!IsLowercase(Guess)) // TODO write function If the guess isnt lower case
	{
		return EGuessStatus::not_lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) //If the guess length is wrong
	{
		return EGuessStatus::invalid_length;
	}
	else
	{
		return EGuessStatus::ok;
	}
}


void FBullCowGame::Reset()
{
	
	constexpr int32 Max_Tries = 8;
	MyMaxTries = Max_Tries;

	srand(time(NULL));
	const Fstring Hidden_Word = HiddenWordList[rand() % 24];
	MyHiddenWord = Hidden_Word;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}



FBullCowCount FBullCowGame::SubmitValidGuess(Fstring Guess) //counts bulls and cows; and increases try # assuming Valid Guess
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			//If they match
			if (Guess[MHWChar] == MyHiddenWord[GChar])
			{
				//Incriment bulls if their in the same place
				if (MHWChar==GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(Fstring word) const
{
	//treat 0 and 1 letter words as isograms
	if (word.length() <= 1) { return true; }
	
	Tmap <char, bool> LetterSeen;
	for (auto Letter : word)//For all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]){return false;} 
		else { LetterSeen[Letter] = true; }
	}

	return true;//for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(Fstring word) const
{
	for (auto letter : word)
	{
		if (islower(letter)) { return true; }
		else {return false;}
	}

	return false;// For example in cases where /0 is entered
}
