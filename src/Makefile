CC = icc
CXX = icpc
INCLUDES = -I/rwthfs/rz/SW/NAG/mmu/c/intel_ilp64_mark9/include -I/opt/intel/Compiler/11.1/069/mkl/include -I/opt/intel/Compiler/11.1/069/mkl/include/fftw -I/opt/intel/Compiler/11.1/069/mkl/include/intel64/lp64 -I/opt/intel/Compiler/11.1/069/mkl/include/ia32 -L/rwthfs/rz/SW/NAG/mmu/c/intel_ilp64_mark9/lib -lnagc_nag -L/opt/intel/Compiler/11.1/069/mkl/lib/intel64 -L/opt/intel/Compiler/11.1/069/mkl/lib/ia32 -lrwthmkl -lpthread -openmp
CFLAGS = 
COMPILE = $(CC) $(INCLUDES) $(CFLAGS) -c

# Für das einfache Testprogramm
test: test.o utils.o	
	$(CXX) $(INCLUDES) -o test test.o utils.o

%.o: %.cpp
	$(COMPILE) -o $@ $<	

clean:
	rm *.o
