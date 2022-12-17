#pragma once

#include <stack>
#include <vector>
#include <array>
#include <cassert>

using namespace std;

class rock_t {
public:
	static const unsigned long chamber_width = 7;

	using chamber_t = vector<array<char, chamber_width>>;

	rock_t(vector<vector<char>> shape) : _shape(shape) {};

	bool try_position(const chamber_t& chamber, int left_offset, unsigned long top_offset) const;
	void set_position(chamber_t& chamber, int left_offset, unsigned long top_offset) const;

	bool fit(const vector<char>& shape, const array<char, chamber_width>& dest, int left_offset) const;

	int get_width() const { assert(_shape.size() > 0);  return _shape[0].size(); };
	int get_height() const { return _shape.size(); };

protected:
	vector <vector<char>> _shape;

};