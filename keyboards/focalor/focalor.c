/*
Copyright 2022

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "focalor.h"

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
	// Left
	{{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}},
	{{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}},
	{{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}},
	{{X, X}, {X, X}, {2, 8}, {3, 8}, {4, 8}},
	// Right
	{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}},
	{{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}},
	{{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}},
	{{0, 3}, {1, 3}, {2, 3}, {X, X}, {X, X}}
};
#endif
