em++ -std=c++11 -I C:\work\Hybrid\hybridapp\Hybrid\src\*.cpp C:\work\Hybrid\hybridapp\Hybrid\src\HybridInterface.h C:\work\Hybrid\hybridapp\JavaScript\make\Bridging.cpp C:\work\Hybrid\hybridapp\Hybrid\src\json11\json11.cpp C:\work\Hybrid\hybridapp\Hybrid\src\map\LayerManager.cpp -s RESERVED_FUNCTION_POINTERS=10 -s EXPORTED_FUNCTIONS="[ '_bridgingMainControllerStart', '_bridgingMainControllerStop', '_bridgingLoadCsvComplete', '_bridgingSerachLoadDataListRecord', '_bridginggetLoadDataDetail' ]" -s TOTAL_MEMORY=134217728 -s ALLOW_MEMORY_GROWTH=1 -o hybrid.js
