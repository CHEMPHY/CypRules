java -jar ../bin/PaDEL-Descriptor/PaDEL-Descriptor.jar -2d -retain3d -standardizenitro -removesalt -detectaromaticity -retainorder -dir ../workspace/input/ -file ../workspace/2c19.p2fp3.cc.case2 > ../workspace/log_PaDEL-Descriptor.txt
../bin/Mold2.exe -i input.sdf -o 2c19.m2.cc.case2
copy ..\program_example\2C19\2c19.p2m2fp3.cc.names ..\workspace\2c19.p2m2fp3.cc.names
..\bin\trim_2c19.exe ..\workspace\2c19.p2fp3.cc.cases2 ..\workspace\2c19.m2.cc.cases2 ..\workspace\2c19.p2m2fp3.cc.cases
copy ..\program_example\2C19\2c19.p2m2fp3.cc.rules ..\workspace\2c19.p2m2fp3.cc.rules
..\bin\predict.exe -R -f ..\workspace\2c19.p2m2fp3.cc > ..\workspace\2c19.p2m2fp3.cc.predict
..\bin\parse_2c19.exe ..\workspace\
copy ..\workspace\2c19.p2m2fp3.cc.statistics ..\workspace\output\out.txt