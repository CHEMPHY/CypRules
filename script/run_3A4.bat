java -jar ../bin/PaDEL-Descriptor/PaDEL-Descriptor.jar -2d -retain3d -standardizenitro -removesalt -detectaromaticity -retainorder -dir ../workspace/input/ -file ../workspace/3a4.p2fp3.cc2.cases2 > ../workspace/log_PaDEL-Descriptor.txt
..\bin\Mold2.exe -i ..\workspace\input\input.sdf -o ..\workspace\3a4.m2.cc2.cases2 < nul
copy ..\program_example\3a4\3a4.p2m2fp3.cc2.names ..\workspace\3a4.p2m2fp3.cc2.names
..\bin\trim_3a4.exe ..\workspace\3a4.p2fp3.cc2.cases2 ..\workspace\3a4.m2.cc2.cases2 ..\workspace\3a4.p2m2fp3.cc2.cases
copy ..\program_example\3a4\3a4.p2m2fp3.cc2.rules ..\workspace\3a4.p2m2fp3.cc2.rules
..\bin\predict.exe -R -f ..\workspace\3a4.p2m2fp3.cc2 > ..\workspace\3a4.p2m2fp3.cc2.predict
..\bin\parse_3a4.exe ..\workspace\
copy ..\workspace\3a4.p2m2fp3.cc2.statistics ..\workspace\output\out.txt
..\bin\postProcessing.exe ..\workspace\output\out.txt ..\workspace\output\out2.txt