#pragma once
#include "Method.h"
class MethodEuler :
	public Method
{
public:
	MethodEuler();
	~MethodEuler();

	void nextStep(double *y, double t);
};

