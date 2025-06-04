# Fordító
CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude -Iinclude/glad -Iinclude/KHR


# pkg-config használata glfw3-hoz
PKG_CONFIG = pkg-config
GLFW_CFLAGS = $(shell $(PKG_CONFIG) --cflags glfw3)
GLFW_LIBS = $(shell $(PKG_CONFIG) --static --libs glfw3)

# Könyvtárak
LIBS = $(GLFW_LIBS) -lassimp -lopengl32 -lgdi32 -luser32 -lkernel32

# Forrásfájlok
SRC = src/main.cpp src/shader.cpp src/camera.cpp src/model.cpp src/stb_image.cpp src/texture.cpp src/glad.c

# Objektumfájlok
OBJ = $(SRC:.cpp=.o)
OBJ := $(OBJ:.c=.o)

# Kimeneti fájl neve
EXEC = InteractiveSculpture.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(GLFW_CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(GLFW_CFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) $(GLFW_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)
