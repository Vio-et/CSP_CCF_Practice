#include <bits/stdc++.h>

using namespace std;

class Matrix {
    int row;
    int column;
    long long** data;
public:
    Matrix(int row = 0,int column = 0);
    Matrix(const Matrix& matrix);
    void initMatrix();
    void outputMatrix();
    void transposeMatrix();
    Matrix crossProduct(const Matrix& matrixA, const Matrix& matrixB);
    void dotProduct(const Matrix& vector);
    ~Matrix();
};

int main() {
    int n = 0, d = 0;

    cin >> n >> d;

    Matrix Q(n, d), K(n, d), V(n, d), W(1, n), result(n,d);

    Q.initMatrix();
    K.initMatrix();
    V.initMatrix();
    W.initMatrix();

    K.transposeMatrix();


  	// Matrix productMatrix(result.crossProduct(Q, K));
	// productMatrix.dotProduct(W);

  	// result.crossProduct(productMatrix, V).outputMatrix();
   
	Matrix crossProductKV(result.crossProduct(K, V));
	Matrix crossProductQKV(result.crossProduct(Q, crossProductKV));
	crossProductQKV.dotProduct(W);
	crossProductQKV.outputMatrix();

    return 0;
}

Matrix::Matrix(int row,int column) {
    this->row = row, this->column = column;

    data = new long long* [row];

    for(int i = 0; i < row; i++)
        data[i] = new long long[column];

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            data[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix &matrix) {
    this->row = matrix.row, this->column = matrix.column;

    data = new long long * [row];

    for(int i = 0; i < row; i++)
        data[i] = new long long[column];

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            data[i][j] = matrix.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    for(int i = 0; i < row; i++)
        delete[] data[i];

    delete[] data;
}

void Matrix::initMatrix() {
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            cin >> data[i][j];
        }
    }
}

void Matrix::outputMatrix() {
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++)
            cout << data[i][j] << " ";
        cout << endl;
    }
}

void Matrix::transposeMatrix() {
    Matrix result(this->column, this->row);

    for(int i = 0; i < this->column; i++){
        for(int j = 0; j < this->row; j++){
            result.data[i][j] = this->data[j][i];
        }
    }

    for(int i = 0; i < row; i++)
        delete[] data[i];
    delete[] data;

    this->row = result.row;
    this->column = result.column;
    data = new long long* [row];

    for(int i = 0; i < row; i++)
        data[i] = new long long[column];

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            data[i][j] = result.data[i][j];
        }
    }
}

Matrix Matrix::crossProduct(const Matrix& matrixA, const Matrix& matrixB) {
    Matrix result(matrixA.row, matrixB.column);

    for(int i = 0; i < result.row; i++){
        for(int j = 0; j < result.column; j++){
            for(int k = 0; k < matrixA.column; k++)
                result.data[i][j] += matrixA.data[i][k] * matrixB.data[k][j];
        }
    }
    
    return result;
}

void Matrix::dotProduct(const Matrix& vector) {
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            data[i][j] *= vector.data[0][i];
        }
    }
}
