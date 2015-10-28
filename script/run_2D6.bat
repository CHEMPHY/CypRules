java -jar ../bin/PaDEL-Descriptor/PaDEL-Descriptor.jar -2d -retain3d -standardizenitro -removesalt -detectaromaticity -retainorder -dir ../workspace/input/ -file ../workspace/2d6.f.cc2.cases2 > ../workspace/log_PaDEL-Descriptor.txt
copy ..\program_example\2d6\2d6.f.cc2.names ..\workspace\2d6.f.cc2.names
..\bin\trim_2d6.exe ..\workspace\2d6.f.cc2.cases2 ..\workspace\2d6.f.cc2.cases
copy ..\program_example\2d6\2d6.f.cc2.rules ..\workspace\2d6.f.cc2.rules
..\bin\predict.exe -R -f ..\workspace\2d6.f.cc2 > ..\workspace\2d6.f.cc2.predict
..\bin\parse_2d6.exe ..\workspace\
copy ..\workspace\2d6.f.cc2.statistics ..\workspace\output\out.txt
..\bin\postProcessing.exe ..\workspace\output\out.txt ..\workspace\output\out2.txt