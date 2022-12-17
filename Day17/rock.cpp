#include "rock.hpp"

bool rock_t::try_position(const chamber_t& chamber, int left_offset, unsigned long top_offset) const
{
	if (chamber.size() - top_offset < get_height())
		return false;

	if (left_offset < 0)
		return false;

	if (chamber[0].size() - left_offset < get_width())
		return false;

	for (int t = get_height() - 1; t >= 0; t--) {
		if (!fit(_shape[t], chamber[t + top_offset], left_offset))
			return false;
	}

	return true;
}

void rock_t::set_position(chamber_t& chamber, int left_offset, unsigned long top_offset) const
{
	//assert(try_position(chamber, left_offset, top_offset));

	for (int t = 0; t < get_height(); t++) {
		for (int i = 0; i < get_width(); i++) {
			if (_shape[t][i] == '#')
				chamber[t + top_offset][i + left_offset] = '#';
		}
	}
}

bool rock_t::fit(const vector<char>& shape, const array<char, chamber_width>& dest, int left_offset) const
{
	if (shape.size() + left_offset > chamber_width)
		return false;

	for (int i = 0; i < shape.size(); i++) {
		if (shape[i] == '#' && dest[i + left_offset] == '#') // collision
			return false;
	}

	return true;
}