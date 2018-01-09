\echo Use "CREATE EXTENSION euler" to load this file. \quit

CREATE OR REPLACE FUNCTION gin_extract_value_euler(euler,internal)
    RETURNS internal
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION gin_extract_query_euler(euler, internal, int2, internal, internal)
    RETURNS internal
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION gin_consistent_euler(internal, int2, anyelement, int4, internal, internal)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION euler_greater_text(euler,text)
    RETURNS boolean
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR > (
    LEFTARG   = euler,
    RIGHTARG  = text,
    PROCEDURE = euler_greater_text
);

CREATE OPERATOR CLASS euler_gin_float4_ops FOR TYPE euler USING gin AS
   OPERATOR         1       <,
    OPERATOR        2       <=,
    OPERATOR        3       =,
    OPERATOR        4       >=,
    OPERATOR        5       >,
    FUNCTION        1       pg_catalog.btfloat4cmp(float4,float4),
    FUNCTION        2       gin_extract_value_euler(euler, internal),
    FUNCTION        3       gin_extract_query_euler(euler, internal, int2, internal, internal),
    FUNCTION        4       gin_consistent_euler(internal, int2, anyelement, int4, internal, internal),
STORAGE    float4;


CREATE OR REPLACE FUNCTION gin_extract_value_int4_euler(euler,internal)
    RETURNS internal
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION gin_extract_query_int4_euler(euler, internal, int2, internal, internal)
    RETURNS internal
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

-- GIN



CREATE OPERATOR CLASS euler_gin_ops DEFAULT FOR TYPE euler USING gin AS
   OPERATOR         1       <,
    OPERATOR        2       <=,
    OPERATOR        3       =,
    OPERATOR        4       >=,
    OPERATOR        5       >,
    FUNCTION        1       pg_catalog.btint4cmp(integer,integer),
    FUNCTION        2       gin_extract_value_int4_euler(euler, internal),
    FUNCTION        3       gin_extract_query_int4_euler(euler, internal, int2, internal, internal),
    FUNCTION        4       gin_consistent_euler(internal, int2, anyelement, int4, internal, internal),
STORAGE    int4;

CREATE OR REPLACE FUNCTION gin_extract_query_overlap_euler(euler, internal, int2, internal, internal)
    RETURNS internal
    AS '$libdir/euler'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR CLASS euler_gin_overlap_ops FOR TYPE euler  USING gin AS
   OPERATOR         1       <  (euler,int4),
    OPERATOR        2       <= (euler,int4),
    OPERATOR        3       =  (euler,int4),
    OPERATOR        4       >= (euler,int4),
    OPERATOR        5       >  (euler,int4),
    FUNCTION        1       pg_catalog.btint4cmp(integer,integer),
    FUNCTION        2       gin_extract_value_int4_euler(euler, internal),
    FUNCTION        3       gin_extract_query_overlap_euler(euler, internal, int2, internal, internal),
    FUNCTION        4       gin_consistent_euler(internal, int2, anyelement, int4, internal, internal),
STORAGE    int4;

/*
CREATE OPERATOR CLASS euler_gin_text_ops FOR TYPE euler  USING gin AS
    OPERATOR        3       =  (euler,text),
    FUNCTION        1       pg_catalog.btint4cmp(integer,integer),
    FUNCTION        2       gin_extract_value_int4_euler(euler, internal),
    FUNCTION        3       gin_extract_query_text_euler(euler, internal, int2, internal, internal),
    FUNCTION        4       gin_consistent_euler(internal, int2, anyelement, int4, internal, internal),
STORAGE    int4;
*/


-- BRIN

CREATE OPERATOR && (
    LEFTARG   = euler,
    RIGHTARG  = euler,
    PROCEDURE = euler_overlaps
);


CREATE OPERATOR CLASS euler_inclusion_ops
  FOR TYPE euler
  USING brin  AS
    OPERATOR      3        &&(euler, euler),
    FUNCTION      1        brin_inclusion_opcinfo(internal) ,
    FUNCTION      2        brin_inclusion_add_value(internal, internal, internal, internal) ,
    FUNCTION      3        brin_inclusion_consistent(internal, internal, internal) ,
    FUNCTION      4        brin_inclusion_union(internal, internal, internal) ;


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


