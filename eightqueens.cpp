#include<iostream>
#include<string.h>
#include<unordered_map>
#include<random>
#include<algorithm>
using namespace std;

int perm[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
int total_soluions = 0;
int total_perms = 0;
class Options{
    public:
        int options[9] = {0, 0, 0, 0, 0, 0, 0, -1};
};

Options generate_options(int perm[8]){ // Find numbers from 0 to 7 NOT included in perm
    Options options;
    int potential_entries[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    for(int i = 0; i < 8; i++){
        potential_entries[perm[i]] = -1;
    }
    int j = 0;
    for(int i = 0; i < 8; i++){
        if(potential_entries[i] != -1){
            options.options[j] = potential_entries[i]; j++;
        }
    }
    for(int i = 0; j + i < 9; i++){
        options.options[j + i] = -1;
    }
    for(int i = 0; i < 9; i++){
    }
    return options;
}

// ------------------------------------ Can the queens see each other? ------------------------------------

bool queen_check(int perm[8]){
    int attackers = 0;
    int board[8][8] = {0};
    for(int i = 0; i < 8; i++){
        board[i][perm[i]] = 1;
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == 1){
                board[i][j] = 0;
                for(int k = 0; i + k < 8 and j + k < 8; k++){ // Down & Right
                    attackers += board[i + k][j + k];
                    if(attackers > 0){return true;}
                }
                for(int k = 0; i - k >= 0 and j + k < 8; k++){ // Up & Right
                    attackers += board[i - k][j + k];
                    if(attackers > 0){return true;}
                }
                for(int k = 0; i + k < 8 and j - k >= 0; k++){ // Down & Left
                    attackers += board[i + k][j - k];
                    if(attackers > 0){return true;}
                }
                for(int k = 0; i - k >= 0 and j - k >= 0; k++){ // Up & Left
                    attackers += board[i - k][j - k];
                    if(attackers > 0){return true;}
                }
            }
        }
    }
    return false;
}

// ------------------------------------ Search ------------------------------------

int search(int depth){
    if(depth == 0){
        total_perms++;
        if(!queen_check(perm)){ total_soluions++;
            for(int i = 0; i < 8; i++){ cout << perm[i];} cout << endl;
        }
        return 0;
    }
    int prev_state[8] = {0}; memcpy(prev_state, perm, sizeof(perm));
    Options options = generate_options(perm);
    for(int i = 0; options.options[i] != -1; i++){
        perm[8 - depth] = options.options[i];
        search(depth - 1);
        memcpy(perm, prev_state, sizeof(prev_state));
    }
    return 0;
}

// ------------------------------------ Execution ------------------------------------

int main(void){

    search(8);

    cout << "Total positions tested: " << total_perms << endl;
    cout << "Total peaceful positions found: " << total_soluions << endl;

}