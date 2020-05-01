module StablePtr_Vector_extractor.SomethingToVector (somethingToVec) where

import qualified Data.Vector.Storable as VS
import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr


foreign export ccall "somethingToVec_hs" somethingToVec :: CInt -> IO (StablePtr (VS.Vector CDouble))


somethingToVec :: CInt -> IO (StablePtr (VS.Vector CDouble))
somethingToVec = newStablePtr . VS.enumFromN 0 . fromIntegral
