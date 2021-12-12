g++ -c *.cpp
g++ -shared -o MainController.dll BaseClass.o BaseController.o BaseModel.o DebugLogger.o MainController.o MainModel.o
g++ -o UnitTest.exe UnitTest.cpp -L. MainController.dll
