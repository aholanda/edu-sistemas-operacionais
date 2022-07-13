--------------------------------- MODULE CPUInterface --------------------------------
EXTENDS Naturals
VARIABLE cpuInt
CONSTANTS 
        Schedule(_,_,_,_), (* A Schedule(p, cpu, cpuInt, cpuInt') step represents 
                              the scheduler sending a process p to CPU cpu to 
                              be executed *)
        Suspend(_,_,_,_), (* A Suspend(p, cpu, cpuInt, cpuInt') step represents 
                             a CPU cpu suspending a Proc p execution *)
        CPU, (* The set of CPU identifiers *)
        Proc, (* The set of processes *)
        InitCPUInt (* The set of possible values of cpuInt *)
ASSUME \A p, cpu, ciOld, ciNew : /\ Schedule(p, cpu, ciOld, ciNew) \in BOOLEAN
                                 /\ Suspend(p, cpu, ciOld, ciNew) \in BOOLEAN
-------------------------------------------------------------------------------------
MSched == [op:{"Sched"}, proc:Proc] \union [op:{"Spd"}, proc:Proc]                                 
=====================================================================================
