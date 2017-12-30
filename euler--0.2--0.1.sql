-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION euler" to load this file. \quit


DROP OPERATOR IF EXISTS && ;

DROP OPERATOR CLASS IF EXISTS  euler_inclusion_ops USING brin;

