#include <iostream>


int main()
{
	// Dynamically allocate matrix on heap
	const int count = 5;
	int** matrix = new int*[count];
	for (int i = 0; i < count; i++)
	{
		matrix[i] = new int[count];
	}

	// Initialize matrix values
	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++)
			matrix[i][j] = 0;

	// Print matrix
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			std::cout << matrix[i][j] << " ";
		}

		std::cout << "\n";
	}

	// Deallocate matrix
	for (int i = 0; i < count; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
	
	return 0;
}