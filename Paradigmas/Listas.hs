module Listas where
    
    cubo :: Int->Int
    cubo x = x*x*x

    aoCubo :: [Int]->[Int]
    aoCubo [] = []
    aoCubo (h:t) = cubo h : aoCubo t
    
    par :: Int -> Bool
    par x = (mod x 2 == 0)

    impar :: Int -> Bool
    impar x = (mod x 2 == 1)
    -- Função de Alta Ordem
    filtro :: (Int -> Bool) -> [Int] -> [Int]
    filtro _ [] = []
    filtro f (h:t) 
            | (f h) == True = h : (filtro f t)
            | otherwise = filtro f t

    somaInt :: [Int] -> Int
    somaInt [] = 0
    somaInt (h:t) = h + somaInt t

    remPar :: [Int] -> [Int]
    remPar [] = []
    remPar (h:t) 
        | mod h 2 == 0 = remPar t
        | otherwise = h : remPar t
    
    invertLista :: [Integer] -> [Integer]
    invertLista [] = []  -- Caso base: lista vazia, retorna lista vazia
    invertLista (x:xs) = invertLista xs ++ [x]  -- Inverte a cauda da lista e coloca o elemento atual no final

    nomesComA :: [String] -> [String]
    nomesComA [] = []  -- Caso base: lista vazia, retorna lista vazia
    nomesComA (nome:resto)
        | head nome == 'A' = nome : nomesComA resto  -- Se o nome começa com 'A', inclui na lista resultante
        | otherwise = nomesComA resto  -- Caso contrário, ignora o nome e continua com o restante da lista

    ehPrimo :: Integer -> Bool
    ehPrimo n = divisores == [1,n]
        where
            divisores = [x | x <- [1..n], mod n x == 0]

    listaA = [x*3 | x <- [0..5]]

    listaB = [[x] | x<- [1..5]]


    type NomeAluno = String
    type MediaNota = Integer
    type Aluno = (NomeAluno, MediaNota)
    type Turma = [Aluno]

    aprovados :: Turma -> Integer -> [NomeAluno]
    aprovados tma nota = [nome | (nome, media) <- tma, media >= nota]

    turma = [("Joao", 8), ("Pedro", 6), ("Maria" , 9), ("Bia", 5)]

