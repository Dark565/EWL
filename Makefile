objdir=Build/Object
sodir=Build

libdir_ql=QL
libdir_q3d=Q3D
srcdir=source
headir=headers
srcdir_ac_ql=$(srcdir)/$(libdir_ql)
headir_ac_ql=$(headir)/$(libdir_ql)

libs=-ltiff -lpng -ljpeg
qlobjs=$(objdir)/pixmap.o $(objdir)/images.o $(objdir)/colors.o $(objdir)/console.o $(objdir)/ptiff.o $(objdir)/ppng.o $(objdir)/pjpeg.o $(objdir)/pbmp.o $(objdir)/maths.o $(objdir)/video.o $(objdir)/vgif.o $(objdir)/vmkv.o $(objdir)/vmp4.o $(objdir)/vwmv.o $(objdir)/system.o $(objdir)/time.o $(objdir)error.o $(objdir)/audio.o $(objdir)/awav.o
qllibs=-lql-pixmap -ql-console -ql-maths -lql-video -lql-system -lql-audio

g++_obj_flags = -fPIC -c -O2 -I$(headir)

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
	install -d $(headir) $(prefix)usr/include/
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
	rm -f $(prefix)usr/lib64/libql-audio.so

build:
	$(MAKE) directory
	$(MAKE) compile
	$(MAKE) libs

libs:
	g++ -shared $(objdir)/fbmp.o $(objdir)/fwav.o -o $(sodir)/libql-files.so
	g++ -shared $(objdir)/colors.o -o $(sodir)/libql-colors.so
	g++ -shared $(objdir)/console.o -o $(sodir)/libql-console.so
	g++ -shared $(objdir)/maths.o -o $(sodir)/libql-maths.so -lql-console -L$(sodir)
	g++ -shared $(objdir)/pixmap.o $(objdir)/ptiff.o $(objdir)/pbmp.o -o $(sodir)/libql-pixmap.so -lql-maths -lql-files $(libs) -L$(sodir)
	g++ -shared $(objdir)/video.o $(objdir)/vgif.o $(objdir)/vmkv.o $(objdir)/vmp4.o $(objdir)/vwmv.o $(objdir)/files.o $(objdir)/windows.o -o $(sodir)/libql-video.so -lavcodec -I/usr/include/ffmpeg/
	g++ -shared $(objdir)/system.o $(objdir)/time.o $(objdir)/files.o $(objdir)/init.o $(objdir)/program.o $(objdir)/version.o $(objdir)/error.o -o $(sodir)/libql-system.so
	g++ -shared $(objdir)/audio.o $(objdir)/awav.o -o $(sodir)/libql-audio.so -lql-files -L$(sodir)
	touch $(objdir)/compiled
compile:
ifneq ("$(wildcard $(sodir))","")
	rm -rf $(objdir)
endif
	mkdir $(objdir)
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Pixmap/pixmap.cpp -o $(objdir)/pixmap.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Files/files.cpp -o $(objdir)/files.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Colorize/colors.cpp -o $(objdir)/colors.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Console/console.cpp -o $(objdir)/console.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Pixmap/IO/tiff.cpp -o $(objdir)/ptiff.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Pixmap/IO/bmp.cpp -o $(objdir)/pbmp.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Maths/maths.cpp -o $(objdir)/maths.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Video/video.cpp -o $(objdir)/video.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Video/IO/gif.cpp -o $(objdir)/vgif.o -I/usr/include/ffmpeg
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Video/IO/mkv.cpp -o $(objdir)/vmkv.o -I/usr/include/ffmpeg
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Video/IO/mp4.cpp -o $(objdir)/vmp4.o -I/usr/include/ffmpeg
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Video/IO/wmv.cpp -o $(objdir)/vwmv.o -I/usr/include/ffmpeg
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/System/system.cpp -o $(objdir)/system.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Time/units.cpp -o $(objdir)/time.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Windows/windows.cpp -o $(objdir)/windows.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Formats/bmp.cpp -o $(objdir)/fbmp.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Formats/wav.cpp -o $(objdir)/fwav.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Init/init.cpp -o $(objdir)/init.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Program/program.cpp -o $(objdir)/program.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Info/version.cpp -o $(objdir)/version.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Error/error.cpp -o $(objdir)/error.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Audio/audio.cpp -o $(objdir)/audio.o
	g++ $(g++_obj_flags) $(srcdir_ac_ql)/Audio/IO/wav.cpp -o $(objdir)/awav.o

directory:
ifneq  ("$(wildcard $(sodir))","")
	rm -rf $(sodir)
endif
	mkdir $(sodir)