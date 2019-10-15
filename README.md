# Fuzz-testing-pthreads


Build glibc from ubuntu sources -
https://packages.ubuntu.com/bionic/glibc-source
https://www.cmiss.org/cmgui/wiki/BuildingUbuntuPackagesFromSource

https://wiki.ubuntu.com/Kernel/BuildYourOwnKernel#Obtaining_the_source_for_an_Ubuntu_release


Build vanilla glibc -
https://www.gnu.org/software/libc/sources.html
https://www.gnu.org/software/libc/manual/html_node/Configuring-and-compiling.html

Changes needed in files:
- pthread_create.c
- pthread_attr_setschedparam.c //don't let the user to make changes to sched param
- pthread_attr_setschedpolicy.c //don't let the user to make changes to sched policy

Control program
- Create multiple producer and one consumer, producers write their thread id X number of times.
- Schedule producers using the configuration file. At then end see what is sitting in the queue.

Main experiments
- Run TPC-H queries on different DBMS's with original pthread lib and get the results.
- Run TPC-H queries on different DBMS's with changed pthread lib and validate the results.
