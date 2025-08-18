#include <iostream>
using namespace std;

int main()
{

          int matrix[5][4];    // Initializing Matrix of 5 rows and 4 columns
          int sparsem[21][3];

          sparsem[0][0] = 5;
          sparsem[0][1] = 4;
          sparsem[0][2] = 0;

          int k = 1;

          for (int i = 0; i < 5; i++)
          {
                    for (int j = 0; j < 4; j++)
                    {
                              cout << "Enter marks at indices: " << i << " " << j << " : ";   // Entering marks of students per course according to the indices of matrix
                              cin >> matrix[i][j];
                    }
          }

          cout << "\nRows - Students, Columns - Courses" << endl;   // Display in the matrix
          for (int i = 0; i < 5; i++)
          {
                    for (int j = 0; j < 4; j++)
                    {
                              cout << matrix[i][j] << " ";
                    }
                    cout << endl;
          }

          for (int i = 0; i < 5; i++)
          {
                    for (int j = 0; j < 4; j++)
                    {
                              if (matrix[i][j] != 0)
                              {
                                        sparsem[k][0] = i;
                                        sparsem[k][1] = j;
                                        sparsem[k][2] = matrix[i][j];
                                        k++;
                              }
                    }
          }
          sparsem[0][2] = k - 1;

          cout << "Sparse Matrix :" << endl;  // Display the sparse matrix
          for (int i = 0; i < k; i++)
          {
                    cout << sparsem[i][0] << " " << sparsem[i][1] << " " << sparsem[i][2] << endl;
          }

          double s_marks[5];
          int s_count[5];
          double c_avg[4];
          int c_count[4];

          for (int i = 0; i < 5; i++)
          {
                    s_marks[i] = 0;
                    s_count[i] = 0;
          }
          for (int j = 0; j < 4; j++)
          {
                    c_avg[j] = 0;
                    c_count[j] = 0;
          }

          for (int i = 0; i < 5; i++)
          {
                    for (int j = 0; j < 4; j++)
                    {
                              s_marks[i] += matrix[i][j];
                              if (matrix[i][j] != 0)
                              {
                                        s_count[i]++;
                              }
                              c_avg[j] += matrix[i][j];
                              if (matrix[i][j] != 0)
                              {
                                        c_count[j]++;
                              }
                    }
          }

          for (int i = 0; i < 5; i++)
          {
                    if (s_count[i] != 0)
                              s_marks[i] = s_marks[i] / s_count[i];
          }
          for (int j = 0; j < 4; j++)
          {
                    if (c_count[j] != 0)
                              c_avg[j] = c_avg[j] / c_count[j];
                    else
                              c_avg[j] = 0;
          }

          cout << "Average marks per student:" << endl;   // Display average marks per student
          for (int i = 0; i < 5; i++)
          {
                    cout << "Student " << (i + 1) << ": " << s_marks[i] << endl;
          }

          cout << "Average marks per course:" << endl;   // Display average marks per course
          for (int j = 0; j < 4; j++)
          {
                    cout << "Course " << (j + 1) << ": " << c_avg[j] << endl;
          }

          return 0;

}
