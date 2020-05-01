module StablePtr_Vector_extractor.Lib (extractFromStablePtr_vector, free) where

import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr
import qualified Data.Vector.Storable as Vector (Vector,length,map,thaw,unsafeFromForeignPtr0,unsafeWith)


foreign export ccall "extractFromStablePtr_vector_double_hs" extractFromStablePtr_vector :: StablePtr (Vector.Vector CDouble) -> Ptr CInt -> Ptr (Ptr CDouble) -> IO ()
foreign export ccall "extractFromStablePtr_vector_int_hs"    extractFromStablePtr_vector :: StablePtr (Vector.Vector CInt)    -> Ptr CInt -> Ptr (Ptr CInt)    -> IO ()


foreign export ccall "vector_double_free_hs" freeStablePtr :: StablePtr (Vector.Vector CDouble) -> IO ()
foreign export ccall "vector_int_free_hs"    freeStablePtr :: StablePtr (Vector.Vector CInt)    -> IO ()


 --                                                                         |_________OUPUT_______|
extractFromStablePtr_vector :: Storable a => StablePtr (Vector.Vector a) -> Ptr CInt -> Ptr (Ptr a) -> IO ()
extractFromStablePtr_vector arrStablePtr   czPtr dstPtrPtr = do
  arr <- deRefStablePtr arrStablePtr
  poke czPtr (fromIntegral . Vector.length $ arr)
  Vector.unsafeWith arr $ poke dstPtrPtr
