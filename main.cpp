#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// ================= Matrix class definition =================

const int MAX_SIZE = 100;

class Matrix
{
private:
    int size;
    int data[MAX_SIZE][MAX_SIZE];

public:
    // constructors
    Matrix();
    Matrix(int n);

    // getters and setters
    int getSize() const;
    int getValue(int row, int col) const;
    void setValue(int row, int col, int value);

    // display the matrix
    void print() const;

    // operator overloading
    Matrix operator+(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
};

// reads two matrices from a file, returns true if it worked
bool readMatricesFromFile(string filename, Matrix &A, Matrix &B);

// practice 4
void printDiagonalSums(const Matrix &m);

// practice 5, 6, 7 (pass by value so original is not changed)
void swapRows(Matrix m, int row1 = 0, int row2 = 1);
void swapColumns(Matrix m, int col1 = 0, int col2 = 1);
void updateElement(Matrix m, int row = 0, int col = 0, int newValue = 100);

// ================= Matrix function code =================

// default constructor
Matrix::Matrix()
{
    size = 0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            data[i][j] = 0;
        }
    }
}

// constructor with size
Matrix::Matrix(int n)
{
    size = n;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            data[i][j] = 0;
        }
    }
}

int Matrix::getSize() const
{
    return size;
}

int Matrix::getValue(int row, int col) const
{
    return data[row][col];
}

void Matrix::setValue(int row, int col, int value)
{
    data[row][col] = value;
}

// prints the matrix with columns lined up
void Matrix::print() const
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << setw(4) << data[i][j];
        }
        cout << endl;
    }
}

// practice 2: add two matrices
Matrix Matrix::operator+(const Matrix &other) const
{
    Matrix result(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// practice 3: multiply two matrices
Matrix Matrix::operator*(const Matrix &other) const
{
    Matrix result(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int sum = 0;
            for (int k = 0; k < size; k++)
            {
                sum = sum + data[i][k] * other.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

// practice 1: read the file
bool readMatricesFromFile(string filename, Matrix &A, Matrix &B)
{
    ifstream inFile;
    inFile.open(filename);

    if (!inFile)
    {
        cout << "Error: could not open file " << filename << endl;
        return false;
    }

    int n;
    inFile >> n;

    if (n <= 0 || n > MAX_SIZE)
    {
        cout << "Error: matrix size must be between 1 and " << MAX_SIZE << endl;
        return false;
    }

    A = Matrix(n);
    B = Matrix(n);

    int value;

    // read first matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inFile >> value;
            A.setValue(i, j, value);
        }
    }

    // read second matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inFile >> value;
            B.setValue(i, j, value);
        }
    }

    inFile.close();
    return true;
}

// practice 4: sum of main and secondary diagonals
void printDiagonalSums(const Matrix &m)
{
    int n = m.getSize();
    int mainSum = 0;
    int secondarySum = 0;

    for (int i = 0; i < n; i++)
    {
        mainSum = mainSum + m.getValue(i, i);
        secondarySum = secondarySum + m.getValue(i, n - 1 - i);
    }

    cout << "Main diagonal sum: " << mainSum << endl;
    cout << "Secondary diagonal sum: " << secondarySum << endl;
}

// practice 5: swap two rows
void swapRows(Matrix m, int row1, int row2)
{
    int n = m.getSize();

    if (row1 < 0 || row1 >= n || row2 < 0 || row2 >= n)
    {
        cout << "Error: invalid row index" << endl;
        return;
    }

    for (int j = 0; j < n; j++)
    {
        int temp = m.getValue(row1, j);
        m.setValue(row1, j, m.getValue(row2, j));
        m.setValue(row2, j, temp);
    }

    cout << "Problem 5 - Rows " << row1 << " and " << row2 << " swapped:" << endl;
    m.print();
}

// practice 6: swap two columns
void swapColumns(Matrix m, int col1, int col2)
{
    int n = m.getSize();

    if (col1 < 0 || col1 >= n || col2 < 0 || col2 >= n)
    {
        cout << "Error: invalid column index" << endl;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        int temp = m.getValue(i, col1);
        m.setValue(i, col1, m.getValue(i, col2));
        m.setValue(i, col2, temp);
    }

    cout << "Problem 6 - Columns " << col1 << " and " << col2 << " swapped:" << endl;
    m.print();
}

// practice 7: update one element
void updateElement(Matrix m, int row, int col, int newValue)
{
    int n = m.getSize();

    if (row < 0 || row >= n || col < 0 || col >= n)
    {
        cout << "Error: invalid index" << endl;
        return;
    }

    m.setValue(row, col, newValue);

    cout << "Problem 7 - Updated matrix:" << endl;
    m.print();
}

// ================= main program =================

int main()
{
    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    Matrix A;
    Matrix B;

    // practice 1
    if (!readMatricesFromFile(filename, A, B))
    {
        return 1;
    }

    cout << endl
         << "Matrix A:" << endl;
    A.print();
    cout << endl
         << "Matrix B:" << endl;
    B.print();

    // practice 2
    Matrix sum = A + B;
    cout << endl
         << "A + B:" << endl;
    sum.print();

    // practice 3
    Matrix product = A * B;
    cout << endl
         << "A * B:" << endl;
    product.print();

    // practice 4
    cout << endl
         << "Diagonal sums for Matrix A:" << endl;
    printDiagonalSums(A);

    // practice 5 (default would be rows 0 and 1, here we use 0 and 2)
    cout << endl;
    swapRows(A, 0, 2);

    // practice 6 (default would be columns 0 and 1, here we use 0 and 2)
    cout << endl;
    swapColumns(A, 0, 2);

    // practice 7 (default would be [0][0] = 100, here we use [1][2] = 99)
    cout << endl;
    updateElement(A, 1, 2, 99);

    return 0;
}