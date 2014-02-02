#--------------------------------------------
# INSTRUCTION
# Quoted strings are to be filled in by student
#
CCC = python2
SOURCE = lex.py
STUTEST = test.ibtl


stutest.out:
	@echo "Input file: $(STUTEST):"
	@cat $(STUTEST)
	@$(CCC) $(SOURCE) $(STUTEST) > stutest1.out
	@cat stutest1.out

proftest.out:
	cat $(PROFTEST)
	$(CCC) $(SOURCE) $(PROFTEST) > proftest.out
	cat proftest.out

