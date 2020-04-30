module VectorToVector_FAULTY.Lib (twiceVec, free) where

import qualified Data.Vector.Storable as VS
import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr
import           StorableInstances


foreign export ccall "twiceVec_hs" twiceVec :: Ptr (VS.Vector CDouble) -> IO (Ptr (VS.Vector CDouble))

-- This is just a toy -- DO NOT ASSUME THE OUTPUT VECTOR HAS THE SAME SIZE AS THE INPUT VECTOR
twiceVec :: Ptr (VS.Vector CDouble) -> IO (Ptr (VS.Vector CDouble))
twiceVec cDoubleVectorPtr = new . VS.map (2*) =<< peek cDoubleVectorPtr


foreign export ccall "vector_free_hs" free :: Ptr (VS.Vector CDouble) -> IO ()
