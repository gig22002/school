#include <iostream>
using namespace std;

bool ECCompare(int x, int y){
	return x>y;
}

// complete the definition of the sorting function ...
void ECSortFP(int *listNumbers, int size, bool (*comp)(int, int))
{
  // your code here
  for (int i=0; i<size-1; i++){
	for(int j=0; j<size-i-1; j++){
		if(comp(listNumbers[j],listNumbers[j+1])){
			int temp = listNumbers[j];
			listNumbers[j] = listNumbers[j+1];
			listNumbers[j+1] = temp;
		}
	}
  }
}

int main()
{
  int arr[] = {1,3,2,4};
  ECSortFP(arr, 4, ECCompare);

  // print it out
  for(int i=0; i<4; ++i)
  {
    cout << arr[i] << " ";
  }
  cout << endl;
}

