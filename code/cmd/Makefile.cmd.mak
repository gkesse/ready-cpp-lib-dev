#================================================
SHELL := /bin/bash
#================================================
GSRC = ../src
GBIN = bin
GBUILD = build
GBUILD_G = build_g
GTARGET = $(GBIN)/rdv_cpp.exe
#================================================
GDEVS = ../libs

GINCS =\
	-I$(GDEVS)/include \
	-I/usr/include \
	-I/usr/local/include \
	-I/usr/include/libxml2 \
	-I/usr/include/json-c \

GLIBS =\
	-L$(GDEVS)/lib \
    -L/usr/local/lib \
    -lxml2 -ljson-c -lbase64 \
	
GOBJS =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \

GOBJS_G =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD_G)/%.o, $(wildcard $(GSRC)/*.cpp)) \

GCFLAGS =\
    -std=gnu++11 \
    
GCFLAGS_G =\
	-g \
	-rdynamic \
    -std=gnu++11 \
#================================================
# cpp
#================================================
all: clean_exe compile run
all_g: clean_exe compile_g run_g

compile: $(GOBJS)
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	g++ $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
compile_g: $(GOBJS_G)
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	g++ $(GCFLAGS_G) -o $(GTARGET) $(GOBJS_G) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD_G)/%.o: $(GSRC)/%.cpp
	@if ! [ -d $(GBUILD_G) ] ; then mkdir -p $(GBUILD_G) ; fi
	g++ $(GCFLAGS_G) -c $< -o $@ $(GINCS)
run:
	@source envs.sh && $(GTARGET) $(argv)
run_g:
	@source envs.sh && gdb -ex run --args $(GTARGET) $(argv)
clean_exe: 
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	rm -f $(GTARGET)
clean: clean_g
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	rm -f $(GBUILD)/* $(GTARGET)
clean_g: 
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	@if ! [ -d $(GBUILD_G) ] ; then mkdir -p $(GBUILD_G) ; fi
	rm -f $(GBUILD_G)/* $(GTARGET)
#================================================
