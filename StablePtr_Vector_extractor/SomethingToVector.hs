module StablePtr_Vector_extractor.SomethingToVector (somethingToVec) where

import qualified Data.Vector.Storable as VS
import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr


foreign export ccall "somethingToVec_double_hs" somethingToVec :: CInt -> IO (StablePtr (VS.Vector CDouble))
foreign export ccall "somethingToVec_int_hs"    somethingToVec :: CInt -> IO (StablePtr (VS.Vector CInt))


somethingToVec :: (Num a,Storable a) => CInt -> IO (StablePtr (VS.Vector a))
somethingToVec = newStablePtr . VS.enumFromN 0 . fromIntegral
