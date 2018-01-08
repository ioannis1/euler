\timing off
SET SEARCH_PATH TO :path,public;

INSERT INTO try
SELECT --public.random_string(4)
       i
     ,( '('|| i ||','|| i || ')')::euler
FROM  generate_series(1,4) a(i);

INSERT INTO try values (20, '1<20>'::euler);

ANALYZE try;

\q


\COPY try FROM stdin;
1	(1,3)
2	(2,4)
\.

\q

