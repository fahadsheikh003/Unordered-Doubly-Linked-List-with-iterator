//Fahad Waheed

#include<iostream>
#include"List.h"

using namespace std;

int main()
{
	List<int> L;

	for (int i = 0; i < 10; i++)
		L.InsertinFirst(i * 10);

	L.BubbleSort();

	cout << L[5] << endl;

	List<int>::Interator it;

	for (it = L.begin(); it != L.end(); it++)
		cout << *it << "  ";
}