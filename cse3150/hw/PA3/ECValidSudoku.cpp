/*Instructions-
Return True/False if the sudoku board is valid
It is valid if:
	Each row contains non-duplicate values of 1-9
	Each column contains non-duplicate values of 1-9
	Each of the nine 3x3 sub-boxes of the board must contain non-duplicate values of 1-9

Note: "." represents a blank sudoku square
	  The board does not need to be solvable for it to be a valid board
	  You should be able to complete this with an O(n) time complexity
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;


bool ECValidSudoku(vector<vector<string>> &board){
	
	//your code here
	for(int r=0; r<9; r++){
		unordered_set<string> map;
		for(int i=0; i<9; i++){
			if(board[r][i] == ".") { continue; }
			if(map.count(board[r][i])!=0){
				//cout << r << "," << i << endl;
				//cout << board[r][i] << endl;
				return false;
			}
			map.insert(board[r][i]);
		}
	}
	
	for(int c=0; c<9; c++){
		unordered_set<string> map;
		for(int j=0; j<9; j++){
			if(board[j][c] == ".") { continue; }
			if(map.count(board[j][c])!=0)
				return false;
			map.insert(board[j][c]);
		}
	}

	for(int subI=0; subI<9; subI++){
		unordered_set<string> map;
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				int r = (subI/3)*3 + i;
				int c = (subI%3)*3 + j;
				if(board[r][c] == ".") { continue; }
				if(map.count(board[r][c]) != 0)
					return false;
				map.insert(board[r][c]);
			}
		}
	}
	//cout << "true" << endl;
	
	/*vector<int> map(10);
	vector<vector<int>> subMap(10, vector<int>(10));
	for(vector<string> i : board){
		map.clear();
		for(string j : i){
			if(j == ".") { continue; }
			if(map[stoi(j)] != 0)
				return false;
			map[stoi(j)]++;
		}	
	}*/

	return true;

}
