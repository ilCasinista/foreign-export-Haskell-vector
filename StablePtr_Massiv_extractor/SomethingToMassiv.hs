module StablePtr_Massiv_extractor.SomethingToMassiv (somethingToVec) where

import qualified Data.Massiv.Array as Massiv
import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr


foreign export ccall "somethingToVec_double_hs" somethingToVec :: CInt -> IO (StablePtr (Massiv.Array Massiv.S Massiv.Ix1 CDouble))
foreign export ccall "somethingToVec_int_hs"    somethingToVec :: CInt -> IO (StablePtr (Massiv.Array Massiv.S Massiv.Ix1 CInt))


somethingToVec :: (Num a,Storable a) => CInt -> IO (StablePtr (Massiv.Array Massiv.S Massiv.Ix1 a))
somethingToVec = newStablePtr . Massiv.compute . Massiv.enumFromN Massiv.Seq 0 . fromIntegral
