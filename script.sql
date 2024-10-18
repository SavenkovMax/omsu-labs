CREATE SCHEMA contacts;

CREATE TABLE contacts.people (
	id INT AUTO_INCREMENT PRIMARY KEY,
	first_name VARCHAR(50),
	last_name VARCHAR(50),
	email VARCHAR(50)
);

INSERT INTO contacts.people (first_name, last_name, email) VALUES
('Denis', 'Sigitov', 'larlnevinovat@gmail.com'),
('Yaroslav', 'Naidenov', 'miposhka@gmail.com'),
('Illya', 'Mulyarchuk', 'raddan@gmail.com'),
('Myroslav', 'Kolpakov', 'mira@gmail.com'),
('Magomed', 'Khalilov', 'ogremaga@gmail.com');

SELECT * FROM contacts.people;

SELECT first_name, last_name FROM contacts.people;

UPDATE contacts.people
SET email = 'horntosstaxi@gmail.com'
WHERE first_name = 'Magomed';

DELETE FROM contacts.people
WHERE first_name = 'Illya';

CREATE SCHEMA shop;

CREATE TABLE shop.products (
	id INT AUTO_INCREMENT PRIMARY KEY,
    name TEXT,
    price INT UNSIGNED,
    available BOOLEAN
);

CREATE TABLE shop.orders (
	id INT AUTO_INCREMENT PRIMARY KEY,
    product_id INT REFERENCES shop.products(id),
    quantity INT UNSIGNED,
    order_date DATE
);

INSERT INTO shop.products (name, price, available) VALUES 
('White bread', 40, true),
('Ketchup', 130, true),
('Gel pen', 35, false),
('Pencil', 10, true);

INSERT INTO shop.orders (product_id, quantity, order_date) VALUES
(1, 5, '2024-10-14'),
(4, 2, '2024-10-15'),
(2, 1, '2024-10-16');

SELECT * FROM shop.products
WHERE price < 50;

SELECT * FROM shop.orders
WHERE order_date > '2024-10-14';

UPDATE shop.orders
SET quantity = 10
WHERE product_id = 1;


CREATE SCHEMA blog;

CREATE TABLE blog.authors (
	id INT AUTO_INCREMENT PRIMARY KEY,
    first_name VARCHAR(55),
    last_name VARCHAR(55)
);

CREATE TABLE blog.posts (
	id INT AUTO_INCREMENT PRIMARY KEY,
    header VARCHAR(128),
    text TEXT,
    author_id INT REFERENCES blog.authors(id) ON DELETE CASCADE
);

CREATE TABLE blog.comments (
	id INT AUTO_INCREMENT PRIMARY KEY,
    text TEXT,
    post_id INT REFERENCES blog.posts(id) ON DELETE CASCADE,
    author_id INT REFERENCES blog.authors(id) ON DELETE CASCADE
);

INSERT INTO blog.authors (first_name, last_name) VALUES
('Elon', 'Musk'),
('Jeff', 'Bezos'),
('Mark', 'Zuckerberg');

INSERT INTO blog.posts (header, text, author_id) VALUES
('Elon Musk''s SpaceX launches Starship rocket and catches booster in astonishing test flight', 'SpaceX has pulled off its boldest text
flight yet of the enormous Starship rocket, catching the returning booster.', 1),
('PS5 Pro is coming in Amazon', 'PS5 Pro will go on sale Amazon in a week', 2),
('Mark Zuckerberg on X', 'Twitter, now X, is less likely to maximize its potential now with Elon Musk behind the wheel', 3);

INSERT INTO blog.comments (text, post_id, author_id) VALUES
('You''re genius!', 1, 2),
('I would rather buy xbox series X', 2, 1),
('I don''t care', 3, 1);

SELECT * FROM blog.posts
WHERE author_id = 1;

SELECT * FROM blog.comments
WHERE post_id = 3;

DELETE FROM blog.authors
WHERE id = 1;