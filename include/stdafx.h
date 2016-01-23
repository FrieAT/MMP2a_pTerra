#pragma once

#include <math.h>
#include <cmath>
#include <stack>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cfloat>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <TGUI/TGUI.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

struct pairhash {
public:
	template <typename T, typename U>
	std::size_t operator()(const std::pair<T, U> &x) const
	{
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};