CC=g++
CCFlags=-c -O2 -fPIC
LDFlags=-shared

pre=libql-
suf=.so

modules=$(pre)audio$(suf) $(pre)formats$(suf) $(pre)graphics$(suf) $(pre)network$(suf) $(pre)system$(suf)

all: build

build: $(modules)

$(modules): module_folder:=$(@:$(pre)%=%) module_folder:=$(module_folder:%$(suf)=%) module_folder:=$(shell s=$(module_folder); echo $$(tr '[a-z]' '[A-Z]' <<< $${s:0:1})$${s:1}) specific:=$($(wildcard $(module_folder)/*/*.cpp):/=-) $($(wildcard $(module_folder)/*.cpp):/=-) $(specific)
	$(CC) -o $@ $(wildcard $(shell s=$(module_folder); echo $$(tr '[A-Z]' '[a-z]' <<< $${s:0:1})$${s:1})*.o) $(LDFlags)

$(specific):
	$(CC) -o $@ $(@:-=/) $(CCFlags)


.phony: all build clean