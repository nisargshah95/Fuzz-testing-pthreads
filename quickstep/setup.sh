for i in {1..100}; do
    for RAND_YIELD in 0 1; do
        CUSTOM_SCHED=1
#        for CUSTOM_SCHED in 0 1; do
            for SCHED_POLICY in 1 2; do
#                for RAND_PRIO in 0 1; do
                    export RAND_YIELD CUSTOM_SCHED SCHED_POLICY RAND_PRIO
                    echo -e "\nTest: RAND_YIELD=$RAND_YIELD, CUSTOM_SCHED=$CUSTOM_SCHED, SCHED_POLICY=$SCHED_POLICY, RAND_PRIO=$RAND_PRIO"
                    /fastdisk/quickstep/build/quickstep_cli_shell -printing_enabled=true -num_workers=40 -preload_buffer_pool=false -storage_path=/slowdisk/qs_tpch_1_qstor < tmp.sql > query_c-${RAND_YIELD}-${SCHED_POLICY}.out
 #               done
            done
#        done
    done
done
