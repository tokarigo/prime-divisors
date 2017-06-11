#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <float.h>
#include <locale.h>
#include <sys/time.h>

#define MaxM 99

void printfcomma2(long long unsigned int n)
{
	if (n < 1000)
	{
		printf("%llu", n);
		return;
	}
	printfcomma2(n / 1000);
	printf(",%03llu", n % 1000);
}

void printfcomma(long long unsigned int n)
{
	if (n < 0)
	{
		printf("-");
		n = -n;
	}
	printfcomma2(n);
}

int chkEven(long long unsigned int chkNo)
{
	if (chkNo % 2 == 0)
	{
		return 1;
	}
	else
		return 0;

}

void skipgarb()
{
	while (getchar() != '\n')
	{
	}
}

int dvdrChk(long long unsigned testNo, long long unsigned dvdr)
{

	long long unsigned retDvdr;
	bool flagD = false;
	
	do
	{
		printf("%llu\r", dvdr);	// printing current divider being
		// printfcomma(dvdr); // printing current divider being
		// printf("\r");
		// tested
		if (testNo % dvdr == 0)
		{
			retDvdr = dvdr;// returns first found divider
			flagD = true;
		}

		dvdr += 2;
		if ((dvdr % 5) == 0 && (dvdr != 5))
			dvdr += 2;
		if (dvdr > sqrt(testNo))
		{
			dvdr = testNo;
		}
	}
	while (testNo != 1 && !flagD);
	return retDvdr;
}


int main()
{
	long long unsigned int testNo, rt, dvdr, chk, mltpl[MaxM];
	int i, j, k, m, inp;
	long double maxP, rtf, inv;
	bool flag, flagDiv, contd;
	char YN;

	struct timeval t1, t2;
	double tte;

	// setlocale(LC_ALL, "");

	do
	{
		for (i = 0; i < MaxM; i++)
			mltpl[i] = 0;

		do
		{
			printf("Input number to check (max 2^64-1): ");
			inp = scanf("%llu", &testNo);
			skipgarb;
		}
		while (inp == '\0');

		if (testNo >= (pow(256, 8) - 1))
			printf
				("Entered number is larger than 2^64-1, therefore it's been truncated to 2^64-1\n");
		// printf("Number being tested is: %'llu\n", testNo);
		// printf("Square root of test number is: % llu \n", (long long
		// int)round(sqrt((double)testNo)));
		// printf("Float precision is %d \n", FLT_DIG);
		printf("Number being tested is: ");
		printfcomma(testNo);
		printf("\nsquare of the number: ");
		printfcomma((long long unsigned int)(testNo * testNo));
		printf("\nSquare root (rounded) of test number is: ");
		printfcomma((long long int)round(pow((double)testNo, 0.5)));

		printf("\nnumber times 3 and times 5: \n ");
		printfcomma((long long unsigned int)(testNo * 3));
		printf("  xxx ");
		printfcomma((long long unsigned int)(testNo * 5));

		printf("\nDivider being  tested:\n");

		i = 1;
		j = 1;
		gettimeofday(&t1, NULL);

		while (chkEven(testNo) == 1)
		{
			mltpl[i] = 2;
			testNo = testNo / 2;
			// printf("divider is %d ", mltpl[i]);
			i++;
		}

		flagDiv = true;
		dvdr = 3;

		do						// start of overall search cycle (1 -power
								// base, 2 - trial division)
		{

			if (flagDiv)
			{					// enter power base search only of testNo
								// changed after successful dvdr

				flag = false;
				maxP = log2((double)testNo);
				// printf("log2 %.10f \n", maxP);
				k = 2;

				do				// search for power base
				{
					inv = (1 / (double)k);
					// printf("invert is %f", inv);
					rtf = pow((double)testNo, inv);
					rt = round(rtf);
					// printf("for k %d, root 1/k is (float, round) %f %llu
					// \n", k, rtf, rt);
					if (testNo % rt == 0)
					{
						chk = rt;
						for (m = 1; m < k; m++)
							chk = chk * rt;	// check that root is not a
											// rounding coincedence
						// issue
						if (chk == testNo)
						{		// need to do a check here that the power base 
								// is not a composite itself!!!
							dvdr = dvdrChk(rt, dvdr);	// need to check if
														// pass dvdr or 3
							flag = true;
						}
					}
					k++;
				}
				while (k <= maxP && flag == false);

				flagDiv = false;
			}

			// printf("power search exit divisor is %llu \n", dvdr);

			printf("%llu\r", dvdr);	// printing current divider being
			// printfcomma(dvdr); // printing current divider being
			// printf("\r");
			// tested
			while (testNo % dvdr == 0 && testNo != 1)
			{

				mltpl[i] = dvdr;
				printf("\nDivisors found so far: ");
				k = 1;
				do
				{
					printf("%llu ", mltpl[k]);
					k++;
				}
				while (mltpl[k] != 0);
				printf("\033[1A");
				// printf("divider is %d ", mltpl[i]);
				i++;
				testNo = testNo / dvdr;
				flagDiv = true;
			}

			// if ((testNo !=1) && (flag!=true))
			// { noMult[j]=dvdr;
			// j++;
			// }

			// do
			// {
			dvdr += 2;
			if ((dvdr % 5) == 0 && (dvdr != 5))
				dvdr += 2;
			if (dvdr > sqrt(testNo))
				dvdr = testNo;
			// }
			// while(chkNoMult(dvdr)==1);
			// flag = false;
		}
		while (testNo != 1);

		gettimeofday(&t2, NULL);
		// printf("remaining multiple is %d ", testNo);

		printf("\n\nMultiples are: ");
		for (i = 1; mltpl[i] != 0; i++)
		{
			// printf("%llu ", mltpl[i]);
			printfcomma(mltpl[i]);
			printf(" * ");
		}

		tte = (t2.tv_sec - t1.tv_sec) * 1000.0;	// sec to ms
		tte += (t2.tv_usec - t1.tv_usec) / 1000.0;	// us to ms
		printf("1\nTime elapsed: %f s.\nOne more (y/n)?", (tte / 1000));

		skipgarb();
		YN = getchar();
		if ((YN == 'y') || (YN == 'Y'))
			contd = true;
		else
			contd = false;
		skipgarb();

	}
	while (contd);
	return 0;
}