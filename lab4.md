
```sql

create table users (
	user_id bigserial primary key,
	name varchar(30) not null,
	email varchar(255) unique,
	phone varchar(20) unique,
	registration_date timestamp default now(),
	check (char_length(name) > 0),
	check (email ~* '.+@.+\..+'),
	check (phone ~ '^(\+)?((\d{2,3}) ?\d|\d)(([ -]?\d)|( ?(\d{2,3}) ?)){5,12}\d$'),
	check (registration_date <= now())
);

create table orders (
	order_id bigserial primary key,
	user_id bigint references users(user_id) on delete cascade,
	amount numeric(12, 2) not null,
	order_date timestamp default now() not null,
	status text default 'active' not null,
	constraint positive_amount CHECK (amount > 0),
	check (order_date <= now()),
	check (status in ('active', 'completed', 'canceled'))
);

create index idx_user_email on users (email);
create index idx_order_date on orders (order_date);

insert into users (name, email, phone, registration_date) values
('Saul', 'drivesdale6@microsoft.com', '+420 399 103 2083', '2024-05-02 13:50:21'),
('Nikolia', 'nstate9@psu.edu', '+63 639 139 2267', '2024-06-09 17:55:32'),
('Martyn', 'mklezmskit@usnews.com', '+375 565 733 4965', '2024-04-23 08:11:23'),
('Darrel', 'dspilsted63@drupal.org', '+55 675 207 1744', '2024-08-02 10:32:45'),
('Dan', 'djikovsky5y@cbslocal.com', '+86 324 494 2014', '2024-04-30 12:15:43'),
('Clyve', 'cdummett67@goo.ne.jp', '+230 267 396 3055', '2024-05-14 20:21:34'),
('Cristina', 'celoi53@weibo.com', '+46 285 503 4651', '2024-06-17 09:53:21'),
('Javier', 'jguyther6a@twitter.com', '+212 846 723 9602', '2024-08-17 16:40:59'),
('Wynn', 'wcobbe1g@msn.com', '+7 166 181 2750', '2022-05-12 19:53:52'),
('Ethan', 'edingley1i@cbsnews.com', '+1 646 217 6170', '2023-09-12 10:35:12'),
('Bartholomew', 'bharsthorn1o@chron.com', '+62 209 430 1776', '2023-10-05 03:53:12');

insert into orders (user_id, amount, order_date, status) values
(1, 1099.99, '2024-05-10 20:24:56', 'active'),
(1, 525.50, '2024-05-09 09:55:15', 'completed'),
(1, 256.99, '2024-05-10 07:35:21', 'completed'),
(1, 2153.99, '2024-05-08 18:05:10', 'canceled'),
(4, 999.99, '2024-08-03 06:25:24', 'canceled'),
(5, 25000.00, '2024-05-15 22:05:15', 'completed'),
(5, 1599.00, '2024-05-16 11:08:12', 'completed'),
(6, 638.50, '2024-05-15 15:50:34', 'active'),
(7, 2345.99, '2024-06-18 08:52:12', 'canceled'),
(8, 5251.50, '2024-08-17 18:50:23', 'active'),
(2, 563.25, '2024-06-19 15:52:55', 'active'),
(2, 1950.25, '2024-06-20 09:31:56', 'active'),
(9, 5555.55, '2023-01-02 10:10:05', 'completed'),
(10, 849.00, '2023-09-13 20:24:12', 'completed'),
(11, 154.99, '2023-10-06 15:45:05', 'completed'),
(11, 9999.99, '2024-11-14 10:00:23', 'active');


// 1 Подсчитайте общее количество заказов, включая только завершенные.

select status, count(*) from orders group by status having status = 'completed';

// 2 Подсчитайте количество завершенных и отмененных заказов для каждого
клиента.

select users.user_id, name, status, count(*) from users join orders on users.user_id = orders.user_id group by users.user_id, name, status having status in ('completed', 'canceled');

// 3 Определите среднюю стоимость всех завершенных заказов за последние 6
месяцев.

select round(avg(amount), 2) as average_amount from orders where order_date < now() - interval '6 month' and status = 'completed';

// 4  Определите среднюю стоимость завершенных заказов для каждого
пользователя, у которого сумма всех заказов превышает 500.

select users.user_id, name, round(avg(amount), 2) as average from users join orders on users.user_id = orders.user_id group by name, users.user_id having sum(amount) > 500;

// 5 Рассчитайте суммарную стоимость заказов для каждого клиента, разбив
заказы по статусу (завершен, в процессе, отменен).

select users.user_id, name, status, sum(amount) from users join orders on users.user_id = orders.user_id group by users.user_id, name, status order by users.user_id asc;

// 6 Выведите максимальную и минимальную суммы завершенных заказов
каждого клиента.

select name, max(amount) as maximum_amount, min(amount) as minimum_amount from users join orders on users.user_id = orders.user_id group by name, status having status = 'completed';

// 7 Выведите количество заказов для каждого года и месяца, включая разбивку
по статусу.

select extract(year from order_date) as year, extract (month from order_date) as month, status, count(*) as order_count from orders group by extract(year from order_date), extract(month from order_date), status order by year, month, status;

// 8 Определите клиентов, у которых хотя бы один заказ был отменен, и
выведите дату самого раннего отмененного заказа.

select users.user_id, name, min(order_date) min_order_date from users join orders on users.user_id = orders.user_id group by users.user_id, status, order_date having status = 'canceled';

// 9 Найдите клиентов, у которых сумма любого отдельного заказа превышает
среднюю стоимость всех заказов по системе.

select users.user_id, name, min(amount) as min_amount from users join orders on users.user_id = orders.user_id group by users.user_id, name having min(amount) > (select avg(amount) from orders);

// 10 Покажите клиентов, которые сделали заказы в каждом месяце текущего
года, с указанием количества заказов в каждом месяце.

WITH monthly_orders AS ( SELECT u.user_id, u.name, EXTRACT(MONTH FROM o.order_date) AS month, COUNT(o.order_id) AS order_count FROM users u JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.order_date) = EXTRACT(YEAR FROM CURRENT_DATE) GROUP BY u.user_id, u.name, EXTRACT(MONTH FROM o.order_date) ), user_months AS ( SELECT user_id, name, COUNT(DISTINCT month) AS months_ordered FROM monthly_orders GROUP BY user_id, name HAVING COUNT(DISTINCT month) = 12 ) SELECT um.name, mo.month, mo.order_count FROM user_months um JOIN monthly_orders mo ON um.user_id = mo.user_id ORDER BY um.name, mo.month;

```