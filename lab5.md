
```sql 

create table products (
	product_id bigserial primary key,
	name varchar(255) not null unique,
	category varchar(55) not null,
	price numeric(10, 2) not null check (price > 0),
	date_added timestamp not null default now()
);

create table orders (
	order_id bigserial primary key,
	product_id bigint references products(product_id) on delete cascade,
	quantity int not null check (quantity > 0),
	order_date timestamp not null default now(),
	status varchar(20) not null check (status in ('active', 'completed','canceled'))
);

create index idx_category on products (category);
create index idx_order_date on orders (order_date);

insert into products (name, category, price, date_added) values 
('Apple', 'Fruits', 2.00, '2024-01-01'), 
('Banana', 'Fruits', 1.50, '2024-01-02'), 
('Orange', 'Fruits', 1.50, '2024-01-03'),
('Lemon', 'Fruits', 1.10, '2024-11-14'),
('Carrot', 'Vegetables', 1.00, '2024-01-04'), 
('Potato', 'Vegetables', 0.50, '2024-01-05'),
('Peach', 'Fruits', 0.99, '2024-12-15'),
('Cucumber', 'Vegetables', 0.65, '2023-12-29'),
('Tomato', 'Vegetables', 2.00, '2024-01-06'), 
('Milk', 'Dairy', 1.20, '2024-01-07'), 
('Cheese', 'Dairy', 3.50, '2024-01-08'), 
('Yogurt', 'Dairy', 1.00, '2024-01-09');

insert into orders (product_id, quantity, order_date, status) values 
(1, 30, '2023-01-15', 'completed'), 
(1, 25, '2023-03-20', 'canceled'), 
(2, 50, '2023-02-05', 'completed'), 
(3, 60, '2023-04-10', 'completed'),
(3, 15, '2023-04-15', 'canceled'),
(4, 15, '2023-03-25', 'completed'), 
(5, 5, '2023-05-15', 'canceled'), 
(6, 100, '2023-06-05', 'completed'),
(6, 32, '2023-06-06', 'canceled'),
(7, 20, '2023-07-10', 'completed'), 
(8, 50, '2023-08-15', 'completed'), 
(9, 12, '2023-09-20', 'canceled');

// 1 Выведите список продуктов с ценой выше средней цены по всем продуктам в
каждой категории, отсортировав по убыванию цены.

select products.category, name, price from products join (select category, avg(price) as average_price from products group by category) average_prices on products.category = average_prices.category where products.price > average_prices.average_price order by products.category, products.price desc;

// 2 Покажите продукты с наименьшей и наибольшей ценой в каждой категории.

select category, min(price) as min_price, max(price) as max_price from products group by category;

// 3 Отобразите продукты, которые еще не были заказаны, и отсортируйте их по
дате добавления в порядке убывания.

select name, category, price, date_added from products left join orders on products.product_id = orders.product_id where orders.product_id is null order by date_added desc;

// 4 Выведите продукты с ценой, превышающей среднюю цену всех заказов за
2023 год для завершенных заказов.

select name, category, price, date_added from products join orders on products.product_id = orders.product_id where orders.status = 'completed' and extract(year from orders.order_date) = 2023 group by products.product_id, name, price having price > (select avg(price) from orders;

// 5 Покажите продукты с общим количеством завершенных заказов более 50, с
разбивкой по категориям

select category, name, sum(quantity) as total_quanity from products join orders on products.product_id = orders.product_id where orders.status = 'completed' group by category, name having sum(quantity) > 50 order by category, sum(quantity) desc;

// 6 Найдите продукты, у которых был хотя бы один заказ с количеством более 10
единиц.

select name, category, quantity from products join orders on products.product_id = orders.product_id where quantity > 10;

// 7 Выведите продукты, которые были заказаны в каждом месяце 2023 года, с
указанием количества заказов в каждом месяце.

with monthly_ordered as (select p.product_id, p.name, extract(month from o.order_date) as month, count(o.order_id) as order_count from products p join orders o on p.product_id = o.product_id where extract(year from o.order_date) = 2023 group by p.product_id, p.name, extract(month from o.order_date)), product_months as (select product_id, name, count(distinct month) as months_ordered from monthly_ordered group by product_id, name having count(distinct month) = 12) select pm.name, mo.month, mo.order_count from product_months pm join monthly_ordered mo on pm.product_id = mo.product_id order by pm.name, mo.month;

// 8 Покажите продукты, цена которых выше среднего по всем продуктам в
таблице, но ни разу не были заказаны в статусе "отменен".

select name, category, price from products left join orders on products.product_id = orders.product_id and orders.status = 'canceled' where price > (select avg(price) from products) and orders.order_id is null;

// 9 Найдите продукты, по которым были заказы как со статусом "завершен", так
и "отменен", и покажите их вместе с датами заказов.

select distinct p.name, o1.order_date from products p join orders o1 on p.product_id = o1.product_id and o1.status = 'completed' join orders o2 on p.product_id = o2.product_id and o2.status = 'canceled';

// 10 Определите продукты с наибольшим количеством заказов за каждый год и
месяц, с указанием количества заказанных единиц.

select extract(year from order_date) as year, extract(month from order_date) as month, name, sum(quantity) as total_quantity from products join orders on products.product_id = orders.product_id group by year, month, name order by year, month, total_quantity desc;


```