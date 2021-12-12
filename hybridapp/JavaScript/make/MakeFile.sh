em++ -std=c++11 \
-I../../Hybrid/src \
Bridging.cpp \
../../Hybrid/src/*.cpp \
../../Hybrid/src/json11/*.cpp \
../../Hybrid/src/map/*.cpp \
-s RESERVED_FUNCTION_POINTERS=10 \
-s EXPORTED_FUNCTIONS="[ \
  '_bridgingMainControllerStart', \
  '_bridgingMainControllerStop', \
  '_bridgingLoadCsvComplete', \
  '_bridgingSerachLoadDataListRecord', \
  '_bridginggetLoadDataDetail', \
]" \
-s TOTAL_MEMORY=134217728 \
-s ALLOW_MEMORY_GROWTH=1 \
-o ../js/hybrid.js
