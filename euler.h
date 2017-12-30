// COPYRIGHT (c) Ioannis Tambouras 2011-2015

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "libpq/pqformat.h"             /* needed for send/recv functions */
#include <math.h>
#include "utils/guc.h"


#ifndef _EULER_NUMBER
#define _EULER_NUMBER

PG_MODULE_MAGIC;

typedef struct Euler {
    float4      mag;
    float4      phase;
} Euler;


#define MAG_SQUARED(c)      ((c)->mag*(c)->mag )
#define MAG(x,y)            (sqrt( (x*x)+(y*y)))
#define TO_DEGREES          (180/3.14159)
#define TO_RADIANS          (3.14159/180)
#define SENSITIVITY         1e-8

PG_FUNCTION_INFO_V1(euler_in);
PG_FUNCTION_INFO_V1(euler_out);
PG_FUNCTION_INFO_V1(euler_recv);
PG_FUNCTION_INFO_V1(euler_send);
PG_FUNCTION_INFO_V1(euler_conjugate);
PG_FUNCTION_INFO_V1(euler_mult);
PG_FUNCTION_INFO_V1(euler_divide);
PG_FUNCTION_INFO_V1(euler_phase);
PG_FUNCTION_INFO_V1(euler_phase_add);
PG_FUNCTION_INFO_V1(euler_mag);
PG_FUNCTION_INFO_V1(euler_xy);
PG_FUNCTION_INFO_V1(euler_theta);
PG_FUNCTION_INFO_V1(euler_add);
PG_FUNCTION_INFO_V1(euler_subtract);
PG_FUNCTION_INFO_V1(euler_dot);
PG_FUNCTION_INFO_V1(euler_mag_squared);
PG_FUNCTION_INFO_V1(euler_abs_cmp);
PG_FUNCTION_INFO_V1(euler_equal);
PG_FUNCTION_INFO_V1(euler_less);
PG_FUNCTION_INFO_V1(euler_less_equal);
PG_FUNCTION_INFO_V1(euler_greater_equal);
PG_FUNCTION_INFO_V1(euler_greater);
PG_FUNCTION_INFO_V1(euler_overlaps);
PG_FUNCTION_INFO_V1(euler_new);
PG_FUNCTION_INFO_V1(euler_int2c_cmp);
PG_FUNCTION_INFO_V1(euler_int2c_equal);
PG_FUNCTION_INFO_V1(euler_int2c_less);
PG_FUNCTION_INFO_V1(euler_int2c_less_equal);
PG_FUNCTION_INFO_V1(euler_int2c_greater_equal);
PG_FUNCTION_INFO_V1(euler_int2c_greater);

#endif
