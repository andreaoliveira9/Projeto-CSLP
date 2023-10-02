// main.cpp

#include "ImageManipulator.cpp"

int main()
{
    ImageManipulator sourceImage;
    if (!sourceImage.loadPPM("source.ppm"))
    {
        return 1;
    }

    ImageManipulator destinationImage;
    destinationImage.copyImage(sourceImage);

    if (!destinationImage.savePPM("destination.ppm"))
    {
        return 1;
    }

    return 0;
}
