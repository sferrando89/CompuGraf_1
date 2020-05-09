#pragma once
enum class Direction { left, right, up, down };
enum class Direction_x { left, right };
enum class Direction_y { up, down };

Direction operator++(Direction& d, int);

Direction operator--(Direction& d, int);