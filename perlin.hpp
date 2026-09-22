#ifndef NOISE_HPP
#define NOISE_HPP

#include <cmath>

class Noise{
private:

public:

    Noise();
    
    typedef struct { //2D vector struct
        float x,y;
    }vector2;

    static vector2 randomGradient(int ix, int iy){
        const unsigned w = 8 * sizeof(unsigned);
        const unsigned s = w / 2;
        unsigned a = ix, b = iy;
        a *= 3284157443;

        b ^= a << s | a >> w - s;
        b *= 1911520717;

        a ^= b << s | b >> w - s;
        a *= 2048411932;
        float random = a * (3.14159265 / ~(~0u >> 1));

        vector2 v;
        v.x = sin(random);
        v.y = cos(random);

        return v;
    }

    static float gridGradient(int ix, int iy, float x, float y){
        vector2 gradient = randomGradient(ix,iy);

        float dx = x - (float)ix;
        float dy = y - (float)iy;
        return (dx * gradient.x + dy * gradient.y);
    }

    static float interpolate(float a0, float a1, float w){
        return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
    }

    static double perlin(float x, float y){

        //cell corner coords
        int x0 = int(x);
        int y0 = int(y);
        int x1 = x0 + 1;
        int y1 = y0 + 1;

        //interpolation weights
        float ix = x - (float)x0;
        float iy = y - (float)y0;

        float n0 = gridGradient(x0,y0,x,y);
        float n1 = gridGradient(x0,y0,x,y);
        float ix0 = interpolate(n0,n1,ix); 

        n0 = gridGradient(x0,y0,x,y);
        n1 = gridGradient(x0,y0,x,y);
        float ix1 = interpolate(n0,n1,ix); 

        float value = interpolate(ix0,ix1,iy);

        return value;
    }
 
};

#endif