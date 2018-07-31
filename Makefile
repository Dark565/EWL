Src=source/QL
Module_MK=modules.mk

INCLUDE_PATH=$(CURDIR)/headers/
INSTALL_HEADERS_PREFIX=/usr/include
INSTALL_PREFIX:=
PACK=OTHER

ARCH=64

ifeq ($(ARCH),64)
	INSTALL_PREFIX=/usr/lib64
else
	INSTALL_PREFIX=/usr/lib
endif

export INCLUDE_PATH
export INSTALL_PREFIX
export PACK
export ARCH
export QL_TYPE

all: build

build:
	@cd $(Src) && $(MAKE) -f $(Module_MK) $@ 

clean:
	@cd $(Src) && $(MAKE) -f $(Module_MK) $@

clean_modules:
	@cd $(Src) && $(MAKE) -f $(Module_MK) $@

install:
	@cd $(Src) && $(MAKE) -f $(Module_MK) $@

install_headers: headers_output
	install $(INCLUDE_PATH)QL/ $(INSTALL_HEADERS_PREFIX)/

uninstall:
	@cd $(Src) && $(MAKE) -f $(Module_MK) $@

uninstall_headers:
	rm -rd $(INCLUDE_PATH)/QL/

headers_output:
	mkdir -p $(INSTALL_HEADERS_PREFIX)/QL/

.phony: all clean clean_modules build install install_headers uninstall uninstall_headers headers_output