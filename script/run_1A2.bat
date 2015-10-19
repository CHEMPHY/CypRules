java -jar ../bin/PaDEL-Descriptor/PaDEL-Descriptor.jar -2d -retain3d -standardizenitro -removesalt -detectaromaticity -retainorder -dir ../workspace/input/ -file ../workspace/1a2.p2.cc.cases2 > ../workspace/log_PaDEL-Descriptor.txt
copy ..\program_example\1A2\1a2.p2.cc.names ..\workspace\1a2.p2.cc.names
..\bin\trim_1a2.exe ..\workspace\1a2.p2.cc.cases2 ..\workspace\1a2.p2.cc.cases
copy ..\program_example\1A2\1a2.p2.cc.rules ..\workspace\1a2.p2.cc.rules
..\bin\predict.exe -R -f ..\workspace\1a2.p2.cc > ..\workspace\1a2.p2.cc.predict
..\bin\parse_1a2.exe ..\workspace