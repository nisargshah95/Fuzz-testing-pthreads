CONTROL_DIR=/fastdisk/SQL-benchmark/tpch/quickstep/control_10
TEST_DIR=/fastdisk/SQL-benchmark/tpch/quickstep/test_10

for num in 1; do
    name=$num
    if [[ $num -lt 10 ]]; then
        name=0$num
    fi
    CONTROL_DATA=($(cat $CONTROL_DIR/${name}_c.sql | head -n -1 | tail -n +3 | grep -Eo '[0-9\.]+'))
#    echo ${CONTROL_DATA[@]}
    TEST_DATA=($(cat $TEST_DIR/${name}_c.out | head -n -1 | tail -n +3 | grep -Eo '[0-9\.]+'))
#    echo $TEST_DATA
#    echo ${#CONTROL_DATA[@]}
#    for i in ${CONTROL_DATA[@]}; do
#        echo $i
#    done

for i in `seq 0 $((${#CONTROL_DATA[@]}-1))`; do
        if [[ $(printf %.0f ${CONTROL_DATA[$i]}) != $(printf %.0f ${TEST_DATA[$i]}) ]]; then
            echo "${CONTROL_DATA[$i]} != ${TEST_DATA[$i]}"
        else
            echo "${CONTROL_DATA[$i]} = ${TEST_DATA[$i]}"
        fi
    done
done
