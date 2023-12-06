#================================================
SHELL := /bin/bash
#================================================
GSRC = ../code/src
GBIN = bin
GBUILD = build
GBUILD_G = build_g
GTARGET = $(GBIN)/rdv_cpp_server.exe
#================================================
GINCS =\
    -I$(GSRC)/manager \
    -I$(GSRC)/libs/include \
	-I/usr/include/libxml2 \
	-I/usr/local/include \
	
GLIBS =\
    -L$(GSRC)/libs/lib \
    -L/usr/local/lib \
    -lb64c -lbase64 -ltinyexpr -lmd5 -ldatetime \
    -lxml2 -lmysqlcppconn -lcurl -lssl -lcrypto -ljson-c \
	
GOBJS =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \
    $(patsubst $(GSRC)/manager/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.cpp)) \

GOBJS_G =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD_G)/%.o, $(wildcard $(GSRC)/*.cpp)) \
    $(patsubst $(GSRC)/manager/%.cpp, $(GBUILD_G)/%.o, $(wildcard $(GSRC)/manager/*.cpp)) \

GCFLAGS =\
    -std=gnu++11 \
    
GCFLAGS_G =\
    -g \
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
$(GBUILD)/%.o: $(GSRC)/manager/%.cpp
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD_G)/%.o: $(GSRC)/%.cpp
	@if ! [ -d $(GBUILD_G) ] ; then mkdir -p $(GBUILD_G) ; fi
	g++ $(GCFLAGS_G) -c $< -o $@ $(GINCS)
$(GBUILD_G)/%.o: $(GSRC)/manager/%.cpp
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
