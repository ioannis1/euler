\timing off
SET SEARCH_PATH TO :path,public;
SET CLIENT_MIN_MESSAGES = 'ERROR';


CREATE INDEX wave_idx ON try USING gin (wave euler_gin_overlap_ops);
\q
CREATE INDEX wave_idx ON try USING gin (wave euler_gin_ops);

--CREATE INDEX wave_idx ON try USING brin (wave euler_minimax_ops);


