#pragma once
#include "fl/Headers.h"
using namespace fl;

class FuzzyEngine
{
public:
	FuzzyEngine();
	~FuzzyEngine();

	Engine GetEngine();
	void SetInput();
	scalar GetOutput();

private:
	Engine* engine;

};

