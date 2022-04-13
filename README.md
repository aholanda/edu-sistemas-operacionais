# edu-os
Operating systems educational resources.

Each directory contains resources to subsystems study as follows:

* [`fs`](fs): file system;
* [`mm`](mm): memory management;
* [`proc`](proc): process management;
* [`sched`](sched): process scheduling;
* [`sync`](sync): synchronization, concurrency or locking.

Files to be used in Windows operating system start with uppercase
letters, Linux or FreeBSD files start with lowercase letters.  The
exceptions are files with all letters uppercase, like README.md, that are
agnostic.

The only exception that is not a subsystem and it is not following
file name rule is the [spec](spec) directory that contains
 specifications in [TLA+](https://en.wikipedia.org/wiki/TLA%2B).