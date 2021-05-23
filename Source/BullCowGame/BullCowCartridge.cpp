// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Setting up Game
    SetupGame();

    //PrintLine(TEXT("The Hidden Word is %s. \nIt is %i characters long."), *HiddenWord, HiddenWord.Len());// Dont need Fstring::Printf because its already declared in cartridge file
    // PrintLine(FString::Printf(TEXT("The Hidden Word is %s"), *HiddenWord)); // Debug Line
    
}

void UBullCowCartridge::OnInput(const FString & Input) // When the player hits enter
{
    if (bGameOver) { // If the game is over, ClearScreen() and SetupGame() again
            ClearScreen();
            SetupGame();
            
            }   
            else { // else Checking the player guess
                CheckPlayerGuess(Input);         
            }
}

void UBullCowCartridge::SetupGame(){
      //Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cow!"));
    
    HiddenWord = TEXT("heros ");  // Set the hidden word
    Lives = HiddenWord.Len();//Set Lives
    bGameOver = false;

    PrintLine(TEXT("You have %i lives"), HiddenWord.Len());
    PrintLine(TEXT("Guess the %i letter word"), Lives); // Magic Number remove!
    PrintLine(TEXT("Make your guess and press enter"));// Prompt player for guess 

}

void UBullCowCartridge::EndGame(){
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));// Prompt player to continue
}  


void UBullCowCartridge::CheckPlayerGuess(FString Guess){
    

    if (Guess == HiddenWord){
        PrintLine(TEXT("You have won!"));
        EndGame();
        return;
    }

    // if(!IsIsogram){
    //     PrintLine(TEXT("No repeating letters, guess again!"));
    // }
   
    if(Guess.Len() != HiddenWord.Len()){//Check if it has same amount of characters

            PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
            PrintLine(TEXT("Sorry, try again! You have %i lives left"), Lives); // Magic Number was hard coded
            return;
    }

    --Lives;
        PrintLine(TEXT("You have lost a life!"));

    if(Lives <= 0){
        ClearScreen();
        PrintLine(TEXT("You have no lives remaining"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);  
        EndGame();
        return;
    } 
}      


