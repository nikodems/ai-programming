#include "FuzzyEngine.h"



FuzzyEngine::FuzzyEngine()
{
	engine = FisImporter().fromFile("Fuzzy.fis");

	engine->getRuleBlock(0)->setActivation(new General);
	engine->getRuleBlock(0)->setEnabled(true);
}


FuzzyEngine::~FuzzyEngine()
{
}

void FuzzyEngine::SetInput()
{
	engine->getInputVariable("Velocity")->setValue(0.5);
	engine->getInputVariable("Distance")->setValue(0.5);
}

scalar FuzzyEngine::GetOutput()
{
	//scalar output;
	return engine->getOutputValue("Steering");
}


Engine FuzzyEngine::GetEngine()
{
	return *engine;
}

//INPUT
//DISTANCE -1 -> 1
//VELOCITY -1 -> 1

//OUTPUT
//STEERING -1 -> 1