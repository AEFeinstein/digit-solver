#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define NUM_DIGITS 6

/**
 * @brief Depth first recursive solver for a Digit puzzle. When a solution is
 * found the steps will be printed in reverse order
 *
 * @param digits The current set of numbers. May include zeros, which must be
 *               ignored
 * @param target The target number to get after doing a math operation
 * @return true if the target was reached, false if it was not
 */
static bool recursiveDigitCheck(int *digits, int target)
{
	// Addition and multiplication are commutative and always valid
	for (int i = 0; i < NUM_DIGITS; i++)
	{
		for (int j = (i + 1); j < NUM_DIGITS; j++)
		{
			// Skip over zeros
			if (0 == digits[i] || 0 == digits[j])
			{
				continue;
			}

			// Addition
			int newDigitsAdd[NUM_DIGITS];
			memcpy(newDigitsAdd, digits, sizeof(int) * NUM_DIGITS);
			newDigitsAdd[i] = digits[i] + digits[j];
			newDigitsAdd[j] = 0;
			if ((newDigitsAdd[i] == target) || recursiveDigitCheck(newDigitsAdd, target))
			{
				// Solution found! print this step and return
				printf("%d + %d = %d\n", digits[i], digits[j], newDigitsAdd[i]);
				return true;
			}

			// Multiplication
			int newDigitsMul[NUM_DIGITS];
			memcpy(newDigitsMul, digits, sizeof(int) * NUM_DIGITS);
			newDigitsMul[i] = digits[i] * digits[j];
			newDigitsMul[j] = 0;
			if ((newDigitsMul[i] == target) || recursiveDigitCheck(newDigitsMul, target))
			{
				// Solution found! print this step and return
				printf("%d * %d = %d\n", digits[i], digits[j], newDigitsMul[i]);
				return true;
			}
		}
	}

	// Subtraction and division are not commutative
	for (int i = 0; i < NUM_DIGITS; i++)
	{
		for (int j = 0; j < NUM_DIGITS; j++)
		{

			// Skip over zeros
			if (0 == digits[i] || 0 == digits[j])
			{
				continue;
			}

			// Make sure the operands are different
			if (i != j)
			{
				// Operations that produce negative numbers will not be accepted.
				if (digits[i] > digits[j])
				{
					// Subtraction
					int newDigitsSub[NUM_DIGITS];
					memcpy(newDigitsSub, digits, sizeof(int) * NUM_DIGITS);
					newDigitsSub[i] = digits[i] - digits[j];
					newDigitsSub[j] = 0;
					if ((newDigitsSub[i] == target) || recursiveDigitCheck(newDigitsSub, target))
					{
						// Solution found! print this step and return
						printf("%d - %d = %d\n", digits[i], digits[j], newDigitsSub[i]);
						return true;
					}

					// Operations that produce fractions will not be accepted.
					if (0 == digits[i] % digits[j])
					{
						// Division
						int newDigitsDiv[NUM_DIGITS];
						memcpy(newDigitsDiv, digits, sizeof(int) * NUM_DIGITS);
						newDigitsDiv[i] = digits[i] / digits[j];
						newDigitsDiv[j] = 0;
						if ((newDigitsDiv[i] == target) || recursiveDigitCheck(newDigitsDiv, target))
						{
							// Solution found! print this step and return
							printf("%d / %d = %d\n", digits[i], digits[j], newDigitsDiv[i]);
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

/**
 * @brief Print this program's usage
 *
 * @param progName The name of the program
 * @param message A message as to why usage is being printed
 */
static void printUsage(char *progName, char *message)
{
	fprintf(stderr, "%s\nUsage: %s [six numbers] [target number]\n", message, progName);
}

/**
 * @brief Main function, handle the input arguments and run the recursive solver
 *
 * @param argc The number of arguments
 * @param argv An array of string pointer arguments
 * @return -1 if there was a problem with arguments, 0 if everything was OK
 */
int main(int argc, char **argv)
{
	if (argc < 8)
	{
		printUsage(argv[0], "Too few arguments");
		return -1;
	}
	else if (argc > 8)
	{
		printUsage(argv[0], "Too many arguments! Continuing anyway");
	}

	int digits[NUM_DIGITS];
	for (int i = 0; i < NUM_DIGITS; i++)
	{
		digits[i] = atoi(argv[1 + i]);
		if (0 == digits[i])
		{
			printUsage(argv[0], "Non-numeric argument");
			return -1;
		}
	}

	recursiveDigitCheck(digits, atoi(argv[7]));

	return 0;
}
