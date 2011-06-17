CC = icc
CXX = icpc
INCLUDES = -I/rwthfs/rz/SW/NAG/mmu/c/intel_ilp64_mark9/include -I/opt/intel/Compiler/11.1/069/mkl/include -I/opt/intel/Compiler/11.1/069/mkl/include/fftw -I/opt/intel/Compiler/11.1/069/mkl/include/intel64/lp64 -I/opt/intel/Compiler/11.1/069/mkl/include/ia32 -L/rwthfs/rz/SW/NAG/mmu/c/intel_ilp64_mark9/lib -lnagc_nag -L/opt/intel/Compiler/11.1/069/mkl/lib/intel64 -L/opt/intel/Compiler/11.1/069/mkl/lib/ia32 -lrwthmkl -lpthread -openmp
CFLAGS = 
COMPILE = $(CC) $(INCLUDES) $(CFLAGS) -c

all: test_corr_ken test_corr_cov test_reg_sim test_reg_mul

test_corr_ken: test_corr_ken.o utils.o Timer.o
	$(CXX) $(INCLUDES) -o test_corr_ken test_corr_ken.o utils.o Timer.o

test_corr_cov: test_corr_cov.o utils.o Timer.o
	$(CXX) $(INCLUDES) -o test_corr_cov test_corr_cov.o utils.o Timer.o

test_reg_sim: test_reg_sim.o utils.o Timer.o
	$(CXX) $(INCLUDES) -o test_reg_sim test_reg_sim.o utils.o Timer.o

test_reg_mul: test_reg_mul.o utils.o Timer.o
	$(CXX) $(INCLUDES) -o test_reg_mul test_reg_mul.o utils.o Timer.o


%.o: %.cpp
	$(COMPILE) -o $@ $<	

clean:
	rm *.o