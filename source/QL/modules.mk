CC=g++

System=		libql-system.so
Formats=	libql-formats.so
Graphics=	libql-graphics.so
Audio=		libql-audio.so
Network=	libql-network.so

MERGE=		libql.so

CC_Flags=-I$(INCLUDE_PATH) -O2 -fPIC -m$(ARCH)
Linker_Flags=-shared -L./ -m$(ARCH)

System_flags:=-ldl
Formats_flags:=-ltiff
Graphics_flags:=
Audio_flags:=
Network_flags:=

System_flags_shared:=-lpthread
Formats_flags_shared:=
Graphics_flags_shared=-lql-system -lql-formats
Audio_flags_shared=-lql-system
Network_flags_shared:=

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

sources=$(System_source) $(Formats_source) $(Graphics_source) $(Audio_source) $(Network_source)
modules=$(System) $(Formats) $(Graphics) $(Audio) $(Network)

merge_flags=$(Formats_flags) $(System_flags) $(Graphics_flags) $(Audio_flags) $(Network_flags)

all: build

build:
ifeq ($(PACK),MERGE)
	@export QL_TYPE=$(QL_TYPE) && $(MAKE) -f modules.mk $(MERGE)
else
	@$(foreach mod,$(modules),export QL_TYPE=$(QL_TYPE) && $(MAKE) -f modules.mk $(mod);)
endif

clean:
	rm -rf $(sources)

clean_modules:
	rm -rf $(modules) $(MERGE)

install: output
	@$(foreach mod,$(modules) $(MERGE),install $(mod) $(INSTALL_PREFIX)/ 2>/dev/null)

uninstall:
	@$(foreach mod,$(modules) $(MERGE),rm -f $(INSTALL_PREFIX)/$(mod) 2>/dev/null)

output:
	mkdir -p $(INSTALL_PREFIX)/QL/

$(System_source) $(Graphics_source) $(Audio_source) $(Network_source) $(Formats_source):
	$(CC) -c -o $@ $(patsubst %.o,%.cpp,$(subst -,/,$@)) $(CC_Flags)

$(System): $(System_source)
	$(CC) -o $@ $^ $(Linker_Flags) $(System_flags) $(System_flags_shared)

$(Formats): $(Formats_source)
	$(CC) -o $@ $^ $(Linker_Flags) $(Formats_flags) $(Formats_flags_shared)

$(Graphics): $(Graphics_source)
	$(CC) -o $@ $^ $(Linker_Flags) $(Graphics_flags) $(Graphics_flags_shared)

$(Audio): $(Audio_source)
	$(CC) -o $@ $^ $(Linker_Flags) $(Audio_flags) $(Audio_flags_shared)

$(Network): $(Network_source)
	$(CC) -o $@ $^ $(Linker_Flags) $(Network_flags) $(Network_flags_shared)

$(MERGE): $(sources)
	$(CC) -o $@ $^ $(Linker_Flags) $(merge_flags)


.phony: all build install uninstall clean clean_modules output
