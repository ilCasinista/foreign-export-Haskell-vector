module StablePtr_Massiv_extractor.Lib (fromStablePtr_massiv, free) where

import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr
import qualified Data.Massiv.Array        as Massiv
import qualified Data.Massiv.Array.Unsafe as Massiv


foreign export ccall "fromStablePtr_massiv_double_hs" fromStablePtr_massiv :: StablePtr (Massiv.Array Massiv.S Massiv.Ix1 CDouble) -> Ptr CInt -> Ptr (Ptr CDouble) -> IO ()
foreign export ccall "fromStablePtr_massiv_int_hs"    fromStablePtr_massiv :: StablePtr (Massiv.Array Massiv.S Massiv.Ix1 CInt)    -> Ptr CInt -> Ptr (Ptr CInt)    -> IO ()


foreign export ccall "massiv_double_free_hs" freeStablePtr :: StablePtr (Massiv.Array Massiv.S Massiv.Ix1 CDouble) -> IO ()
foreign export ccall "massiv_int_free_hs"    freeStablePtr :: StablePtr (Massiv.Array Massiv.S Massiv.Ix1 CInt)    -> IO ()


 --                                                                  |_________OUPUT_______|
fromStablePtr_massiv :: Storable a => StablePtr (Massiv.Array Massiv.S Massiv.Ix1 a) -> Ptr CInt -> Ptr (Ptr a) -> IO ()
fromStablePtr_massiv arrStablePtr   czPtr dstPtrPtr = do
  arr <- deRefStablePtr arrStablePtr
  poke czPtr (fromIntegral . Massiv.unSz . Massiv.size $ arr)
  Massiv.unsafeWithPtr arr $ poke dstPtrPtr
