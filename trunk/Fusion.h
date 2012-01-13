#ifndef FUSION_H
#define FUSION_H
#include "Image.h"

class Fusion
{
public:
    Fusion();
    virtual ~Fusion();
    void calculFusion(RgbImage imgbase, RgbImage imgchoisi, float p);
protected:
private:
};

#endif // FUSION_H
