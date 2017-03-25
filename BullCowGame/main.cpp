/* This is the Console Executable, That makes use of the BullCow Class. 
This acts as the view in a MVC pattern, and is responsible for all User interactions.
For Game Logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//To make Syntax Unreal Friendly
using Ftext= std::string;
using int32 = int;

//variable that is globally used too lazy to clean up and make private.
Ftext GUESS = "";

//Entrypoints
Ftext GetValidGuess();
void PlayLoop();

FBullCowGame BCGame; //instantiate a new game, which we reuse across plays

int main() //Main Class
{
	PlayLoop();
	return 0;//exit application
}


void PlayGame() //Plays a single game to completion
{
	
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		GetValidGuess();

		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(GUESS);
	
		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << " Cows: " << BullCowCount.Cows << "\n\n";
	}
	
	return;
}

void PrintGameSummary() //prints win lose message
{
	int32 MaxTries = BCGame.GetMaxTries();
	if (!BCGame.IsGameWon() && BCGame.GetCurrentTry() >= MaxTries)
	{
		std::cout << "You lost! Better Luck Next Time!\n\n";
			return;
	}
	else
	{
		std::cout << "Congratulations! You Win!\n\n";
		return;
	}
}

void PrintIntro() 
{
	BCGame.Reset();
	std::cout << "                      =======================================\n"; 
	std::cout << "    ,           ,     |      Welcome To Bulls and Cows      |\n";
	std::cout << "   /             \\    |    ***************************      |\n";
	std::cout << "  ((__-^^-,-^^-__))   |                                     |\n";
	std::cout << "   `-_---' `---_-'    |                                     |\n";
	std::cout << "    <__|o` 'o|__>     |     ***************************     |\n";
	std::cout << "       \\  `  /        |     *  A C++ Learning Project *     |\n";
	std::cout << "        ): :(         |     *  Made by Kenneth White  *     |\n";
	std::cout << "        :o_o:         |     ***************************     |\n";
	std::cout << "        ' - '         |                                     |\n";
	std::cout << "                      =======================================\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	return;
}

Ftext GetValidGuess() //get valid guess from player
{
	EGuessStatus Status = EGuessStatus::invalid_status;
	do
	{

		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, GUESS);

		Status = BCGame.IsGuessValid(GUESS);
		switch (Status)
		{
		case EGuessStatus::invalid_length:
			std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::not_isogram:
			std::cout << "Please Enter a word without repeating letters. \n";
			break;
		case EGuessStatus::not_lowercase:
			std::cout << "Please Enter All lowercase Letters. \n";
		default:
			break;
		}
	} while (Status != EGuessStatus::ok );
	return GUESS;
}

bool bPlayAgain() //Replay prompt logic
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	Ftext response;
	std::getline(std::cin, response);
	return (response[0] == 'y' || response[0] == 'Y');
}

void PlayLoop() //Main Game Loop, allows game to be played to completion.
{
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	}

	while (bPlayAgain() == true);
	return;
}
