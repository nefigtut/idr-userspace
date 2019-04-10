
#define DEFINE_PER_CPU(type, val) type val

#define __get_cpu_var(var)	var
#define this_cpu_ptr(var)	var
#define per_cpu_ptr(ptr, cpu)   ({ (void)(cpu); (ptr); })
#define per_cpu(var, cpu)	(*per_cpu_ptr(&(var), cpu))

#define __this_cpu_read(var)		(var)
#define __this_cpu_write(var, val)	uatomic_set(&(var), val)
#define __this_cpu_inc(var)             uatomic_inc(&(var))
#define __this_cpu_dec(var)		uatomic_dec(&(var))
