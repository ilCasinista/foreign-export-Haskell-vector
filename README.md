# DO NOT USE THIS CODE - IT IS FAULTY

## This is OK.

$ stack run main_VectorToSomething 10
input Vec:  C_DoubleVector(size=10,[0.000000,1.000000,2.000000,3.000000,4.000000,5.000000,6.000000,7.000000,8.000000,9.000000,END])
sum:        45.000000




## This can give memory corruption.

$ stack run main_SomethingToVector 10
output Vec: C_DoubleVector(size=10,[0.000000,1.000000,2.000000,3.000000,4.000000,5.000000,6.000000,7.000000,8.000000,9.000000,END])
