
INSERT INTO Autor (ID_Autor, Nome, Data_Nascimento) VALUES
(4, 'Isaac Asimov', '1920-01-02'),
(5, 'Arthur C. Clarke', '1917-12-16'),
(6, 'Frank Herbert', '1920-10-08'),
(7, 'Philip K. Dick', '1928-12-16'),
(8, 'William Gibson', '1948-03-17'),
(9, 'Ursula K. Le Guin', '1929-10-21'),
(10, 'Margaret Atwood', '1939-11-18'),
(11, 'Neil Gaiman', '1960-11-10'),
(12, 'Terry Pratchett', '1948-04-28'),
(13, 'Agatha Christie', '1890-09-15'),
(14, 'Stephen King', '1947-09-21'),
(15, 'H.P. Lovecraft', '1890-08-20'),
(16, 'George Orwell', '1903-06-25'),
(17, 'Aldous Huxley', '1894-07-26'),
(18, 'Mary Shelley', '1797-08-30');


INSERT INTO Categoria (ID_Categoria, Nome) VALUES
(4, 'Distopia'),
(5, 'Cyberpunk'),
(6, 'Alta Fantasia'),
(7, 'Fantasia Sombria'),
(8, 'Mistério'),
(9, 'Terror'),
(10, 'Horror Cósmico'),
(11, 'Romance Policial'),
(12, 'Sátira'),
(13, 'Ficção Filosófica'),
(14, 'Gótico'),
(15, 'Pós-apocalíptico'),
(16, 'Comédia'),
(17, 'Drama'),
(18, 'Não-ficção');


INSERT INTO Livro (ID_Livro, Titulo, ID_Autor, Ano_Publicacao) VALUES
(4, 'Fundação', 4, 1951),
(5, '2001: Uma Odisseia no Espaço', 5, 1968),
(6, 'Duna', 6, 1965),
(7, 'Androides Sonham com Ovelhas Elétricas?', 7, 1968),
(8, 'Neuromancer', 8, 1984),
(9, 'O Feiticeiro de Terramar', 9, 1968),
(10, 'O Conto da Aia', 10, 1985),
(11, 'Sandman', 11, 1989),
(12, 'Belas Maldições', 12, 1990),
(13, 'O Assassinato no Expresso do Oriente', 13, 1934),
(14, 'O Iluminado', 14, 1977),
(15, 'O Chamado de Cthulhu', 15, 1928),
(16, '1984', 16, 1949),
(17, 'Admirável Mundo Novo', 17, 1932),
(18, 'Frankenstein', 18, 1818);

-- Associação dos novos livros com suas categorias
INSERT INTO Livro_Categoria (ID_Livro, ID_Categoria) VALUES
(4, 2),
(5, 2),
(6, 2), (6, 3),
(7, 2), (7, 5),
(8, 2), (8, 5),
(9, 1), (9, 3), (9, 6),
(10, 2), (10, 4),
(11, 1), (11, 7),
(12, 1), (12, 16),
(13, 8), (13, 11),
(14, 9),
(15, 9), (15, 10),
(16, 2), (16, 4),
(17, 2), (17, 4),
(18, 2), (18, 9), (18, 14);

-- Inserção de 15 novos Usuários
INSERT INTO Usuario (ID_Usuario, Nome, Email) VALUES
(4, 'David', 'david@example.com'),
(5, 'Eve', 'eve@example.com'),
(6, 'Frank', 'frank@example.com'),
(7, 'Grace', 'grace@example.com'),
(8, 'Heidi', 'heidi@example.com'),
(9, 'Ivan', 'ivan@example.com'),
(10, 'Judy', 'judy@example.com'),
(11, 'Mallory', 'mallory@example.com'),
(12, 'Niaj', 'niaj@example.com'),
(13, 'Olivia', 'olivia@example.com'),
(14, 'Peggy', 'peggy@example.com'),
(15, 'Rupert', 'rupert@example.com'),
(16, 'Sybil', 'sybil@example.com'),
(17, 'Trent', 'trent@example.com'),
(18, 'Victor', 'victor@example.com');

-- Inserção de 15 novos Empréstimos
INSERT INTO Emprestimo (ID_Emprestimo, ID_Livro, ID_Usuario, Data_Emprestimo, Data_Devolucao) VALUES
(4, 4, 4, '2024-07-11', '2024-07-20'),
(5, 5, 5, '2024-07-12', '2024-07-22'),
(6, 6, 6, '2024-07-13', NULL),
(7, 7, 7, '2024-07-14', '2024-07-24'),
(8, 8, 8, '2024-07-15', NULL),
(9, 9, 9, '2024-07-16', '2024-07-26'),
(10, 10, 10, '2024-07-17', '2024-07-27'),
(11, 11, 11, '2024-07-18', NULL),
(12, 12, 12, '2024-07-19', '2024-07-29'),
(13, 13, 13, '2024-07-20', '2024-07-30'),
(14, 14, 14, '2024-07-21', NULL),
(15, 15, 15, '2024-07-22', '2024-08-01'),
(16, 16, 16, '2024-07-23', '2024-08-02'),
(17, 17, 17, '2024-07-24', NULL),
(18, 18, 18, '2024-07-25', '2024-08-04');