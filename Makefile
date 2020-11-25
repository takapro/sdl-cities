PROGRAM = game
OBJS = Main.o Game.o Shader.o Texture.o VertexArray.o Earth.o GeodesicDome.o Math.o Viewport.o Text.o Cities.o

CXX = c++ -Wall --std=c++17 -Iinclude
LIBS = -Llib -lSDL2 -lSDL2_ttf -lSOIL -lglew -framework OpenGL -framework Foundation

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)
