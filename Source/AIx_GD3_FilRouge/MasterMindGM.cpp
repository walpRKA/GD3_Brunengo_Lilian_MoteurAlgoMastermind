// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterMindGM.h"

// Sets default values
AMasterMindGM::AMasterMindGM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMasterMindGM::BeginPlay()
{
	uint8 GoodPlace = 0;
	uint8 WrongPlaces = 0;
	int TotalTry = 0;
	Super::BeginPlay();
	CreateSolution();
	
	
}

// Called every frame
void AMasterMindGM::Tick(float DeltaTime)
{
		
	Super::Tick(DeltaTime);

}

FLinearColor AMasterMindGM::GetColor(uint8 ColorNumber)
{
	if(ColorNumber < Colors.Num())
	{
		return Colors[ColorNumber];
	}

	return FLinearColor::Black;
	
}



void AMasterMindGM::CreateSolution()
{
	Solution.SetNum(4);
	for(uint8 i = 0; i < 4; i++)
	{
		Solution[i] = FMath::RandRange(0,5);
	}
		
}

bool AMasterMindGM::CheckAnswer(TArray<uint8> Answer)
{
	bool result = true;
	TArray<bool> SolutionsAllowed {true,true,true,true};
	TArray<bool> AnswersAllowed {true,true,true,true};
	for(uint8 i = 0; i < 4; i++)
	{
		Tries();
		if(Solution[i] == Answer[i])
		{
			SolutionsAllowed[i] = false;
			AnswersAllowed[i] = false;
			GoodPlaces++;
			if (GoodPlaces == 4)
			{
				 if (GEngine)
				 {
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Vous avez gagné"));	
				}
			}
			if (GoodPlaces == 3)
			{
				 if (GEngine)
				 {
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bon endroit x3"));	
				}
			}
			
			if (GoodPlaces == 2)
			{
				 if (GEngine)
				 {
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bon endroit x2"));	
				}
				
			}
			if (GoodPlaces == 1)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bon endroit"));	
				}
			}
			
			return false;
			
			
		} else
		{
			result = false;
		}
	}
	// GoodPlaces contient le nombre de réponses bien placées


	// Recherche des réponses mal placées
	for(uint8 i = 0; i < 4; i++)
	{
		if(AnswersAllowed[i])
		{
			for(uint8 j = 0; j < 4; j++)
			{
				if(SolutionsAllowed[j] && Answer[i] == Solution[j])
				{
					WrongPlaces++;
					if (WrongPlaces == 4)
					{
						 if (GEngine)
						 {
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bonne couleur mauvais endroit x4"));	
						}
					}
					if (WrongPlaces == 3)
					{
						 if (GEngine)
						 {
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bonne couleur mauvais endroit x3"));	
						}
					}
			
					if ( WrongPlaces == 2)
					{
						if (GEngine)
						{
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bonne couleur mauvais endroit x2"));	
						}
					}
					if (WrongPlaces == 1)
					{
						 if (GEngine)
						 {
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bonne couleur mauvais endroit"));	
						}
					}
					SolutionsAllowed[j] = false;
					break;
				}
			}
		}
		
	}
}
void AMasterMindGM::Tries()
{
	TotalTry++;
	if (TotalTry == 7)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Game Over"));	
		}
	}
	// On regarde le nombre total d'essais. S'il dépasse 7, la partie se termine et le joueur perd. On devrait ensuite pouvoir récupérer le nombre d'essais
	// et l'afficher au dessus du mastermind pour informer le joueur
	OnSolutionChecked.Broadcast(GoodPlaces,WrongPlaces);
	UE_LOG(LogTemp,Warning,TEXT("CheckAnswer Done"));
	
}

