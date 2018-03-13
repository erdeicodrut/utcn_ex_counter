#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

const string fisierText = "/home/oddy/Programming/politehnica/probs.txt";

struct Prob {
	int num;
	string answ;
	bool done;

	Prob(int n, string a, bool t) : num(n), answ(std::move(a)), done(t) {}
};

void init(vector<Prob> &probs) {
	ifstream data(fisierText);

	while (!data.eof()) {

		int nr, d;
		string r;
		bool done;

		data >> nr >> r >> d;

		done = d == 1;

		Prob p = Prob(nr, r, done);

		probs.push_back(p);

	}

	data.close();
}

void out(vector<Prob> &probs, int prob) {
	ofstream g(fisierText);
	for (Prob p : probs) {
		if (p.num == prob)
			g << p.num << " " << p.answ << " " << true << '\n';
		else g << p.num << " " << p.answ << " " << p.done << '\n';
	}
	g.close();
}


int main(int argc, char *argv[]) {

	vector<Prob> probs;

	init(probs);

	if (argc == 1) {
		srand(time(nullptr));
		while (true) {
			int p = rand() % probs.size();
			if (!probs[p].done) {
				cout << probs[p].num << '\n';
				return 0;
			}
		}
	}

	string current_exec_name = argv[0];
	string first_arge;
	vector<string> all_args;

	first_arge = argv[1];
	all_args.assign(argv + 1, argv + argc);


	int nrProb;
	nrProb = atoi(all_args[0].c_str());

	string rasp = all_args[1];

	for (Prob &p : probs) {
		if (p.num != nrProb) continue;

		if (p.answ == rasp) {
			cout << "Bravo!\n";
			p.done = true;
			out(probs, p.num);
			return 0;
		} else {
			cout << "Mai incearca\n";
		}
	}


	return 0;
}
