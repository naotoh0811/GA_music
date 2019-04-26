#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
#include <stdlib.h> //自宅PCのbashの環境だと必要
#include <sys/time.h> //gettimeofday
using namespace std;

const int chord_number = 30;
const int gen_size = 300;
const int bar_MAX = 24; //最大小節数
const int leave_number = 10; //上位何個をスワップせず残すか
const int mutation_rate = 1; //突然変異率(%)

void begin(int chord_prog[chord_number][bar_MAX + 1], int bar) {
	struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned int)tv.tv_sec * ((unsigned int)tv.tv_usec + 1));
	for (int i = 0; i < chord_number; i++) {
		for (int j = 0; j < bar; j++) {
			chord_prog[i][j] = rand() % 6;
		}
	}
};

void eva(int chord_prog[chord_number][bar_MAX + 1], int bar) {
	for (int i = 0; i < chord_number; i++) { //ポイントを50にリセット
		chord_prog[i][bar] = 50;
	}

	for (int i = 0; i < chord_number; i++) {
		if (chord_prog[i][0] == 0 && chord_prog[i][bar - 1] == 0)chord_prog[i][bar] += 6; //最初と最後
		else if (chord_prog[i][0] == 5 && chord_prog[i][bar - 1] == 5)chord_prog[i][bar] += 5;
		else if (chord_prog[i][0] == 3 && chord_prog[i][bar - 1] == 0)chord_prog[i][bar] += 4;
		else chord_prog[i][bar] -= 6;

		for (int j = 0; j < bar - 1; j++) {
			if (chord_prog[i][j + 1] - chord_prog[i][j] == 3 || chord_prog[i][j] - chord_prog[i][j + 1] == 4)chord_prog[i][bar] += 1; //5度下進行

			if (chord_prog[i][j] == 0 || chord_prog[i][j] == 5) { //カデンツ
				if (chord_prog[i][j + 1] == 1 || chord_prog[i][j + 1] == 3 || chord_prog[i][j + 1] == 4)chord_prog[i][bar] += 1;
			}
			if (chord_prog[i][j] == 1 || chord_prog[i][j] == 3) {
				if (chord_prog[i][j + 1] == 4)chord_prog[i][bar] += 2;
				if (chord_prog[i][j + 1] == 0 || chord_prog[i][j + 1] == 5)chord_prog[i][bar] += 1;
			}
			if (chord_prog[i][j] == 4) {
				if (chord_prog[i][j + 1] == 1 || chord_prog[i][j + 1] == 3)chord_prog[i][bar] -= 3;
				if (chord_prog[i][j + 1] == 0 || chord_prog[i][j + 1] == 5)chord_prog[i][bar] += 2;
			}
		}
	}
}

void sort(int chord_prog[chord_number][bar_MAX + 1], int bar) {
	for (int i = 0; i < (chord_number - 1); i++) {
		for (int j = (chord_number - 1); j > i; j--) {
			if (chord_prog[j - 1][bar] > chord_prog[j][bar]) {
				for (int ii = 0; ii < bar + 1; ii++) {
					int temp = chord_prog[j - 1][ii];
					chord_prog[j - 1][ii] = chord_prog[j][ii];
					chord_prog[j][ii] = temp;
				}
			}
		}
	}
}

void swap(int chord_prog[chord_number][bar_MAX + 1], int bar) {
	int pre_chord_prog[chord_number][bar_MAX + 1] = {};
	for (int i = 0; i < chord_number; i++) {
		for (int j = 0; j < bar + 1; j++) {
			pre_chord_prog[i][j] = chord_prog[i][j];
		}
	}

	for (int i = 0; i < (chord_number - leave_number) / 2; i++) { //交叉
		int upper1 = rand() % leave_number + (chord_number - leave_number);
		int upper2 = rand() % leave_number + (chord_number - leave_number);
		//始まりと終わりの各2小節をスワップ
		for (int j = 0; j < bar; j++){
			if (j < 2 || j > (bar - 3))chord_prog[i * 2][j] = pre_chord_prog[upper1][j];
			else chord_prog[i * 2][j] = pre_chord_prog[upper2][j];
		}
		for (int j = 0; j < bar; j++){
			if (j < 2 || j > (bar - 3))chord_prog[i * 2 + 1][j] = pre_chord_prog[upper2][j];
			else chord_prog[i * 2 + 1][j] = pre_chord_prog[upper1][j];
		}

	}

	for (int i = 0; i < chord_number; i++) { //突然変異
		for (int j = 0; j < bar + 1; j++) {
			if (rand() % 100 < mutation_rate)chord_prog[i][j] = rand() % 6;
		}
	}
}

string num2chord(int num) {
	string chord;
	switch (num) {
		case 0:
			chord = "C ";
			break;
		case 1:
			chord = "Dm";
			break;
		case 2:
			chord = "Em";
			break;
		case 3:
			chord = "F ";
			break;
		case 4:
			chord = "G ";
			break;
		case 5:
			chord = "Am";
			break;
		}
	return chord;
}

void show_chordlist(int chord_prog[chord_number][bar_MAX + 1], int bar) {
	for (int i = 0; i < chord_number; i++) {
		for (int j = 0; j < bar + 1; j++) {
			if (j != bar)cout << num2chord(chord_prog[i][j]) << " ";
			else cout << chord_prog[i][j];
		}
		cout << endl;
	}
}

void show_lastchord(int chord_prog[chord_number][bar_MAX + 1], int bar) {
	for (int i = 0; i < bar + 1; i++) {
		if (i != bar)cout << num2chord(chord_prog[chord_number - 1][i]) << " ";
		else cout << chord_prog[chord_number - 1][i];
	}
	cout << endl;
}

void show_lastchord_line(int chord_prog[chord_number][bar_MAX + 1], int bar) {
	for (int i = 0; i < bar; i++) {
		cout << num2chord(chord_prog[chord_number - 1][i]) << endl;
	}
}

int main(int argc, char* argv[]) {
	if(argc == 1){
		cout << "[ERROR] Please put argument." << endl;
		return 1;
	}
	
	int chord_prog[chord_number][bar_MAX + 1] = {};
	int bar = atoi(argv[1]);
	begin(chord_prog, bar);
	eva(chord_prog, bar);
	sort(chord_prog, bar);
	//show_chordlist(chord_prog, bar);
	for (int i = 0; i < gen_size; i++) {
		/*if (i % 100 == 0 || i == gen_size - 1){
			cout << i << "gen. " << chord_prog[chord_number - 1][bar] << endl;
		}*/
		swap(chord_prog, bar);
		eva(chord_prog, bar);
		sort(chord_prog, bar);
	}
	//show_chordlist(chord_prog, bar);
	show_lastchord_line(chord_prog, bar);
}
