g++ tiggit.cpp dirfinder/dirfinder.cpp dialogs.cpp -o tiggit.exe -Wl,--subsystem,windows -I../wxWidgets/include -I../wxWidgets/lib/gcc_dll/mswu -I../curl-7.21.7/include -I../mingw-div/include/ -L../boost -lboost_filesystem -lboost_system -Ilibs/jsoncpp/include -I../zziplib -I../zlib libs/jsoncpp/src/json_reader.cpp libs/jsoncpp/src/json_value.cpp libs/jsoncpp/src/json_writer.cpp -L../zziplib/zzip -lzzip -L../zlib-1.2.5 -lz -L../curl-7.21.7/lib/.libs/ -lcurl wxbase28u_gcc_custom.dll wxmsw28u_core_gcc_custom.dll resources.res
