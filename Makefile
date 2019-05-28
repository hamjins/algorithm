CXX             = g++ 
SRCS            = $(wildcard *.cpp)
OBJS            = $(SRCS:.cpp=.o)
TARGET          = $(SRCS:.cpp=)
#LIBS            = -lprint
#LIB_DIRS        = -L./lib
#INC             = -I./include
 
all : $(TARGET)
	$(CXX) -o $(TARGET) $(OBJS)
 
$(TARGET) :
	$(CXX) -c $(SRCS) -std=c++17
 
clean :
	rm -f $(TARGET)
	rm -f *.o
