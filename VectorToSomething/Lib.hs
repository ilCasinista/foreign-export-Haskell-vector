module VectorToSomething.Lib (vecToSomething) where

import qualified Data.Vector.Storable as VS
import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr
import           StorableInstances


foreign export ccall "vecToSomething_hs" vecToSomething :: Ptr (VS.Vector CDouble) -> IO CDouble


vecToSomething :: Ptr (VS.Vector CDouble) -> IO CDouble
vecToSomething = fmap VS.sum . peek
