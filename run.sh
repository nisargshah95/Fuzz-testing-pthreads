for RAND_YIELD in 0 1; do
    for CUSTOM_SCHED in 0 1; do
        for SCHED_POLICY in 1 2; do
            for RAND_PRIO in 0 1; do
                export $RAND_YIELD $CUSTOM_SCHED $SCHED_POLICY $RAND_PRIO
                sudo $RUN_BENCHMARK
            done
        done
    done
done

