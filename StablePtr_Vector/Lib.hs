module StablePtr_Vector.Lib (twiceVec, free) where

import           Foreign
import           Foreign.C.Types
import           Foreign.StablePtr
import           StorableInstances
import qualified Data.Vector.Storable as Vector (Vector,length,map,thaw,unsafeFromForeignPtr0,unsafeWith)



foreign export ccall "twiceVec_hs" twiceVec :: CInt -> Ptr CDouble -> Ptr CInt -> Ptr (Ptr CDouble) -> IO (StablePtr (Vector.Vector CDouble))

foreign export ccall "massiv_free_hs" freeStablePtr :: StablePtr (Vector.Vector CDouble) -> IO ()


 --                                |____________OUPUT__________|
twiceVec :: CInt -> Ptr CDouble -> Ptr CInt -> Ptr (Ptr CDouble) -> IO (StablePtr (Vector.Vector CDouble))
twiceVec csz srcPtr   czPtr dstPtrPtr = do
  srcArr <- flip Vector.unsafeFromForeignPtr0 (fromIntegral csz) <$> newForeignPtr_ srcPtr
  let dstArr = (Vector.map (*2) srcArr)

  poke czPtr (fromIntegral . Vector.length $ dstArr)
  Vector.unsafeWith dstArr $ poke dstPtrPtr
  newStablePtr dstArr
