#pragma once
#include <iostream>
#include "utils.h"

class Pipe
{
private:
	int id;
public:
	Pipe();
	static int MAX_ID;
	float length;
	float diam;
	bool repaired = false;

	friend std::ostream& operator << (std::ostream& out, const Pipe& pipe);
	friend std::istream& operator >> (std::istream& in, Pipe& pipe);
};

