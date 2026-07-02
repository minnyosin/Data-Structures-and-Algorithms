#include <iostream>

using namespace std;

void CA1()
{
	int nums[] = {-110,110, 44, 56};
	int total = 0;
	int max = nums[0];
	int min = nums[0];
	for (int i = 0; i < sizeof(nums) / sizeof(int); i++) // sizeof(nums)/sizeof(int) defines how many elements are in the array
	//for (int i = 0; i < size(nums); i++)
	{
		total += nums[i];
	}
	cout << "Total is " << total << '\n';

	for (int i = 1; i < size(nums); i++)
	{
		if (max <= nums[i])
		{
			max = nums[i];
		}
	}
	cout << "The maximum number is " << max << endl;
	for (int i = 1; i < size(nums); i++)
	{
		if (min >= nums[i])
		{
			min = nums[i];
		}
	}
	cout << "The minimum number is " << min << endl;
}
void CA4()
{
	int matrixA[2][2] = { 0 };
	int matrixB[2][2] = { 0 };
	int matrixSum[2][2] = { 0 };
	int matrixDiff[2][2] = { 0 };
	int matrixMulti[2][2] = { 0 };


	cout << "Enter the values of the 1st Matrix : " << endl;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> matrixA[i][j];
		}
	}

	cout << "Enter the values of the 2nd Matrix : " << endl;
	for (int i = 0; i < 2; i++)
	{

		for (int j = 0; j < 2; j++)
		{
			cin >> matrixB[i][j];
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			matrixSum[i][j] = matrixA[i][j] + matrixB[i][j];
			matrixDiff[i][j] = matrixA[i][j] - matrixB[i][j];
		}
	}

	cout << "Sum of entered matrices : " << endl;
	for (int i = 0; i < 2; i++)
	{

		for (int j = 0; j < 2; j++)
		{
			cout << matrixSum[i][j];
			cout << "  ";
		}
		cout << '\n';
	}

	cout << "Difference of entered matrices : " << endl;
	for (int i = 0; i < 2; i++)
	{

		for (int j = 0; j < 2; j++)
		{
			cout << matrixDiff[i][j];
			cout << "  ";
		}
		cout << '\n';
	}

	cout << "Multiplication of entered matrices : " << endl;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				matrixMulti[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}

	// I tried to hardcode this as I cannot think about the way anymore :')

	//matrixMulti[0][0] = matrixA[0][0] * matrixB[0][0] + matrixA[0][1] * matrixB[1][0];  
	//matrixMulti[0][1] = matrixA[0][0] * matrixB[0][1] + matrixA[0][1] * matrixB[1][1];
	//matrixMulti[1][0] = matrixA[1][0] * matrixB[0][0] + matrixA[1][1] * matrixB[1][0];
	//matrixMulti[1][1] = matrixA[1][0] * matrixB[0][1] + matrixA[1][1] * matrixB[1][1];

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << matrixMulti[i][j];
			cout << "  ";
		}
		cout << '\n';
	}

}
void AddValuesToArray(int arrayNew[], int i)
{
	cout << "Enter value's " << (i + 1) << ": ";
	cin >> arrayNew[i];
}

void reversePrintValues(int arrayNew[], int size)
{
	for (int i = size - 1; i >= 0; i--)
	{
		cout << arrayNew[i] << ", ";
	}
	cout << endl;
}

void grow(int& x)
{
	x += 1;
	cout << "Your new age is : " << x << endl;
	cout << "Your age is stored in " << &x << endl;
}

int main()
{
	//CA1();
	//CA4();

	//int age = 30;

	//cout << "You are " << age << " years old!" << '\n';
	//grow(age);
	//cout << "Your age is stored in " << &age;
	//cout << endl;
	//cout << "You are " << age << " years old!" << '\n';

	int array1[5];

	for (int i = 0; i < sizeof(array1) / sizeof(int); i++)
	{
		AddValuesToArray(array1, i);
	}

	reversePrintValues(array1, size(array1));
}
//|1  2| |1  2|
//|3  4| |3  4|

