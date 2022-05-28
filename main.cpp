#include <iostream>
#include <array>
#include <memory>

using namespace std;




int main() {
    std::array<int, 3> first_row = {1,2,3};
    std::array<std::array<int, 3>, 3> b ={
            first_row,
            {4, 5, 6},
            {7, 8, 9}
    };

    std::array<std::array<int, 3>, 2> a={
            first_row,
            {2, 2, 2}
    };

    board.at(0) = {1,2,3};
    board.at(1) = {4,5,6};
    board.at(2) = {7,8,9};
//    int board[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    for (auto &row : board) {
        for (auto &col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
    return 0;
}
