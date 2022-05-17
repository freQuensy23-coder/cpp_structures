#include<cstddef>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

struct subvector {
     int *mas;  		// Массив для хранения данных
     unsigned int top; 		// Сдвиг первого элемента
     unsigned int capacity;	// Длинна
};

bool init(subvector *subvec) {
	subvec->mas = NULL;
	subvec->top = 0;
	subvec->capacity = 0;
	return true;
}

void clear(subvector *subvec) {
	subvec->top = 0;
}

void destructor(subvector *subvec) {
	delete[] subvec->mas;
	init(subvec);
}

bool push_back(subvector *subvec, int d) {
	if (subvec->top + 1 > subvec->capacity) {   // Проверка на выход за пределы выделеной памяти
		int * new_mas = new int[subvec->capacity + 1]; // Переместить массив в новое место, удлинить его
		for (int i = 0; i< subvec->capacity; i++) {
			new_mas[i] = subvec->mas[i];
		}
		new_mas[(*subvec).capacity] = d;
	    delete[] subvec->mas;
		subvec->mas = new_mas;
		subvec->capacity = subvec->capacity + 1;
		subvec->top++;
	} else {
		subvec->mas[subvec->top] = d; // Если все хорошо просто записать след элемент
		subvec->top++;
	}
	return true;
}


bool resize(subvector *subvec, unsigned int new_capacity) {
	if ((*subvec).top > new_capacity) {
		int * new_mas = new int[new_capacity];
		for (int i = 0; i < new_capacity; i++) {
			new_mas[i] = (*subvec).mas[i];
		}
	    delete[] (*subvec).mas;
		(*subvec).mas = new_mas;
		(*subvec).capacity = new_capacity;
		subvec->top = new_capacity;

		return true;
	} else {
		int * new_mas = new int[new_capacity];
		for (int i = 0; i < (*subvec).top; i++) {
			new_mas[i] = (*subvec).mas[i];
		}
	    delete[] (*subvec).mas;
		(*subvec).mas = new_mas;
		(*subvec).capacity = new_capacity;
		return true;
	}
}

int pop_back(subvector *subvec) {
	if (subvec->top <=0) { // Получить элемент из пустого сабвектора
		//raise(SIGSEGV); ????? какие то беды с профайлером   
		return 0;
	}
	int el = subvec->mas[subvec->top - 1]; 
	subvec->top--;
	return el;
}


void shrink_to_fit(subvector *subvec) {
	subvec->capacity = subvec->top;
	int * new_mas = new int[subvec -> capacity];
	for (int i = 0; i < (*subvec).top; i++) {
		new_mas[i] = (*subvec).mas[i];
	}
	delete[] (*subvec).mas;
	(*subvec).mas = new_mas;

}

