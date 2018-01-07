-- COPYRIGHT (c) Ioannis Tambouras 2011-2015
\echo Use "CREATE EXTENSION euler" to load this file. \quit

CREATE OR REPLACE FUNCTION gin_extract_value_euler(euler,internal)
    RETURNS float4
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION gin_extract_query_euler(euler, internal, int2, internal, internal)
    RETURNS float4
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION gin_consistent_euler(internal, int2, anyelement, int4, internal, internal)
    RETURNS float4
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;


CREATE OPERATOR CLASS euler_gin_ops DEFAULT FOR TYPE euler USING gin AS
   OPERATOR         1       <,
    OPERATOR        2       <=,
    OPERATOR        3       =,
    OPERATOR        4       >=,
    OPERATOR        5       >,
    FUNCTION        1       pg_catalog.btfloat4cmp(float4,float4),
    FUNCTION        2       gin_extract_value_euler(euler, internal),
    FUNCTION        3       gin_extract_query_int2(euler, internal, int2, internal, internal),
    FUNCTION        4       gin_consistent_euler(internal, int2, anyelement, int4, internal, internal),
STORAGE         float4;


CREATE OPERATOR CLASS euler_brin_ops FOR TYPE euler USING brin AS
        FUNCTION 1      brin_minmax_opcinfo(internal) ,
        FUNCTION 2      brin_minmax_add_value(internal,internal,internal,internal) ,
        FUNCTION 3      brin_minmax_consistent(internal,internal,internal) ,
        FUNCTION 4      brin_minmax_union(internal,internal,internal) ,
        OPERATOR 1 <  ,
        OPERATOR 2 <= ,
        OPERATOR 3 =  ,
        OPERATOR 4 >= ,
        OPERATOR 5 > ;
