module StablePtr_Massiv.Lib (twiceVec, free) where

import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr
import           StorableInstances
import qualified Data.Massiv.Array        as Massiv
import qualified Data.Massiv.Array.Unsafe as Massiv


foreign export ccall "twiceVec_hs" twiceVec :: CInt -> Ptr CDouble -> Ptr CInt -> Ptr (Ptr CDouble) -> IO (StablePtr (Massiv.Array Massiv.S Massiv.Ix1 CDouble))

foreign export ccall "massiv_free_hs" freeStablePtr :: StablePtr (Massiv.Array Massiv.S Massiv.Ix1 CDouble) -> IO ()


 --                                |____________OUPUT__________|
twiceVec :: CInt -> Ptr CDouble -> Ptr CInt -> Ptr (Ptr CDouble) -> IO (StablePtr (Massiv.Array Massiv.S Massiv.Ix1 CDouble))
twiceVec csz srcPtr   czPtr dstPtrPtr = do
  srcArr <- flip (Massiv.unsafeArrayFromForeignPtr0 Massiv.Par) (Massiv.Sz $ fromIntegral csz) <$> newForeignPtr_ srcPtr
  dstArr <- Massiv.computeIO (Massiv.map (*2) srcArr)

  poke czPtr (fromIntegral . Massiv.unSz . Massiv.size $ dstArr)
  Massiv.unsafeWithPtr dstArr $ poke dstPtrPtr
  newStablePtr dstArr
