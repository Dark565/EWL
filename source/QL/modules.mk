CC=g++

Libraries_out=	bin/

System=		libql-system.so
Formats=	libql-formats.so
Graphics=	libql-graphics.so
Audio=		libql-audio.so
Network=	libql-network.so
#Utils=		libql-utils.so
MERGE=		libql.so

out_System=		$(Libraries_out)$(System)
out_Formats=	$(Libraries_out)$(Formats)
out_Graphics=	$(Libraries_out)$(Graphics)
out_Audio=		$(Libraries_out)$(Audio)
out_Network=	$(Libraries_out)$(Network)
#out_Utils=		$(Libraries_out)$(Utils)
out_MERGE=		$(Libraries_out)$(MERGE)

CC_Flags=-I"$(INCLUDE_PATH)" -O2 -fPIC -m$(ARCH)
Linker_Flags=-shared -L$(Libraries_out) -m$(ARCH)

System_flags:=-ldl
Formats_flags:=-ltiff
Graphics_flags:=
Audio_flags:=
Network_flags:=
#Utils_flags:=

System_flags_shared:=-lpthread
Formats_flags_shared:=
Graphics_flags_shared=-lql-system -lql-formats
Audio_flags_shared=-lql-system
Network_flags_shared:=
#Utils_flags_shared:=

ADDITIONAL_FLAGS:=

ifeq ($(QL_TYPE),LINK)
	ADDITIONAL_FLAGS+=-DQL_LINK
	Graphics_flags+=-lX11 -lXrandr
endif

System_source=	$(patsubst %.cpp,%.o,$(subst /,-,$(wildcard System/*.cpp)))
Formats_source=	$(patsubst %.cpp,%.o,$(subst /,-,$(wildcard Formats/*.cpp)))
Graphics_source=$(patsubst %.cpp,%.o,$(subst /,-,$(wildcard Graphics/*.cpp)))
Audio_source=	$(patsubst %.cpp,%.o,$(subst /,-,$(wildcard Audio/*.cpp)))
Network_source=	$(patsubst %.cpp,%.o,$(subst /,-,$(wildcard Network/*.cpp)))
#Utils_source=	$(patsubst %.cpp,%.o,$(subst /,-,$(wildcard Utils/*.cpp)))

sources=$(System_source) $(Formats_source) $(Graphics_source) $(Audio_source) $(Network_source) #$(Utils_source)
modules=$(System) $(Formats) $(Graphics) $(Audio) $(Network) #$(Utils)
out_modules=$(out_System) $(out_Formats) $(out_Graphics) $(out_Audio) $(out_Network) #$(out_Utils)

merge_flags=$(Formats_flags) $(System_flags) $(Graphics_flags) $(Audio_flags) $(Network_flags) #$(Utils_flags)

all: build

build: $(sources)
	$(MAKE) -f modules.mk $(Libraries_out)
ifeq ($(PACK),MERGE)
	@export QL_TYPE=$(QL_TYPE) && $(MAKE) -f modules.mk $(out_MERGE)
else
	@$(foreach mod,$(out_modules),export QL_TYPE=$(QL_TYPE) && $(MAKE) -f modules.mk $(mod);)
endif

$(Libraries_out):
	mkdir $(Libraries_out)

clean_objects:
	rm $(sources)

clean_modules:
	rm -rf $(Libraries_out)

install_modules: output
	cp $(Libraries_out)* $(INSTALL_PREFIX)/

uninstall_modules:
	@$(foreach mod,$(modules) $(MERGE),rm -rf $(INSTALL_PREFIX)/$(mod))

output:
	mkdir -p $(INSTALL_PREFIX)/QL/

$(sources):
	$(CC) -c -o $@ $(patsubst %.o,%.cpp,$(subst -,/,$@)) $(CC_Flags) $(ADDITIONAL_FLAGS)

$(out_System):
	$(CC) -o $@ $(System_source) $(Linker_Flags) $(System_flags) $(System_flags_shared)

$(out_Formats):
	$(CC) -o $@ $(Formats_source) $(Linker_Flags) $(Formats_flags) $(Formats_flags_shared)

$(out_Graphics):
	$(CC) -o $@ $(Graphics_source) $(Linker_Flags) $(Graphics_flags) $(Graphics_flags_shared)

$(out_Audio):
	$(CC) -o $@ $(Audio_source) $(Linker_Flags) $(Audio_flags) $(Audio_flags_shared)

$(out_Network):
	$(CC) -o $@ $(Network_source) $(Linker_Flags) $(Network_flags) $(Network_flags_shared)

#$(out_Utils):
	#$(CC) -o $@ $(Utils_source) $(Linker_Flags) $(Utils_flags) $(Utils_flags_shared)

$(out_MERGE):
	$(CC) -o $@ $(sources) $(Linker_Flags) $(merge_flags)


.phony: all build install uninstall clean clean_modules output
