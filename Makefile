PROGRAM = game
OBJS = Main.o Game.o

CXX = c++ -Wall --std=c++17
LIBS = -lSDL2 -lglew -framework OpenGL

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)
