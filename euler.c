// COPYRIGHT (c) Ioannis Tambouras 2011-2015

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "libpq/pqformat.h"             /* needed for send/recv functions */
#include <math.h>
#include "utils/guc.h"
#include "euler.h"

PG_FUNCTION_INFO_V1(gin_extract_query_euler);
PG_FUNCTION_INFO_V1(gin_extract_value_int4_euler);
PG_FUNCTION_INFO_V1(gin_extract_query_int4_euler);
//PG_FUNCTION_INFO_V1(create_elem);
Datum create_elem(int32);

Datum
gin_extract_value_int4_euler(PG_FUNCTION_ARGS)
{
        Euler      *item     = (Euler *)  PG_GETARG_POINTER(0);
        int32      *nentries = (int32 *)  PG_GETARG_POINTER(1);

        Datum      *entries  = (Datum *) palloc(sizeof(Datum) * 1);

        entries[0] = Int32GetDatum( round(item->phase) );
        *nentries  = 1;
        PG_RETURN_POINTER(entries);
}

Datum
create_elem(int32 i)
{
      PG_RETURN_INT32(i);
}

Datum
gin_extract_query_int4_euler(PG_FUNCTION_ARGS)
{
        Euler          *query    = (Euler *)  PG_GETARG_POINTER(0);
        int32          *nentries = (int32 *) PG_GETARG_POINTER(1);

        Datum           *items ;
        int32           size;
        //Datum              query = PG_GETARG_DATUM(0);
        StrategyNumber  strategy = PG_GETARG_UINT16(2);
        //bool      **partialmatch = (bool **) PG_GETARG_POINTER(3);
        //Pointer     **extra_data = (Pointer **) PG_GETARG_POINTER(4);

        *nentries   = 0;
        switch (strategy)
        {
            case 3 : items = (Datum *) palloc(sizeof(Datum));
                     items[0]  = create_elem( round( (int) round(query->phase)) );
	             *nentries   = 1;
                     break;
            case 2 :
            case 1 : size     =   ((int) round(query->phase)) +1;
                     items = (Datum *) palloc(sizeof(Datum)* size);

                     for (int i=0;i<= (int) round(query->phase); i++)  {
                              items[i] = create_elem( (int) i);
                             *nentries   += 1;
                     }
                     break;
            case 5 :
            case 4 : size     =   91 - ((int) round(query->phase));
                     items = (Datum *) palloc(sizeof(Datum)* size);

                     for (int i=(int)round(query->phase);i<=90; i++)  {
                              items[*nentries] = create_elem( (int) i);
                             *nentries   += 1;
                     }
                     break;

        }
	PG_RETURN_POINTER(items);
}


Datum
gin_extract_query_euler(PG_FUNCTION_ARGS)
{
        //Datum              query = PG_GETARG_DATUM(0);
        int32          *nentries = (int32 *) PG_GETARG_POINTER(1);
        //StrategyNumber  strategy = PG_GETARG_UINT16(2);
        //bool      **partialmatch = (bool **) PG_GETARG_POINTER(3);
        //Pointer     **extra_data = (Pointer **) PG_GETARG_POINTER(4);
        float4             phase;

        Datum           *entries = (Datum *) palloc(sizeof(Datum));

        //query2 = query_fields(VARDATA_ANY(val), VARSIZE_ANY_EXHDR(val));
        phase       = 10;
	*nentries   = 1;
	entries     = (Datum *) palloc(sizeof(Datum) * 1);
        entries[0]  = Float4GetDatum( phase );

        //result = cstring_to_text_with_len((char *) resstr, reslen);

	PG_RETURN_POINTER(entries);
}

PG_FUNCTION_INFO_V1(gin_consistent_euler);

Datum
gin_consistent_euler(PG_FUNCTION_ARGS)
{
        //bool             *check = (bool *) PG_GETARG_POINTER(0);
        //StrategyNumber strategy = PG_GETARG_UINT16(1);
        //* text    *query = PG_GETARG_TEXT_PP(2); 
        //int32             nkeys = PG_GETARG_INT32(3);
        //Pointer     *extra_data = (Pointer *) PG_GETARG_POINTER(4);
        bool           *recheck = (bool *) PG_GETARG_POINTER(5);

        *recheck = false;
        PG_RETURN_BOOL(true);
}
 
Datum
gin_extract_value_euler(PG_FUNCTION_ARGS)
{
        Euler      *item     = (Euler *)  PG_GETARG_POINTER(0);
        int32      *nentries = (int32 *)  PG_GETARG_POINTER(1);

        Datum      *entries  = (Datum *) palloc(sizeof(Datum) * 2);
        entries[0] = Float4GetDatum( item->mag );
        entries[1] = Float4GetDatum( item->phase) ;
        *nentries  = 2;
        PG_RETURN_POINTER(entries);
}



PG_FUNCTION_INFO_V1(euler_float4_cmp);
Datum
euler_float4_cmp( PG_FUNCTION_ARGS )
{
    float4      a = PG_GETARG_FLOAT4(0);
    float4      b = PG_GETARG_FLOAT4(1);

     if ( a < b  ) PG_RETURN_FLOAT4(-1);
     if ( a == b ) PG_RETURN_FLOAT4(0) ;
     PG_RETURN_FLOAT4( 1 ) ;
}


Datum
euler_in(PG_FUNCTION_ARGS)
{
     char       *str = PG_GETARG_CSTRING(0);
     float4     x, y;
     Euler    *result;
     char       buf[54], c;

     buf[0]='\0';
     strncat( buf, str, 50);
     strcat( buf, "__");

     result = (Euler *) palloc(sizeof(Euler));
     if (sscanf(str, "%f< %f >", &x, &y) == 2) { 
               result->mag   = x ;
               result->phase = y ;
     } else if (sscanf(str, "(%f,%f)", &x, &y) == 2) {
               result->mag   =  MAG(x,y);
               result->phase =  TO_DEGREES * atan(y/x);
     } else if (sscanf(str, "%f,%f", &x, &y) == 2) {
               result->mag   =  MAG(x,y);
               result->phase =  TO_DEGREES  * atan(y/x);
     } else if (sscanf(str, "%f,%f[ji]", &x, &y) == 2) {
               result->mag   =  MAG(x,y);
               result->phase =  TO_DEGREES * atan(y/x);
     } else if ( (sscanf(buf, "%g%[ji]%[_]",  &y, &c, &c) == 3) ) {
               result->mag   =  MAG(0,y);
               result->phase =  90;
     } else if ( (sscanf(buf,"%g%[_]%[_]",  &x,&c,&c) == 2) ) {
               result->mag   =  MAG(x,0);
               result->phase =  0;
     } else if ( (sscanf(buf,"%g%g%[ji]%[_]",  &x,&y,&c,&c) == 4) ) {
               result->mag   =  MAG(x,y);
               result->phase =  TO_DEGREES * atan(y/x);
     }else{ 
             ereport(ERROR, (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                            errmsg("syntax is like \"8<60>\", \"2,5\",\"(2,5)\",\"2-5j\", \"+5i\", or \"2\"")));
     }
     PG_RETURN_POINTER(result);
}


Datum
euler_out(PG_FUNCTION_ARGS)
{
    Euler      *a = (Euler *) PG_GETARG_POINTER(0);
    char       *result;
    float4      x, y;
    const char  *output_style = GetConfigOption("euler.style",true,false);

     if ( (NULL != output_style) && !(strcmp( output_style, "polar")) ) {
               result = psprintf("%.3f<%.3f>", a->mag, a->phase) ;
     } else if ( (NULL != output_style) && !(strcmp( output_style, "j")) ) {
                x  =  a->mag * ( cos(a->phase * TO_RADIANS ))     ;
                y  =  a->mag * ( sin(a->phase * TO_RADIANS ))     ;
               result = psprintf("%.3f,%.3fj", a->mag, a->phase) ;
     } else if ( (NULL != output_style) && !(strcmp( output_style, "i")) ) {
                x  =  a->mag * ( cos(a->phase * TO_RADIANS ))     ;
                y  =  a->mag * ( sin(a->phase * TO_RADIANS ))     ;
               result = psprintf("%.3f,%.3fi", a->mag, a->phase) ;
     }else{
              result = psprintf("%.3f<%.3f>", a->mag, a->phase) ;
     }
     PG_RETURN_CSTRING(result);
}

Datum
euler_recv(PG_FUNCTION_ARGS)
{
    StringInfo  buf = (StringInfo) PG_GETARG_POINTER(0);
    Euler    *result;

    result = (Euler *) palloc(sizeof(Euler));
    result->mag   = pq_getmsgfloat4(buf);
    result->phase = pq_getmsgfloat4(buf);
    PG_RETURN_POINTER(result);
}


Datum
euler_send(PG_FUNCTION_ARGS)
{
    Euler    *euler = (Euler *) PG_GETARG_POINTER(0);
    StringInfoData buf;
    pq_begintypsend(&buf);
    pq_sendfloat4(&buf, euler->mag);
    pq_sendfloat4(&buf, euler->phase);
    PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}


Datum
euler_conjugate(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *result;

        result = (Euler *) palloc(sizeof(Euler));
        result->mag   = a->mag;
        result->phase = -1*(a->phase);
        PG_RETURN_POINTER(result);
}



Datum
euler_mult(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);
        Euler    *result;

        result = (Euler *) palloc(sizeof(Euler));
        result->mag   = (a->mag * b->mag);
        result->phase = (a->phase + b->phase) ;
        PG_RETURN_POINTER(result);
}

Datum
euler_divide(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);
        Euler    *result;

        result = (Euler *) palloc(sizeof(Euler));
        result->mag   = (a->mag * b->mag);
        result->phase = (a->phase - b->phase) ;
        PG_RETURN_POINTER(result);
}

Datum
euler_phase(PG_FUNCTION_ARGS)
{
     Euler      *a = (Euler *) PG_GETARG_POINTER(0);
     float4      phi  = PG_GETARG_FLOAT4(1);
    
     PG_RETURN_FLOAT4(a->phase + phi);
}

Datum
euler_phase_add(PG_FUNCTION_ARGS)
{
     Euler      *a = (Euler *) PG_GETARG_POINTER(0);
     float4      phi  = PG_GETARG_FLOAT4(1);
     Euler      *result;
    

     result = (Euler *) palloc(sizeof(Euler));

     result->mag    =  a->mag;
     result->phase  =  a->phase + phi ;
     PG_RETURN_POINTER(result);
}


Datum
euler_mag(PG_FUNCTION_ARGS)
{
    Euler    *a = (Euler *) PG_GETARG_POINTER(0);
    PG_RETURN_FLOAT4( a->mag );
}

Datum
euler_xy(PG_FUNCTION_ARGS)
{
     // Convert euler from polar to cartesian cordinates
     // Output: c->x is x coordinate
     // Output: c->y is y coordinate
     Euler    *a = (Euler *) PG_GETARG_POINTER(0);
     Euler    *result;
     float4     x,y;

     result = (Euler *) palloc(sizeof(Euler));
     x      =  a->mag * ( cos(a->phase * TO_RADIANS))  ;
     y      =  a->mag * ( sin(a->phase * TO_RADIANS))  ;

     if (x< SENSITIVITY) x = 0;
     if (y< SENSITIVITY) y = 0;
     result->mag   = x;
     result->phase = y;
     PG_RETURN_POINTER(result);
}

Datum
euler_theta(PG_FUNCTION_ARGS)
{
    // Finds the angle between two vectors
    Euler    *a = (Euler *) PG_GETARG_POINTER(0);
    Euler    *b = (Euler *) PG_GETARG_POINTER(1);

    PG_RETURN_FLOAT4( fabs(a->phase - b->phase) );
}

Datum
euler_add(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);
        Euler    *result;
        float4     a_x, a_y, b_x, b_y;

        a_x      =  a->mag * ( cos(a->phase * TO_RADIANS))  ;
        a_y      =  a->mag * ( sin(a->phase * TO_RADIANS))  ;
        b_x      =  b->mag * ( cos(b->phase * TO_RADIANS))  ;
        b_y      =  b->mag * ( sin(b->phase * TO_RADIANS))  ;

        a_x     =  a_x + b_x;
        a_y     =  a_y + b_y;
        if (a_x< SENSITIVITY) a_x = 0;
        if (a_y< SENSITIVITY) a_y = 0;

        result = (Euler *) palloc(sizeof(Euler));
        result->mag   =  MAG(a_x, a_y);
        result->phase =  (0==a_x) ? 0 : TO_DEGREES * atan(a_y/a_x);
        PG_RETURN_POINTER(result);
}

Datum
euler_subtract(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);
        Euler    *result;
        float4     a_x, a_y, b_x, b_y;

        a_x      =  a->mag * ( cos(a->phase * TO_RADIANS))  ;
        a_y      =  a->mag * ( sin(a->phase * TO_RADIANS))  ;
        b_x      =  b->mag * ( cos(b->phase * TO_RADIANS))  ;
        b_y      =  b->mag * ( sin(b->phase * TO_RADIANS))  ;

        a_x     =  a_x - b_x;
        a_y     =  a_y - b_y;
        if (a_x< SENSITIVITY) a_x = 0;
        if (a_y< SENSITIVITY) a_y = 0;

        result = (Euler *) palloc(sizeof(Euler));
        result->mag   =  MAG(a_x, a_y);
        result->phase =  (0==a_x) ? 0 : TO_DEGREES * atan(a_y/a_x);
        PG_RETURN_POINTER(result);
}

Datum
euler_dot(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);

        PG_RETURN_FLOAT4( (a->mag * b->mag) * ( cos(fabs(a->phase - b->phase) * TO_RADIANS)) );
}



Datum
euler_mag_squared(PG_FUNCTION_ARGS)
{
    Euler    *a = (Euler *) PG_GETARG_POINTER(0);
    PG_RETURN_FLOAT4( MAG_SQUARED(a) );
}

static int
euler_cmp_internal( Euler *a, Euler *b ) 
{
     float4   amag = MAG_SQUARED(a),  bmag=MAG_SQUARED(b);
     if ( amag < bmag  ) return -1;
     if ( amag == bmag ) return 0 ;
     return 1 ;
}

Datum
euler_mag_cmp(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);
        
        PG_RETURN_INT32( euler_cmp_internal(a,b) );
}


Datum
euler_equal(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);
        
        if (euler_cmp_internal(a,b) == 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}



Datum
euler_less(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);
        
        if (euler_cmp_internal(a,b) == -1 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}

Datum
euler_less_equal(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);
        
        if (euler_cmp_internal(a,b) <= 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}

Datum
euler_greater_equal(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);
        
        if (euler_cmp_internal(a,b) >= 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}


Datum
euler_greater(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *) PG_GETARG_POINTER(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);
        
        if (euler_cmp_internal(a,b) > 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}


Datum
euler_overlaps(PG_FUNCTION_ARGS)
{
        Euler    *a = (Euler *)    PG_GETARG_POINTER(0);
        Euler    *b = (Euler *)    PG_GETARG_POINTER(1);
        
        if ( a->mag   < b->mag)    PG_RETURN_BOOL(false);
        if ( a->phase < b->phase)  PG_RETURN_BOOL(false);
        PG_RETURN_BOOL(true);
}


Datum
euler_new(PG_FUNCTION_ARGS)
{
    float4      a = PG_GETARG_FLOAT4(0);
    float4      b = PG_GETARG_FLOAT4(1);
    Euler      *result;

    result = (Euler *) palloc(sizeof(Euler));
    result->mag   = a;
    result->phase = b;
    PG_RETURN_POINTER(result);
}

// cross-data comparisons

static int
euler_int2c_cmp_internal( int32 a, Euler *b ) 
{
     float4     bmag= MAG_SQUARED(b);
     if ( a < bmag  ) return -1;
     if ( a == bmag ) return 0 ;
     return 1 ;
}

Datum
euler_int2c_cmp(PG_FUNCTION_ARGS)
{
	int32       a = PG_GETARG_INT32(0);
        Euler    *b = (Euler *) PG_GETARG_POINTER(1);
        
        PG_RETURN_INT32( euler_int2c_cmp_internal(a,b) );
}



Datum
euler_int2c_equal(PG_FUNCTION_ARGS)
{
	int32       a = PG_GETARG_INT32(0);
        Euler      *b = (Euler *) PG_GETARG_POINTER(1);
        
        if (euler_int2c_cmp_internal(a,b) == 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}


Datum
euler_int2c_less(PG_FUNCTION_ARGS)
{
	int32       a = PG_GETARG_INT32(0);
        Euler      *b = (Euler *) PG_GETARG_POINTER(1);
        
        if (euler_int2c_cmp_internal(a,b) == -1 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}

Datum
euler_int2c_less_equal(PG_FUNCTION_ARGS)
{
	int32       a = PG_GETARG_INT32(0);
        Euler      *b = (Euler *) PG_GETARG_POINTER(1);
        
        if (euler_int2c_cmp_internal(a,b) <= 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}


Datum
euler_int2c_greater_equal(PG_FUNCTION_ARGS)
{
	int32       a = PG_GETARG_INT32(0);
        Euler      *b = (Euler *) PG_GETARG_POINTER(1);
        
        if (euler_int2c_cmp_internal(a,b) >= 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}


Datum
euler_int2c_greater(PG_FUNCTION_ARGS)
{
	int32       a = PG_GETARG_INT32(0);
        Euler      *b = (Euler *) PG_GETARG_POINTER(1);
        
        if (euler_int2c_cmp_internal(a,b) > 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}
