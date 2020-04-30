module StablePtr_Vector_extractor.Lib (extractStablePtr_vector, free) where

import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr
import           StorableInstances
import qualified Data.Vector.Storable as Vector (Vector,length,map,thaw,unsafeFromForeignPtr0,unsafeWith)



foreign export ccall "extractStablePtr_vector_hs" extractStablePtr_vector :: StablePtr (Vector.Vector CDouble) -> Ptr CInt -> Ptr (Ptr CDouble) -> IO ()

foreign export ccall "vector_free_hs" freeStablePtr :: StablePtr (Vector.Vector CDouble) -> IO ()


 --                                                             |____________OUPUT__________|
extractStablePtr_vector :: StablePtr (Vector.Vector CDouble) -> Ptr CInt -> Ptr (Ptr CDouble) -> IO ()
extractStablePtr_vector arrStablePtr   czPtr dstPtrPtr = do
  arr <- deRefStablePtr arrStablePtr
  poke czPtr (fromIntegral . Vector.length $ arr)
  Vector.unsafeWith arr $ poke dstPtrPtr
