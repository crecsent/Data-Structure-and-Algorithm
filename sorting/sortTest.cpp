#include<iostream>
#include<time.h>
#include<Windows.h>
#include<algorithm>
#include<fstream>
using namespace std;

void insertSort(int * a, int size)
{
	for (int i = 2; i <= size; i++)
	{
		int toInsert = a[i];
		int index = i - 1;
		while (index >= 1 && toInsert < a[index])
		{
			a[index + 1] = a[index];
			index--;
		}
		a[index + 1] = toInsert;
	}
}

void quickSort(int * a, const int left, const int right)
{
	if (left < right) {
		int pivot = (left + right) / 2;
		//三个值两两比较
		bool lVSr = a[left] < a[right], lVSp = a[left] < a[pivot], pVSr = a[pivot] < a[right];
		int l = 0, p = 0, r = 0;//用于记录各位置值的相对大小关系
		l += (lVSr ? (lVSp ? -1 : 0) : (lVSp ? 0 : 1));
		p += (lVSp ? (pVSr ? 0 : 1) : (pVSr ? -1 : 0));
		//等于-1为最小值，等于0为中值，等于1为最大值
		int min = a[(l < 0 ? left : (p < 0 ? pivot : right))];
		int mid = a[(l == 0 ? left : (p == 0 ? pivot : right))];
		int max = a[(l > 0 ? left : (p > 0 ? pivot : right))];

		//这里的赋值顺序极其重要
		a[pivot] = a[right - 1]; a[right - 1] = mid; a[left] = min; a[right] = max;
		//l,p,r重用为下标
		l = left; p = right - 1; r = p;
		while (true)
		{
			while (a[++l] < a[p]);
			while (r > left&&a[--r] > a[p]);
			if (l < r)
				swap(a[l], a[r]);
			else
				break;
		}
		if (l < right)
			swap(a[l], a[p]);

		quickSort(a, left, l - 1);
		quickSort(a, l + 1, right);
	}
}

void quickSort(int * a, const int n)
{
	quickSort(a, 1, n);
}

void merge(int * init, int * merged, const int l, const int m, const int n)
{
	int i1 = l, iResult = l, i2 = m + 1;
	for (; i1 <= m && i2 <= n; iResult++)
	{
		if (init[i1] <= init[i2])
		{
			merged[iResult] = init[i1];
			i1++;
		}
		else
		{
			merged[iResult] = init[i2];
			i2++;
		}

	}

	copy(init + i1, init + m + 1, merged + iResult);
	copy(init + i2, init + n + 1, merged + iResult);
}
void mergePass(int * init, int * result, const int n, const int s)
{
	int i = 1;
	for (; i <= n - 2 * s + 1; i += 2 * s)
	{
		merge(init, result, i, i + s - 1, i + 2 * s - 1);
	}
	if ((i + s - 1) < n)
		merge(init, result, i, i + s - 1, n);
	else
		copy(init + i, init + n + 1, result + i);

}
void mergeSort(int * a, int n)
{
	int * temp = new int[n + 1];
	for (int l = 1; l < n; l *= 2)
	{
		mergePass(a, temp, n, l);
		l *= 2;
		mergePass(temp, a, n, l);
	}
	delete[] temp;
}

void adjustMaxHeap(int * a, int i, int size)
{
	int root = a[i];
	int pos = i * 2;
	for (; pos <= size; pos *= 2)
	{
		if (pos<size&&a[pos + 1]>a[pos])
			pos++;
		if (root >= a[pos])
			break;
		a[pos / 2] = a[pos];
	}
	a[pos / 2] = root;
}
void heapSort(int * a, int size)
{
	for (int i = size / 2; i >= 1; i--)
		adjustMaxHeap(a, i, size);

	for (int i = size - 1; i >= 1; i--)
	{
		swap(a[1], a[i + 1]);
		adjustMaxHeap(a, 1, i);
	}
}

void auxillaryPick(int * a, int * left, int * right, int l, int r)
{
	if (l < r)
	{
		int i, lIndex = 0, rIndex = 0;
		for (i = l; i <= r; i += 2)
			left[lIndex++] = a[i];
		for (i = l + 1; i <= r; i += 2)
			right[rIndex++] = a[i];
		int lnum = lIndex, rnum = rIndex;
		for (i =l, lIndex = 0;lIndex<lnum;i++)
			a[i] = left[lIndex++];
		for (rIndex = 0; rIndex < rnum; i++)
			a[i] = right[rIndex++];

		auxillaryPick(a, left, right, l, r-rIndex);
		auxillaryPick(a, left, right,r-rIndex+1, r);
	}
}

void worstInputForInsertAndQuickSort(int *a, int n)
{
	for (int i = 1,j=n; i <= n; i++,j--)
		a[i] = j;
}

//当两个子序列的元素为父序列中元素的交替排列时，要做的比较次数最多
//即对应着归并排序的最坏情况下的输入数据
void worstInputForMergeSort(int * a,int n)
{
	int l = 1, r = n;
		int m = (r + l) / 2;
		int* left= new int[m - l + 1];
		int* right=new int[r - m];
		auxillaryPick(a, left, right, l, r);
		delete[] left;
		delete[] right;
}

void worstInputForHeapSort(int * a, int n)
{
	for (int i = n; i >= 2; i--)
	{
		int j = rand() % i + 1;
		swap(a[j], a[i]);
	}
}

void mixSort(int * a, int n)
{
	if (n < 100)
		insertSort(a, n);
	else
		quickSort(a, n);
}

void printArray(int * a,int n)
{
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << endl;
}
int main()
{
	srand(time(0));
	LARGE_INTEGER start, end, tc;
	QueryPerformanceFrequency(&tc);
	fstream file;
	file.open("d:/test.txt");
	//const int count[] = {5,10,15,20,25,30,40,50,60,80,100,120,140,160,180,200,220,240,260,280,300,
	//340,380,420,460,500,540,580,620,660,700,750,800,850,900,950,1000};
	const int count[] = { 500,1000,2000,3000,4000,5000 };
	const int REPEAT = 50;

	for (int n : count)
	{
		file << n << " ";
		int* a = new int[n + 1];
		double cost[5] = { 0 };
		for (int i = 0; i < REPEAT; i++)
		{
			//插入排序
			worstInputForInsertAndQuickSort(a, n);
			QueryPerformanceCounter(&start);
			insertSort(a, n);
			QueryPerformanceCounter(&end);
			//printArray(a, n);
			//cout <<"insertSort: "<< (end.QuadPart - start.QuadPart)*1000000.0 / tc.QuadPart<<"微秒"<<endl;
			cost[0] += (end.QuadPart - start.QuadPart)*1000000.0 / tc.QuadPart;

			//快速排序
			worstInputForInsertAndQuickSort(a, n);
			QueryPerformanceCounter(&start);
			quickSort(a, n);
			QueryPerformanceCounter(&end);
			//printArray(a, n);
			//cout << "quickSort: " << (end.QuadPart - start.QuadPart)*1000000.0 / tc.QuadPart << "微秒" << endl;
			cost[1] += (end.QuadPart - start.QuadPart)*1000000.0 / tc.QuadPart;

			//归并排序
			worstInputForMergeSort(a, n);
			QueryPerformanceCounter(&start);
			mergeSort(a, n);
			QueryPerformanceCounter(&end);
			//printArray(a, n);
			//cout << "mergeSort: "<< (end.QuadPart - start.QuadPart)*1000000.0 / tc.QuadPart << "微秒" << endl;
			cost[2] += (end.QuadPart - start.QuadPart)*1000000.0 / tc.QuadPart;

			//堆排序
			worstInputForHeapSort(a, n);
			QueryPerformanceCounter(&start);
			heapSort(a, n);
			QueryPerformanceCounter(&end);
			//printArray(a, n);
			//cout << "heapSort: "<< (end.QuadPart - start.QuadPart)*1000000.0 / tc.QuadPart << "微秒" << endl;
			cost[3] += (end.QuadPart - start.QuadPart)*1000000.0 / tc.QuadPart;

			//复合排序
			worstInputForInsertAndQuickSort(a, n);
			QueryPerformanceCounter(&start);
			mixSort(a, n);
			QueryPerformanceCounter(&end);
			cost[4] += (end.QuadPart - start.QuadPart)*1000000.0 / tc.QuadPart;
		}
		for (double c : cost)
			file << c / REPEAT << " ";

		file << "\n";
		delete[] a;
	}
	file.close();
}