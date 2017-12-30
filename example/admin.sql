\timing off
SET SEARCH_PATH TO :path;
SET CLIENT_MIN_MESSAGES = 'ERROR';


CREATE INDEX wave_idx ON try USING brin (wave euler_minimax_ops);


