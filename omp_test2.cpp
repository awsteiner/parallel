#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main(void) {

  // This array is shared by all threads
  vector<size_t> arr(100);
  
#pragma omp parallel
  {
#pragma omp for
    for(size_t i=0;i<100;i++) {
      // j is private by default
      int j=i*2;
      arr[i]=i;
      std::cout << i << " " << j << std::endl;
    }
  }
  
  for(size_t i=0;i<100;i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  return 0;
}
               
