source monetdb.cfg

export CUSTOM_SCHED=1

monetdb stop tpch1
monetdb destroy tpch1

monetdb create tpch1
monetdb release tpch1

mclient -d tpch1 < create.sql
