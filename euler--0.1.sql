-- COPYRIGHT (c) Ioannis Tambouras 2011-2015
\echo Use "CREATE EXTENSION euler" to load this file. \quit

CREATE TYPE euler;

CREATE OR REPLACE FUNCTION euler_in(cstring)
    RETURNS euler
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;


CREATE OR REPLACE FUNCTION euler_out(euler)
    RETURNS cstring
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;


CREATE OR REPLACE FUNCTION euler_recv(internal)
   RETURNS euler
    AS '$libdir/euler'
   LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_send(euler)
   RETURNS bytea
    AS '$libdir/euler'
   LANGUAGE C IMMUTABLE STRICT;


CREATE TYPE euler (
   internallength = 8,
   input          = euler_in,
   output         = euler_out,
   receive        = euler_recv,
   send           = euler_send,
   alignment      = float
);

CREATE OR REPLACE FUNCTION euler_abs_cmp(euler,euler)
   RETURNS int
    AS '$libdir/euler'
   LANGUAGE C IMMUTABLE STRICT;


CREATE OR REPLACE FUNCTION euler_add(euler, euler)
    RETURNS euler
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_subtract(euler, euler)
    RETURNS euler
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_dot(euler, euler)
    RETURNS float4
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION mag(euler)
    RETURNS real
    AS '$libdir/euler', 'euler_mag'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_mag_squared(euler)
    RETURNS real
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_equal(euler,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_less(euler,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_less_equal(euler,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_greater_equal(euler,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_greater(euler,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_conjugate(euler)
    RETURNS euler
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_mult(euler,euler)
    RETURNS euler
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_polar(euler)
    RETURNS euler
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_xy(euler)
    RETURNS euler
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR | (
    rightarg = euler,
    procedure = mag
);
CREATE OPERATOR |^ (
    rightarg = euler,
    procedure = euler_mag_squared
);
CREATE OPERATOR ^ (
    rightarg = euler,
    procedure = euler_polar
);
CREATE OPERATOR @ (
    leftarg = euler,
    procedure = euler_conjugate
);
CREATE OPERATOR + (
    leftarg = euler,
    rightarg = euler,
    procedure = euler_add,
    commutator = +
);

CREATE OPERATOR - (
    leftarg = euler,
    rightarg = euler,
    procedure = euler_subtract
);
CREATE OPERATOR * (
    leftarg = euler,
    rightarg = euler,
    procedure = euler_mult
);

CREATE OPERATOR < (
    leftarg    = euler,
    rightarg   = euler,
    procedure  = euler_less,
    commutator = >  ,
    restrict   = scalarltsel,
    join       = scalarltjoinsel
);

CREATE OPERATOR <= (
    leftarg    = euler,
    rightarg   = euler,
    procedure  = euler_less_equal,
    commutator = >=  ,
    restrict   = scalarltsel,
    join       = scalarltjoinsel
);

CREATE OPERATOR = (
    leftarg    = euler,
    rightarg   = euler,
    procedure  = euler_equal,
    commutator = = ,
    restrict   = eqsel,
    join       = eqjoinsel
);


CREATE OPERATOR >= (
    leftarg    = euler,
    rightarg   = euler,
    procedure  = euler_greater_equal,
    commutator = <= ,
    restrict   = scalargtsel,
    join       = scalargtjoinsel
);

CREATE OPERATOR > (
    leftarg    = euler,
    rightarg   = euler,
    procedure  = euler_greater,
    commutator = < ,
    restrict   = scalargtsel,
    join       = scalargtjoinsel
);

CREATE AGGREGATE sum (
   sfunc = euler_add,
   basetype = euler,
   stype = euler,
   initcond = '(0,0)'
);


CREATE OPERATOR CLASS euler_abs_ops DEFAULT FOR TYPE euler USING btree AS 
        OPERATOR 1 <  ,
        OPERATOR 2 <= ,
        OPERATOR 3 =  ,
        OPERATOR 4 >= ,
        OPERATOR 5 >  ,
        FUNCTION 1  euler_abs_cmp(euler,euler)
;

CREATE OR REPLACE FUNCTION euler_int2c_cmp(int,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_int2c_equal(int,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_int2c_less(int,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_int2c_less_equal(int,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_int2c_greater_equal(int,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_int2c_greater(int,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_overlaps(euler,euler)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_real(euler)
    RETURNS float4
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_img(euler)
    RETURNS float4
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_new(float4,float4)
    RETURNS euler
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_angle(euler)
    RETURNS float4
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_theta(euler,euler)
    RETURNS float4
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_angle_add(euler,float4)
    RETURNS euler
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;


CREATE OR REPLACE FUNCTION euler_new_polar(float4,float4)
    RETURNS euler
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;


CREATE OPERATOR < (
    leftarg    = int,
    rightarg   = euler,
    procedure  = euler_int2c_less,
    commutator = >  ,
    restrict   = scalarltsel,
    join       = scalarltjoinsel
);

CREATE OPERATOR <= (
    leftarg    = int,
    rightarg   = euler,
    procedure  = euler_int2c_less_equal,
    commutator = >=  ,
    restrict   = scalarltsel,
    join       = scalarltjoinsel
);

CREATE OPERATOR = (
    leftarg    = int,
    rightarg   = euler,
    procedure  = euler_int2c_equal,
    commutator = = ,
    restrict   = eqsel,
    join       = eqjoinsel
);


CREATE OPERATOR >= (
    leftarg    = int,
    rightarg   = euler,
    procedure  = euler_int2c_greater_equal,
    commutator = <= ,
    restrict   = scalargtsel,
    join       = scalargtjoinsel
);

CREATE OPERATOR > (
    leftarg    = int,
    rightarg   = euler,
    procedure  = euler_int2c_greater,
    commutator = < ,
    restrict   = scalargtsel,
    join       = scalargtjoinsel
);

CREATE OPERATOR CLASS euler_minimax_ops DEFAULT FOR TYPE euler USING brin AS
        FUNCTION 1      brin_minmax_opcinfo(internal) ,
        FUNCTION 2      brin_minmax_add_value(internal,internal,internal,internal) ,
        FUNCTION 3      brin_minmax_consistent(internal,internal,internal) ,
        FUNCTION 4      brin_minmax_union(internal,internal,internal) ,
        OPERATOR 1 <  ,
        OPERATOR 2 <= ,
        OPERATOR 3 =  ,
        OPERATOR 4 >= ,
        OPERATOR 5 >
;

