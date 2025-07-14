#include "VisAlgorithm.h"

using namespace VisAlgorithm;
int main() 
{
	Region rgn;
	auto a = rgn.GenCircle(200, 200, 50);
	double row, col;
	auto area = rgn.AreaCenter(&row,&col);
    return 0;
}