{-# LANGUAGE FlexibleInstances,TypeSynonymInstances #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module StorableInstances_Massiv () where

import qualified Data.Massiv.Array as Massiv
import qualified Data.Massiv.Array.Unsafe as Massiv
import           Foreign
import           Foreign.C.Types
import           Foreign.ForeignPtr

#include "DoubleVector.h"
instance Storable a => Storable (Massiv.Array Massiv.S Massiv.Ix1 a) where
  sizeOf    _ = #{size      C_DoubleVector}

  alignment _ = #{alignment C_DoubleVector}
  -- Note that peek is needed when, with C-main, an array is defined in C and then passed to H.
  peek ptr = do
    doubleVectorSize <- (#{peek C_DoubleVector, c_doubleVectorSize} ptr)
    doubleVectorPtr  <- (#{peek C_DoubleVector, c_doubleVectorPtr}  ptr)
    fmap (Massiv.convert . flip (Massiv.unsafeArrayFromForeignPtr0 Massiv.Seq) (Massiv.Sz $ intFromCInt doubleVectorSize)) (newForeignPtr_ doubleVectorPtr)
  -- Note that poke is NOT used when, with C-main, an array is defined in H and then passed to C. Use the extractor instead. Should I just remove the definition of poke?
  poke ptr it = flip withForeignPtr poke_worker . fst . Massiv.unsafeArrayToForeignPtr $ it
    where
    doubleVectorSize :: CInt
    doubleVectorSize = cIntFromInt . Massiv.unSz . Massiv.size $ it

    poke_worker ptr_ = do
      (#{poke C_DoubleVector, c_doubleVectorSize}) ptr doubleVectorSize
      (#{poke C_DoubleVector, c_doubleVectorPtr }) ptr ptr_




cIntFromInt :: Int -> CInt
cIntFromInt = fromIntegral


intFromCInt :: CInt -> Int
intFromCInt = fromIntegral
