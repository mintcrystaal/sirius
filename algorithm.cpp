#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


struct Rule {
	string to_find, to_replace;
	bool is_term;
	Rule(string _find, string _replace, bool _is_term) {
		to_find = _find;
		to_replace = _replace;
		is_term = _is_term;
	}

	bool step(string &s) {
		int index = s.find(to_find);
		if (index == -1) {
			return false;
		}
		s.replace(index, to_find.size(), to_replace);
		return true;
	}
};


struct Algorithm {
	vector<Rule> substitutions;

	Algorithm(vector<Rule> substitutions_) {
		substitutions = substitutions_;
	}

	bool one_step(string &s, bool &stop) {
		for (Rule rule : substitutions) {
			if (rule.step(s)) {
				if (rule.is_term) {
					stop = true;
				}
				return true;
			}
		}
		return false;
	}

	string apply(string s) {
		bool stop = false;
		while (one_step(s, stop)) {
			if (stop) {
				return s;
			}
			cerr << s << "\n";
		}
		return s;
	}
};


void run(string filename_in, string filename_out) {
	ifstream fin;
	fin.open(filename_in);
	string input;
	fin >> input;
	vector<Rule> markov_substitution;
	string first, second, splitter;
	while (fin >> first >> splitter >> second) {
		if (splitter == "===>") {
			markov_substitution.push_back(Rule(first, second, true));
		} else {
			markov_substitution.push_back(Rule(first, second, false));
		}
	}
	fin.close();
	Algorithm my_algorithm = Algorithm(markov_substitution);
	ofstream fout;
	fout.open(filename_out);
	fout << my_algorithm.apply(input) << "\n";
	fout.close();
	cerr << "done\n";
}


int main() {
	string filename_in, filename_out;
	while (cin >> filename_in >> filename_out) {
		run(filename_in, filename_out);
	}
	return 0;
}
