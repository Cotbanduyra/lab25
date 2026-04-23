#include <iostream>
#include "work.h"

bool comp(char* a, char* b) {
	cout << string(a) << endl;
	return string(a) > string(b);
}

int main(int argc, char* argv[]) {
	///scope for txt => dat
	{
		ifstream ifs(argv[1]);
		ofstream ofs(argv[2], ios::binary);
		Text_to_typed(ifs, ofs);
		ofs.close();
	}

	vector<student> list_of_educ;
	ifstream ifs(argv[2], ios::binary);
	Read_to_arr_from_typed(ifs, list_of_educ);

	print(list_of_educ); cout << endl;

	quicksort(list_of_educ, 0, list_of_educ.size() - 1, wrap_make(&student::surename));

	print(list_of_educ); cout << endl;

	list_of_educ = search(list_of_educ, &student::marks, subj::info, short(5));

	print(list_of_educ); cout << endl;

//	for (const auto& i : list_of_educ) cout << i.name << endl;

	vector<student> searched = search(search(list_of_educ, &student::marks, info, short(5)), &student::gender, 'M');

	print(searched);

	
 	cout << count(searched, &student::group, "A-5-10") << "  000asdasd\n";


	return 0;

	
}
