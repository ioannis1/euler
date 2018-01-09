\timing off
SET SEARCH_PATH TO  :path,public;
SET CLIENT_MIN_MESSAGES = 'ERROR';
begin;

SET enable_seqscan = off;

--explain
SELECT wave 
FROM try
WHERE  wave <  45
--WHERE  wave >  '2<20>'::euler
;

\q
SELECT wave FROM wave.try WHERE  wave > '2.3<2>'::euler

\q

--set enable_seqscan = off;
--set enable_indexscan = off;

EXPLAIN (analyze)
SELECT wave 
FROM try
WHERE  wave = '(33,33)'
--     AND age > wave 
;

\q

