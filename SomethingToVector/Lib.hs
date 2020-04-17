module SomethingToVector.Lib (somethingToVec) where

import qualified Data.Vector.Storable as VS
import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr
import           StorableInstances


foreign export ccall "somethingToVec_hs" somethingToVec :: CInt -> IO (Ptr (VS.Vector CDouble))


somethingToVec :: CInt -> IO (Ptr (VS.Vector CDouble))
somethingToVec = new . VS.enumFromN 0 . fromIntegral


foreign export ccall "vector_free_hs" free :: Ptr (VS.Vector CDouble) -> IO ()
