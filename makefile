SRC=src/

VPATH=$(addprefix $(SRC), c_file c_file/virtual func interface lowlevel)

OBJS=c_file.o c_file_synod.o c_file_base.o c_file_ciclico.o funcs.o CrittoxGuiApp.o CrittoxGuiMain.o Error.o interface.o modf.o

CXXFALGS=-lcrypto -lssl

OBJD=obj/

all:CrittoxGui


CrittoxGui:$(OBJS)
	g++ -o CrittoxGui $(addprefix $(OBJD),$(OBJS)) $(CXXFLAGS) `wx-config --libs`

CrittoxGuiApp.o: CrittoxGuiApp.cpp CrittoxGuiApp.h
	g++ -c `wx-config --cxxflags` -o $(OBJD)$@ $<

CrittoxGuiMain.o: CrittoxGuiMain.cpp CrittoxGuiMain.h
	g++ -c `wx-config --cxxflags` -o $(OBJD)$@ $<

Error.o: Error.cpp Error.h
	g++ -c `wx-config --cxxflags` -o $(OBJD)$@ $<

%.o:%.cpp
	g++ -c -o $(OBJD)$@ $< $(CXXFLAGS)

clean:
	rm $(OBJD)/*.o



