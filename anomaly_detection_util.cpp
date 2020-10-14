#include <cmath>
#include <stdio.h>
#include "anomaly_detection_util.h"
using namespace std;

float mean(float *x, int size)
{
    if (size == 0)
        return 0.0f;
    
    float sum = 0.0f;
    for (int i = 0; i < size; ++i)
    {
        sum += x[i];
    }
    return sum * ((float)1 / size);
}

float var(float *x, int size)
{
    if (size == 0)
        return 0.0f;

    float sum = 0.0f;
    float m_x = mean(x, size);

    for (int i = 0; i < size; ++i)
    {
        sum += pow(x[i], 2);
    }

    sum *= ((float)1 / size);

    return sum - pow(m_x, 2);
}

float cov(float *x, float *y, int size)
{
    if (size == 0)
        return 0.0f;

    float m_x = mean(x, size);
    float m_y = mean(y, size);
    float sum_xy = 0.0f;

    for (int i = 0; i < size; ++i) {
        sum_xy += x[i] * y[i];
    }
    return (sum_xy * ((float) 1 / size)) - (m_x * m_y);
}

float pearson(float *x, float *y, int size) {
    float cov_xy = cov(x, y, size);
    float v_x = var(x, size), v_y = var(y, size);
    
    if ((size == 0) || (v_x == 0) || (v_y == 0))
        return 0.0f; 

    return (cov_xy / (sqrt(v_x) * sqrt(v_y)));
}

Line linear_reg(Point** points, int size) {
    if (size == 0) {
        Line *line = NULL;
        return *line;
    }

    float x[size], y[size];
    for (int i = 0; i < size; ++i) {
        Point *point = points[i];
        x[i] = point->x;
        y[i] = point->y;
    }

    float m_x = mean(x, size), m_y = mean(y, size);
    float a = (cov(x, y, size) / var(x, size));
    float b = m_y - (a * m_x);
    
    Line line(a, b);
    return line;
}

float dev(Point p, Line l) {
    float f_x = l.f(p.x);
    return abs((f_x - p.y));
}

float dev(Point p, Point** points, int size) {
    if (size == 0)  
        return 0.0f;

    Line line = linear_reg(points, size);
    return dev(p, line);
}
