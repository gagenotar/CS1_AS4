// Gage Notargiacomo, Spring 2023
// The goal of this program is to properly implement different sorting functions/styles over varying sizes of arrays.
// This is done to show how each sort method works and its effectiveness depending on the size of a given input.

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int extraMemoryAllocated;

// This is a helper function for the mergeSort function
// This function does the bulk of the processing required when merging the two arrays
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create two temporary arrays
	int *L = (int*) malloc(n1*sizeof(int));
	int *R = (int*) malloc(n2*sizeof(int));

	// Count extra bytes of memory allocated
	extraMemoryAllocated += sizeof(L) + sizeof(R);

	// Copy data to temp arrays
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];

	i = 0;
	j = 0; 
	k = l; // Initial index of merged subarray

	// Merge the two arrays back into main array "arr"
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}

		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy over any remaining elements of L
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy over any remaining elements of R
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);
}

// Implement merge sort
void mergeSort(int pData[], int l, int r)
{
	if (l < r)
	{
		// Get the mid point
		int m = (l+r)/2;

		// Sort first and second halves
		mergeSort(pData, l, m);
		mergeSort(pData, m+1, r);
		merge(pData, l, m, r);
	}
}

// Implement insertion sort
void insertionSort(int* pData, int n)
{
	int i, key, j;

	// *Important* i must start at 1 so that there is something to compare to index 0
	for (i = 1; i < n; i++) 
	{
		key = pData[i];

		for(j=i-1; j>=0; j--)
		{
			// Shift elements greater than the key over by one
			if(pData[j]>key)
				pData[j+1] = pData[j]; 

			// Otherwise it is already in place
			else
				break; 
		}

		// Put the item in hand after j
		pData[j+1] = key;
	}

}

// Helper function for the bubbleSort method
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// Implement bubble sort
void bubbleSort(int* pData, int n)
{

	int i, j;
	for (int i = 0; i < n-1; i++)
	{
		// Last i elements are already in place. So, stop j before n-i
		for (int j = 0; j < n-i-1; j++)
		{
			if (pData[j] > pData[j+1])
			swap(&pData[j], &pData[j+1]);
		}  
	}

}

// Implement selection sort
void selectionSort(int* pData, int n)
{
	int i, j, min_idx, temp;

	// Move through the unsorted array
	for (i = 0; i < n-1; i++)
	{
		// Find the minimum element in unsorted array  
		min_idx = i;
		for (j = i+1; j < n; j++)
		{
			if (pData[j] < pData[min_idx])  
			min_idx = j;
		}

		// Swap the found minimum element with the first element  
		temp = pData[i];
		pData[i] = pData[min_idx];  
		pData[min_idx] = temp;

}


}

// Parses input file to an integer array and returns the data size
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		
		// Implement parse data block
		for (int i = 0; i <= dataSz; i++)
		{
			fscanf(inFile, "%d ", &((*ppData)[i]));
		}
	}
	
	return dataSz;
}

// Prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
}