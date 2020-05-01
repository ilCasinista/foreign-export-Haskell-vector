module StablePtr_Vector_extractor.Lib (fromStablePtr_vector, free) where

import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr
import qualified Data.Vector.Storable as Vector (Vector,length,map,thaw,unsafeFromForeignPtr0,unsafeWith)


foreign export ccall "fromStablePtr_vector_double_hs" fromStablePtr_vector :: StablePtr (Vector.Vector CDouble) -> Ptr CInt -> Ptr (Ptr CDouble) -> IO ()
foreign export ccall "fromStablePtr_vector_int_hs"    fromStablePtr_vector :: StablePtr (Vector.Vector CInt)    -> Ptr CInt -> Ptr (Ptr CInt)    -> IO ()


foreign export ccall "vector_double_free_hs" freeStablePtr :: StablePtr (Vector.Vector CDouble) -> IO ()
foreign export ccall "vector_int_free_hs"    freeStablePtr :: StablePtr (Vector.Vector CInt)    -> IO ()


 --                                                                  |_________OUPUT_______|
fromStablePtr_vector :: Storable a => StablePtr (Vector.Vector a) -> Ptr CInt -> Ptr (Ptr a) -> IO ()
fromStablePtr_vector arrStablePtr   czPtr dstPtrPtr = do
  arr <- deRefStablePtr arrStablePtr
  poke czPtr (fromIntegral . Vector.length $ arr)
  Vector.unsafeWith arr $ poke dstPtrPtr
