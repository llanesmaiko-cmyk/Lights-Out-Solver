#include <iostream>
#include <cmath>
#include <iterator>
#include <vector>

using namespace std;


//Complete a XOR operation of row 2 to row 1
void xorRow(vector<bool> & toggleMatrix, vector<bool> & lOMatrix, int row1, int row2) {
  int rowSize = sqrt(toggleMatrix.size());
  int row1Location = (row1 - 1) * rowSize;
  int row2Location = (row2 - 1) * rowSize;

  //Iterates through two rows of the toggle matrix, XORs row 2 to row 1
  for (int i = 0; i < rowSize; i++) {
    toggleMatrix[row1Location + i] = toggleMatrix[row1Location + i] ^ toggleMatrix[row2Location + i];
  }
  //XORs the positions in the lights out matrix that correspond to the rows that were XORed
  lOMatrix[row1 - 1] = lOMatrix[row1 - 1] ^ lOMatrix[row2 - 1];
}


//Swap row 1 and row 2
void swapRow(vector<bool> & toggleMatrix, vector<bool> & lOMatrix, int row1, int row2) {
  int rowSize = sqrt(toggleMatrix.size());
  int row1Location = (row1 - 1) * rowSize;
  int row2Location = (row2 - 1) * rowSize;
  int temp = 0;

  //Iterates through two rows of the toggle matrix, swaps row 2 to row 1
  for (int i = 0; i < rowSize; i++) {
    temp = toggleMatrix[row1Location + i];
    toggleMatrix[row1Location + i] = toggleMatrix[row2Location + i];
    toggleMatrix[row2Location + i] = temp;
  }
  //Swaps the positions in the lights out matrix that correspond to the rows that were swaped
  temp = lOMatrix[row1 - 1];
  lOMatrix[row1 - 1] = lOMatrix[row2 - 1];
  lOMatrix[row2 - 1] = temp;
}

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

//Create the toggle matrix and convert to RREF
void solveLightsOut (vector<bool> & lOMatrix) {
  vector<bool> toggleMatrix = createToggleMatrix(lOMatrix);
  int rowI = 0;
  int rowJ = 1;
  
  //Iterate through the matrix. Chose the next pivot to be along the diagonal.
  for (int i = 0; i < toggleMatrix.size(); i += lOMatrix.size() + 1) {
    rowI++;
    //If the pivot = 0, attempt to swap a row below the pivot that = 1 on the same column.
    if (toggleMatrix[i] == 0) {
      rowJ = rowI;
      //Find a 1 in the column below and swap the corresponding row
      for (int j = i; j < toggleMatrix.size(); j += lOMatrix.size()) {
        if (toggleMatrix[j] == 1) {
          swapRow(toggleMatrix, lOMatrix, rowI, rowJ);
        }
        rowJ++;
      }
    }

    rowJ = 1;
    //Check if any other number in the pivot column = 1
    for (int j = i % lOMatrix.size(); j < toggleMatrix.size(); j += lOMatrix.size()) {
      if (toggleMatrix[j] == 1 && rowJ != rowI && j != i) {
        //XOR the row that has a 1 by the pivot row
        xorRow(toggleMatrix, lOMatrix, rowJ, rowI);
      }

      rowJ++;
    }

    rowJ = 1;
  }

  rowI = 0;

  //Check if there is no solution
  for (int i = 0; i < toggleMatrix.size(); i += lOMatrix.size() + 1) {
    if (toggleMatrix[i] == 0 && lOMatrix[rowI] == 1) {
      lOMatrix = {0};
      break;
    }
    rowI++;
  }
}

int main() {
  //Lights Out input
    //0=off 1=on
  vector<bool> lOMatrix = {
    1,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0};

  int rowSize = sqrt(lOMatrix.size());
  vector<bool> toggleMatrix = createToggleMatrix(lOMatrix);
  //swapRow(toggleMatrix, lOMatrix, 2, 9);
  solveLightsOut(lOMatrix);

  int counter = 0;
  //Print the Lights Out matrix
  cout << endl << "Matrix size: " << lOMatrix.size() << endl;
  for (int value : lOMatrix) {
    cout << value << " ";
    counter++;
    if (counter % rowSize == 0) {
        cout << endl;
    }
  }

  return 0;
}