# Edmanuel Torres 21/10/2004

include makeinclude

all:	$(OBJS)
	echo "==== Compiling  ====";
	$(CXX) -o $(PROG) $(OBJS) $(LFLAGS)


clean:
	echo "==== Cleaning ====";
	rm -rf *.o $(OBJS) $(PROG)
