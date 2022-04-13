------------------------- MODULE MCSchedULE --------------------------
EXTENDS SchedULE

CONSTANT MaxQLen
Constraint ==  Len(runQ) \leq MaxQLen
======================================================================
