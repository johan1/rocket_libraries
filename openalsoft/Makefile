BUILD_ROOT := openal-soft-1.17.2/build

all: host windows

deploy: host windows
	./deploy.sh

$(BUILD_ROOT):
	bash ./fetch_sources.sh

host: $(BUILD_ROOT)/host/libopenal.dll

windows: $(BUILD_ROOT)/windows/libOpenAL32.dll

$(BUILD_ROOT)/host/libopenal.dll: $(BUILD_ROOT)
	mkdir -p $(BUILD_ROOT)/host;
	cd $(BUILD_ROOT)/host; cmake ../..; make openal

$(BUILD_ROOT)/windows/libOpenAL32.dll: $(BUILD_ROOT)
	mkdir -p $(BUILD_ROOT)/windows;
	cd $(BUILD_ROOT)/windows; cmake -DDSOUND_INCLUDE_DIR="/usr/share/mingw-w64/include" -DDSOUND_LIB="-ldsound" -DALSOFT_STATIC_LIBGCC=1 -DCMAKE_TOOLCHAIN_FILE=../../../Toolchain-mingw32.cmake ../..; make OpenAL32

clean:
	rm -fr openal-soft-1.17.2 openal-soft-1.17.2.tar.bz2
