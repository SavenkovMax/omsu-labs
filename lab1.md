
```sql
create table people (
	person_id serial primary key,
	name varchar(50),
	last_name varchar(50),
	email varchar(50)
);

insert into people (name, last_name, email) values
('Denis', 'Sigitov', 'larlnevinovat@gmail.com'),
('Yaroslav', 'Naidenov', 'miposhka@gmail.com'),
('Illya', 'Mulyarchuk', 'raddan@gmail.com'),
('Myroslav', 'Kolpakov', 'mira@gmail.com'),
('Magomed', 'Khalilov', 'ogremaga@gmail.com');

select * from people;

select name, last_name from people;

update people
set email = 'newemail@gmail.com'
where name = 'Denis';

delete from people
where name like 'M%';

create table products (
	product_id bigserial primary key,
	name varchar(100),
	price numeric(10, 2) constraint positive_price CHECK (price > 0),
	available boolean
);

create table orders (
	order_id serial primary key,
	product_id bigint references products(product_id),
	count integer constraint not_empty_order CHECK (count > 0),
	order_date date not null
);

insert into products (name, price, available) values
('White bread', 40, true),
('Ketchup', 130, true),
('Gel pen', 35, false),
('Pencil', 10, true);

insert into orders (product_id, count, order_date) values
(1, 5, '2024-10-14'),
(4, 2, '2024-10-15'),
(2, 1, '2024-10-16');

select * from products
where price < 50;

select * from orders
where order_date > '2024-10-14';

update orders
set count = count + 10
where product_id = 1;

create table authors (
	author_id bigserial primary key, 
	initials varchar(50)
);

create table posts (
	post_id bigserial primary key,
	title varchar(255) not null,
	content text not null,
	author_id bigint references authors(author_id) on delete cascade
);

create table comments (
	comment_id serial primary key,
	content text not null,
	post_id bigint references posts(post_id) on delete cascade,
	author_id bigint references authors(author_id) on delete cascade
);

insert into authors (initials) values
('Ivanov I.I'),
('Petrov P.P'),
('Alexandrov A.A');

insert into posts (title, content, author_id) values
('Simple title', 'lorem ipsum text', 1),
('Another simple title', 'lorem ipsum text again', 2),
('Simple title again', 'I am tired of lorem ipsum text', 3);

insert into comments (content, post_id, author_id) values
('This is the finnest lorem ipsum text', 1, 2),
('Not this text again', 2, 1),
('Help me, i am tired of filling this text', 3, 1);

select * from posts
where author_id = 1;

select * from comments
where post_id = 3;

delete from authors
where author_id = 1;
```