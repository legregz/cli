# Variables
CXX = g++
LDFLAGS = `pkg-config --cflags --libs opencv4`
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TARGET = main

# Liste des fichiers source
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Règle par défaut
all: $(BINDIR)/$(TARGET)

# Règle pour créer l'exécutable
$(BINDIR)/$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Règle pour compiler les fichiers source en fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJS) $(BINDIR)/$(TARGET)
