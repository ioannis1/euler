SET CLIENT_MIN_MESSAGES = 'ERROR';
SET SEARCH_PATH to public;
BEGIN;

SELECT euler_mult( '(2,7)'::euler, '(3,9)');
SELECT euler_mult( '(3,2)'::euler, '(1,7)');
SELECT euler_mult( '(1,1)'::euler, '(1,1)');
SELECT euler_polar( '(4,3)');
SELECT euler_xy('(5,36.8699)');
SELECT euler_xy(euler_polar( '(4,3)'));
SELECT euler_polar(euler_theta_add('(4,3)',20));

\q
CREATE OPERATOR && (
    LEFTARG   = euler,
    RIGHTARG  = euler,
    PROCEDURE = euler_overlaps
);

CREATE OPERATOR CLASS euler_inclusion_ops
  DEFAULT FOR TYPE euler
  USING brin  AS
    OPERATOR      3        &&(euler, euler),
    FUNCTION      1        brin_inclusion_opcinfo(internal) ,
    FUNCTION      2        brin_inclusion_add_value(internal, internal, internal, internal) ,
    FUNCTION      3        brin_inclusion_consistent(internal, internal, internal) ,
    FUNCTION      4        brin_inclusion_union(internal, internal, internal) 
;
