# Compiler und Flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -I. -I./bcrypt -I./DAO
LDFLAGS = -lSQLiteCpp -lsqlite3 -lpthread -lcryptopp

# Quellen
SRC = main.cpp bcrypt/Hash.cpp DAO/DAO.cpp crypto++/AES.cpp
OBJ = $(SRC:.cpp=.o)

# Statische Bibliothek
LIBS = bcrypt/bcrypt.a

# Ziel
TARGET = main

# Standard-Rule
all: $(TARGET)

# Kompiliere das Ziel
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LIBS) $(LDFLAGS) -o $(TARGET)

# Kompiliere Objektdateien
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Aufräumen
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean