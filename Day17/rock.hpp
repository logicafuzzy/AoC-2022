#pragma once

#include <stack>
#include <vector>
#include <array>
#include <cassert>
#include <bitset>
#include <utility>

using namespace std;

class rock_t {
public:
	static const unsigned long area_width = 7;

	using row_t = vector<bool>;
	using area_t = vector<row_t>;

	using chamber_row_t = array<bool, area_width>;
	using chamber_t = vector<chamber_row_t>;

	rock_t(const area_t& shape) : _shape(shape) {
		for (int r = 0; r < shape.size(); r++)
			for (int c = 0; c < shape[r].size(); c++)
				if (shape[r][c])
					_indexes.push_back({ r, c });
	};

	bool try_position(const chamber_t& chamber, int left_offset, unsigned long top_offset) const;
	void set_position(chamber_t& chamber, int left_offset, unsigned long top_offset) const;

	bool fit(const row_t& shape, const chamber_row_t& dest, int left_offset) const;

	int get_width() const { assert(_shape.size() > 0);  return _shape[0].size(); };
	int get_height() const { return _shape.size(); };

	const vector<pair<int, int>>& get_indexes() const { return _indexes; };

protected:
	area_t _shape;
	vector<pair<int, int>> _indexes;
};