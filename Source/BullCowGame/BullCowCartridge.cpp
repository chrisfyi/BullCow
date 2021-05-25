// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Math/UnrealMathUtility.h" // For the RandRange function

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

    // PrintLine(TEXT("%i"), FMath::RandRange(0, 10));
   

    Isograms = GetValidWords(Words);

    // Setting up Game
    SetupGame();
     
}

void UBullCowCartridge::OnInput(const FString & PlayerInput) // When the player hits enter
{
    if (bGameOver) { // If the game is over, ClearScreen() and SetupGame() again
            ClearScreen();
            SetupGame();
            
            }   
            else { // else Checking the player guess
                CheckPlayerGuess(PlayerInput);         
            }
}

void UBullCowCartridge::SetupGame(){
      //Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cow!"));
    
    HiddenWord = Isograms [FMath::RandRange(0, Isograms.Num() - 1)];  // Set the hidden word
    Lives = HiddenWord.Len();//Set Lives
    bGameOver = false;

    PrintLine(TEXT("You have %i lives"), HiddenWord.Len());
    PrintLine(TEXT("Guess the %i letter word"), Lives); // Magic Number remove!
    // PrintLine(FString::Printf(TEXT("The Hidden Word is %s"), *HiddenWord)); // Debug Line
    PrintLine(TEXT("Make your guess and press enter"));// Prompt player for guess 
    // IsIsogram(HiddenWord);
}

void UBullCowCartridge::EndGame(){
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));// Prompt player to continue
}  


void UBullCowCartridge::CheckPlayerGuess(const FString& Guess){
    

    if (Guess == HiddenWord){
        PrintLine(TEXT("You have won!"));
        EndGame();
        return;
    }

    if(!IsIsogram(Guess)){

        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }
   
    if(Guess.Len() != HiddenWord.Len()){//Check if it has same amount of characters

            PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
            PrintLine(TEXT("Sorry, try again! You have %i lives left"), Lives); // Magic Number was hard coded
            return;
    }

    --Lives;
        PrintLine(TEXT("You have lost a life! You have %i lives left"), Lives);

    if(Lives <= 0){
        ClearScreen();
        PrintLine(TEXT("You have no lives remaining"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);  
        EndGame();
        return;
    }
        
        FBullCowCount Score = GetBullCows(Guess);

        PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
        PrintLine(TEXT("Sorry, try again! You have %i lives left"), Lives);

     
}     

bool UBullCowCartridge::IsIsogram(const FString& Word) const{

  for (int32 Index = 0; Index < Word.Len(); Index++) //Loops through Index
        {
            for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++) // Loops through Comparison
            {
                if (Word[Index]== Word[Comparison])
                {
                    return false;
                }
            }
        }
    return true;

}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const {

    TArray<FString> ValidWords;
    
        for (FString Word : WordList){

            if ( Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word)){
               
              ValidWords.Emplace(Word);
                
            }
        }   
        return ValidWords;    
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const {
    
    FBullCowCount Count;

    //If the index guess is the same as index Hidden, Bullcount ++
    //if not a bull was it as cow? if yes cowcount ++

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex]){
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}

