#pragma once
#include "Method.h"
class MethodHeun :
	public Method
{
public:
	MethodHeun();
	~MethodHeun();

	void nextStep(double *y, double t);
};

