# idr-userspace

linux kernel idr subsystem implementation in userspace

put into tools/testing/ and "make". the build automatically
uses lib/idr.c and include/linux/idr.h from this kernel tree.

put any tests you want to run on idr to `main.c`.

- works with RHEL-7.7 kernel-3.10.0-1036.el7 sources tree.

- should work with the Linux kernel v4.10 tree

# limitations

only single-threaded as spinlocks are not implemented

requires a userspace RCU library (requires `<urcu.h>` and `<urcu/uatomic.h>`)