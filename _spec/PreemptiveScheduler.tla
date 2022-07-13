-------------------------------- MODULE PreemptiveScheduler -------------------------
EXTENDS Naturals, Sequences, CPUInterface
CONSTANT
  State (* The set of possible states *)
VARIABLES proc, runQ, state
ASSUME State \in {
        "running",         (* The process is executing or waiting *) 
        "interruptible",   (* The process is sleeping waiting some condition to occur.
                              This condition should be an interrupt, system resource release 
                              or a signal. *)
        "uninterruptible", (* Like interruptible, but a signal leaves it unchanged. *)
        "stopped",         (* Process execution is stopped after receiving a signal,
                              but it is ready to be executed again, because there is 
                              no condition pending. *)
        "dead"             (* The process execution is terminated. *)                              
}
----------------------------------------------------------------------------------
TypeInvariant ==
        /\ proc \in Proc 
        /\ runQ \in Seq(Proc)
----------------------------------------------------------------------------------
EnqueueProcess(p) ==
/\ p.state = "interruptible"
/\ p.state' = "running"
\*/\ runQ \U {p}
DequeueProcess(p) == 
/\ p.state \in {"running", "interruptible"}
/\ p.state = "running"
==================================================================================
