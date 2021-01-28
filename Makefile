CXX = g++ 
CXXFLAGS = -Wall -Wextra -L. -g -std=c++11
RM = rm -f firewall.exe $(NEW_LIB)

NEW_LIB = firewall

all:firewall.exe

$(NEW_LIB):
	$(CXX) $(CXXFLAGS) -fPIC -shared string.cpp field.cpp ip.cpp port.cpp  -o lib$(NEW_LIB).so

firewall.exe: $(NEW_LIB)
	$(CXX) $(CXXFLAGS) main.cpp -o firewall.exe -l$(NEW_LIB) -linput


clean:
	$(RM)