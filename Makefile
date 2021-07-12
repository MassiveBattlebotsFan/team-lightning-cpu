BUILD = build
SRC = src
HEADERS = $(SRC)/headers
CXXFLAGS = -std=c++2a
ifeq ($(OS), Windows_NT)
	EXECUTABLE=main.exe
else
	EXECUTABLE=main.out
endif

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)/*.cpp $(HEADERS)/*.hpp
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $(BUILD)/$@
