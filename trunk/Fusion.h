#ifndef FUSION_H
#define FUSION_H
#include "Image.h"

class Fusion
{
public:
    Fusion(RgbImage img1, RgbImage img2);
    virtual ~Fusion();
    void calculFusion(float p);
protected:
private:
    RgbImage imgbase;
    RgbImage imgchoisi;
};

#endif // FUSION_H
