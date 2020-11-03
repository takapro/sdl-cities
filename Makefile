PROGRAM = game
OBJS = Main.o Game.o Shader.o Texture.o VertexArray.o

CXX = c++ -Wall --std=c++17 -Iinclude
LIBS = -Llib -lSDL2 -lSOIL -lglew -framework OpenGL -framework Foundation

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)
