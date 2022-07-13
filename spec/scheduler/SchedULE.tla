------------------------------ MODULE SchedULE ------------------------------
EXTENDS Integers, Naturals, Sequences
CONSTANT Classes, CPUs, Threads
VARIABLES
    runQ,
    cls
    
ASSUME Classes \in {"idle", "interrupt", "realtime", "timesharing"}
-----------------------------------------------------------------------------

TypeInvariant == 
    /\ cls \in [Threads -> Classes]
    /\ runQ \in Seq(CPUs \X Threads)


Init ==
    /\ cls = [t \in Threads |-> "idle"] 
    /\ runQ =  << >>
    
-----------------------------------------------------------------------------

Schedule(c,t,l) ==
    /\ cls[t] = l
    /\ runQ' = Append(runQ, << c, t >>)

-----------------------------------------------------------------------------

Next == \A c \in CPUs, t \in Threads, l \in Classes : Schedule(c, t, l)

vars == <<cls, runQ>>

Spec == Init /\ [][Next]_vars

THEOREM SchedULE == []TypeInvariant

\*ASSUME Priority \in Nat
\* ASSUME Class \in {"idle", "interrupt", "realtime", "timesharing"}
\* ASSUME Queue \in {"current", "next", "idle"}


=============================================================================

\* (* Specification of FreeBSD scheduler *)
\* EXTENDS FiniteSets, Sequences
\* CONSTANTS CPUs, Priorities, Threads
\* \* ASSUME IsFiniteSet(CPUs) \* Number of CPUs is finite
\* VARIABLES
\*     runq, (* Queue to put threads to wait to run *)
\*     running, (* Threads that are running *)
\*     cls  (* Classes of threads *)

\* ----------------------------------------------------------------------------    

\* (* Some equivalences *)
\* Queue == Seq(Threads)
\* Classes == {"idle", "interrupt", "realtime", "timesharing"}
\* EmptyQ == CHOOSE q : q \notin Queue
\* NoClass == CHOOSE c : c \notin Classes
\* NoThread == CHOOSE t : t \notin Threads

\* -----------------------------------------------------------------------------

\* (* Each CPU is associated with three run queues (current, next and idle) *)
\* TypeInvariant ==
\*     /\ runq \in [CPUs -> [{"current","next","idle"} -> Seq(Priorities \X Threads)]]
\*     /\ running \in [CPUs -> Threads \cup {NoThread}]
\*     /\ cls \in [Threads ->  Classes \cup {NoClass}]

\* -----------------------------------------------------------------------------

\* (* During initialization queues are empty and CPUs are idle *)
\* Init ==
\*     /\ runq = [c \in CPUs |-> [q \in {"current","next","idle"} |-> <<>>]]
\*     /\ running = [c \in CPUs |-> NoThread]
\*     /\ cls = [t \in Threads |-> NoClass]

\* \* (* Schedule thread t to run in CPU c *)
\* Schedule(p,t,c) ==
\*      /\  IF cls[t] = "idle" THEN runq[c]["idle"]' = Append(runq[c]["idle"], <<p,t>>) 
\*               ELSE IF cls[t] = "interrupt" \/ cls[t] = "realtime" THEN
\*                 	 runq[c]["current"]' = Append(runq[c]["current"], <<p, t>>)
\*                 ELSE runq[c]["next"]' = Append(runq[c]["next"], <<p, t>>) \* Thread class is time sharing

\* \* Switch(c) == TRUE
\* \*     /\ \E t \in Threads : /\ t = running[c] /\ Schedule(t,c)
\* \*     /\ IF Len(runq[c]["current"]) # 0 THEN running[c] = Head(runq[c]["current"])
\* \*         ELSE IF Len(runq[c]["next"]) # 0 THEN runq[c]["current"] <=> runq[c]["next"] \* Swap queues
\* \*             ELSE running[c] = Head(runq[c]["idle"])
            
\* Next == \* The system next-state relation
\*      \A t \in Threads, c \in CPUs, p \in Priorities :
\*          /\ Schedule(p,t,c)
\* 	 \* /\ Switch(c)

\* vars == <<runq>>\*, prio, running, cls>>

\* -----------------------------------------------------------------------------

\* SchedULE == \* The complete high level specification
\*     /\ Init
\*     /\ [][Next]_<<vars>>

\* -----------------------------------------------------------------------------

\* \* (* Threads of class idle must be placed in idle queue only,
\* \*    the other classes of threads can be placed in current 
\* \*    and next queues *)
\* \* QueuesPolicy ==
\* \*     /\ \E t \in Threads, c \in SUBSET CPUs : 
\* \*             /\ cls[t] = "idle" => t \in runq[c]["idle"]
\* \*             /\ cls[t] \in {"interrupt", "realtime", "timesharing"} =>
\* \*                 \A l \in {"current", "next"} : t \in Seq(runq[c][l])

\* \* -----------------------------------------------------------------------------

\* THEOREM SchedULE => []TypeInvariant
\* \* THEOREM SchedULE => []QueuesPolicy                                         

\* \* Modification History
\* Last modified Fri Aug 08 16:14:33 BRT 2014 by ajh
\* \* Last modified Wed Aug 06 15:06:47 BRT 2014 by ajh
\* \* Created Wed Aug 06 11:57:40 BRT 2014 by ajh
