module Tuplas where

-- contar a quantidade de pares e impares
contar :: [Int] -> (Int, Int)

contar [] = (0, 0)
contar (h:t)
    | mod h 2 == 0 = (pares + 1, impares)
    | otherwise = (pares, impares + 1)
        where
            (pares, impares) = contar t

contar2 :: [Int] -> (Int,Int)

contar2 [] = (0,0)
contar2 (h:t)
        | mod h 2 == 0 = (pares+1,impares)
        | otherwise = (pares,impares + 1)
            where
                (pares,impares) = contar2 t

gerarTupla :: Int -> (Int, Int, Int, Int)
gerarTupla x = (2 * x, 3 * x, 4 * x, 5 * x)

verificarParidade :: Int -> (Int, String)
verificarParidade n1 = (n1 `div` 2, if even n1 then "Par" else "Impar")

listaA = [x*3 | x <- [0..5]]



somaEProduto :: [Int] -> (Int, Int)
somaEProduto [] = (0, 1)  -- Caso base: lista vazia, retorna (0, 1)
somaEProduto (x:xs)
    | x > 0     = (somaPos + x, produtoNeg)  -- Se x for positivo, adiciona x à somaPos
    | x < 0     = (somaPos, produtoNeg * x)  -- Se x for negativo, multiplica x ao produtoNeg
    | otherwise = (somaPos, produtoNeg)  -- Se x for zero, não altera a tupla
        where
            (somaPos, produtoNeg) = somaEProduto xs  -- Chama recursivamente para o restante da lista


type Nome = String
type Avaliacao = Int
type Tipo = String
type PontoTuristico = (Nome, Avaliacao, Tipo)

pontosTuristicos :: Avaliacao -> [PontoTuristico] -> [PontoTuristico]
pontosTuristicos valorReferencia pontos =
    [(nome, avaliacao, tipo) | (nome, avaliacao, tipo) <- pontos, avaliacao > valorReferencia, tipo `elem` ["parque", "museu","rua"]]


type TuplaExemplo = (String, String, Char)

-- Função para obter o primeiro elemento da tupla (String)
primeiroElemento :: TuplaExemplo -> String
primeiroElemento (a, _, _) = a

-- Função para obter o segundo elemento da tupla (String)
segundoElemento :: TuplaExemplo -> String
segundoElemento (_, b, _) = b

-- Função para obter o terceiro elemento da tupla (Char)
terceiroElemento :: TuplaExemplo -> Char
terceiroElemento (_, _, c) = c

