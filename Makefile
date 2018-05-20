objdir=Build/Object
sodir=Build

libdir=QL
srcdir=$(libdir)/source
headir=$(libdir)/headers

libs=-ltiff -lpng -ljpeg
qlobjs=$(objdir)/pixmap.o $(objdir)/images.o $(objdir)/colors.o $(objdir)/console.o $(objdir)/tiff.o $(objdir)/png.o $(objdir)/jpeg.o $(objdir)/maths.o $(objdir)/video.o $(objdir)/vgif.o $(objdir)/vmkv.o $(objdir)/vmp4.o $(objdir)/vwmv.o $(objdir)/system.o $(objdir)/time.o
qllibs=-lql-pixmap -ql-console -ql-maths -lql-video -lql-system

prefix=/
compiled:=0

ifneq ($(compiled),1)
	ifneq ("$(wildcard $(objdir)/compiled)","")
		compiled:=1
	endif
endif

all: build

clean:
	@rm -rf $(sodir)

install:
ifeq ($(compiled),1)
ifeq ("$(wildcard $(prefix)usr/include/QL)","")
	mkdir -p $(prefix)usr/include/QL
endif
	install -d $(headir) $(prefix)usr/include/QL
	install -d $(sodir) $(prefix)usr/lib64/
else
	@echo "Ohh, it looks like, that .so files don't exist yet"
endif


delete:
ifneq ("$(wildcard $(prefix)usr/include/QL)","")
	rm -rf $(prefix)usr/include/QL
endif
	rm -f $(prefix)usr/lib64/libql-colors.so
	rm -f $(prefix)usr/lib64/libql-console.so
	rm -f $(prefix)usr/lib64/libql-maths.so
	rm -f $(prefix)usr/lib64/libql-video.so
	rm -f $(prefix)usr/lib64/libql-system.so
	rm -f $(prefix)usr/lib64/libql-pixmap.so

build:
	$(MAKE) directory
	$(MAKE) compile
	$(MAKE) libs

libs:
	g++ -shared $(objdir)/colors.o -o $(sodir)/libql-colors.so
	g++ -shared $(objdir)/console.o -o $(sodir)/libql-console.so
	g++ -shared $(objdir)/maths.o -o $(sodir)/libql-maths.so -lql-console -L$(sodir)
	g++ -shared $(objdir)/pixmap.o $(objdir)/tiff.o $(objdir)/bmp.o -o $(sodir)/libql-pixmap.so -lql-maths $(libs) -L$(sodir)
	g++ -shared $(objdir)/video.o $(objdir)/vgif.o $(objdir)/vmkv.o $(objdir)/vmp4.o $(objdir)/vwmv.o $(objdir)/files.o $(objdir)/windows.o -o $(sodir)/libql-video.so -lavcodec -I/usr/include/ffmpeg/
	g++ -shared $(objdir)/system.o $(objdir)/time.o $(objdir)/files.o -o $(sodir)/libql-system.so
	touch $(objdir)/compiled
compile:
ifneq ("$(wildcard $(sodir))","")
	rm -rf $(objdir)
endif
	mkdir $(objdir)
	g++ -fPIC -c $(srcdir)/Pixmap/pixmap.cpp -o $(objdir)/pixmap.o -I$(headir)
	g++ -fPIC -c $(srcdir)/Files/files.cpp -o $(objdir)/files.o -I$(headir)
	g++ -fPIC -c $(srcdir)/Colorize/colors.cpp -o $(objdir)/colors.o -I$(headir)
	g++ -fPIC -c $(srcdir)/Console/console.cpp -o $(objdir)/console.o -I$(headir)
	g++ -fPIC -c $(srcdir)/Pixmap/IO/tiff.cpp -o $(objdir)/tiff.o -I$(headir)
	g++ -fPIC -c $(srcdir)/Pixmap/IO/bmp.cpp -o $(objdir)/bmp.o -I$(headir)
	g++ -fPIC -c $(srcdir)/Maths/maths.cpp -o $(objdir)/maths.o -I$(headir)
	g++ -fPIC -c $(srcdir)/Video/video.cpp -o $(objdir)/video.o -I$(headir)
	g++ -fPIC -c $(srcdir)/Video/IO/gif.cpp -o $(objdir)/vgif.o -I$(headir) -I/usr/include/ffmpeg
	g++ -fPIC -c $(srcdir)/Video/IO/mkv.cpp -o $(objdir)/vmkv.o -I$(headir) -I/usr/include/ffmpeg
	g++ -fPIC -c $(srcdir)/Video/IO/mp4.cpp -o $(objdir)/vmp4.o -I$(headir) -I/usr/include/ffmpeg
	g++ -fPIC -c $(srcdir)/Video/IO/wmv.cpp -o $(objdir)/vwmv.o -I$(headir) -I/usr/include/ffmpeg
	g++ -fPIC -c $(srcdir)/System/system.cpp -o $(objdir)/system.o -I$(headir)
	g++ -fPIC -c $(srcdir)/Time/units.cpp -o $(objdir)/time.o -I$(headir)
	g++ -fPIC -c $(srcdir)/Windows/windows.cpp -o $(objdir)/windows.o -I$(headir)

directory:
ifneq  ("$(wildcard $(sodir))","")
	rm -rf $(sodir)
endif
	mkdir $(sodir)