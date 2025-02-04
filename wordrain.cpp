#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cstring>
#include <fstream>

#include <jni.h>
#include "Main_WordRain.h"

#include <stdlib.h>
#include <time.h>

using namespace std;

class Letter;

const int WIDTH = 120;
const int HEIGHT = 40;
string os;
vector<Letter> letters;
char word[HEIGHT]; // = {'T', 'E', 'S', 'T', 'N', 'A', 'T', 'V'};

class Letter {
    public:
        char c;
        int x, y;
        
        Letter(int x, char c) {
            this->x = x;
            this->y = HEIGHT;
            this->c = c;
        }
        void update () {
            y--;
        }
        bool operator==(const Letter& other) const {
            return this->x == other.x && this->y == other.y && this->c == other.c;
        }
};

void draw () {
    for (int i=HEIGHT; i>0; i--) { // y
        for (int j=WIDTH; j>0; j--) { // x
            bool drawed = false;

            for (Letter& letter : letters) {
                if (letter.x==j&&letter.y==i) {
                    drawed = true;
                    cout << letter.c;
                }
            }

            if (!drawed) {
                cout << ' ';
            }
        }

        cout << endl;
    }

}

void update () {
    for (Letter& letter : letters) {
        letter.update();
        if (letter.y < 0 || letter.y-10 > HEIGHT) {
            letters.erase(remove(letters.begin(), letters.end(), letter), letters.end());
        }
    }
}

void addLetter (int x) {
    const int size = sizeof(word)/sizeof(char);

    for (int i=0; i<size; i++) {
        Letter l = Letter(x, word[i]);
        l.y += i;

        letters.push_back(l);
    }
}

void start ()
{
    //initWord();
    srand(time(NULL));

    // init string
    ifstream file("message.txt");
    string message;
    if (file.is_open()) {
        getline(file, message);
        file.close();

        strcpy(word, message.c_str());
    } else {
        cout << "cannot read file idk :(" << endl;
    }

    // start
    while (1) {
        cout << "Letters: " << letters.size() << endl;
        update();
        draw();

        if (rand() % 4 == 0) {
            addLetter(rand() % WIDTH-2);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        system("clear");
        //system("cls");
    }

}

// JNIEXPORT void JNICALL Java_Main$WordRain_rainWord (JNIEnv *env, jobject obj) { // maybe replace with __
//     start();
// } // this was the problem

JNIEXPORT void JNICALL Java_Main_00024WordRain_rainWord(JNIEnv *, jobject) {
    start();
};

