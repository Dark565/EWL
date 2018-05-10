objdir=Build/Object
sodir=Build
libdir=QL

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

clear:
	@rm -rf $(sodir)

install:
ifeq ($(compiled),1)
ifeq ("$(wildcard $(prefix)usr/include/QL)","")
	mkdir -p $(prefix)usr/include/QL
endif
	rsync -v -r --exclude='*.cpp' $(libdir)/ $(prefix)usr/include/QL/
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
	rm -f $(prefix)usr/lib64/libql-images.so
	rm -f $(prefix)usr/lib64/libql-maths.so
	rm -f $(prefix)usr/lib64/libql-video.so
	rm -f $(prefix)usr/lib64/libql-system.so
	rm -f $(prefix)usr/lib64/libql-pixmap.so

build: directory compile libs 

libs:
	g++ -shared $(objdir)/colors.o -o $(sodir)/libql-colors.so
	g++ -shared $(objdir)/console.o -o $(sodir)/libql-console.so
	g++ -shared $(objdir)/maths.o -o $(sodir)/libql-maths.so -lql-console -L$(objdir)
	g++ -shared $(objdir)/pixmap.o $(objdir)/tiff.o $(objdir)/png.o $(objdir)/jpeg.o -o $(sodir)/libql-pixmap.so -lql-maths $(libs) -L$(objdir)
	g++ -shared $(objdir)/video.o $(objdir)/vgif.o $(objdir)/vmkv.o $(objdir)/vmp4.o $(objdir)/vwmv.o $(objdir)/files.o -o $(sodir)/libql-video.so -lavcodec -I/usr/include/ffmpeg/
	g++ -shared $(objdir)/system.o $(objdir)/time.o -o $(sodir)/libql-system.so
	touch $(objdir)/compiled
compile:
ifneq ("$(wildcard $(sodir))","")
	rm -rf $(objdir)
endif
	mkdir $(objdir)
	g++ -fPIC -c $(libdir)/Pixmap/pixmap.cpp -o $(objdir)/pixmap.o
	g++ -fPIC -c $(libdir)/Files/files.cpp -o $(objdir)/files.o
	g++ -fPIC -c $(libdir)/Colorize/colors.cpp -o $(objdir)/colors.o
	g++ -fPIC -c $(libdir)/Console/console.cpp -o $(objdir)/console.o
	g++ -fPIC -c $(libdir)/Pixmap/IO/tiff.cpp -o $(objdir)/tiff.o
	g++ -fPIC -c $(libdir)/Pixmap/IO/png.cpp -o $(objdir)/png.o
	g++ -fPIC -c $(libdir)/Pixmap/IO/jpeg.cpp -o $(objdir)/jpeg.o
	g++ -fPIC -c $(libdir)/Maths/maths.cpp -o $(objdir)/maths.o
	g++ -fPIC -c $(libdir)/Video/video.cpp -o $(objdir)/video.o
	g++ -fPIC -c $(libdir)/Video/IO/gif.cpp -o $(objdir)/vgif.o -I/usr/include/ffmpeg
	g++ -fPIC -c $(libdir)/Video/IO/mkv.cpp -o $(objdir)/vmkv.o -I/usr/include/ffmpeg
	g++ -fPIC -c $(libdir)/Video/IO/mp4.cpp -o $(objdir)/vmp4.o -I/usr/include/ffmpeg
	g++ -fPIC -c $(libdir)/Video/IO/wmv.cpp -o $(objdir)/vwmv.o -I/usr/include/ffmpeg
	g++ -fPIC -c $(libdir)/System/system.cpp -o $(objdir)/system.o
	g++ -fPIC -c $(libdir)/Time/units.cpp -o $(objdir)/time.o

directory:
ifneq  ("$(wildcard $(sodir))","")
	rm -rf $(sodir)
endif
	mkdir $(sodir)