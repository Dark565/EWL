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

clean: clean_modules clean_objects

clean_modules:
	@cd $(Src) && $(MAKE) -f $(Module_MK) $@

clean_objects:
	@cd $(Src) && $(MAKE) -f $(Module_MK) $@

install: install_modules install_headers

install_modules:
	@cd $(Src) && $(MAKE) -i -f $(Module_MK) $@

install_headers: headers_output
	cp -r $(INCLUDE_PATH)QL/ $(INSTALL_HEADERS_PREFIX)/

uninstall: uninstall_modules uninstall_headers

uninstall_modules:
	@cd $(Src) && $(MAKE) -i -f $(Module_MK) $@

uninstall_headers:
	rm -rd $(INSTALL_HEADERS_PREFIX)/QL/

headers_output:
	mkdir -p $(INSTALL_HEADERS_PREFIX)/QL/

.phony: all clean clean_modules build install install_headers uninstall uninstall_headers headers_output