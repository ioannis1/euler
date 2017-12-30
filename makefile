# -- COPYRIGHT (c) Ioannis Tambouras 2011-2015

EXTENSION = euler             # the extensions name
DATA      = euler--0.1.sql  euler--0.1--0.2.sql   euler--0.2--0.1.sql
REGRESS   = euler_test        # our test script file (without extension)
MODULES   = euler             # our c module file to build

# postgres build stuff
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

vi:
	 vi ~postgres/src/postgres/src/tutorial/euler.c
ins:
	sudo -u postgres make install
i drop:
	psql -qX -h localhost -d contrib_regression -U postgres  < $@.sql
c:
	PGUSER=postgres sudo -E  make  installcheck
pgxs:
	vi $(PGXS)
