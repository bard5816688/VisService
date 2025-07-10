#include "VisAlgorithm.h"

int main() 
{
    VisAlgorithm::Image img(512, 512, VisAlgorithm::PixelFormat::Mono8);
    VisAlgorithm::HShapeModel sm;
	sm.CreateShapeModel(img, 0, 0, 1, 0.1, "", "", 0, 0);
    return 0;
}