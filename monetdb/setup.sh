for RAND_YIELD in 0 1; do
    CUSTOM_SCHED=1
#    for CUSTOM_SCHED in 0 1; do
        for SCHED_POLICY in 1 2; do
#            for RAND_PRIO in 0 1; do
                export RAND_YIELD CUSTOM_SCHED SCHED_POLICY RAND_PRIO
                echo -e "\nTest: RAND_YIELD=$RAND_YIELD, CUSTOM_SCHED=$CUSTOM_SCHED, SCHED_POLICY=$SCHED_POLICY, RAND_PRIO=$RAND_PRIO"
                monetdbd stop /scratch/monet-data
                monetdbd start /scratch/monet-data
                ./run100.sh
 #           done
        done
#    done
done
