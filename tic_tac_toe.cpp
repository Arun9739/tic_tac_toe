#include <iostream>
using namespace std;

#define CPU 'X'
#define HUMAN 'O'
#define MAX CPU
#define MIN HUMAN
#define WIN_SCORE 10
#define LOOSE_SCORE -10

char* getSurface();
void showSurafce(char*);
bool checkMove(char*, char, int);
bool checkWin(char*);
int best_move(char*);
int findGood(char*, int, bool);
bool moves_left(char*);

int main(){    
    char* surface = getSurface();

    int n, move = 1;
    char player;
    bool win;
     do {
        // player = (move_num%2 == 0) ? HUMAN : CPU ;
        player = (move%2 == 0) ? CPU : HUMAN ;
        if (player == CPU) {
            int move = best_move(surface);
            surface[move] = player;
        } 
        else {
            showSurafce(surface);
            cout<<"Enter your move: ";
            cin>>n;
            if (!checkMove(surface, player, n-1)) {
                cout<<"Sorry ! Cannot move there ! Try again"<<endl;
                continue;
            }
        }

        win = checkWin(surface);
        if (win)
            break;
        move++;
    } while (!win && move<10);
    showSurafce(surface);
    if (win)    
        cout<< player<<" wins"<<endl;
    else
        cout<<"OOPS ! Match draw"<<endl;
    return 0;
}

char* getSurface(){
    static char surface[]  = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    return surface;
}

void showSurafce(char* surface){
    for(int i = 0; i < 9; i++){
        cout << *(surface+i);
        if((i + 1) % 3 == 0 && i != 8){
            cout << endl;
            cout << "---------";
            cout << endl;
        }
        else if(i != 8)
            cout << " | ";
    }
    cout << endl; 
}

bool checkMove(char* surface, char player, int index){
    if(surface[index] == ' '){
        surface[index] = player;
        return true;
    }
    return false;
}

bool checkWin(char* surface){
    bool win = false;
    if(surface[0] != ' ' && surface[0] == surface[4] && surface[4] == surface[8])
        win = true;
    else if(surface[2] != ' ' && surface[2] == surface[4] && surface[4] == surface[6])
        win = true;
    else if(surface[0] != ' ' && surface[0] == surface[1] && surface[1] == surface[2])
        win = true;
    else if(surface[3] != ' ' && surface[3] == surface[4] && surface[4] == surface[5])
        win = true;
    else if(surface[6] != ' ' && surface[6] == surface[7] && surface[7] == surface[8])
        win = true;
    else if(surface[0] != ' ' && surface[0] == surface[3] && surface[3] == surface[6])
        win = true;
    else if(surface[1] != ' ' && surface[1] == surface[4] && surface[4] == surface[7])
        win = true;
    else if(surface[2] != ' ' && surface[2] == surface[5] && surface[5] == surface[8])
        win = true;
    return win;
}

int best_move(char* surface){
     
    int best_score = -1000;
    int best_move;
    int move_score;
    for (int i=0; i<9 ; i++) {
        if (surface[i] == ' ') {
 
            surface[i] = MAX;
 
            move_score = findGood(surface, 1, false);
            if (best_score <= move_score) {
                best_move = i;
                best_score = move_score;
            }
            surface[i] = ' ';
        }
    }
    return best_move;

}

int findGood(char* surface, int depth, bool power){
    int win = checkWin(surface);
    if (win && !power) 
        return WIN_SCORE - depth;
    else if (win && power) 
        return LOOSE_SCORE + depth;
 
    if (!moves_left(surface)) 
        return 0;
 
    if (power) {
        int best_score = -1000;
        for (int i=0; i<9 ; i++) {
            if (surface[i] == ' ') {
                surface[i] = MAX;
                best_score = max(best_score, findGood(surface, depth+1, false));
                surface[i] = ' ';
            }
        }
        return best_score;
    } else {
        int best_score = 1000;
        for (int i=0; i<9 ; i++) {
            if (surface[i] == ' ') {
                surface[i] = MIN;
                best_score = min(best_score, findGood(surface, depth+1, true));
                surface[i] = ' ';
            }
        }
        return best_score;
    }
}

bool moves_left(char* surface){
    for(int i = 0; i < 9; i++){
        if(surface[i] == ' '){
            return true;
        }
    }
    return false;
}