# ringMPI
*Example of a ring using MPI*

Dr. Victor De la Luz

vdelaluz@enesmorelia.unam.mx

License: **GNU/GPL**

The ring start in zero. For each step, the proc 0 insert a new value in the ring. After the ring is fullfilled the process continue closing the ring.

The architecture is focused in first receive/then send a message with an old value:

Receive value from (proc-1) -> The (proc) print their own oldvalue -> Send oldvalue to (proc+1)

The last proc sent their value to first proc to close the ring.

There are two tricks:

1) We need a dummy "send" from the last to the first processor at the first step. This dummy send is mandatory to start the ring and reduce the complexity of the code.

2) The last processor send the "actual value" and not the "old value" to the first processor to close the ring with the actual value. 


## Compile:

```
make
```

## Run example:

```
mpiexec -n 4 ./ring
```

## Output*

step	proc	value

0	0	10

0	1	0

0	2	0

0	3	0


1	0	20

1	1	10

1	2	0

1	3	0


2	0	30

2	1	20

2	2	10

2	3	0


3	0	40

3	1	30

3	2	20

3	3	10


4	0	10

4	1	40

4	2	30

4	3	20


5	0	20

5	1	10

5	2	40

5	3	30


6	0	30

6	1	20

6	2	10

6	3	40


7	0	40

7	1	30

7	2	20

7	3	10


*The print of the output is aleatory.
