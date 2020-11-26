PROGRAM = game
OBJS = Main.o Game.o Shader.o Texture.o VertexArray.o Earth.o GeodesicDome.o Math.o Viewport.o Text.o Cities.o CitiesGame.o

CXX = c++ -Wall --std=c++17 -Iinclude
LIBS = -Llib -lSDL2 -lSDL2_ttf -lSOIL -lglew -framework OpenGL -framework Foundation

all: $(PROGRAM)

depend:
	$(CXX) -isystem /usr/local/include -isystem include -MM $(OBJS:.o=.cpp) > .depend

.depend:
	$(CXX) -isystem /usr/local/include -isystem include -MM $(OBJS:.o=.cpp) > .depend

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)

include .depend
