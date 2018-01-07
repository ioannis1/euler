-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION euler" to load this file. \quit


DROP OPERATOR CLASS IF EXISTS  euler_inclusion_ops USING brin;
DROP OPERATOR CLASS IF EXISTS  euler_gin_ops       USING gin ;

