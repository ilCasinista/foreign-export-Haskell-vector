{-# LANGUAGE FlexibleInstances,TypeSynonymInstances #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module StorableInstances () where

import qualified Data.Vector.Storable as VS
import           Foreign
import           Foreign.C.Types
import           Foreign.ForeignPtr

#include "DoubleVector.h"
instance Storable a => Storable (VS.Vector a) where
  sizeOf    _ = #{size      C_DoubleVector}

  alignment _ = #{alignment C_DoubleVector}

  peek ptr = do
    doubleVectorSize <- (#{peek C_DoubleVector, c_doubleVectorSize} ptr)
    doubleVectorPtr  <- (#{peek C_DoubleVector, c_doubleVectorPtr}  ptr)
    fmap (VS.convert . flip VS.unsafeFromForeignPtr0 (intFromCInt doubleVectorSize)) (newForeignPtr_ doubleVectorPtr)

  poke ptr it = flip withForeignPtr poke_worker . fst . VS.unsafeToForeignPtr0 $ it
    where
    doubleVectorSize :: CInt
    doubleVectorSize = cIntFromInt . VS.length $ it

    poke_worker ptr_ = do
      (#{poke C_DoubleVector, c_doubleVectorSize}) ptr doubleVectorSize
      (#{poke C_DoubleVector, c_doubleVectorPtr }) ptr ptr_




cIntFromInt :: Int -> CInt
cIntFromInt = fromIntegral


intFromCInt :: CInt -> Int
intFromCInt = fromIntegral
