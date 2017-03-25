/*
The Game Logic (No View Code or Direct User Interation)
The Game is a simple guess the word game based on mastermind
*/

#pragma once
#include <string>

//To make the syntax Unreal Friendly
using Fstring = std::string;
using int32 = int;

enum class EGuessStatus
{
	invalid_status,
	ok,
	not_isogram,
	invalid_length,
	not_lowercase
};


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;

};


class FBullCowGame
{
public:
	FBullCowGame(); // constructor
	
	int32	GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus IsGuessValid(Fstring) const;

	void Reset(); 
	FBullCowCount SubmitValidGuess(Fstring);

private:
	//See Constructor for Initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	Fstring MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(Fstring) const;
	bool IsLowercase(Fstring) const;
	Fstring HiddenWordList[24] =
	{ "myth","duck","verb","gasp","jinx","wolf","black","fight","jumpy","drown","plane","stumped","flyback","whoring",
		"mucking","batfowl","zephyrs","jordans","phlegmy","fuckwit","overply","dumbing","thwacks","planet" };
};