/******************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the
concepts learned. I have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and debugged by my own efforts. I further
certify that I have not copied in part or whole or otherwise plagiarized the work of other students and/or
persons.

Nicole P. Jocson
******************************************************************/

/*
 Description: This program simulates the Stalk Market mechanic in the video game Animal Crossing: New Horizons
 Programmed by: Nicole Jocson
 Last modified: February 6, 2022
 Version: 7.0
 [Acknowledgements: https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
	 				https://www.geeksforgeeks.org/generating-random-number-range-c/]
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* This function prints the opening game text */

void
welcome ()
{
	printf ("Welcome to your new island!\n");
	printf ("Every week, you can buy turnips using Bells on Sundays;\n");
	printf ("and you can sell the turnips from Monday to Saturday.\n\n");
	printf ("The prices for buying and selling turnips are random.\n");
	printf ("You have 20 weeks to earn 1,000,000 Bells from buying and selling turnips.\n");
	printf ("Good luck!\n");
}

/*	This function displays the day of the week
	Precondition: Sunday is 1 and Saturday is 7
	@param nDay is the nth day of the week
*/

void
displayDayOfWeek (int nDay)
{
	printf(".......................................................\n");
	printf("Today is ");
	
	switch (nDay)
	{
		case 1: printf ("Sunday.\n\n");
			break;
		case 2: printf ("Monday.\n\n");
			break;
		case 3: printf ("Tuesday.\n\n");
			break;
		case 4: printf ("Wednesday.\n\n");
			break;
		case 5: printf ("Thursday.\n\n");
			break;
		case 6: printf ("Friday.\n\n");
			break;
		case 7: printf ("Saturday.\n\n");
			break;
	}
}

/*	This function generates a random number within a range
	Precondition: nLower and nUpper are non-negative integers
	@param nLower is the lower limit of the random number to generate
	@param nUpper is the upper limit of the random number to generate
	@return a random integer within nLower and nUpper
*/

int
randomize (int nLower, int nUpper)
{
	return (rand() % (nUpper - nLower + 1)) + nLower;
}

/*	This function asks the user how many turnips they want to buy
	Precondition: all parameters are non-negative integers
	@param nUpdateBells is the amount of Bells to subtract after buying turnips
	@param nUpdateTurnips is the amount of turnips to add after buying turnips
	@param nBuyingPrice is the price of turnips on the Sunday for the week
	@param nTurnipsToBuy is the inputted amount of turnips the user buys
*/

void
buyTurnips (int * nUpdateBells, int * nUpdateTurnips,
			int nBuyingPrice, int nTurnipsToBuy)
{
	do {
		printf ("How many stacks of 10 turnips would you like to buy this Sunday? ");
		scanf ("%d", &nTurnipsToBuy);
		printf("\n");
		
		// Tells the user the maximum amount they can input
		if (* nUpdateBells < nBuyingPrice * 10 * nTurnipsToBuy)
			printf ("\tYou can only buy %d stacks of turnips. Try again!\n\n", * nUpdateBells / nBuyingPrice / 10);
		
	// The program will ask the user to buy again if they have insufficient Bells
	} while (* nUpdateBells < nBuyingPrice * 10 * nTurnipsToBuy);
	
	// Bells and turnips will be updated
	* nUpdateBells = * nUpdateBells - nTurnipsToBuy * 10 * nBuyingPrice;
	* nUpdateTurnips = * nUpdateTurnips + nTurnipsToBuy * 10;
}

/*	This function generates a random selling price
	Precondition: all parameters are non-negative integers with a random value
	@param nTrend is the random trend for the week
	@param nBuyingPrice is the price of turnips on the Sunday for the week
	@param nSellingPrice is the daily price of turnips from Monday to Saturday
	@return a random selling price within the random trend
*/

int
dailySellingPrice (int nTrend, int nBuyingPrice, int nSellingPrice)
{
	switch (nTrend)
	{
		/*
			Average trend
			Minimum: 80 Bells
			Maximum: 5% increase of the Sunday price
		*/
		case 1:
			nSellingPrice = randomize (80, nBuyingPrice + 21 * nBuyingPrice / 20);
			break;
		/*
			Awesome trend
			Minimum: Sunday price
			Maximum: 300% of the Sunday price
		*/
		case 2:
			nSellingPrice = randomize (nBuyingPrice, nBuyingPrice * 3);
			break;
		/*
			Bad trend
			Minimum: 20 Bells
			Maximum: Sunday price
		*/
		case 3:
			nSellingPrice = randomize (20, nBuyingPrice);
			break;
	}
	return nSellingPrice;
}

/*	This function asks the user how many turnips they want to sell
	Precondition: all parameters are non-negative integers
	@param nUpdateBells is the amount of Bells to add after buying turnips
	@param nUpdateTurnips is the amount of turnips to subtract after buying turnips
	@param nSellingPrice is the daily price of turnips from Monday to Saturday
	@param nTurnipsToSell is the inputted amount of turnips the user sells
*/

void
sellTurnips (int * nUpdateBells, int * nUpdateTurnips,
			 int nSellingPrice, int nTurnipsToSell)
{
	do {
		printf ("How many stacks of turnips do you want to sell? ");
		scanf ("%d", &nTurnipsToSell);
		printf("\n");
		
		// Tells the user the maximum amount they can input
		if (* nUpdateTurnips < nTurnipsToSell * 10)
			printf ("\tYou only have %d stacks of turnips to sell. Try again!\n\n", * nUpdateTurnips / 10);
		
	//The program will ask the user to sell again if they have insufficient turnips
	} while (* nUpdateTurnips < nTurnipsToSell * 10);
	
	// Bells and turnips will be updated
	* nUpdateBells = * nUpdateBells + nTurnipsToSell * 10 * nSellingPrice;
	* nUpdateTurnips = * nUpdateTurnips - nTurnipsToSell * 10;
}

int main ()
{
	int nDay;
	int nWeek;
	
	int nBells = 5000;
	int nTurnips = 0;
	
	int nBuyingPrice;
	int nSellingPrice;
	int nTrend;
	int nPrevTrend;
	
	int nTurnipsToBuy;
	int nTurnipsToSell;
	char cConfirm;
	
	int nForceGameOver = 0;
		
	// Used to generate unique sets of random numbers
	srand (time(0));
	
	// Display the beginning message
	welcome ();
	
	// Makes sure the program runs for 20 weeks
	for (nWeek = 1; nWeek <= 20; nWeek++)
	{
		// The Sunday price (buying price) will be random
		nBuyingPrice = randomize (90, 110);
		
		nPrevTrend = nTrend;
		
		// nTrend will generate a new value if the current week's trend is the same as previous week's
		do {
			// nTrend is the same for the week
			nTrend = randomize (1, 3);
		} while (nTrend == nPrevTrend);
		
		printf (".......................................................\n");
		printf ("Week %d begins!\n", nWeek);
		
		for (nDay = 1; nDay <= 7; nDay++)
		{
			/*
				The week will continue (1) on Sunday: to buy turnips
									   (2) from Monday to Saturday: if they have turnips to sell
			*/
			if (nDay == 1 || 
			   (nDay > 1 && nTurnips > 0))
			{
				displayDayOfWeek (nDay);
				
				// Display user's current possessions
				printf("You currently possess:\n");
				printf("(1) %d Bells and \n", nBells);
				printf("(2) %d turnips!\n\n", nTurnips);
				
				// Sunday: Buy Turnips
				if (nDay == 1)
				{
					printf ("Daisy Mae is selling turnips for %d each!\n\n", nBuyingPrice);
					
					// Checks if the user can buy at least one stack of turnips
					if (nBells < nBuyingPrice * 10)
					{
						printf ("\tOh no! You have insufficient Bells to buy a stack of turnips.\n");
						nWeek = 20;
						nForceGameOver = 1;
					} else
					{
						do {
							printf ("Would you like to buy turnips this Sunday? [Y]es or [N]o: ");
							scanf (" %c", &cConfirm);
							printf("\n");
							
							if (cConfirm != 'Y' && cConfirm != 'y' &&
								cConfirm != 'N' && cConfirm != 'n')
									printf ("\tInvalid option!\n\n");
							
						// The program will ask the user again if they enter an invalid input
						} while (cConfirm != 'Y' && cConfirm != 'y' &&
								 cConfirm != 'N' && cConfirm != 'n');
						
						if (cConfirm == 'Y' || cConfirm == 'y')
						{
							nTurnipsToBuy = 0;
							
							buyTurnips (&nBells, &nTurnips,
										nBuyingPrice, nTurnipsToBuy);
						}
					}
					
				// Monday to Saturday: Sell Turnips
				} else if (nDay >= 2 && nDay <= 7)
				{
					// Selling price has a different value everyday but within the random trend
					nSellingPrice = dailySellingPrice (nTrend, nBuyingPrice, nSellingPrice);
					
					printf ("Nook's Cranny is currently buying turnips for %d Bells per turnip!\n", nSellingPrice);
					printf ("You bought turnips for %d Bells last Sunday.\n\n", nBuyingPrice);
					
					do {
					printf ("Would you like to sell your turnips? [Y]es or [N]o: ");
					scanf (" %c", &cConfirm);
					printf ("\n");
					
					if (cConfirm != 'Y' && cConfirm != 'y' &&
						cConfirm != 'N' && cConfirm != 'n')
							printf ("\tInvalid option!\n\n");
					
					// The program will ask the user again if they enter an invalid input
					} while (cConfirm != 'Y' && cConfirm != 'y' &&
							 cConfirm != 'N' && cConfirm != 'n');
					
					if (cConfirm == 'Y' || cConfirm == 'y')
					{
						nTurnipsToSell = 0;
						
						sellTurnips (&nBells, &nTurnips,
									 nSellingPrice, nTurnipsToSell);
					}
					
					// Unsold turnips will go spoiled
					if (nDay == 7 && nTurnips > 0)
					{
						nTurnips = 0;
						printf("\tYour unsold turnips for the week have gone bad!\n");
					}
				}
				
			// The rest of the week skips if the user has no turnips to sell
			} else if (nForceGameOver != 1 && nTurnips == 0)
			{
				if (nDay == 2)
					printf ("\tYou did not buy turnips to sell. ");
				else
					printf ("\tYou've sold all your turnips. ");
			
				printf("The rest of the week is skipped.\n");
				nDay = 7;
			}
		}
	}
	
	// "Game Over" message after 20 weeks
	printf(".......................................................\n");
	printf ("GAME OVER!\n");
	printf(".......................................................\n");
	
	// Message display if the goal is reached
	if (nBells >= 1000000)
		printf("Congratulaions! You have earned 1 million Bells!");
	else
		printf("You failed to earn 1 million Bells. Try again!");
	
	return 0;
}
