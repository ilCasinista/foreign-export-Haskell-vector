# DO NOT USE THIS CODE - IT IS FAULTY

## This is OK.

$ stack build --exec "main_VectorToSomething 10"
input Vec:  C_DoubleVector(size=10,[0.000000,1.000000,2.000000,3.000000,4.000000,5.000000,6.000000,7.000000,8.000000,9.000000,END])
sum:        45.000000




## I think this can give memory corruption (occasionally on my machine).

$ stack build --exec "main_SomethingToVector 10"
output Vec: C_DoubleVector(size=10,[0.000000,1.000000,2.000000,3.000000,4.000000,5.000000,6.000000,7.000000,8.000000,9.000000,END])



## This can give memory corruption (always on my machine).

$ stack build --exec "main_VectorToVector 100000"
input Vec:  C_DoubleVector(size=10,[0.000000,1.000000,2.000000,3.000000,4.000000,[OMITTED],END])
twice:      C_DoubleVector(size=10,[0.000000,2.000000,4.000000,6.000000,8.000000,[OMITTED],END])
four times: C_DoubleVector(size=10,[0.000000,4.000000,8.000000,12.000000,16.000000,[OMITTED],0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,END]) (???)
