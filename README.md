# Fuzz-testing-pthreads

## Build glibc

Copy libgcc

cp /lib/x86_64-linux-gnu/libgcc_s.so.1 "${DESTDIR}/lib/"

## Run prod-con2 and plot results

Compile

SYSROOT=/fastdisk/glibc-master-install gcc   -L${SYSROOT}/usr/lib64   -I${SYSROOT}/include   --sysroot=${SYSROOT}   -Wl,-rpath=${SYSROOT}/lib64   -Wl,--dynamic-linker=/fastdisk/glibc-master-install/lib64/ld-2.30.9000.so  -pthread -g -o /mnt/hd/prod-con2 /mnt/hd/prod-con2.c

Run

cd <glibc build dir>

sudo CUSTOM_SCHED=1 SCHED_POLICY=1 RAND_PRIO=1 ./testrun.sh /mnt/hd/prod-con2 > /mnt/hd/prod-con2-static-fifo-2-100m.out

Plot

python3 plot.py /mnt/hd/prod-con2-static-rr-2-100m.out

## Build glibc from ubuntu sources -
https://packages.ubuntu.com/bionic/glibc-source

https://www.cmiss.org/cmgui/wiki/BuildingUbuntuPackagesFromSource

https://wiki.ubuntu.com/Kernel/BuildYourOwnKernel#Obtaining_the_source_for_an_Ubuntu_release

This doesn't look like a viable option because ubuntu sources are in form of diffs and not actual C files. It will be difficult to make changes.

## Build vanilla glibc -
https://www.gnu.org/software/libc/sources.html

https://www.gnu.org/software/libc/manual/html_node/Configuring-and-compiling.html

https://sourceware.org/glibc/wiki/Testing/Builds has steps to build and install glibc to a different location and run programs with both old and new glibc.

## Changes needed in files:
- pthread_create.c
- pthread_attr_setschedparam.c //don't let the user to make changes to sched param
- pthread_attr_setschedpolicy.c //don't let the user to make changes to sched policy

## Control program
- Create multiple producer and one consumer, producers write their thread id X number of times.
- Schedule producers using the configuration file. At then end see what is sitting in the queue.

## Main experiments
- Run TPC-H queries on different DBMS's with original pthread lib and get the results.
- Run TPC-H queries on different DBMS's with changed pthread lib and validate the results.
