#--------------------------------------------
# INSTRUCTION
# Quoted strings are to be filled in by student
#
CCC = gforth
CCFLAGS = ""
OBJS = "list of obj f"
SOURCE = hw1.fs stutest1.in
RUNFLAGS = -e bye

$(OBJS): $(SOURCE)
	$(CCC) $(CCFLAGS) -c $(SOURCE)

compiler: $(OBJS)
	$(CCC) $(CCFLAGS) -o compiler $(OBJS)

clean:
	rm -f ".o files" core ".exe/class files" "outputs"
	ls

stutest.out:
	cat stutest1.in
	$(CCC) $(SOURCE) $(RUNFLAGS) > stutest1.out
	cat stutest1.out
# Notice the next line. The `-' says to ignore the return code. This
# is a way to have multiple tests of errors that cause non-zero return
# codes.

proftest.out:
	cat $(PROFTEST)
	$(CCC) $(SOURCE) $(PROFTEST) $(RUNFLAGS) > proftest.out
	cat proftest.out

