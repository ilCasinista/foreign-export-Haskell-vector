# DO NOT USE THIS CODE - IT IS FAULTY

## How to pass vectors in and out with foreign export from C to Haskell (main in C).

Hello, I found enough information for "foreign import" in Haskell but not much on the "foreign export". 

I'm stuck with passing in and out vectors (of Data.Vector.Storable package) in foreign exported functions. Here I assume the main is in C, not Haskell (H from now on). I was using code like this (here is the full code):

  foreign export ccall function :: Ptr (Array.Vector CInt) -> IO (Ptr (Array.Vector CDouble))

  function :: Ptr (Array.Vector CInt) -> IO (Ptr (Array.Vector CDouble))
  function = (new . function_worker =<<) . peek
    where -- DO NOT ASSUME INPUT AND OUTPUT VECTORS HAVE THE SAME SIZE
    function_worker :: Array.Vector CInt -> Array.Vector CDouble
    function_worker = Array.Vector.map fromIntegral

with

  instance Storable a => Storable (Array.Vector a) 

defined via Storable (CInt,Ptr a) using Vector.unsafeFromForeignPtr0 for peek and Vector.unsafeToForeignPtr0 for poke, where CInt represents the size of the vector (number of elements).


It turned out there was occasional memory corruption. When memory corruption does not show, everything works correctly.


I have been suggested that H GC could mess up memory when control is returned back to C and to look into StablePtr.
StablePtr are not affected by H GC but also are opaque for C so I can pass them back to H from C, but I cannot use them in C.


On second thoughts, there might be 4 cases to be considered.

Case 1: The C-main pass an array to a H function. The H-function imports it as a vector, and returns something (not a vector).

Case 2,3,4: The C-main pass something to a H function. The H-function imports it and returns a vector. Then,
  Case 2: C-main does something with it.
  Case 3: C-main does something with it without altering that vector and pass it to another H function.
  Case 4: C-main does something with it         altering that vector and pass it to another H function.


I think what I did so far is OK only for case 1. And at the moment I am not even considering efficiency.

Any help is appreciated. Thanks in advance.



### This is OK.

$ stack build --exec "main_VectorToSomething 10"
input Vec:  C_DoubleVector(size=10,[0.000000,1.000000,2.000000,3.000000,4.000000,5.000000,6.000000,7.000000,8.000000,9.000000,END])
sum:        45.000000




### I think this can give memory corruption (occasionally on my machine).

$ stack build --exec "main_SomethingToVector 10"
output Vec: C_DoubleVector(size=10,[0.000000,1.000000,2.000000,3.000000,4.000000,5.000000,6.000000,7.000000,8.000000,9.000000,END])



### This can give memory corruption (always on my machine).

$ stack build --exec "main_VectorToVector 100000"
input Vec:  C_DoubleVector(size=10,[0.000000,1.000000,2.000000,3.000000,4.000000,[OMITTED],END])
twice:      C_DoubleVector(size=10,[0.000000,2.000000,4.000000,6.000000,8.000000,[OMITTED],END])
four times: C_DoubleVector(size=10,[0.000000,4.000000,8.000000,12.000000,16.000000,[OMITTED],0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,END]) (???)
