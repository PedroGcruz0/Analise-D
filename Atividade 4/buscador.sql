
-- Listar todos os livros com seus autores:
SELECT
    a.Nome AS Autor,
    l.Titulo AS Livro
FROM Livro AS l
INNER JOIN Autor AS a ON l.ID_Autor = a.ID_Autor;

-- Listar todos os empréstimos e os usuários correspondentes:
SELECT
    e.ID_Emprestimo,
    u.Nome AS Usuario
FROM Emprestimo AS e
INNER JOIN Usuario AS u ON e.ID_Usuario = u.ID_Usuario;

-- Listar todos os livros e suas categorias:
SELECT
    l.Titulo,
    c.Nome AS Categoria
FROM Livro AS l
INNER JOIN Livro_Categoria AS lc ON l.ID_Livro = lc.ID_Livro
INNER JOIN Categoria AS c ON lc.ID_Categoria = c.ID_Categoria
ORDER BY l.Titulo;

-- Listar todos os livros atualmente emprestados com o nome do usuário:
SELECT
    l.Titulo,
    u.Nome AS Usuario
FROM Emprestimo AS e
INNER JOIN Livro AS l ON e.ID_Livro = l.ID_Livro
INNER JOIN Usuario AS u ON e.ID_Usuario = u.ID_Usuario
WHERE e.Data_Devolucao IS NULL;

-- Listar todos os autores e seus livros publicados (semelhante à primeira, mas com foco no autor):
SELECT
    a.Nome AS Autor,
    l.Titulo
FROM Autor AS a
INNER JOIN Livro AS l ON a.ID_Autor = l.ID_Autor
ORDER BY a.Nome;


-- 3 Novas Buscas

-- 1. Listar todos os usuários que pegaram livros da categoria 'Fantasia' emprestado:
SELECT DISTINCT
    u.Nome AS Usuario
FROM Usuario AS u
INNER JOIN Emprestimo AS e ON u.ID_Usuario = e.ID_Usuario
INNER JOIN Livro_Categoria AS lc ON e.ID_Livro = lc.ID_Livro
INNER JOIN Categoria AS c ON lc.ID_Categoria = c.ID_Categoria
WHERE c.Nome = 'Fantasia';

-- 2. Contar quantos livros cada autor tem na biblioteca:
SELECT
    a.Nome AS Autor,
    COUNT(l.ID_Livro) AS Quantidade_Livros
FROM Autor AS a
LEFT JOIN Livro AS l ON a.ID_Autor = l.ID_Autor
GROUP BY a.Nome
ORDER BY Quantidade_Livros DESC;

-- 3. Listar os 5 livros mais emprestados:
SELECT
    l.Titulo,
    COUNT(e.ID_Emprestimo) AS Vezes_Emprestado
FROM Livro AS l
INNER JOIN Emprestimo AS e ON l.ID_Livro = e.ID_Livro
GROUP BY l.Titulo
ORDER BY Vezes_Emprestado DESC
LIMIT 5;