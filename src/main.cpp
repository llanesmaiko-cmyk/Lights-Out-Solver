#include <iostream>
#include <cmath>
#include <iterator>
#include <vector>

using namespace std;

//Take in the original Lights Out puzzle and return its toggle matrix
vector<bool> createToggleMatrix(const vector<bool> & lOMatrix) {
    vector<bool> toggleMatrix;
  int lOSize = lOMatrix.size();
  int rowSize = sqrt(lOSize);
  int i = 0;
      //Neighbors
  bool uN = true;
  bool dN = true;
  bool lN = true;
  bool rN = true;
  int up = 0;
  int down = 0;
  int left = 0;
  int right = 0;

  //Iterate through the elements of the Lights Out matrix. Determine if i is a neighber of j.
  for (int value : lOMatrix) {
    if (i - rowSize < 0){uN = false;}
      else {uN = true;}
    if (i + rowSize > lOSize - 1){dN = false;}
      else {dN = true;}
    if ((i - 1) % rowSize == (i % rowSize) - 1 && i - 1 >= 0){lN = true;}
      else {lN = false;}
    if ((i + 1) % rowSize == (i % rowSize) + 1) {rN = true;}
      else {rN = false;}
    up = i - rowSize;
    down = i + rowSize;
    left = i - 1;
    right = i + 1;
    //Iterate through the original matrix. Add 1 to the new matrix if j is a neighber of i, else add 0 to the matrix.
    for (int j = 0; j <= lOSize - 1; j++){
      if (j == i || j == up && uN == true || j == down && dN == true || j == left && lN == true || j == right && rN == true) {
        toggleMatrix.push_back(1);
      }
      else {
        toggleMatrix.push_back(0);
      }
    }
    i++;
  }

  return toggleMatrix;
}

int main() {
  //Lights Out input
    //0=off 1=on
  vector<bool> lOMatrix = {
    1,1,1,
    1,1,1,
    1,1,1};

  int lOSize = lOMatrix.size();
  vector<bool> toggleMatrix = createToggleMatrix(lOMatrix);

  //Prints the toggle matrix
  cout << endl << "Matrix size: " << toggleMatrix.size() << endl;
  int counter = 0;
  for (int value : toggleMatrix) {
    cout << value << " ";
    counter++;
    if (counter % lOSize == 0) {
        cout << endl;
    }
  }

  return 0;
}