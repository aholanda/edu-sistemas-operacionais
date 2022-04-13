-------------------------------- MODULE FIFOScheduler -------------------------
EXTENDS Naturals, Sequences, CPUInterface
VARIABLES proc, Q
----------------------------------------------------------------------------------
TypeInvariant ==
        /\ proc \in Proc
        /\ Q \in Seq(Proc)
----------------------------------------------------------------------------------
Sched(cpu) ==
        /\ \E sched \in MSched:
         /\ p \in Proc : p = Tail(Q)
                /\ Schedule(p, cpu, cpuInt, cpuInt')
                
                /\ TODO Temporal Synchronous Communication
==================================================================================
