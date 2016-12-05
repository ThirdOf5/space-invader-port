CXX=g++ -std=c++11
OBJS=ship.o map.o enemy.o
SYSLIBS=-lsfml-graphics -lsfml-window -lsfml-system

main: $(OBJS)
	$(CXX)  $(^) main.cpp -o main $(SYSLIBS)

%.o: %.cpp
	$(CXX) -c $(^) -o $(@) $(SYSLIBS)

clean:
	rm main *.o
