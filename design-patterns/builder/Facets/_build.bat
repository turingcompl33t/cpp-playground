:: _build.bat

cl /c /EHsc /nologo /std:c++17 /W4 person.cpp
cl /c /EHsc /nologo /std:c++17 /W4 person_builder.cpp
cl /EHsc /nologo /std:c++17 /W4 facets.cpp /link person.obj person_builder.obj