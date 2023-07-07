#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main(void) {

  vector<size_t> arr(100);
  
#pragma omp parallel
  {
#pragma omp for
    for(size_t i=0;i<100;i++) {
      arr[i]=i;
      std::cout << i << std::endl;
    }
  }
  
  for(size_t i=0;i<100;i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  return 0;
}
               
