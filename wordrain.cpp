#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <time.h>
// app things
#include <jni.h>
#include "Main_WordRain.h"

void start();

const int WIDTH = 120;
const int HEIGHT = 40;
char word[HEIGHT];
std::string os;

namespace rain {
    class Letter;
    void draw();
    void update();
    void addLetter(int);
    std::vector<Letter> letters;

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
                        std::cout << letter.c;
                    }
                }

                if (!drawed)
                    std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }

    void update () {
        for (Letter& letter : letters) {
            letter.update();
            if (letter.y < 0 || letter.y-10 > HEIGHT)
                letters.erase(remove(letters.begin(), letters.end(), letter), letters.end());
        }
    }

    void addLetter (int x) {
        const int size = sizeof(word)/sizeof(char);
        for (int i=0; i<size; i++) {
            rain::Letter l = rain::Letter(x, word[i]);
            l.y += i;
            letters.push_back(l);
        }
    }
};

JNIEXPORT void JNICALL Java_Main_00024WordRain_rainWord(JNIEnv *, jobject) {
    srand(time(NULL));

    std::ifstream file("message.txt");
    std::string message;
    if (file.is_open()) {
        getline(file, message);
        file.close();
        strcpy(word, message.c_str());
    } else {
        std::cout << "Cannot read file 'message.txt'. Terminating app..." << std::endl;
        std::exit(1);
    }

    while (1) {
        std::cout << "Letters: " << rain::letters.size() << std::endl;
        rain::update();
        rain::draw();

        if (rand() % 4 == 0)
            rain::addLetter(rand() % WIDTH-2);

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        system("clear");
    }
};
