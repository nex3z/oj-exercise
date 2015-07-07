#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#define MAX_TEAM_NUM 18

using namespace std;

struct TeamRecord;
typedef struct TeamRecord Team;
void solveE2g();
int inputTeamList(Team teams[], map<string, int> *isTeamedUp);
void printDict(map<string, int> m);
void findMaxTeamNum(int teamId, int teamNum, int totalNum);

struct TeamRecord {
	string member[3];
};

int main() {
	solveE2g();
	return 0;
}

Team teams[MAX_TEAM_NUM];
map<string, int> isTeamedUp;
int maxNum;
void solveE2g() {
	int k;

	k = inputTeamList(teams, &isTeamedUp);
	//printDict(isTeamedUp);

	for (int teamId = 0; teamId < k; ++teamId) {
		//printDict(isTeamedUp);
		isTeamedUp[teams[teamId].member[0]] = 1;
		isTeamedUp[teams[teamId].member[1]] = 1;
		isTeamedUp[teams[teamId].member[2]] = 1;
		findMaxTeamNum(teamId + 1, 1, k);
		isTeamedUp[teams[teamId].member[0]] = 0;
		isTeamedUp[teams[teamId].member[1]] = 0;
		isTeamedUp[teams[teamId].member[2]] = 0;
	}

	cout << maxNum << endl;
}

int inputTeamList(Team teams[], map<string, int> *isTeamedUp) {
	int k;

	scanf("%d\n", &k);
	for (int i = 0; i < k; ++i) {
		cin >> teams[i].member[0] >> teams[i].member[1] >> teams[i].member[2];
		for (int j = 0; j < 3; ++j) {
			if ((*isTeamedUp).count(teams[i].member[j]) == 0) {
				(*isTeamedUp)[teams[i].member[j]] = 0;
			}
		}
	}

	return k;
}

void findMaxTeamNum(int teamId, int teamNum, int totalNum) {
	//printDict(isTeamedUp);
	maxNum = maxNum > teamNum ? maxNum : teamNum;
	if (teamId < totalNum) {
		if (isTeamedUp[teams[teamId].member[0]] == 0 && isTeamedUp[teams[teamId].member[1]] == 0 && isTeamedUp[teams[teamId].member[2]] == 0) {
			isTeamedUp[teams[teamId].member[0]] = 1;
			isTeamedUp[teams[teamId].member[1]] = 1;
			isTeamedUp[teams[teamId].member[2]] = 1;
			findMaxTeamNum(teamId + 1, teamNum + 1, totalNum);
			isTeamedUp[teams[teamId].member[0]] = 0;
			isTeamedUp[teams[teamId].member[1]] = 0;
			isTeamedUp[teams[teamId].member[2]] = 0;

		} 
		findMaxTeamNum(teamId + 1, teamNum, totalNum);
	}
}


void printDict(map<string, int> m) {
	for (map<string, int>::iterator it = m.begin(); it != m.end(); ++it) {
		cout << it->first << " " << it->second << "\n";
	}
	cout << endl;
}