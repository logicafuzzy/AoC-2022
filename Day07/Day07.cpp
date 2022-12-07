#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <cassert>
#include <sstream>
#include <optional>
#include <memory>

using namespace std;

struct dir {
	int filesize = 0;
	string name = "";
	vector<dir> subdirs;
	dir* prev = nullptr;

	int getSize() {
		return filesize + accumulate(subdirs.begin(), subdirs.end(), 0,
			[](int acc, dir d) {return acc + d.getSize(); });
	};

	int getSizeIf(int thresh) {
		int size = 0;
		for (dir& d : subdirs) {
			int sized = d.getSize();
			if (sized < thresh)
				size += sized;

			size += d.getSizeIf(thresh);
		}

		return size;
	}

	vector<int> getSubdirSize() {
		vector<int> subdirsize;
		for (dir& d : subdirs) {
			subdirsize.push_back(d.getSize());
			vector<int> s = d.getSubdirSize();
			subdirsize.insert(subdirsize.end(), s.begin(), s.end());
		}

		return subdirsize;
	}

	dir* getDir(string name) {
		for (dir& d : subdirs)
			if (d.name.compare(name) == 0)
				return &d;
		dir* d{};
		assert(false);
		return d;
	}
};

dir* getTree(string filename) {
	ifstream input(filename);

	dir* root = new dir{ 0, "/", {}, nullptr };
	dir* current = root;

	string currentcmd = "";

	while (input) {
		string line;
		getline(input, line);

		if (line.length() == 0)
			break;

		string start;
		istringstream sline(line);
		getline(sline, start, ' ');

		if (start.compare("$") == 0) {
			string cmd;
			getline(sline, cmd, ' ');
			
			if (cmd.compare("cd") == 0) {
				currentcmd = "cd";
				string dirname;
				getline(sline, dirname, ' ');

				assert(dirname.length() > 0);

				if (dirname.compare("/") == 0)
					current = root;
				else if (dirname.compare("..") == 0)
					current = current->prev != nullptr ? current->prev : current;
				else
					current = current->getDir(dirname);
			}
			else if (cmd.compare("ls") == 0)
				currentcmd = "ls";
		}
		else if (currentcmd.compare("ls") == 0) {
			if (start.compare("dir") == 0) {
				string dirname;
				getline(sline, dirname);

				assert(dirname.length() > 0);

				current->subdirs.emplace_back(dir{ 0, dirname, {}, current });
			}
			else {
				//must be a file with size
				string filename;
				getline(sline, filename);
				//can be used later

				current->filesize += atoi(start.data());
			}
		}

	}

	input.close();

	return root;
}

int getClosest(const vector<int>& values, int threshold) {
	int current = -1;
	for (int v : values) {
		if (v >= threshold && (v < current || current == -1))
			current = v;
	}

	return current;
}

void test() {
	dir* root = getTree("Day07test.txt");
	assert(root->getSize() == 48381165);
	cout << root->getSizeIf(100000) << endl;
	assert(root->getSizeIf(100000) == 95437);

	const int total  = 70000000;
	const int unused = 30000000;
	int freethreshold = unused - (total - root->getSize());
	//cout << "Must delete: " << freethreshold << endl;
	assert(freethreshold == 8381165);

	vector<int> subdirs = root->getSubdirSize();
	int closestsize = getClosest(subdirs, freethreshold);
	//cout << "Dirsize to delete: " << closestsize << endl;
	assert(closestsize == 24933642);
}

int main() {
	cout << " AoC 2022 Day 07" << endl;

	test();

	dir* root = getTree("Day07.txt");
	cout << "Total: " << root->getSize() << endl;
	cout << root->getSizeIf(100000) << endl;

	const int total = 70000000;
	const int unused = 30000000;
	int freethreshold = unused - (total - root->getSize());
	cout << "Must delete: " << freethreshold << endl;

	vector<int> subdirs = root->getSubdirSize();
	int closestsize = getClosest(subdirs, freethreshold);
	cout << "Dirsize to delete: " << closestsize << endl;

	return 0;
}
