#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>

using namespace std;

enum subj {phys, info, mata};

typedef char fio[16];
typedef char group_f[7];

struct student {
	group_f group;
	fio name;
	fio surename;
	fio patr;
	char gender;
	short int byear;
	short int marks[3];
	int payment;
} test_st;


void print(const student a) {
	cout << a.group << endl << a.name << endl << a.surename << endl << a.patr << endl << a.gender << endl << a.byear << endl;
	cout << a.marks[phys] << endl << a.marks[info] << a.marks[mata] << endl;
	cout << a.payment << endl << endl;
}

void print(const vector<student> a) { for (const auto& i : a) print(i); }

template<class T>
bool compare_great(T& first, T& second){
	return string(first) > string(second);
}
template<class T>
bool compare_less(T& first, T& second) { return !compare_great(first, second); }

#define readfrom(a) from.read((char*)a, sizeof(a));
/// <summary>
/// Reading single from typed
/// </summary>
student Read_from_typed(ifstream& from) {
	student temp;
	
	from.read((char*)&temp, sizeof(temp));
	
	/*
	readfrom(temp.group);
	readfrom(temp.name);
	readfrom(temp.patr);
	readfrom(temp.byear);
	readfrom(temp.gender);
	for (int i = 0; i < 3; i++) readfrom(temp.marks[i]);
	readfrom(temp.payment);
	//*/
	return temp;
}

#undef readfrom(a)

void Read_to_arr_from_typed(ifstream& from, vector<student>& to) {
	while (from.peek() != EOF) to.push_back(Read_from_typed(from));
}

#define writeto(a)  to.write((char*)&a, sizeof(a))
/// <summary>
///  Writing single to typed
/// </summary>
void Write_to_typed(ofstream& to, const student& what) {

	to.write((char*)&what, sizeof(what));
	/*
	writeto(what.group);
	writeto(what.name);
	writeto(what.patr);
	writeto(what.byear);
	writeto(what.gender);
	for (int i = 0; i < 3; i++) writeto(what.marks[i]);
	writeto(what.payment);
	//*/
}

#undef writeto(a)

void Text_to_typed(ifstream& fromtxt, ofstream& todat) {
	student temp;
	
	while (fromtxt.peek() != EOF){
		fromtxt >> temp.group >> temp.name >> temp.surename >> temp.patr >> temp.gender >> temp.byear;
		for (int i = 0; i < 3; i++) fromtxt >> temp.marks[i];
		fromtxt >> temp.payment;
		Write_to_typed(todat, temp);
	}
}

template<typename field_type>
bool compare(const student& a, const student& b, field_type student::* field) {
	///compare by feald;
	if (!(is_same_v<field_type, fio> || is_same_v<field_type, group_f>))
		return a.*field < b.*field;
	else
		return compare_less(a.*field, b.*field);
}


template <typename Tf>
function<bool(const student&, const student&)> wrap_make(Tf student::* field) {
	return [field](const student& a, const student& b) -> bool {return compare(a, b, field); };
}


void quicksort(vector<student>& arr, int low, int high, function<bool(const student&,const student&)> fn) {
	if (low >= high) return;

	student pivot = arr[high];
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (fn(arr[j], pivot)) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);

	int pi = i + 1;
	quicksort(arr, low, pi - 1, fn);
	quicksort(arr, pi + 1, high, fn);
}

// Для одиночного char
string to_str(char c) {
	return string(1, c);
}

// Для C-строк (char*, char[])
string to_str(const char* str) {
	return string(str);
}

template<typename Tf>
vector<student> search(const vector<student>& where, Tf student::* conc, Tf what) {
	vector<student> temp;
	if (is_same_v<Tf, fio> || is_same_v < Tf, group_f>) {
		for (const auto& i : where)
			if (to_str(i.*conc) == to_str(what))
				temp.push_back(i);
	}
	else
		for (const auto& i : where) if (i.*conc == what) temp.push_back(i);
	return temp;
}


template<typename Tf, int n>
vector<student> search(const vector<student>& where, Tf (student::* conc)[n], int subj, Tf what) {
	vector<student> temp;
	for (const auto& i : where)
		if ((i.*conc)[subj] == what)
			temp.push_back(i);
	return temp;
}

template<typename Tf>
int count(const vector<student>& where, Tf student::* conc, Tf what) {
	int count = 0;
	for (const auto& i : where) if (i.*conc == what) count++;
	return count;
}


template<typename Tf, int n>
int count(const vector<student>& where, Tf(student::* conc)[n], int subj, Tf what) {
	int count = 0;
	for (const auto& i : where)
		if ((i.*conc)[subj] == what)
			count++;
	return count;
}


template<typename Tf, int n>
int count(const vector<student>& where, Tf (student::* conc)[n], const Tf* what) {
	int count = 0;
	for (const auto& i : where)
		if (to_str(i.*conc) == to_str(what))
			count++;
	return count;
}