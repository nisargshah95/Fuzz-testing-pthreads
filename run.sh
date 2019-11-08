#!/bin/bash

RUN_BENCHMARK="/fastdisk/SQL-benchmark/tpch/quickstep/run-benchmark.sh quickstep.cfg"
RUN_EXEC=/mnt/hd/Fuzz-testing-pthreads/pthread_fail1
RUNS=1

cd /mnt/hd/glibc-master-build

for RAND_YIELD in 0 1; do
    for CUSTOM_SCHED in 0 1; do
        for SCHED_POLICY in 1 2; do
            for RAND_PRIO in 0 1; do
                for run in {0..$RUNS}; do
                    export RAND_YIELD CUSTOM_SCHED SCHED_POLICY RAND_PRIO
	                echo -e "\nTest: RAND_YIELD=$RAND_YIELD, CUSTOM_SCHED=$CUSTOM_SCHED, SCHED_POLICY=$SCHED_POLICY, RAND_PRIO=$RAND_PRIO"
                    # sudo $RUN_BENCHMARK
                    ./testrun.sh $RUN_EXEC
                done
            done
        done
    done
done
