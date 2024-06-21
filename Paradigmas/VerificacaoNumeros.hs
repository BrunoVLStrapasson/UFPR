-- VerificacaoNumeros.hs

module VerificacaoNumeros (
  ehPositivo,
  ehNegativo,
  ehZero,
  filtroNumeros
) where

ehPositivo :: Int -> Bool
ehPositivo x = x > 0

ehNegativo :: Int -> Bool
ehNegativo x = x < 0

ehZero :: Int -> Bool
ehZero x = x == 0

filtroNumeros :: (Int -> Bool) -> [Int] -> [Int]
filtroNumeros _ [] = []  -- Caso base: lista vazia, retorna lista vazia
filtroNumeros condicao (x:xs)
  | condicao x = x : filtroNumeros condicao xs
  | otherwise = filtroNumeros condicao xs