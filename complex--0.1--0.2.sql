-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION euler" to load this file. \quit



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
    FUNCTION      4        brin_inclusion_union(internal, internal, internal) 
;
