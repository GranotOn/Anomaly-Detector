#include <cmath>
#include <iostream>
using namespace std;

float var(float *x, int size)
{
    float inv = ((float) 1 / size);

    if (size == 0)
        return 0.0;

    float sum = 0, mean = 0;
    
    for (int i = 0; i < size; ++i)
    {
        sum += pow(x[i], 2);
        mean += x[i];
    }

    sum *= inv;
    mean *= inv;

    return sum - pow(mean, 2);
}

int main()
{
    float x[3] = {1.0f, 2.0f, 3.5f};
    cout << var(x, 3);

    return 0;
}