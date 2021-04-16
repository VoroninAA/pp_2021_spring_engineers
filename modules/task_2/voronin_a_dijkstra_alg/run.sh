NAME=$(pwd|tr / "\n"|tail |tail -1)_seq
cd ../../../build
cmake -D USE_SEQ=ON -D USE_OMP=ON -D USE_TBB=ON -D USE_STD=ON -D USE_LATEX=ON ..
cmake --build . --config RELEASE
cd bin/
ls -la
./$NAME