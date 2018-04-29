CC = gcc
CFLAGS = -O2 -g
CLIB = -lm
CLIBPOSIX = -lm -lpthread
CLIBOMP = -lm -fopenmp
SERIALOBJS = matmul_serial.o utils.o
PTHREADOBJS = matmul_pthread.o utils.o
OMPOBJS = matmul_openmp.o utils.o
serial : $(SERIALOBJS)
	$(CC) $(CFLAGS) -o matmul_serial $(SERIALOBJS) $(CLIB)

pthread : $(PTHREADOBJS)
	$(CC) $(CFLAGS) -o matmul_pthread $(PTHREADOBJS) $(CLIBPOSIX)

omp : $(OMPOBJS)
	$(CC) $(CFLAGS) -c matmul_openmp.c -fopenmp
	$(CC) $(CFLAGS) -o matmul_openmp $(OMPOBJS) $(CLIBOMP)
