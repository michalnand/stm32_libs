#ifndef _SCALAR_H_
#define _SCALAR_H_

template<class DType>
DType abs(DType v)
{
    if (v < 0)
    {
        v = -v;
    }

    return v;
}


template<class DType>
DType min(DType va, DType vb)
{
    if (va < vb)
    {
        return va;
    }
    else
    {
        return vb;
    }
}

template<class DType>
DType max(DType va, DType vb)
{
    if (va > vb)
    {
        return va;
    }
    else
    {
        return vb;
    }
}

template<class DType>
DType sgn(DType v)
{
    if (v > 0)
    {
        return 1.0;
    }
    else
    {
        return -1.0;
    }
}


template<class DType>
DType clip(DType v, DType min_v, DType max_v)
{
    if (v < min_v)
    {
        v = min_v;
    }

    if (v > max_v)
    {
        v = max_v;
    }

    return v;
}

template<class DType>
DType shrink(DType v, DType s_low, DType s_high)
{
    if (v < s_low || v > s_high)
    {
        return v;
    }
    else
    {
        return 0;
    }
}






//http://pubs.opengroup.org/onlinepubs/009695399/functions/atan2.html

template<class DType>
DType fatan(DType x) 
{
    if (x > 1.0)
    {
        return PI/2 - fatan(1.0/x);
    }  
    else if (x < -1.0)
    {
        return -PI/2 - fatan(1.0/x);
    }


    float xx  = x * x;
    float a   = 0.0776509570923569;
    float b   = -0.287434475393028;
    float c   = PI/4.0 - a - b;

    return ((a*xx + b)*xx + c)*x;
}

template<class DType>
DType fatan2(DType x, DType y)
{
    if (x == 0 && y == 0)
    {
        return 0; 
    }

    auto a = min(abs(x), abs(y))/max(abs(x), abs(y));
    auto s = a*a;

    auto result = ((-0.0464964749 * s + 0.15931422) * s - 0.327622764) * s * a + a;

    if (abs(y) > abs(x))
    {
        result = 1.57079637 - result;
    }

    if (x < 0)
    {
        result = 3.14159274 - result;
    }

    if (y < 0)
    {
        result = -result;
    }

    return result;
}

template<class DType>
DType exp(DType x)  
{
    
    uint32_t factorial = 1;  
    float pow       = 1.0;

    float result    = 1.0;

    for (unsigned int i = 0; i < 10; i++)
    {
        factorial*= (i+1);  
        pow*= x;

        result+= pow/factorial;
    }

    return result;
}


#endif