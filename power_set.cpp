#include<iostream>
#include<malloc.h>
#include<math.h>
#include"power_set.h"
using namespace std;
template<typename T>
void power_set(T* inb, int size) {
	int max = pow(2, size);
	for (int round = 0; round < max; round++) {
		for (int r = 0; r <= size; r++) {
			int k = 1,nub;
			k <<= r;
			nub = k & round;
			if(nub)cout << inb[k >> 1];
		}
		cout << endl;
	}
}