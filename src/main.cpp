#include "dynamic_matrix.hpp"
int main(){

  unsigned int ga{1000};
  brocolio::container::dynamic_matrix<int> m{ga,ga};
  m*=m;

}